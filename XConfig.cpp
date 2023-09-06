#include "XConfig.h"

XConfig::XConfig(const char *filename)
{
  if (path != NULL)
  {
    delete path;
  }

  int len = strlen(filename);
  path = new char[len]();
  strcpy(path, filename);
}

XConfig::~XConfig()
{
    delete path;
}

void XConfig::GetVal(char** value, const char *section, const char *var)
{
  FILE* fp = fopen(path, "r");
  if (fp == NULL)
  {
    value = NULL;
    return;
  }

  char* line = NULL;
  char *cleanLine = NULL;
  size_t len = 0;
  bool inSection = false;
  bool found = false;
  char* sect = NULL;
  int sectLen  = 0;
  char* key = NULL;
  int keyLen = 0;
  char* buf = NULL;

  // Bracket-wrap the section name
  sect = new char[strlen(section) + 2]();
  strcpy(sect + 1, section);
  sect[0] = '[';
  sect[strlen(sect)] = ']';

  // Add = to end of key value
  key = new char[strlen(var) + 1]();
  strcpy(key, var);
  key[strlen(key)] = '=';

  sectLen = strlen(sect);
  keyLen = strlen(key);

  while ((getline(&line, &len, fp)) != -1 && !found)
  {
    // Sanitize the line that was read in (remove all non-printable characters)
    cleanLine = new char[strlen(line)]();
    int j = 0;
    for (int i = 0; i < (int)strlen(line); i++)
    {
      if ((unsigned char)line[i] > 31 && (unsigned char)line[i] < 127)
      {
        cleanLine[j] = line[i];
        j++;
      }
    }

    if(cleanLine[0] == '[')
    {
      // See if we're in the right section
      buf = new char[sectLen]();
      strncpy(buf, cleanLine, sectLen);

      inSection = (strcmp(sect, buf) == 0);

      delete buf;
    }
    else if (inSection)
    {
      // See if we have the right key
      buf = new char[keyLen]();
      strncpy(buf, cleanLine, keyLen);

      if(strcmp(key, buf) == 0)
      {
        delete buf;
        // Found a match, copy the value and bail out of loop
        buf = new char[strlen(cleanLine) - keyLen]();
        strncpy(buf, cleanLine + keyLen, strlen(cleanLine) - keyLen);
        *value = strdup(buf);
        found = true;
      }
      else
      {
        delete buf;
      }
    }

    delete cleanLine;
  }

  fclose(fp);

  delete sect;
  delete key;
  delete buf;
  delete line;
}

void XConfig::GetInt(int &value, const char *section, const char *var, int def)
{
  char *buf = NULL;

  value = def;

  this->GetVal(&buf, section, var);

  if (buf != NULL)
  {
    value = atoi(buf);
    printf("Found %i\r\n", value);
  }
}

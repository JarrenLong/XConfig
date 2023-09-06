#include <cstdio>
#include "XConfig.h"

int main(int argc, char** argv)
{
  int xc,yc,xw,yw;

  XConfig cfg("./XConfig.ini");
  cfg.GetInt(xc, "Application","WinXCoord",-1);
  cfg.GetInt(yc, "Application","WinYCoord",-1);
  cfg.GetInt(xw, "Application","WinXWidth",-1);
  cfg.GetInt(yw, "Application","WinYWidth",-1);

  printf("(%i, %i, %i, %i)\r\n", xc, yc, xw, yw);

  return 0;
}

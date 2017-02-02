#include "Timer.hpp"

#include <time.h>
#include <windows.h>
#include <winbase.h>
#include <math.h>

void sleep(int ms)
{
  Sleep(ms);
}

double currentTime()
{
  double dTime = GetTickCount() / 1000.0;
  
  return (dTime);
}

#include "STrace.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class STrace {
public:
  void write(byte level, String message);
  void debug(String message);
  void info(String message);
  void important(String message);
  void warning(String message);
  void error(String message);
};


void STrace::write(byte level, String message)
{
}

void STrace::debug(String message)
{
	STrace::write(STRACE_DEBUG, message);
}

void STrace::info(String message)
{
	STrace::write(STRACE_INFO, message);
}

void STrace::important(String message)
{
	STrace::write(STRACE_IMPORTANT, message);
}

void STrace::warning(String message)
{
	STrace::write(STRACE_WARNING, message);
}

void STrace::error(String message)
{
	STrace::write(STRACE_ERROR, message);
}

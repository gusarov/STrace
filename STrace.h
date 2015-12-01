#ifndef STrace_h
#define STrace_h

#define STRACE_VERBOSE 0x05
#define STRACE_DEBUG 0x10
#define STRACE_INFO 0x20
#define STRACE_IMPORTANT 0x30
#define STRACE_WARNING 0x40
#define STRACE_ERROR 0x50

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <stdarg.h>

//void p(char* fmt, ... );
//int lenDigs(int value);

void write2(byte level, String code, String message);

void logV(String code, String message);
void logD(String code, String message);
void logI(String code, String message);
void logP(String code, String message);
void logW(String code, String message);
void logE(String code, String message);

class STrace {
public:
  STrace(String tag);
  void v(String message);
  void d(String message);
  void i(String message);
  void p(String message);
  void w(String message);
  void e(String message);
  
private:
  void write(byte level, String message);
  String _tag;
};


#endif

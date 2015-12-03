#ifndef STrace_h
#define STrace_h

#define STRACE_VERBOSE 0x05
#define STRACE_DEBUG 0x10
#define STRACE_INFO 0x20
#define STRACE_INFORMATION 0x20
#define STRACE_IMPORTANT 0x30
#define STRACE_WARN 0x40
#define STRACE_WARNING 0x40
#define STRACE_ERROR 0x50
#define STRACE_FATAL 0x60

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif


/*
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdarg.h>
*/

// void p(char* fmt, ... );
// int lenDigs(int value);
// void STraceWrite(byte level, char* code, char* message);

class STrace {
public:
  STrace(char* tag);
  
  void write(byte level, char* message);
  void writef(byte level, char* message, ...);
  void writev(byte level, char* message, va_list args);

  void verbose(char* message, ...);
  void debug(char* message, ...);
  void info(char* message, ...);
  void important(char* message, ...);
  void warning(char* message, ...);
  void error(char* message, ...);
  void fatal(char* message, ...);
  
private:
  char* _tag;
};

class STraceLog {
public:
  void write(byte level, char* tag, char* message);
  void writef(byte level, char* tag, char* message, ...);
  void writev(byte level, char* tag, char* message, va_list args);
  
  void v(char* tag, char* message, ...);
  void d(char* tag, char* message, ...);
  void i(char* tag, char* message, ...);
  void p(char* tag, char* message, ...);
  void w(char* tag, char* message, ...);
  void e(char* tag, char* message, ...);
  void f(char* tag, char* message, ...);
  
  // COMMON CORE DATA AND METHODS
  int level = 0;
  
  // 0 means that there is no error tracking
  // 1 means that led is turned on constantly after error
  // 2 means that led is blinked synchronously 2 times with a 1 sec total delay
  // 3 means that blinking maintained while calling other logging methods, or separate routine 'handleBackground' should be called when appropriate (like at the end of each loop)
  int errorLedMode = 0;
  int errorLedPin = 13;
  
  void handleBackground();

  int debugLedPin = 13;
  void blink5V(float voltage);
  void blink12V(float voltage);
  void blinkNumber(int num); // quick blink some number
  void blinkDigit(byte dig); // quick blink some digit
  void blinkRatio(float dig, int pulses); // quick blink some ratio 0..1
};

extern STraceLog Log;

#endif

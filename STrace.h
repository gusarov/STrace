#ifndef STrace_h
#define STrace_h

#define STRACE_DEBUG 0x10
#define STRACE_INFO 0x20
#define STRACE_IMPORTANT 0x30
#define STRACE_WARNING 0x40
#define STRACE_ERROR 0x50

class STrace {
public:
  void write(byte level, String message);
  void debug(String message);
  void info(String message);
  void important(String message);
  void warning(String message);
  void error(String message);
};

#endif

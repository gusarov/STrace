#include <STrace.h>

STrace log1 = STrace("log1");
STrace log2 = STrace("log2");

void setup() {
  Log.level = STRACE_INFO;
  Log.errorLedMode = 0;
  
  Serial.begin(115200);
  
  Log.v("M_TAG", "Initializing...");

  delay(1500);
  
  Android_style();
  Apache_Log4J_Log4Net_CommonLogging_Style();
  Formatting();
  OldLoggingLibrary();
}

void Android_style_write(int q, ...) {
  Log.write(STRACE_INFO, "M_TAG", "Android write");
  Log.writef(STRACE_INFO, "M_TAG", "Android writef=%d", q);
  
  va_list args;
  va_start(args, q);
  Log.writev(STRACE_INFO, "M_TAG", "Android %s writev=%d", args);
}

void Android_style() {
  Log.v("M_TAG", "Android Verbose");
  Log.d("M_TAG", "Android Debug");
  Log.i("M_TAG", "Android Information");
  Log.p("M_TAG", "Android Improtant");
  Log.w("M_TAG", "Android Warning");
  Log.e("M_TAG", "Android Error");
  Log.f("M_TAG", "Android Fatal");
  Android_style_write(1, "a", 4);
}

void Apache_Log4J_Log4Net_CommonLogging_Style_write(int q, ...) {
  log1.write(STRACE_INFO, "Android write");
  log1.writef(STRACE_INFO, "Android writef=%d", q);
  
  va_list args;
  va_start(args, q);
  log1.writev(STRACE_INFO, "Android %s writev=%d", args);
}

void Apache_Log4J_Log4Net_CommonLogging_Style() {
  log1.verbose("Common Verbose");
  log1.debug("Common Debug");
  log1.info("Common Information");
  log2.important("Common Improtant");
  log2.warning("Common Warning");
  log2.error("Common Error");
  log2.fatal("Common Fatal");
  Apache_Log4J_Log4Net_CommonLogging_Style_write(1, "a", 4);
}

void Formatting() {
  Log.v("M_TAG", "Format String=%s Verbose %3d", "test", 5);
  Log.v("M_TAG", "Format String=%s Verbose %3d", "test", 25);
  Log.v("M_TAG", "Format String=Asd Verbose Asd");

  log1.verbose("Format String=%s Verbose %d", "test", 5);
  log1.debug("Format String=%s Debug %d", "test", 5);
  log1.info("Format String=%s Information %d", "test", 5.5);
  log1.important("Format String=%s Improtant %d", "test", 5);
  log1.warning("Format String=%s Warning %d", "test", 5);
  log1.error("Format String=%s Error %d", "test", 5);
  log1.fatal("Format String=%s Fatal %d ", "test", 5);

  Log.v("M_TAG", "Format String=%s Verbose %d", "test", 5);
  Log.d("M_TAG", "Format String=%s Debug %d", "test", 5);
  Log.i("M_TAG", "Format String=%s Information %d", "test", 5.5);
  Log.p("M_TAG", "Format String=%s Improtant %d", "test", 5);
  Log.w("M_TAG", "Format String=%s Warning %d", "test", 5);
  Log.e("M_TAG", "Format String=%s Error %d", "test", 5);
  Log.f("M_TAG", "Format String=%s Fatal %d ", "test", 5);
}

int myInt1, myInt2;
long myLong1, myLong2;
bool myBool1, myBool2;
char* myString = "this is a string";

void OldLoggingLibrary() {
    myInt1 = 232;
    myInt2 = 32199;
    myLong1 = 99403020;
    myLong2 = 45021;
    myBool1 = true;
    myBool2 = !myBool1;

    log1.info("Display my integers myInt1 %d, myInt2 %d", myInt1, myInt2);
    log1.info("Display as hex myInt1=%x, myInt1=%X", myInt1, myInt1);
    log1.info("Display as hex myInt2=%x, myInt2=%X", myInt2, myInt2);
    log1.info("Display as binary myInt1=%b, myInt1=%B", myInt1, myInt1);
    log1.info("Display as binary myInt2=%b, myInt2=%B", myInt2, myInt2);
    log1.info("Display my longs myLong1 %l, myLong2=%l", myLong1, myLong2);
    log1.info("Display my bool myBool1=%t, myBool2=%T", myBool1, myBool2);
    log1.info("Output: %s", myString);
    log1.error("is this an real error? %T", myBool2);
    log1.debug("%d, %d, %l, %l, %t, %T", myInt1, myInt2,
              myLong1, myLong2,
              myBool1, myBool2);
    log1.info("have fun with this Log");
}

void loop() {
  delay(5000);
  Log.blinkNumber(0.25 * 10);
  delay(5000);
  Log.blinkNumber(0.50 * 10);
  delay(5000);
  Log.blinkNumber(0.75 * 10);
}

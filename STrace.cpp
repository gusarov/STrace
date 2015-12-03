#include "STrace.h"

/*
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
*/

int lenDigsQuick(int value){
	if (value >= 1000) return 4;
	if (value >= 100) return 3;
	if (value >= 10) return 2;
	return 1;
}

int lenDigs(int value){
	int l = 0;

	do {
		l++;
		value /= 10;
	} while (value > 0);
	
	return l;
}

void printPadding(int value, int padding){
	int l = lenDigsQuick(value);
	for (int i = l; i < padding; i++) {
		Serial.print(' ');
	}
	Serial.print(value);
}

char getLevel(byte level) {
	switch (level) {
		case STRACE_VERBOSE:
			return 'V';
		case STRACE_DEBUG:
			return 'D';
		case STRACE_INFORMATION:
			return 'I';
		case STRACE_IMPORTANT:
			return 'P';
		case STRACE_WARNING:
			return 'W';
		case STRACE_ERROR:
			return 'E';
		case STRACE_FATAL:
			return 'F';
		default:
			return '_';
	}
}

inline bool enabled(byte level)
{
	return level >= Log.level;
}

bool error = 0;
int errorLedSetAt = -1;
int errorLedState = 0;

void handleError()
{
	error = 1;
	switch (Log.errorLedMode) {
		case 0:
			break;
		case 1:
			pinMode(Log.errorLedPin, OUTPUT);
			digitalWrite(Log.errorLedPin, 1);
			break;
		case 2:
			pinMode(Log.errorLedPin, OUTPUT);
			digitalWrite(Log.errorLedPin, 1);
			delay(250);
			digitalWrite(Log.errorLedPin, 0);
			delay(250);
			digitalWrite(Log.errorLedPin, 1);
			delay(250);
			digitalWrite(Log.errorLedPin, 0);
			delay(250);
			break;
		case 3:
			pinMode(Log.errorLedPin, OUTPUT);
			digitalWrite(Log.errorLedPin, 1);
			errorLedState = 1;
			errorLedSetAt = millis();
			break;
	}
}

void writeCore(byte level, char* tag, char* message)
{
	if (level >= STRACE_ERROR) {
		handleError();
	}
	if (error) {
		Log.handleBackground(); // we have some job to do
	}
	if (enabled(level)) {
		printPadding(millis() / 1000, 3);
		Serial.print(": ");
		Serial.print(getLevel(level));
		Serial.print('/');
		Serial.print(tag);
		Serial.print(": ");
		Serial.println(message);
	}
}

char buffer[256];

void writeCore(byte level, char* tag, char* message, va_list args)
{
	if (enabled(level)) {
		vsprintf(buffer, message, args);
		writeCore(level, tag, buffer);
		va_end(args);
	}
}

STrace::STrace(char* tag)
{
	_tag = tag;
}

void STrace::write(byte level, char* message)
{
	writeCore(level, _tag, message);
}

void STrace::writef(byte level, char* message, ...)
{
	va_list args;
	va_start(args, message);
	writeCore(level, _tag, message, args);
}

void STrace::writev(byte level, char* message, va_list args)
{
	writeCore(level, _tag, message, args);
}

void STrace::verbose(char* message, ...)
{
	va_list args;
	va_start(args, message);
	writev(STRACE_VERBOSE, message, args);
}

void STrace::debug(char* message, ...)
{
	va_list args;
	va_start(args, message);
	writev(STRACE_DEBUG, message, args);
}

void STrace::info(char* message, ...)
{
	va_list args;
	va_start(args, message);
	writev(STRACE_INFORMATION, message, args);
}

void STrace::important(char* message, ...)
{
	va_list args;
	va_start(args, message);
	writev(STRACE_IMPORTANT, message, args);
}

void STrace::warning(char* message, ...)
{
	va_list args;
	va_start(args, message);
	writev(STRACE_WARNING, message, args);
}

void STrace::error(char* message, ...)
{
	va_list args;
	va_start(args, message);
	writev(STRACE_ERROR, message, args);
}

void STrace::fatal(char* message, ...)
{
	va_list args;
	va_start(args, message);
	writev(STRACE_FATAL, message, args);
}




void STraceLog::write(byte level, char* tag, char* message)
{
	writeCore(level, tag, message);
}
void STraceLog::writef(byte level, char* tag, char* message, ...)
{
	va_list args;
	va_start(args, message);
	writeCore(level, tag, message, args);
}
void STraceLog::writev(byte level, char* tag, char* message, va_list args)
{
	writeCore(level, tag, message, args);
}

void STraceLog::v(char* tag, char* message, ...)
{
	va_list args;
	va_start(args, message);
	writeCore(STRACE_VERBOSE, tag, message, args);
}
void STraceLog::d(char* tag, char* message, ...)
{
	va_list args;
	va_start(args, message);
	writeCore(STRACE_DEBUG, tag, message, args);
}
void STraceLog::i(char* tag, char* message, ...)
{
	va_list args;
	va_start(args, message);
	writeCore(STRACE_INFORMATION, tag, message, args);
}
void STraceLog::p(char* tag, char* message, ...)
{
	va_list args;
	va_start(args, message);
	writeCore(STRACE_IMPORTANT, tag, message, args);
}
void STraceLog::w(char* tag, char* message, ...)
{
	va_list args;
	va_start(args, message);
	writeCore(STRACE_WARNING, tag, message, args);
}
void STraceLog::e(char* tag, char* message, ...)
{
	va_list args;
	va_start(args, message);
	writeCore(STRACE_ERROR, tag, message, args);
}
void STraceLog::f(char* tag, char* message, ...)
{
	va_list args;
	va_start(args, message);
	writeCore(STRACE_FATAL, tag, message, args);
}
void STraceLog::handleBackground()
{
	if (error && Log.errorLedMode == 3) {
		int m = millis();
		if (m - errorLedSetAt > 250) {
			errorLedState = errorLedState==0?1:0;
			digitalWrite(Log.errorLedPin, errorLedState);
			errorLedSetAt = m;
		}
	}
}
void STraceLog::blink5V(float voltage)
{
	delay(500);
	blinkNumber(voltage * 10);
}
void STraceLog::blink12V(float voltage)
{
	delay(500);
	blinkNumber((voltage - 10) * 10);
}
void STraceLog::blinkNumber(int num)
{
	int rem = num;
	int d = rem % 10;
	rem /= 10;
	if (rem > 0) {
		blinkNumber(rem);
	}
	blinkDigit(d);
}
void STraceLog::blinkDigit(byte dig)
{
	delay(500);
	if (dig > 5) {
		dig -= 5;
		digitalWrite(Log.errorLedPin, 1);
		delay(500);
		digitalWrite(Log.errorLedPin, 0);
		delay(100);
	}
	for (int i = 0; i < dig; i++) {
		digitalWrite(Log.errorLedPin, 1);
		delay(200);
		digitalWrite(Log.errorLedPin, 0);
		delay(100);
	}
}
void STraceLog::blinkRatio(float ratio, int pulses)
{
	for (int i = 0; i < pulses; i++) {
		digitalWrite(Log.errorLedPin, 1);
		delay(1000 * ratio);
		digitalWrite(Log.errorLedPin, 0);
		delay(1000 * (1-ratio));
	}
}

STraceLog Log = STraceLog();
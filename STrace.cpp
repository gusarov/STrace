#include "STrace.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

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
	for(int i = l; i < padding; i++) {
		Serial.print(' ');
	}
	Serial.print(value);
}

char getLevel(byte level) {
	switch(level) {
		case STRACE_VERBOSE:
			return 'V';
		case STRACE_DEBUG:
			return 'D';
		case STRACE_INFO:
			return 'I';
		case STRACE_IMPORTANT:
			return 'M';
		case STRACE_WARNING:
			return 'W';
		case STRACE_ERROR:
			return 'E';
		case STRACE_FATAL:
			return 'F';
	}
}

void write2(byte level, char* tag, char* message)
{
	printPadding(millis() / 1000, 3);
	Serial.print(": ");
	Serial.print(getLevel(level));
	Serial.print('/');
	Serial.print(tag);
	Serial.print(": ");
	Serial.println(message);
}

STrace::STrace(char* tag)
{
	_tag = tag;
}

void STrace::write(byte level, char* message)
{
	write2(level, _tag, message);
}

void STrace::verbose(char* message)
{
	STrace::write(STRACE_VERBOSE, message);
}

void STrace::debug(char* message)
{
	STrace::write(STRACE_DEBUG, message);
}

void STrace::info(char* message)
{
	STrace::write(STRACE_INFO, message);
}

void STrace::important(char* message)
{
	STrace::write(STRACE_IMPORTANT, message);
}

void STrace::warning(char* message)
{
	STrace::write(STRACE_WARNING, message);
}

void STrace::error(char* message)
{
	STrace::write(STRACE_ERROR, message);
}

void STrace::fatal(char* message)
{
	STrace::write(STRACE_FATAL, message);
}

void STraceLog::v(char* tag, char* message, ...)
{
	write2(STRACE_VERBOSE, tag, message);
}
void STraceLog::d(char* tag, char* message)
{
	write2(STRACE_DEBUG, tag, message);
}
void STraceLog::i(char* tag, char* message)
{
	write2(STRACE_INFO, tag, message);
}
void STraceLog::p(char* tag, char* message)
{
	write2(STRACE_IMPORTANT, tag, message);
}
void STraceLog::w(char* tag, char* message)
{
	write2(STRACE_WARNING, tag, message);
}
void STraceLog::e(char* tag, char* message)
{
	write2(STRACE_ERROR, tag, message);
}
void STraceLog::f(char* tag, char* message)
{
	write2(STRACE_FATAL, tag, message);
}

 STraceLog Log = STraceLog();
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
	}
}

void write2(byte level, String tag, String message)
{
	printPadding(millis() / 1000, 3);
	Serial.print(": ");
	Serial.print(getLevel(level));
	Serial.print('/');
	Serial.print(tag);
	Serial.print(": ");
	Serial.println(message);
}

STrace::STrace(String tag)
{
	_tag = tag;
}

void STrace::write(byte level, String message)
{
	write2(level, _tag, message);
}

void STrace::v(String message)
{
	STrace::write(STRACE_VERBOSE, message);
}

void STrace::d(String message)
{
	STrace::write(STRACE_DEBUG, message);
}

void STrace::i(String message)
{
	STrace::write(STRACE_INFO, message);
}

void STrace::p(String message)
{
	STrace::write(STRACE_IMPORTANT, message);
}

void STrace::w(String message)
{
	STrace::write(STRACE_WARNING, message);
}

void STrace::e(String message)
{
	STrace::write(STRACE_ERROR, message);
}

void logV(String code, String message)
{
	write2(STRACE_VERBOSE, code, message);
}

void logD(String code, String message)
{
	write2(STRACE_DEBUG, code, message);
}

void logI(String code, String message)
{
	write2(STRACE_INFO, code, message);
}

void logP(String code, String message)
{
	write2(STRACE_IMPORTANT, code, message);
}

void logW(String code, String message)
{
	write2(STRACE_WARNING, code, message);
}

void logE(String code, String message)
{
	write2(STRACE_ERROR, code, message);
}

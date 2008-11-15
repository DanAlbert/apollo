////////////////////////////////////////////////////////////////////////////////
// Filename: Debug.cpp
// Author:   Dan Albert
// Date:     November 25, 2007

#include "debug.h"

const char LOG_FILE[] = "apollo.log";

// MessageBox() wrappers
inline void ErrorMessage(const char* szText)
{
	MessageBox(NULL, szText, "Error!", MB_OK);
}

inline void ErrorQuit(const char* szText, int iErrNo)
{
	MessageBox(NULL, szText, "Error!", MB_OK);
	Log("%s %02X", szText, iErrNo);
}

inline void Log(const char* szFormat, ...)
{
	if (!szFormat)
	{
		return;
	}

	const time_t t = time(NULL);
	tm* c = localtime(&t);
	
	FILE* fp = NULL;
	if ((fp = fopen(LOG_FILE, "a")) == NULL)
	{
		return;
	}

	// Begin by prepending time to log file
	fprintf(
		fp,
		"|%02d-%02d-%04d  %02d:%02d:%02d| ",
		(c->tm_mon + 1),
		c->tm_mday,
		(c->tm_year + 1900),
		c->tm_hour,
		c->tm_min,
		c->tm_sec);

	// Begin va list 
	va_list args;
	va_start(args, szFormat);
	
	// Print formatted log message to log file
	vfprintf(fp, szFormat, args);
	putc('\n', fp);

	// Print formatted log message to stdout
	vprintf(szFormat, args);
	putchar('\n');

	va_end(args);
	fclose(fp);
}

inline void LogNoTime(const char* szFormat, ...)
{
	if (!szFormat)
	{
		return;
	}
	
	FILE* fp = NULL;
	if ((fp = fopen(LOG_FILE, "a")) == NULL)
	{
		return;
	}

	// Begin va list 
	va_list args;
	va_start(args, szFormat);
	
	// Print formatted log message to log file
	vfprintf(fp, szFormat, args);
	putc('\n', fp);

	// Print formatted log message to stdout
	vprintf(szFormat, args);
	putchar('\n');

	va_end(args);
	fclose(fp);
}

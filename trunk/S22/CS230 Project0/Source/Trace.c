//------------------------------------------------------------------------------
//
// File Name:	Trace.c
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 0
// Course:		CS230S22
//
// Copyright © 2022 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <stdarg.h>
#include <stdio.h>

#include "AEEngine.h"
#include "Trace.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

static const char* traceFileName = "Trace.log";

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

// TODO: Declare a private variable for storing a file handle.
static FILE* fp;
static errno_t err;


//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the Tracing/Logging module.
// - Open "trace.log" for writing in text mode.
// - Perform error handling in the event that the file failed to open.
void TraceInit()
{
	// TODO: Open "trace.log" for writing (text mode).
	err = fopen_s(&fp, traceFileName, "wt");

	if (err == 0)
	{
		AESysPrintf("The file was opened. \n");
	}
	else
	{
		AESysPrintf("\n");
		AESysPrintf("The file was not opened. \n");
		AESysPrintf("We hit a null pointer. \n");
		AESysPrintf("------------------------------------------------------- \n");
		AESysPrintf("\n");
	}
}

// Output a message to the Tracing/Logging file.
// - Print the given message to the file if it was opened successfully.
// - Every message must be printed on its own line.
// - There must be no blank lines between messages.
void TraceMessage(const char * formatString, ...)
{
	UNREFERENCED_PARAMETER(formatString);
	if (fp)
	{
		// TODO: Write the message to the Tracing/Logging file.
		va_list args;
		va_start(args, formatString);
		vfprintf(fp, formatString, args);
		vfprintf(fp, "\n", args);
		va_end(args);
	}
	else
	{
		AESysPrintf(formatString);
		AESysPrintf("\n");
	}
}

// Shutdown the Tracing/Logging module.
// - Close the file if-and-only-if the file was opened successfully
void TraceShutdown()
{
	// TODO: Close "trace.log" if it has been opened successfully.
	if (fp)
	{
		err = fclose(fp);
		if (err == 0)
		{
			AESysPrintf("The file was closed. \n");
		}
		else
		{
			AESysPrintf("The file was not closed. \n");
		}
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------


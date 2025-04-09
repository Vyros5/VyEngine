#pragma once

#include <string>
#include <cstring>

#include <iostream>
#include <fstream>

#include <cstdarg>
#include <cstdlib>

#include <WinUser.h>


void VyLogError(const char* pFileName, unsigned int line, const char* pFormat, ...);
void VyLogFileError(const char* pFileName, unsigned int line, const char* pFileError);

#define VY_LOG_INFO(format) VyLogError(__FILE__, __LINE__, format)
#define VY_LOG_ERROR(format, ...) VyLogError(__FILE__, __LINE__, format, __VA_ARGS__)
#define VY_LOG_FILE_ERROR(FileError) VyLogFileError(__FILE__, __LINE__, FileError)
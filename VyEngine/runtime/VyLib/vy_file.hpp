#pragma once

#include <vector>
#include <memory>

#include <string>
#include <cstring>

#include <iostream>
#include <fstream>

#include <cassert>

bool ReadFile(const char* pFileName, std::string& outFile);
char* ReadBinaryFile(const char* pFilename, int& size);
void WriteBinaryFile(const char* pFilename, const void* pData, int size);
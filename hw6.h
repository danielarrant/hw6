#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>
#include "cdk.h"

using namespace std;
const int maxRecordStringLength = 25;

class BinaryFileHeader
{
 public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

class BinaryFileRecord
{
 public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
}; 

bool aGreaterThanB (int, int);

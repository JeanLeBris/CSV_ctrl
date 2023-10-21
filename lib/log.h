#include "../lib/table.h"

#ifndef __LOG__

#define __LOG__

void LogString(char *fileName, char *string);
void LogTable(char *fileName, tableType table);
void LogData(char *fileName, char data[25][25]);

#endif
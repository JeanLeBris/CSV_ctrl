#include "../lib/table.h"
#include "../lib/command.h"

#ifndef __LOG__

#define __LOG__

void LogList(char *fileName, command commandList);

void LogString(char *fileName, char *string);
void LogTable(char *fileName, tableType table, char outputModeVar);
void LogData(char *fileName, char data[25][25]);

#endif
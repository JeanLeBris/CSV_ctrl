#ifndef __DECLARATIONS__

#define __DECLARATIONS__

typedef struct tableCellType{
	char value[100];
	int lenght;

	struct tableCellType *back;
	struct tableCellType *next;
}tableCellType;

typedef struct tableLineType{
	int lenght;

	struct tableCellType *begin;
	struct tableCellType *end;

	struct tableLineType *back;
	struct tableLineType *next;
}*tableLineType;

typedef struct tableType{
	int lenght;
	int *cellWidth;
	int width;
	char name[25];

	struct tableLineType *begin;
	struct tableLineType *end;
}*tableType;

// Creation

tableLineType NewTableLine();
tableType NewTable();

tableType CreateFileData(char *fileName);

// IsNull

int IsNullTableLine(tableLineType tableLine);
int IsNullTable(tableType table);

// IsEmpty

int IsEmptyTableLine(tableLineType tableLine);
int IsEmptyTable(tableType table);

// Push

tableLineType PushBackTableLine(tableLineType tableLine, char *value);
tableLineType PushBackTableLineBis(tableLineType tableLine, char *value);
tableType PushBackTable(tableType table, tableLineType* tableLine);

// Pull

//tableCellType* PullFrontTableLine(tableLineType tableLine);
//tableLineType PullFrontTable(tableType table);

// Clear

void ClearTableCell(tableCellType *tableCell);
tableLineType ClearTableLine(tableLineType tableLine);
tableType ClearTable(tableType table);

// Information

void GetTableLenght(tableType table);
tableCellType* GetCellValue(tableType table, int line, int column);
tableCellType* CopyCell(tableCellType* cell);
tableLineType CreateTableLine(tableType table, int line, int* orderColumns, int nbColumns);
tableType GetTable(tableType tables, char tableName[25][25]);
tableType GetAssortedTable(tableType table, char tableArguments[25][25]);
int GetLineLenght(tableType table, int line);
void GetTableWidth(tableType table);
void GetTableCellWidth(tableType table);

// Print

void PrintTable(tableType table);
void ToPrint(char action[25], char tableName[25][25], char tableArguments[25][25], tableType table);
void PrintError();
void PrintHelp();
void PrintStart();




tableType GetFileData(tableType table, char *fileName);
tableType CreateFileTable(tableType table, char tableName[25][25]);
void SetFileData(tableType table, char *fileName);
tableType CreateFileTableColumn(tableType tableBuffer, char tableArguments[25][25]);
tableType CreateFileTableLine(tableType tableBuffer, char tableArguments[25][25], char tableValues[25][25], int tableSize);
tableType SetTable(tableType tables, tableType tableBuffer);

#endif
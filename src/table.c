#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../lib/table.h"

#define GRAPHIC_MODE_BIT (1<<0)
#define CSV_SEMICOLON_MODE_BIT (1<<1)
#define CSV_COMMA_MODE_BIT (1<<2)
#define XML_MODE_BIT (1<<3)

#define FILE_ACCESS "./"

// Creation : Return NULL

tableLineType NewTableLine(){
	return NULL;
}
tableType NewTable(){
	return NULL;
}

tableType CreateFileData(char *fileName){
	/*
	char srcFileName[100] = "\0";
	char commandPrompt[100] = "\0";
	strcat(strcat(srcFileName, FILE_ACCESS), fileName);
	strcat(strcat(commandPrompt, "touch "), srcFileName);
	system(commandPrompt);
	//system("ls");

    return NULL;
	*/
	char srcFileName[100] = "\0";
	strcat(strcat(srcFileName, FILE_ACCESS), fileName);
	FILE *file_var = fopen(srcFileName, "wx");
	if(file_var == NULL){
		printf("File \"%s\" already exists\n", fileName);
		return NULL;
	}
	printf("Create file \"%s\"\n", fileName);
	fclose(file_var);
	return NULL;
}

/*
	IsNull : Return True if parameter point to NULL
	                 False if parameter do not point to NULL
*/

int IsNullTableLine(tableLineType tableLine){
	if(tableLine == NULL)
		return 1;
	else
		return 0;
}
int IsNullTable(tableType table){
	if(table == NULL)
		return 1;
	else
		return 0;
}

/*
	IsEmpty : Return True if parameter's lenght is 0
	                 False if parameter's lenght is not 0
*/

int IsEmptyTableLine(tableLineType tableLine){
	if(tableLine->lenght == 0)
		return 1;
	else
		return 0;
}
int IsEmptyTable(tableType table){
	if(table->lenght == 0)
		return 1;
	else
		return 0;
}

// Push

tableLineType PushBackTableLine(tableLineType tableLine, char *line, char sep){
	int i = 0;
	int j = 0;
	tableCellType *node = NULL;

	while(line[i] != '\0'){
		node = malloc(sizeof(tableCellType));

		node->back = NULL;
		node->next = NULL;
		node->lenght = 0;
		j = 0;
		
		while(line[i] != sep && line[i] != '\n' && line[i] != '\0'){
			if(line[i] < 32);
			else{
				node->value[j] = line[i];
				node->lenght++;
				j++;
			}
			i++;
		}

		node->value[j] = '\0';
		if(line[i] != '\0'){
			i++;
		}

		if(IsNullTableLine(tableLine)){
			tableLine = malloc(sizeof(*tableLine));

			tableLine->lenght = 0;
			tableLine->begin = node;
			tableLine->end = node;
			tableLine->back = NULL;
			tableLine->next = NULL;
		}
		else if(IsEmptyTableLine(tableLine)){
			tableLine->lenght = 0;
			tableLine->begin = node;
			tableLine->end = node;
			tableLine->back = NULL;
			tableLine->next = NULL;
		}
		else{
			tableLine->end->next = node;
			node->back = tableLine->end;
			tableLine->end = node;
		}

		tableLine->lenght++;
	}

	return tableLine;
}
tableLineType PushBackTableLineCleaned(tableLineType tableLine, char *line, char sep){
	tableCellType *node = NULL;

	tableLine = PushBackTableLine(tableLine, line, sep);

	while(tableLine != NULL && tableLine->end->lenght == 0 /*|| tableLine->end->lenght == 1*/ && tableLine->lenght > 1){
		node = tableLine->end;
		tableLine->end = tableLine->end->back;
		tableLine->end->next = NULL;
		tableLine->lenght--;
		ClearTableCell(node);
	}
	if(tableLine != NULL && tableLine->end->lenght == 0 && tableLine->lenght == 1){
		ClearTableCell(tableLine->begin);
		tableLine->begin = NULL;
		tableLine->end = NULL;
		tableLine->lenght --;
		ClearTableLine(tableLine);
		tableLine = NULL;
	}

	return tableLine;
}
tableType PushBackTable(tableType table, tableLineType tableLine){
	if(IsNullTable(table)){
		table = malloc(sizeof(*table));

		table->begin = tableLine;
		table->end = tableLine;
		table->lenght = 0;
		table->width = 0;
		table->cellWidth = NULL;
	}
	else if(IsEmptyTable(table)){
		table->begin = tableLine;
		table->end = tableLine;
		table->lenght = 0;
		table->width = 0;
		table->cellWidth = NULL;
	}
	else if(tableLine != NULL){
		table->end->next = tableLine;
		tableLine->back = table->end;
		table->end = tableLine;
	}

	if(tableLine != NULL){
		table->lenght++;
	}

	return table;
}

// Pull

//tableCellType* PullFrontTableLine(tableLineType tableLine);
//tableLineType PullFrontTable(tableType table);

// Clear

void ClearTableCell(tableCellType *tableCell){
	free(tableCell);
}
tableLineType ClearTableLine(tableLineType tableLine){
	tableCellType *buffer = NULL;
	if(tableLine == NULL)
		return NULL;
	else{
		tableLine->begin = NULL;
		while(tableLine->end != NULL){
			buffer = tableLine->end;
			tableLine->end = tableLine->end->back;
			tableLine->lenght--;
			ClearTableCell(buffer);
		}
		free(tableLine);
		return NULL;
	}
}
tableType ClearTable(tableType table){
	tableLineType buffer = NULL;
	if(table == NULL){
		return NULL;
	}
	else{
		table->begin = NULL;
		while(table->end != NULL){
			buffer = table->end;
			table->end = table->end->back;
			table->lenght--;
			buffer = ClearTableLine(buffer);
		}
		free(table);
		return NULL;
	}
}

// Information

void GetTableLenght(tableType table){
	tableLineType tableLine = table->begin;
	int i = 1;
	if(tableLine == NULL){
		table->lenght = 0;
	}
	else{
		while(tableLine != table->end){
			tableLine = tableLine->next;
			i++;
		}
		table->lenght = i;
	}
}
tableCellType* GetCellValue(tableType table, int line, int column){
	tableLineType tableLine = table->begin;
	tableCellType *tableCell = NULL;
	if(line >= table->lenght)
		return NULL;
	else{
		for(int i = 0; i < line; i++){
			tableLine = tableLine->next;
		}
		tableCell = tableLine->begin;
		if(column >= tableLine->lenght)
			return NULL;
		else{
			for(int i = 0; i < column; i++){
				tableCell = tableCell->next;
			}
			return tableCell;
		}
	}
}
tableCellType* CopyCell(tableCellType* cell){
	tableCellType *tableCell = malloc(sizeof(tableCellType));
	if(cell != NULL){
		strcpy(tableCell->value, cell->value);
		tableCell->lenght = cell->lenght;
	}
	else{
		strcpy(tableCell->value, "");
		tableCell->lenght = 0;
	}
	tableCell->back = NULL;
	tableCell->next = NULL;

	return tableCell;
}
tableLineType CreateTableLine(tableType table, int line, int* orderColumns, int nbColumns){
	tableLineType tableLine;
	tableLine = malloc(sizeof(*tableLine));

	tableLine->back = NULL;
	tableLine->next = NULL;
	tableLine->begin = NULL;
	tableLine->end = NULL;
	tableLine->lenght = 0;

	for(int i = 0; i < nbColumns; i++){
		if(tableLine->lenght == 0){
			tableLine->begin = CopyCell(GetCellValue(table, line, orderColumns[i]));
			tableLine->end = tableLine->begin;
			tableLine->lenght = 1;
		}
		else{
			tableLine->end->next = CopyCell(GetCellValue(table, line, orderColumns[i]));
			tableLine->end->next->back = tableLine->end;
			tableLine->end = tableLine->end->next;
			tableLine->lenght++;
		}
	}

	return tableLine;
}
tableType GetTable(tableType tables, char tableName[25][25]){
	char tableNameBuffer[29];
	tableType tableBuffer;
	tableBuffer = malloc(sizeof(*tableBuffer));
	tableBuffer->cellWidth = NULL;
	tableLineType tableLine = tables->begin;

	strcpy(tableNameBuffer, "");										// Modify the name of the table to print, entered by the user, to get the its equivalent in the file to read
	strcat(strcat(strcat(tableNameBuffer, "__"), tableName[0]), "__");	//

	tableBuffer->lenght = 0;

	int i = 0;																			// Get the line of the file at which the chosen table starts, or, if there is no table as the one
	while(i < tables->lenght && strcmp(tableLine->begin->value, tableNameBuffer) != 0){	// chosen by the user, exit the function with a NULL value
		tableLine = tableLine->next;													//
		i++;																			//
	}																					//
	if(i == tables->lenght){															//
		free(tableBuffer);																//
		return NULL;																	//
	}																					//

	if(tableLine->next == NULL || (tableLine->next->begin->value[0] == '_' && tableLine->next->begin->value[1] == '_')){
		tableBuffer->begin = NULL;
		tableBuffer->end = NULL;

		if(tableLine->back == NULL && tableLine->next != NULL){
			tables->begin = tables->begin->next;
			tables->begin->back = NULL;
			tableLine = ClearTableLine(tableLine);
		}
		else if(tableLine->back != NULL && tableLine->next == NULL){
			tables->end = tables->end->back;
			tables->end->next = NULL;
			tableLine = ClearTableLine(tableLine);
		}
		else if(tableLine->back != NULL && tableLine->next != NULL){
			tableLine->back->next = tableLine->next;
			tableLine->next->back = tableLine->back;
			tableLine = ClearTableLine(tableLine);
		}
		else{
			tables->begin = NULL;
			tables->end = NULL;
			tableLine = ClearTableLine(tableLine);
		}
	}
	else{
		tableLine = tableLine->next;														//
		tableBuffer->begin = tableLine;														// Defines the limits of the table chosen by the user inside the file
		while(strstr(tableLine->begin->value, "__") == NULL && tableLine->next != NULL){	//
			tableLine = tableLine->next;													//
		}																					//
		if(strstr(tableLine->begin->value, "__") != NULL)															//
			tableLine = tableLine->back;													//
		tableBuffer->end = tableLine;														//

		tableLine = tableBuffer->begin->back;
		if(tableBuffer->begin->back->back == NULL && tableBuffer->end->next != NULL){
			tables->begin = tableBuffer->end->next;
			tableBuffer->end->next = NULL;
			tableBuffer->begin->back = NULL;
			tables->begin->back = NULL;
			tableLine = ClearTableLine(tableLine);
		}
		else if(tableBuffer->begin->back->back != NULL && tableBuffer->end->next == NULL){
			tables->end = tableBuffer->begin->back->back;
			tableBuffer->end->next = NULL;
			tableBuffer->begin->back = NULL;
			tables->end->next = NULL;
			tableLine = ClearTableLine(tableLine);
		}
		else if(tableBuffer->begin->back->back != NULL && tableBuffer->end->next != NULL){
			tableBuffer->begin->back->back->next = tableBuffer->end->next;
			tableBuffer->end->next->back = tableBuffer->begin->back->back;
			tableBuffer->begin->back = NULL;
			tableBuffer->end->next = NULL;
			tableLine = ClearTableLine(tableLine);
		}
		else{
			tableBuffer->begin->back = NULL;
			tables->begin = NULL;
			tables->end = NULL;
			tableLine = ClearTableLine(tableLine);
		}
	}

	/*
	tableBuffer->begin->back->next = tableBuffer->end->next;	// Separates the table chosen by the user from the rest of the file
	tableBuffer->end->next->back = tableBuffer->begin->back;	//
	tableBuffer->begin->back = NULL;							//
	tableBuffer->end->next = NULL;								//
	*/

	GetTableLenght(tables);				// Get the metadatas of the table chosen by the user
	GetTableWidth(tables);				//
	GetTableCellWidth(tables);			//

	GetTableLenght(tableBuffer);				// Get the metadatas of the table chosen by the user
	GetTableWidth(tableBuffer);					//
	GetTableCellWidth(tableBuffer);				//
	strcpy(tableBuffer->name, tableName[0]);	//

	return tableBuffer;
}
tableType GetAssortedTable(tableType tableBuffer, char tableColumns[25][25]){
	int nbArguments = 0;
	int nbColumns = 0;
	int iterator = 0;
	tableLineType tableLine;
	tableCellType *tableCell;

	if(tableBuffer == NULL){
		return NULL;
	}
	else if(tableBuffer->begin == NULL){
		return tableBuffer;
	}

	if(strcmp(tableColumns[0], "__ALLCOLUMNS__") == 0){			// Initialises nbArguments, allowing to know the numbers of columns to be printed
		nbArguments = 0;											//
	}																//
	else{															//
		while(strcmp(tableColumns[nbArguments], "__END__") != 0){	//
			nbArguments++;											//
		}															//
	}																//

	int *printColumn = malloc(sizeof(int) * nbArguments);	// Defines the table printColumn, allowing to know if a column is to be printed
	for(int i = 0; i < nbArguments; i++){					//
		printColumn[i] = -1;								//
	}														//
	
	if(nbArguments == 0){
		free(printColumn);

		return tableBuffer;
	}
	else{
	
		for(int i = 0; i < nbArguments; i++){															// Put in each cell of the printColumn table the corresponding number of the column to print
			tableLine = tableBuffer->begin;																// from the file
			tableCell = tableLine->begin;																//
			iterator = 0;																				// Initialises the table printColumn, allowing to know if a column is to be printed
			while(strcmp(tableColumns[i], tableCell->value) != 0 && iterator < tableBuffer->width){	//
				tableCell = tableCell->next;															//
				iterator++;																				//
			}																							//
			if(strcmp(tableColumns[i], tableCell->value) == 0){										//
				printColumn[i] = iterator;																//
			}																							//
		}																								//

		iterator = 0;											// Defines the table orderColumns, allowing to know in which order the columns are to be printed
		for(int i = 0; i < nbArguments; i++){					//
			if(printColumn[i] != -1){							//
				iterator++;										//
			}													//
		}														//
		nbColumns = iterator;									//
		int *orderColumns = malloc(sizeof(int) * nbColumns);	//

		iterator = 0;										// Initialises  the table orderColumns, allowing to know in which order the columns are to be printed
		for(int i = 0; i < nbArguments; i++){				//
			if(printColumn[i] != -1){						//
				orderColumns[iterator] = printColumn[i];	//
				iterator++;									//
			}												//
		}													//

		free(printColumn);
		
		tableType table;																	// Effectue une copie de tableBuffer dans table en ne gardant que les colonnes du tableau à garder
		table = malloc(sizeof(*table));														//
		table->lenght = tableBuffer->lenght;												//
		strcpy(table->name, tableBuffer->name);												//
		table->cellWidth = NULL;															//
		tableLine = tableBuffer->begin;														//
		table->begin = CreateTableLine(tableBuffer, 0, orderColumns, nbColumns);			//
		table->end = table->begin;															//
		for(int i = 1; i < table->lenght; i++){												//
			table->end->next = CreateTableLine(tableBuffer, i, orderColumns, nbColumns);	//
			table->end->next->back = table->end;											//
			table->end = table->end->next;													//
		}																					//
		GetTableLenght(table);																//
		GetTableWidth(table);																//
		GetTableCellWidth(table);															//

		free(orderColumns);

		return table;
	}
}
int GetLineLenght(tableType table, int line){
	tableLineType tableLine = table->begin;
	for(int i = 0; i < line; i++){
		tableLine = tableLine->next;
	}
	return tableLine->lenght;
}
void GetTableWidth(tableType table){
	table->width = 0;
	for(int i = 0; i < table->lenght; i++){
		if(GetLineLenght(table, i) > table->width){
			table->width = GetLineLenght(table, i);
		}
	}
}
void GetTableCellWidth(tableType table){
	if(table->cellWidth != NULL){
		free(table->cellWidth);
		table->cellWidth = NULL;
	}
	table->cellWidth = malloc(table->width * sizeof(int));
	tableCellType *tableCell = NULL;
	for(int i = 0; i < table->width; i++){
		table->cellWidth[i] = 0;
		for(int j = 0; j < table->lenght; j++){
			tableCell = GetCellValue(table, j, i);
			if(tableCell != NULL){
				if(tableCell->lenght > table->cellWidth[i]){
					table->cellWidth[i] = tableCell->lenght;
				}
			}
		}
	}
}

// Print

void PrintGraphicTable(tableType table, FILE *flow, char noColor){
	if(table != NULL){
		tableLineType tableLine = NULL;
		tableCellType *tableCell = NULL;
		fprintf(flow, "============================================================\n");
		if(noColor == false){
			StdoutColorRed();
		}
		fprintf(flow, "%s\n", table->name);
		if(noColor == false){
			StdoutColorReset();
		}
		fprintf(flow, "============================================================\n");
		fprintf(flow, "\n");
		if(strcmp(table->name, "__ALLTABLES__") != 0){
			for(int i = 0; i < table->width; i++){
				fprintf(flow, "+");
				for(int j = 0; j < table->cellWidth[i]; j++){
					fprintf(flow, "-");
				}
			}
			if(table->width > 0){
				fprintf(flow, "+\n");
			}
			tableLine = table->begin;
			if(tableLine != NULL){
				tableCell = tableLine->begin;
			}
			for(int i = 0; i < table->width; i++){
				if (tableCell == NULL){								// Impossible théoriquement
					fprintf(flow, "|");
					for (int j = 0; j < table->cellWidth[i]; j++)
						fprintf(flow, " ");
				}
				else{
					fprintf(flow, "|");
					if(noColor == false){
						StdoutColorBlue();
					}
					fprintf(flow, "%s", tableCell->value);
					if(noColor == false){
						StdoutColorReset();
					}
					for (int j = 0; j < table->cellWidth[i] - tableCell->lenght; j++){
						fprintf(flow, " ");
					}
				}
				if(tableCell != NULL){
					tableCell = tableCell->next;
				}
			}
			if(table->width > 0){
				fprintf(flow, "|\n");
			}
			for(int i = 0; i < table->width; i++){
				fprintf(flow, "+");
				for(int j = 0; j < table->cellWidth[i]; j++){
					fprintf(flow, "-");
				}
			}
			if(table->width > 0){
				fprintf(flow, "+\n");
			}
			for(int i = 1; i < table->lenght; i++){
				tableLine = tableLine->next;
				tableCell = tableLine->begin;
				for(int j = 0; j < table->width; j++){
					if(tableCell == NULL){
						fprintf(flow, "|");
						for(int k = 0; k < table->cellWidth[j]; k++)
							fprintf(flow, " ");
					}
					else{
						fprintf(flow, "|%s", tableCell->value);
						for(int k = 0; k < table->cellWidth[j] - tableCell->lenght; k++){
							fprintf(flow, " ");
						}
					}
					if(tableCell != NULL){
						tableCell = tableCell->next;
					}
				}
				fprintf(flow, "|\n");
			}
			if(table->lenght > 1){
				for(int i = 0; i < table->width; i++){
					fprintf(flow, "+");
					for(int j = 0; j < table->cellWidth[i]; j++){
						fprintf(flow, "-");
					}
				}
				fprintf(flow, "+\n");
			}
		}
		else{
			tableLine = table->begin;
			for(int i = 0; i < table->lenght; i++){
				tableCell = tableLine->begin;
				for(int j = 0; j < table->width; j++){
					if(tableCell == NULL){
						fprintf(flow, "[");
						for(int k = 0; k < table->cellWidth[j]; k++)
							fprintf(flow, " ");
						fprintf(flow, "] ");
					}
					else{
						fprintf(flow, "[%s", tableCell->value);
						for(int k = 0; k < table->cellWidth[j] - tableCell->lenght; k++){
							fprintf(flow, " ");
						}
						fprintf(flow, "] ");
					}
					if(tableCell != NULL){
						tableCell = tableCell->next;
					}
				}
				fprintf(flow, "\n");
				tableLine = tableLine->next;
			}
		}
	}
}
// void PrintGraphicTable(tableType table, FILE *flow){
// 	if(table != NULL){
// 		tableLineType tableLine = table->begin;
// 		tableCellType *tableCell = NULL;
// 		fprintf(flow, "============================================================\n");
// 		StdoutColorRed();
// 		fprintf(flow, "%s\n", table->name);
// 		StdoutColorReset();
// 		fprintf(flow, "============================================================\n");
// 		fprintf(flow, "\n");
// 		if(strcmp(table->name, "__ALLTABLES__") != 0){
// 			for(int i = 0; i < table->width; i++){
// 				fprintf(flow, "+");
// 				for(int j = 0; j < table->cellWidth[i]; j++){
// 					fprintf(flow, "-");
// 				}
// 			}
// 			fprintf(flow, "+\n");
// 			for(int i = 0; i < table->width; i++){
// 				tableCell = GetCellValue(table, 0, i);
// 				if (tableCell == NULL){
// 					fprintf(flow, "|");
// 					for (int j = 0; j < table->cellWidth[i]; j++)
// 						fprintf(flow, " ");
// 				}
// 				else{
// 					fprintf(flow, "|");
// 					StdoutColorBlue();
// 					fprintf(flow, "%s", tableCell->value);
// 					StdoutColorReset();
// 					for (int j = 0; j < table->cellWidth[i] - tableCell->lenght; j++){
// 						fprintf(flow, " ");
// 					}
// 				}
// 			}
// 			fprintf(flow, "|\n");
// 			for(int i = 0; i < table->width; i++){
// 				fprintf(flow, "+");
// 				for(int j = 0; j < table->cellWidth[i]; j++){
// 					fprintf(flow, "-");
// 				}
// 			}
// 			fprintf(flow, "+\n");
// 			for(int i = 1; i < table->lenght; i++){
// 				for(int j = 0; j < table->width; j++){
// 					tableCell = GetCellValue(table, i, j);
// 					if(tableCell == NULL){
// 						fprintf(flow, "|");
// 						for(int k = 0; k < table->cellWidth[j]; k++)
// 							fprintf(flow, " ");
// 					}
// 					else{
// 						fprintf(flow, "|%s", tableCell->value);
// 						for(int k = 0; k < table->cellWidth[j] - tableCell->lenght; k++){
// 							fprintf(flow, " ");
// 						}
// 					}
// 				}
// 				fprintf(flow, "|\n");
// 				tableLine = tableLine->next;
// 			}
// 			for(int i = 0; i < table->width; i++){
// 				fprintf(flow, "+");
// 				for(int j = 0; j < table->cellWidth[i]; j++){
// 					fprintf(flow, "-");
// 				}
// 			}
// 			fprintf(flow, "+\n");
// 		}
// 		else{
// 			for(int i = 0; i < table->lenght; i++){
// 				for(int j = 0; j < table->width; j++){
// 					tableCell = GetCellValue(table, i, j);
// 					if(tableCell == NULL){
// 						fprintf(flow, "[");
// 						for(int k = 0; k < table->cellWidth[j]; k++)
// 							fprintf(flow, " ");
// 						fprintf(flow, "] ");
// 					}
// 					else{
// 						fprintf(flow, "[%s", tableCell->value);
// 						for(int k = 0; k < table->cellWidth[j] - tableCell->lenght; k++){
// 							fprintf(flow, " ");
// 						}
// 						fprintf(flow, "] ");
// 					}
// 				}
// 				fprintf(flow, "\n");
// 				tableLine = tableLine->next;
// 			}
// 		}
// 	}
// }
void PrintCsvTable(tableType table, FILE *flow, char sep){
	if(table != NULL){
		tableLineType tableLine = table->begin;
		tableCellType *tableCell = NULL;
		if(tableLine != NULL){
			tableCell = tableLine->begin;
		}
		if(strcmp(table->name, "__ALLTABLES__") != 0){
			fprintf(flow, "__%s__", table->name);
			for(int i = 0; i < table->width - 1; i++){
				fprintf(flow, "%c", sep);
			}
			fprintf(flow, "\n");
		}
		for(int i = 0; i < table->lenght; i++){
			tableCell = tableLine->begin;
			for(int j = 0; j < table->width; j++){
				if(tableCell != NULL){
					fprintf(flow, "%s", tableCell->value);
				}
				if(j != table->width - 1){
					fprintf(flow, "%c", sep);
				}
				if(tableCell != NULL){
					tableCell = tableCell->next;
				}
			}
			// fseek(flow, -1, SEEK_CUR);
			fprintf(flow, "\n");
			tableLine = tableLine->next;
		}
	}
}
void PrintXmlTable(tableType table, FILE *flow){
	if(table != NULL){
		tableLineType tableLine = table->begin;
		tableCellType *tableCell = NULL;
		fprintf(flow, "<table>\n");
		if(tableLine != NULL){
			tableCell = tableLine->begin;
		}
		fprintf(flow, "\t<caption>%s</caption>\n", table->name);
		if(strcmp(table->name, "__ALLTABLES__") != 0){
			tableLine = table->begin;
			if(tableLine != NULL){
				tableCell = tableLine->begin;
			}
			if(table->width > 0){
				fprintf(flow, "\t<thead>\n");
				fprintf(flow, "\t\t<tr>\n");
			}
			for(int i = 0; i < table->width; i++){
				if(tableCell != NULL){
					fprintf(flow, "\t\t\t<th>%s</th>\n", tableCell->value);
				}
				if(tableCell != NULL){
					tableCell = tableCell->next;
				}
			}
			if(table->width > 0){
				fprintf(flow, "\t\t</tr>\n");
				fprintf(flow, "\t</thead>\n");
			}
			if(table->lenght > 1){
				fprintf(flow, "\t<tbody>\n");
			}
			for(int i = 1; i < table->lenght; i++){
				tableLine = tableLine->next;
				tableCell = tableLine->begin;
				fprintf(flow, "\t\t<tr>\n");
				for(int j = 0; j < table->width; j++){
					if(tableCell != NULL){
						fprintf(flow, "\t\t\t<td>%s</td>\n", tableCell->value);
					}
					if(tableCell != NULL){
						tableCell = tableCell->next;
					}
				}
				fprintf(flow, "\t\t</tr>\n");
			}
			if(table->lenght > 1){
				fprintf(flow, "\t</tbody>\n");
			}
		}
		else{
			tableLine = table->begin;
			for(int i = 0; i < table->lenght; i++){
				tableCell = tableLine->begin;
				fprintf(flow, "\t<tr>\n");
				for(int j = 0; j < table->width; j++){
					if(tableCell != NULL){
						fprintf(flow, "\t\t<td>%s</td>\n", tableCell->value);
					}
					if(tableCell != NULL){
						tableCell = tableCell->next;
					}
				}
				fprintf(flow, "\t</tr>\n");
				tableLine = tableLine->next;
			}
		}
		fprintf(flow, "</table>\n");
	}
}
void ToPrint(char action[25], char tableName[25][25], char tableColumns[25][25], tableType table){
	tableLineType tableLine = table->begin;
	//tableCellType *tableCell = tableLine->begin;

	printf("\naction : %s\n", action);
	printf("table : %s\n", tableName[0]);
	printf("arguments : ");
	for(int i = 0; strcmp(tableColumns[i], "__END__") != 0 && i < 25; i++){
		printf("%s ", tableColumns[i]);
	}
	printf("\n");
	if(table != NULL){
		printf("table lenght : %d\n", table->lenght);
		printf("table width : %d\n", table->width);
		for(int i = 0; i < table->lenght; i++){
			printf("table line %d lenght : %d\n", i, tableLine->lenght);
			tableLine = tableLine->next;
		}
		for(int i = 0; i < table->width; i++){
			printf("column %d : %d\n", i, table->cellWidth[i]);
		}
	}
}
void PrintError(){
	printf("Erreur(s) dans le code\n");
}
void PrintHelp(){
	char line[1000];

	printf("============================================================\n");
	printf("Aide d'utilisation\n");
	printf("============================================================\n");
	printf("\n");
	FILE *fic = fopen("fics/help.txt", "r");
	if(fic == NULL){
		exit(1);
	}
	fseek(fic, 0, SEEK_SET);
	while(!feof(fic)){
		fgets(line, 500, fic);
		printf("%s", line);
	}
	fclose(fic);
}
void PrintStart(){
	// char line[1000];

	// FILE *fic = fopen("fics/start.txt", "r");
	// if(fic == NULL){
	// 	exit(1);
	// }
	// fseek(fic, 0, SEEK_SET);
	// ClearTerminal();
	// while(!feof(fic)){
	// 	fgets(line, 500, fic);
	// 	printf("%s", line);
	// }
	// printf("\n");
	// fclose(fic);

	ClearTerminal();

	StdoutColorGreen();
	printf("                 888888888888888888888888888888888888888888888888888888888\n");
	printf("                888888888888888888888888888888888888888888888888888888888\n");
	printf("               8888                                                 8888\n");
	printf("              8888      "); StdoutColorBlue(); printf("CCCCCCC       "); StdoutColorWhite(); printf("SSSSSS   "); StdoutColorRed(); printf("VVV         VVV     "); StdoutColorGreen(); printf("8888\n");
	printf("             8888     "); StdoutColorBlue(); printf("CCCC    CCC   "); StdoutColorWhite(); printf("SS      SS  "); StdoutColorRed(); printf("VVV       VVV     "); StdoutColorGreen(); printf("8888\n");
	printf("            8888     "); StdoutColorBlue(); printf("CCC            "); StdoutColorWhite(); printf("SS           "); StdoutColorRed(); printf("VVV     VVV     "); StdoutColorGreen(); printf("8888\n");
	printf("           8888      "); StdoutColorBlue(); printf("CCC              "); StdoutColorWhite(); printf("SSSSSS      "); StdoutColorRed(); printf("VVV   VVV     "); StdoutColorGreen(); printf("8888\n");
	printf("          8888       "); StdoutColorBlue(); printf("CCC                    "); StdoutColorWhite(); printf("SS     "); StdoutColorRed(); printf("VVV VVV     "); StdoutColorGreen(); printf("8888\n");
	printf("         8888         "); StdoutColorBlue(); printf("CCCC    CCC   "); StdoutColorWhite(); printf("SS      SS      "); StdoutColorRed(); printf("VVVVV     "); StdoutColorGreen(); printf("8888\n");
	printf("        8888            "); StdoutColorBlue(); printf("CCCCCCC       "); StdoutColorWhite(); printf("SSSSSS         "); StdoutColorRed(); printf("VVV     "); StdoutColorGreen(); printf("8888\n");
	printf("       8888                                                 8888\n");
	printf("      888888888888888888888888888888888888888888888888888888888\n");
	printf("     888888888888888888888888888888888888888888888888888888888\n");
	StdoutColorReset();
	printf("\n");
	printf("Project - CSV_ctrl\n");
	printf("Version 00\n");
	printf("\n");
	printf("Author : Jean Le Bris\n");
}
void ClearTerminal(){
	#if defined(__linux__)
	system("clear");
	#elif defined(_WIN32) || defined(_WIN64)
	system("cls");
	#endif
}






tableType GetFileData(tableType table, char *fileName, char inputModeVar){
	tableLineType tableLine = NewTableLine();
	char fileLineBrut[500] = "\0";
	char fileLineBuffer[500] = "\t"; // default value that should not be found in the file
	char srcFileName[100] = "\0";
	char sep;
	switch(inputModeVar){
		case CSV_SEMICOLON_MODE_BIT :
			sep = ';';
			break;
		case CSV_COMMA_MODE_BIT :
			sep = ',';
			break;
		default :
			sep = ';';
			break;
	}
	strcat(strcat(srcFileName, FILE_ACCESS), fileName);
	FILE *fic = fopen(srcFileName, "r");
	if(fic == NULL){
		return NULL;
	}
	fseek(fic, 0, SEEK_SET);
	while(!feof(fic)){
		fgets(fileLineBrut, 500, fic);
		if(strcmp(fileLineBuffer, fileLineBrut) != 0){
			tableLine = NewTableLine();
			tableLine = PushBackTableLineCleaned(tableLine, fileLineBrut, sep);
			table = PushBackTable(table, tableLine);
			strcpy(fileLineBuffer, fileLineBrut);
		}
	}
	fclose(fic);
	strcpy(table->name, "__ALLTABLES__");
	GetTableWidth(table);
	GetTableCellWidth(table);

	return table;
}
tableType CreateFileTable(tableType table, char tableName[25][25], char inputModeVar){
	char tableNameBuffer[29];
	tableLineType tableLine = NewTableLine();
	char sep;
	switch(inputModeVar){
		case CSV_SEMICOLON_MODE_BIT :
			sep = ';';
			break;
		case CSV_COMMA_MODE_BIT :
			sep = ',';
			break;
		default :
			sep = ';';
			break;
	}
	for(int i = 0; strcmp(tableName[i], "__END__") != 0; i++){
		strcpy(tableNameBuffer, "\0");
		tableLine = NewTableLine();
		strcat(strcat(strcat(tableNameBuffer, "__"), tableName[i]), "__\0");
		tableLine = PushBackTableLineCleaned(tableLine, tableNameBuffer, sep);
		table = PushBackTable(table, tableLine);
	}

	GetTableWidth(table);
	GetTableCellWidth(table);

	return table;
}
void SetFileData(tableType table, char *fileName, char outputModeVar){
	char srcFileName[100] = "\0";
	strcat(strcat(srcFileName, FILE_ACCESS), fileName);
	FILE *fic = fopen(srcFileName, "w");
	if(fic == NULL){
		exit(1);
	}
	switch(outputModeVar){
		case GRAPHIC_MODE_BIT :
			PrintGraphicTable(table, fic, 1);
			break;
		case CSV_SEMICOLON_MODE_BIT :
			PrintCsvTable(table, fic, ';');
			break;
		case CSV_COMMA_MODE_BIT :
			PrintCsvTable(table, fic, ',');
			break;
		case XML_MODE_BIT :
			PrintXmlTable(table, fic);
			break;
		default :
			PrintCsvTable(table, fic, ';');
			break;
	}
	fclose(fic);
}
// void SetFileData(tableType table, char *fileName){
// 	tableLineType tableLine = NewTableLine();
// 	tableCellType *tableCell = NULL;
// 	char srcFileName[100] = "\0";
// 	strcat(strcat(srcFileName, FILE_ACCESS), fileName);
// 	FILE *fic = fopen(srcFileName, "w");
// 	if(fic == NULL){
// 		exit(1);
// 	}
// 	tableLine = table->begin;
// 	tableCell = tableLine->begin;
// 	for(int i = 0; i < table->lenght; i++){
// 		for(int j = 0; j < table->width; j++){
// 			if(tableCell != NULL){
// 				fprintf(fic, "%s", tableCell->value);
// 				tableCell = tableCell->next;
// 			}
// 			else{

// 			}

// 			if(j != table->width - 1){
// 				fprintf(fic, ";");
// 			}
// 			else{

// 			}
// 		}
// 		fprintf(fic, "\n");
// 		tableLine = tableLine->next;
// 		if(tableLine != NULL){
// 			tableCell = tableLine->begin;
// 		}
// 	}
// 	fclose(fic);
// }
tableType CreateFileTableColumn(tableType tableBuffer, char tableColumns[25][25], char inputModeVar){
	tableLineType tableLine = NULL;
	char sep;
	switch(inputModeVar){
		case CSV_SEMICOLON_MODE_BIT :
			sep = ';';
			break;
		case CSV_COMMA_MODE_BIT :
			sep = ',';
			break;
		default :
			sep = ';';
			break;
	}
	if(tableBuffer->begin == NULL){
		tableLine = malloc(sizeof(*tableLine));
		tableLine->lenght = 0;
		tableLine->begin = NULL;
		tableLine->end = NULL;
		tableLine->back = NULL;
		tableLine->next = NULL;
		tableBuffer->begin = tableLine;
		tableBuffer->end = tableLine;
	}
	else{
		tableLine = tableBuffer->begin;
	}
	
	for(int i = 0; strcmp(tableColumns[i], "__END__") != 0; i++){
		tableLine = PushBackTableLineCleaned(tableLine, tableColumns[i], sep);
	}

	GetTableLenght(tableBuffer);
	GetTableWidth(tableBuffer);
	GetTableCellWidth(tableBuffer);

	return tableBuffer;
}
tableType CreateFileTableLine(tableType tableBuffer, char tableColumns[25][25], char tableValues[25][25], int tableSize, char inputModeVar){
	int *tableIndexes = NULL;
	tableIndexes = malloc(sizeof(*tableIndexes)*tableSize);
	
	char sep;
	switch(inputModeVar){
		case CSV_SEMICOLON_MODE_BIT :
			sep = ';';
			break;
		case CSV_COMMA_MODE_BIT :
			sep = ',';
			break;
		default :
			sep = ';';
			break;
	}

	for(int i = 0; i < tableSize; i++){
		tableIndexes[i] = -1;
	}

	for(int i = 0; i < tableSize; i++){
		for(int j = 0; j < tableBuffer->width; j++){
			if(strcmp(tableColumns[i], GetCellValue(tableBuffer, 0, j)->value) == 0){
				tableIndexes[i] = j;
			}
		}
	}

	for(int i = 0; i < tableSize; i++){
		if(tableIndexes[i] == -1){
			PrintError();
			return tableBuffer;
		}
	}

	char *tempString;
	tempString = malloc(sizeof(*tempString) * tableBuffer->width);
	strcpy(tempString, "\0");

	for(int i = 0; i < tableBuffer->width; i++){
		strcat(tempString, ";");
	}

	tableLineType tableLine = NewTableLine();

	tableLine = PushBackTableLine(tableLine, tempString, sep);

	free(tempString);

	tableBuffer = PushBackTable(tableBuffer, tableLine);

	for(int i = 0; i < tableSize; i++){
		strcpy(GetCellValue(tableBuffer, tableBuffer->lenght - 1, tableIndexes[i])->value, tableValues[i]);
	}

	free(tableIndexes);

	return tableBuffer;
}
tableType SetTable(tableType tables, tableType tableBuffer, char inputModeVar){
	char tableNameBuffer[29];
	tableLineType tableLine = NewTableLine();
	char sep;
	switch(inputModeVar){
		case CSV_SEMICOLON_MODE_BIT :
			sep = ';';
			break;
		case CSV_COMMA_MODE_BIT :
			sep = ',';
			break;
		default :
			sep = ';';
			break;
	}

	strcpy(tableNameBuffer, "\0");
	strcat(strcat(strcat(tableNameBuffer, "__"), tableBuffer->name), "__\0");
	tableLine = PushBackTableLineCleaned(tableLine, tableNameBuffer, sep);
	tables = PushBackTable(tables, tableLine);
	tables->end->next = tableBuffer->begin;
	tableBuffer->begin->back = tables->end;
	tables->end = tableBuffer->end;

	tableBuffer->begin = NULL;
	tableBuffer->end = NULL;
	
	GetTableLenght(tables);
	GetTableWidth(tables);
	GetTableCellWidth(tables);

	GetTableLenght(tableBuffer);
	GetTableWidth(tableBuffer);
	GetTableCellWidth(tableBuffer);

	return tables;
}
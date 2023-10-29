#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/log.h"

#define GRAPHIC_MODE_BIT (1<<0)
#define CSV_MODE_BIT (1<<1)

void LogList(char *fileName, command commandList){
	commandElement *node = commandList->begin;
	FILE *file = fopen(fileName,"a");
	if(file==NULL){
		exit(1);
	}
	fprintf(file, ">>> ");
	while(node != NULL){
		fprintf(file, "%s ", node->value);
		node = node->next;
	}
	fprintf(file, "\n");
	fprintf(file, "size : %d\n", commandList->lenght);
	fclose(file);
}



void LogString(char *fileName, char *string){
	FILE *file = fopen(fileName,"a");
	if(file==NULL){
		exit(1);
	}
	fprintf(file, "%s\n", string);
	fclose(file);
}

void LogTable(char *fileName, tableType table, char outputModeVar){
	tableLineType tableLine = table->begin;
	FILE *file = fopen(fileName,"a");
	if(file==NULL){
		exit(1);
	}
	if(table != NULL){
		fprintf(file, "table name : %s\n", table->name);
		fprintf(file, "table lenght : %d\n", table->lenght);
		fprintf(file, "table width : %d\n", table->width);
		fprintf(file, "table line lengths :\n");
		for(int i = 0; i < table->lenght; i++){
			fprintf(file, "\t+--[%d] : %d\n", i, tableLine->lenght);
			tableLine = tableLine->next;
		}
		fprintf(file, "table cell widths :\n");
		for(int i = 0; i < table->width; i++){
			fprintf(file, "\t+--[%d] : %d\n", i, table->cellWidth[i]);
		}
		fprintf(file, "\nresult :\n\n");

		switch(outputModeVar){
			case GRAPHIC_MODE_BIT :
				PrintGraphicTable(table, file, 1);
				break;
			case CSV_MODE_BIT :
				PrintCsvTable(table, file);
				break;
			default :
				PrintGraphicTable(table, file, 1);
				break;
		}
	}
	fclose(file);
}

void LogData(char *fileName, char data[25][25]){
	FILE *file = fopen(fileName,"a");
	if(file==NULL){
		exit(1);
	}
	for(int i = 0; strcmp(data[i], "__END__") != 0; i++){
		fprintf(file, "\t+--[%d] : %s\n", i, data[i]);
	}
	fclose(file);
}

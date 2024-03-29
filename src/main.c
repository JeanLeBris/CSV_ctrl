#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "../lib/log.h"
#include "../lib/table.h"
#include "../lib/command.h"
#include "../lib/stdout_color.h"

#define VAL_BIT (1<<0)
#define COL_BIT (1<<1)
#define TAB_BIT (1<<2)
#define INPUT_FILE_BIT (1<<3)
#define OUTPUT_FILE_BIT (1<<4)
#define ALL_BIT (1<<5)
#define ERROR_BIT (1<<6)
#define END_BIT (1<<7)
#define DEBUG_BIT (1<<8)
#define NO_PRINT_BIT (1<<9)
#define NO_COMMAND_PRINT_BIT (1<<10)
#define NO_COLOR_BIT (1<<11)
#define LOG_BIT (1<<12)
#define INPUT_MODE_BIT (1<<13)
#define OUTPUT_MODE_BIT (1<<14)

#define GRAPHIC_MODE_BIT (1<<0)
#define CSV_SEMICOLON_MODE_BIT (1<<1)
#define CSV_COMMA_MODE_BIT (1<<2)
#define XML_MODE_BIT (1<<3)

#define LOG_ACCESS "./log/"

int main(int argc, char *argv[]){
	short runProgram = 1;
	struct timespec timestamp;
	struct tm *timestampStruct = NULL;
	char strTimestamp[40] = "\0";
	char logFileName[100] = "\0";

	char charBuffer[100] = "\0";
	
	command commandList = NewCommand();
	command commandListCopy = NewCommand();
	commandElement *node = NULL;

	int iterator1 = 0;
	int iterator2 = 0;
	char action[25];             // Contains the action to do with the data
	char inputFileName[100];
	char outputFileName[100];
	char tableName[25][25];      // Contains the name of the table taken by the command
	char tableColumns[25][25]; // Contains all the arguments taken by the command
	char tableValues[25][25];
	char debug = 0;
	char noPrint = 0;
	char noCommandPrint = 0;
	char log = 0;
	char noColor = 0;
	unsigned long controlVar = 0;
	char inputModeVar = 0;
	char outputModeVar = 0;

	tableType tablesBrut = NewTable();  // The table that get all the file's data as value
	tableType tableBuffer = NewTable(); // The table that get the unsorted selected data from the file
	tableType table = NewTable();       // The table that get the selected data from the file

	if(argc == 1)
		PrintStart();

	while(runProgram){
		strcpy(tableName[0], "__ALLTABLES__");
		strcpy(tableName[1], "__END__");
		strcpy(tableColumns[0], "__ALLCOLUMNS__");
		strcpy(tableColumns[1], "__END__");
		strcpy(tableValues[0], "__ALLVALUES__");
		strcpy(tableValues[1], "__END__");
		strcpy(inputFileName, "\0");
		strcpy(outputFileName, "\0");
		debug = 0;
		noPrint = 0;
		noCommandPrint = 0;
		log = 0;
		noColor = 0;

		controlVar = 0;
		inputModeVar = 0;
		outputModeVar = 0;

		/*
		Get all the parameters to run the program
		*/

		if(argc > 1){
			for(int i = 1; i < argc; i++){
				commandList = PushBackCommand(commandList, argv[i]);
			}
			runProgram = 0;
		}
		else{
			commandList = InputCommand();
		}

		commandListCopy = CopyCommand(commandList);

		timespec_get(&timestamp, TIME_UTC);
		timestampStruct = gmtime(&timestamp.tv_sec);

		//sprintf(strTimestamp, "%lld", timestamp);
		sprintf(strTimestamp, "%04d-%02d-%02d_%02d-%02d-%02d-%ld", timestampStruct->tm_year+1900, timestampStruct->tm_mon+1, timestampStruct->tm_mday, timestampStruct->tm_hour, timestampStruct->tm_min, timestampStruct->tm_sec, timestamp.tv_nsec);
		strcpy(logFileName, "\0");
		strcat(strcat(strcat(strcat(logFileName, LOG_ACCESS), "log_"), strTimestamp), ".log");

		// if(noPrint == false){
		// 	ClearTerminal();
		// 	PrintCommand(commandList);
		// }

		node = PullFrontCommand(commandList);
		if(node == NULL){
			PrintError();
		}
		else if(strcmp(node->value, "help") == 0){
			strcpy(action, node->value);
			free(node);
		}
		else if(strcmp(node->value, "print") == 0){
			strcpy(action, node->value);
			free(node);
			
			while(commandList->lenght != 0){
				node = PullFrontCommand(commandList);
				if(node->value[0] == '-'){
					if(strcmp(node->value, "--input_mode") == 0 || strcmp(node->value, "-im") == 0){
						controlVar = INPUT_MODE_BIT;
					}
					else if(strcmp(node->value, "--input") == 0 || strcmp(node->value, "-i") == 0){
						controlVar = INPUT_FILE_BIT;
					}
					else if(strcmp(node->value, "--output_mode") == 0 || strcmp(node->value, "-om") == 0){
						controlVar = OUTPUT_MODE_BIT;
					}
					else if(strcmp(node->value, "--output") == 0 || strcmp(node->value, "-o") == 0){
						controlVar = OUTPUT_FILE_BIT;
					}
					else if(strcmp(node->value, "--table") == 0 || strcmp(node->value, "-t") == 0){
						controlVar = TAB_BIT;
					}
					else if(strcmp(node->value, "--columns") == 0 || strcmp(node->value, "--cols") == 0 || strcmp(node->value, "-c") == 0){
						controlVar = COL_BIT;
					}
					else if(strcmp(node->value, "--all") == 0 || strcmp(node->value, "-a") == 0){
						controlVar |= ALL_BIT;
					}
					else if(strcmp(node->value, "--debug") == 0 || strcmp(node->value, "-d") == 0){
						controlVar = DEBUG_BIT;
					}
					else if(strcmp(node->value, "--no_print") == 0 || strcmp(node->value, "-np") == 0){
						controlVar = NO_PRINT_BIT;
					}
					else if(strcmp(node->value, "--no_command_print") == 0 || strcmp(node->value, "-ncp") == 0){
						controlVar = NO_COMMAND_PRINT_BIT;
					}
					else if(strcmp(node->value, "--no_color") == 0 || strcmp(node->value, "-nc") == 0){
						controlVar = NO_COLOR_BIT;
					}
					else if(strcmp(node->value, "--log") == 0 || strcmp(node->value, "-l") == 0){
						controlVar = LOG_BIT;
					}
					else{
						controlVar = ERROR_BIT;
					}
				}
				else{
					switch(controlVar){
						case INPUT_MODE_BIT :
							if(strcmp(node->value, "csv;") == 0){
								inputModeVar = CSV_SEMICOLON_MODE_BIT;
							}
							else if(strcmp(node->value, "csv,") == 0){
								inputModeVar = CSV_COMMA_MODE_BIT;
							}
							break;
						case INPUT_FILE_BIT :
							strcpy(inputFileName, node->value);
							break;
						case OUTPUT_MODE_BIT :
							if(strcmp(node->value, "graphic") == 0){
								outputModeVar = GRAPHIC_MODE_BIT;
							}
							else if(strcmp(node->value, "csv;") == 0){
								outputModeVar = CSV_SEMICOLON_MODE_BIT;
							}
							else if(strcmp(node->value, "csv,") == 0){
								outputModeVar = CSV_COMMA_MODE_BIT;
							}
							else if(strcmp(node->value, "xml") == 0){
								outputModeVar = XML_MODE_BIT;
							}
							break;
						case OUTPUT_FILE_BIT :
							strcpy(outputFileName, node->value);
							break;
						case TAB_BIT :
							iterator1 = 0;
							while(tableName[iterator1][0] != '_' || tableName[iterator1][1] != '_'){
								iterator1++;
							}
							strcpy(tableName[iterator1], node->value);
							strcpy(tableName[iterator1 + 1], "__END__");
							break;
						case TAB_BIT | ALL_BIT :
							strcpy(tableName[0], "__ALLTABLES__");
							strcpy(tableName[1], "__END__");
							//controlVar = END_BIT;
							break;
						case COL_BIT :
							iterator1 = 0;
							while(tableColumns[iterator1][0] != '_' || tableColumns[iterator1][1] != '_'){
								iterator1++;
							}
							strcpy(tableColumns[iterator1], node->value);
							strcpy(tableColumns[iterator1 + 1], "__END__");
							break;
						case COL_BIT | ALL_BIT :
							strcpy(tableColumns[0], "__ALLCOLUMNS__");
							strcpy(tableColumns[1], "__END__");
							//controlVar = END_BIT;
							break;
						/*
						case END_BIT :
							commandList = CleanCommand(commandList);
							break;
						case ERROR_BIT :
							PrintError();
							break;
						case DEBUG_BIT:
							debug = 1;
							controlVar = END_BIT;
							break;
						*/
						default :
							break;
					}
				}
				free(node);
				if(controlVar == DEBUG_BIT){
					debug = 1;
					// controlVar = END_BIT;
				}
				if(controlVar == LOG_BIT){
					log = 1;
				}
				if(controlVar == NO_PRINT_BIT){
					noPrint = 1;
				}
				if(controlVar == NO_COMMAND_PRINT_BIT){
					noCommandPrint = 1;
				}
				if(controlVar == NO_COLOR_BIT){
					noColor = 1;
				}
				if(controlVar == ERROR_BIT){
					PrintError();
					controlVar = END_BIT;
				}
				if(controlVar == END_BIT){
					commandList = CleanCommand(commandList);
				}
			}
		}
		else if(strcmp(node->value, "create") == 0){
			strcpy(action, node->value);
			free(node);

			while(commandList->lenght != 0){
				node = PullFrontCommand(commandList);
				if(node->value[0] == '-'){
					if(strcmp(node->value, "--input_mode") == 0 || strcmp(node->value, "-im") == 0){
						controlVar = INPUT_MODE_BIT;
					}
					else if(strcmp(node->value, "--input") == 0 || strcmp(node->value, "-i") == 0){
						controlVar = INPUT_FILE_BIT;
					}
					else if(strcmp(node->value, "--output_mode") == 0 || strcmp(node->value, "-om") == 0){
						controlVar = OUTPUT_MODE_BIT;
					}
					else if(strcmp(node->value, "--output") == 0 || strcmp(node->value, "-o") == 0){
						controlVar = OUTPUT_FILE_BIT;
					}
					else if(strcmp(node->value, "--table") == 0 || strcmp(node->value, "-t") == 0){
						controlVar = TAB_BIT;
					}
					else if(strcmp(node->value, "--columns") == 0 || strcmp(node->value, "--cols") == 0 || strcmp(node->value, "-c") == 0){
						controlVar = COL_BIT;
					}
					else if(strcmp(node->value, "--values") == 0 || strcmp(node->value, "--vals") == 0 || strcmp(node->value, "-v") == 0){
						controlVar = VAL_BIT;
					}
					else if(strcmp(node->value, "--debug") == 0 || strcmp(node->value, "-d") == 0){
						controlVar = DEBUG_BIT;
					}
					else{
						controlVar = ERROR_BIT;
					}
				}
				else{
					switch(controlVar){
						case INPUT_MODE_BIT :
							if(strcmp(node->value, "csv;") == 0){
								inputModeVar = CSV_SEMICOLON_MODE_BIT;
							}
							else if(strcmp(node->value, "csv,") == 0){
								inputModeVar = CSV_COMMA_MODE_BIT;
							}
							break;
						case INPUT_FILE_BIT :
							strcpy(inputFileName, node->value);
							break;
						case OUTPUT_MODE_BIT :
							if(strcmp(node->value, "csv;") == 0){
								outputModeVar = CSV_SEMICOLON_MODE_BIT;
							}
							else if(strcmp(node->value, "csv,") == 0){
								outputModeVar = CSV_COMMA_MODE_BIT;
							}
							break;
						case OUTPUT_FILE_BIT :
							strcpy(outputFileName, node->value);
							break;
						case TAB_BIT :
							iterator1 = 0;
							while(tableName[iterator1][0] != '_' || tableName[iterator1][1] != '_'){
								iterator1++;
							}
							strcpy(tableName[iterator1], node->value);
							strcpy(tableName[iterator1 + 1], "__END__");
							break;
						case COL_BIT :
							iterator1 = 0;
							while(tableColumns[iterator1][0] != '_' || tableColumns[iterator1][1] != '_'){
								iterator1++;
							}
							strcpy(tableColumns[iterator1], node->value);
							strcpy(tableColumns[iterator1 + 1], "__END__");
							break;
						case VAL_BIT :
							iterator1 = 0;
							while(tableValues[iterator1][0] != '_' || tableValues[iterator1][1] != '_'){
								iterator1++;
							}
							strcpy(tableValues[iterator1], node->value);
							strcpy(tableValues[iterator1 + 1], "__END__");
							break;
						/*
						case END_BIT :
							commandList = CleanCommand(commandList);
							break;
						case ERROR_BIT :
							PrintError();
							break;
						case DEBUG_BIT:
							debug = 1;
							controlVar = END_BIT;
							break;
						*/
						default :
							break;
					}
				}
				free(node);
				if(controlVar == DEBUG_BIT){
					debug = 1;
					// controlVar = END_BIT;
				}
				if(controlVar == ERROR_BIT){
					PrintError();
					controlVar = END_BIT;
				}
				if(controlVar == END_BIT){
					commandList = CleanCommand(commandList);
				}
			}
		}
		else if(strcmp(node->value, "modify") == 0){
			strcpy(action, node->value);
			free(node);
		}
		else if(strcmp(node->value, "quit") == 0){
			strcpy(action, node->value);
			free(node);
		}
		else{
			PrintError();
			strcpy(action, node->value);
			free(node);
		}

		if(noColor == false){
			StdoutColorWhite();
		}
		if(noPrint == false && noCommandPrint == false){
			ClearTerminal();
			PrintCommand(commandListCopy);
		}

		if(log){
			LogList(logFileName, commandListCopy); // issue because commandList is void at this point
			ClearCommand(commandListCopy);
			/*action[25];             // Contains the action to do with the data
			char inputFileName[100];
			char tableName[25][25];      // Contains the name of the table taken by the command
			char tableColumns[25][25]; // Contains all the arguments taken by the command
			char tableValues[25][25];*/
			LogString(logFileName, strcat(strcat(charBuffer, "Action : "), action));
			strcpy(charBuffer, "\0");
			LogString(logFileName, strcat(strcat(charBuffer, "Input file name : "), inputFileName));
			strcpy(charBuffer, "\0");
			LogString(logFileName, strcat(strcat(charBuffer, "Table name : "), tableName[0]));
			strcpy(charBuffer, "\0");
			LogString(logFileName, "Columns : ");
			LogData(logFileName, tableColumns);
			LogString(logFileName, "Values : ");
			LogData(logFileName, tableValues);
		}

		commandList = ClearCommand(commandList);

		/*
		Get all the data from the selected file
		*/

		/*
		Do all the necessary instructions to get the program done
		*/

		if(strcmp(action, "help") == 0){
			PrintHelp();
		}
		else if(strcmp(action, "print") == 0){
			tablesBrut = GetFileData(tablesBrut, inputFileName, inputModeVar);
			if(tablesBrut != NULL){
				if(strcmp(tableName[0], "__ALLTABLES__") == 0){
					tableBuffer = tablesBrut;
					table = tableBuffer; //
				}
				else{
					tableBuffer = GetTable(tablesBrut, tableName);
					if(tableBuffer != NULL){
						if(strcmp(tableColumns[0], "__ALLCOLUMNS__") == 0){
							table = tableBuffer; //
						}
						else{
							table = GetAssortedTable(tableBuffer, tableColumns); // FIX the issue of segmentation fault when a column does not exist
							if(table != NULL){
								//
							}
							else{
								noPrint = 1;
								printf("Error table arguments\n");
							}
						}
					}
					else{
						noPrint = 1;
						printf("Error table name\n");
					}
				}
			}
			else{
				noPrint = 1;
				printf("Error input file name\n");
			}
			if(table != NULL){
				if(noPrint == false){
					switch(outputModeVar){
						case GRAPHIC_MODE_BIT :
							PrintGraphicTable(table, stdout, noColor);
							break;
						case CSV_SEMICOLON_MODE_BIT :
							PrintCsvTable(table, stdout, ';');
							break;
						case CSV_COMMA_MODE_BIT :
							PrintCsvTable(table, stdout, ',');
							break;
						case XML_MODE_BIT :
							PrintXmlTable(table, stdout);
							break;
						default :
							PrintGraphicTable(table, stdout, noColor);
							break;
					}
				}
				if(strcmp(outputFileName, "\0") != 0){
					SetFileData(table, outputFileName, outputModeVar);
				}
				if(log){
					LogTable(logFileName, table, outputModeVar);
				}
				if(debug){
					ToPrint(action, tableName, tableColumns, table);
				}
			}
		}
		else if(strcmp(action, "create") == 0){
			if(outputModeVar == 0){
				outputModeVar = inputModeVar;
			}
			if(strcmp(outputFileName, "\0") == 0){
				strcpy(outputFileName, inputFileName);
			}

			if(strcmp(tableName[0], "__ALLTABLES__") == 0){
				tablesBrut = CreateFileData(outputFileName);
			}
			else if(strcmp(tableColumns[0], "__ALLCOLUMNS__") == 0){
				tablesBrut = GetFileData(tablesBrut, inputFileName, inputModeVar);
				tablesBrut = CreateFileTable(tablesBrut, tableName, inputModeVar);
				SetFileData(tablesBrut, outputFileName, outputModeVar);
			}
			else if(strcmp(tableValues[0], "__ALLVALUES__") == 0){
				tablesBrut = GetFileData(tablesBrut, inputFileName, inputModeVar);
				tableBuffer = GetTable(tablesBrut, tableName);
				tableBuffer = CreateFileTableColumn(tableBuffer, tableColumns, inputModeVar);
				tablesBrut = SetTable(tablesBrut, tableBuffer, inputModeVar);
				SetFileData(tablesBrut, outputFileName, outputModeVar);
			}
			else{
				iterator1 = 0;
				for(int i = 0; strcmp(tableColumns[i], "__END__") != 0; i++){
					iterator1++;
				}
				iterator2 = 0;
				for(int i = 0; strcmp(tableValues[i], "__END__") != 0; i++){
					iterator2++;
				}
				if(iterator1 != iterator2){
					PrintError();
				}
				else{
					tablesBrut = GetFileData(tablesBrut, inputFileName, inputModeVar);
					tableBuffer = GetTable(tablesBrut, tableName);
					tableBuffer = CreateFileTableLine(tableBuffer, tableColumns, tableValues, iterator1, inputModeVar);
					tablesBrut = SetTable(tablesBrut, tableBuffer, inputModeVar);
					SetFileData(tablesBrut, outputFileName, outputModeVar);
				}
			}
		}
		else if(strcmp(action, "quit") == 0){
			runProgram = 0;
		}
		else{
			printf("Code non-redige ou faux\n");
		}

		/*
		Free the allocated memory
		*/

		if(tablesBrut == NULL){

		}
		else if(table == tablesBrut){
			free(tablesBrut->cellWidth);
			tablesBrut = ClearTable(tablesBrut);
			tableBuffer = NULL;
			table = NULL;
		}
		else{
			if(table == tableBuffer){
				free(tablesBrut->cellWidth);
				tablesBrut = ClearTable(tablesBrut);
				if(tableBuffer != NULL){
					free(tableBuffer->cellWidth);
					tableBuffer = ClearTable(tableBuffer);
					table = NULL;
				}
			}
			else{
				free(tablesBrut->cellWidth);
				tablesBrut = ClearTable(tablesBrut);
				if(tableBuffer != NULL){
					free(tableBuffer->cellWidth);
					tableBuffer = ClearTable(tableBuffer);
				}
				if(table != NULL){
					free(table->cellWidth);
					table = ClearTable(table);
				}
			}
		}
	}
	// ClearTerminal();

	return 0;
}
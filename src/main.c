#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "../lib/command.h"
#include "../lib/fonctions.h"
#include "../lib/stdout_color.h"

#define VAL_BIT (1<<0)
#define ARG_BIT (1<<1)
#define TAB_BIT (1<<2)
#define FILE_BIT (1<<3)
#define ALL_BIT (1<<4)
#define ERROR_BIT (1<<5)
#define END_BIT (1<<6)
#define DEBUG_BIT (1<<7)
#define NOPRINT_BIT (1<<8)
#define LOG_BIT (1<<9)

#define LOG_ACCESS "./log/"

int main(int argc, char *argv[]){
	short runProgram = 1;
	struct timespec timestamp;
	struct tm *timestampStruct = NULL;
	char strTimestamp[40] = "\0";
	char logFileName[100] = "\0";
	StdoutColorWhite();

	char charBuffer[100] = "\0";
	
	command commandList = NewCommand();
	command commandListCopy = NewCommand();
	commandElement *node = NULL;

	int iterator1 = 0;
	int iterator2 = 0;
	char action[25];             // Contains the action to do with the data
	char fileName[100];
	char tableName[25][25];      // Contains the name of the table taken by the command
	char tableArguments[25][25]; // Contains all the arguments taken by the command
	char tableValues[25][25];
	char debug = 0;
	char noPrint = 0;
	char log = 0;
	unsigned int controlVar = 0;

	tableType tablesBrut = NewTable();  // The table that get all the file's data as value
	tableType tableBuffer = NewTable(); // The table that get the unsorted selected data from the file
	tableType table = NewTable();       // The table that get the selected data from the file

	if(argc == 1)
		PrintStart();

	while(runProgram){
		strcpy(tableName[0], "__ALLTABLES__");
		strcpy(tableName[1], "__END__");
		strcpy(tableArguments[0], "__ALLARGUMENTS__");
		strcpy(tableArguments[1], "__END__");
		strcpy(tableValues[0], "__ALLVALUES__");
		strcpy(tableValues[1], "__END__");
		debug = 0;
		noPrint = 0;
		log = 0;

		/*
		Get all the parameters to run the program
		*/

		if(argc > 1){
			for(int i = 1; i < argc; i++){
				commandList = ToRename(commandList, argv[i]);
			}
			runProgram = 0;
			noPrint = 1;
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

		#if defined(__linux__)
		system("clear");
		#elif defined(_WIN32) || defined(_WIN64)
		system("cls");
		#endif

		PrintCommand(commandList);

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
					if(strcmp(node->value, "--input") == 0 || strcmp(node->value, "-i") == 0){
						controlVar = FILE_BIT;
					}
					else if(strcmp(node->value, "--table") == 0 || strcmp(node->value, "-t") == 0){
						controlVar = TAB_BIT;
					}
					else if(strcmp(node->value, "--arguments") == 0 || strcmp(node->value, "--args") == 0 || strcmp(node->value, "-a") == 0){
						controlVar = ARG_BIT;
					}
					else if(strcmp(node->value, "--all") == 0){
						controlVar |= ALL_BIT;
					}
					else if(strcmp(node->value, "--debug") == 0 || strcmp(node->value, "-d") == 0){
						controlVar = DEBUG_BIT;
					}
					else if(strcmp(node->value, "--noprint") == 0 || strcmp(node->value, "-np") == 0){
						controlVar = NOPRINT_BIT;
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
						case FILE_BIT :
							strcpy(fileName, node->value);
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
						case ARG_BIT :
							iterator1 = 0;
							while(tableArguments[iterator1][0] != '_' || tableArguments[iterator1][1] != '_'){
								iterator1++;
							}
							strcpy(tableArguments[iterator1], node->value);
							strcpy(tableArguments[iterator1 + 1], "__END__");
							break;
						case ARG_BIT | ALL_BIT :
							strcpy(tableArguments[0], "__ALLARGUMENTS__");
							strcpy(tableArguments[1], "__END__");
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
				if(controlVar == NOPRINT_BIT){
					noPrint = 1;
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
					if(strcmp(node->value, "--input") == 0 || strcmp(node->value, "-i") == 0){
						controlVar = FILE_BIT;
					}
					else if(strcmp(node->value, "--table") == 0 || strcmp(node->value, "-t") == 0){
						controlVar = TAB_BIT;
					}
					else if(strcmp(node->value, "--arguments") == 0 || strcmp(node->value, "--args") == 0 || strcmp(node->value, "-a") == 0){
						controlVar = ARG_BIT;
					}
					else if(strcmp(node->value, "--values") == 0 || strcmp(node->value, "--vals") == 0 || strcmp(node->value, "-v") == 0){
						controlVar = VAL_BIT;
					}
					else if(strcmp(node->value, "--debug") == 0 || strcmp(node->value, "-d") == 0){
						controlVar = DEBUG_BIT;
					}
					else if(strcmp(node->value, "--noprint") == 0 || strcmp(node->value, "-np") == 0){
						controlVar = NOPRINT_BIT;
					}
					else if(strcmp(node->value, "--log") == 0 || strcmp(node->value, "-l") == 0){
						controlVar = NOPRINT_BIT;
					}
					else{
						controlVar = ERROR_BIT;
					}
				}
				else{
					switch(controlVar){
						case FILE_BIT :
							strcpy(fileName, node->value);
							break;
						case TAB_BIT :
							iterator1 = 0;
							while(tableName[iterator1][0] != '_' || tableName[iterator1][1] != '_'){
								iterator1++;
							}
							strcpy(tableName[iterator1], node->value);
							strcpy(tableName[iterator1 + 1], "__END__");
							break;
						case ARG_BIT :
							iterator1 = 0;
							while(tableArguments[iterator1][0] != '_' || tableArguments[iterator1][1] != '_'){
								iterator1++;
							}
							strcpy(tableArguments[iterator1], node->value);
							strcpy(tableArguments[iterator1 + 1], "__END__");
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
					controlVar = END_BIT;
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

		if(log){
			LogList(logFileName, commandListCopy); // issue because commandList is void at this point
			ClearCommand(commandListCopy);
			/*action[25];             // Contains the action to do with the data
			char fileName[100];
			char tableName[25][25];      // Contains the name of the table taken by the command
			char tableArguments[25][25]; // Contains all the arguments taken by the command
			char tableValues[25][25];*/
			LogString(logFileName, strcat(strcat(charBuffer, "Action : "), action));
			strcpy(charBuffer, "\0");
			LogString(logFileName, strcat(strcat(charBuffer, "File name : "), fileName));
			strcpy(charBuffer, "\0");
			LogString(logFileName, strcat(strcat(charBuffer, "Table name : "), tableName[0]));
			strcpy(charBuffer, "\0");
			LogString(logFileName, "Arguments : ");
			LogData(logFileName, tableArguments);
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
			tablesBrut = GetFileData(tablesBrut, fileName);
			if(strcmp(tableName[0], "__ALLTABLES__") == 0){
				tableBuffer = tablesBrut;
				table = tableBuffer;
				if(noPrint == false)
					PrintTable(table, stdout); //
				if(log){
					LogTable(logFileName, table);
				}
			}
			else{
				tableBuffer = GetTable(tablesBrut, tableName);
				if(tableBuffer != NULL){
					if(strcmp(tableArguments[0], "__ALLARGUMENTS__") == 0){
						table = tableBuffer;
						if(noPrint == false)
							PrintTable(table, stdout); //
						if(log){
							LogTable(logFileName, table);
						}
					}
					else{
						table = GetAssortedTable(tableBuffer, tableArguments);
						if(table != NULL){
							if(noPrint == false)
								PrintTable(table, stdout); //
							if(log){
								LogTable(logFileName, table);
							}
						}
						else{
							printf("Error table arguments\n");
						}
					}
				}
				else{
					printf("Error table name\n");
				}
			}
			if(debug){
				ToPrint(action, tableName, tableArguments, table);
			}
		}
		else if(strcmp(action, "create") == 0){
			if(strcmp(tableName[0], "__ALLTABLES__") == 0){
				tablesBrut = CreateFileData(fileName);
			}
			else if(strcmp(tableArguments[0], "__ALLARGUMENTS__") == 0){
				tablesBrut = GetFileData(tablesBrut, fileName);
				tablesBrut = CreateFileTable(tablesBrut, tableName);
				SetFileData(tablesBrut, fileName);
			}
			else if(strcmp(tableValues[0], "__ALLVALUES__") == 0){
				tablesBrut = GetFileData(tablesBrut, fileName);
				tableBuffer = GetTable(tablesBrut, tableName);
				tableBuffer = CreateFileTableColumn(tableBuffer, tableArguments);
				tablesBrut = SetTable(tablesBrut, tableBuffer);
				SetFileData(tablesBrut, fileName);
			}
			else{
				iterator1 = 0;
				for(int i = 0; strcmp(tableArguments[i], "__END__") != 0; i++){
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
					tablesBrut = GetFileData(tablesBrut, fileName);
					tableBuffer = GetTable(tablesBrut, tableName);
					tableBuffer = CreateFileTableLine(tableBuffer, tableArguments, tableValues, iterator1);
					tablesBrut = SetTable(tablesBrut, tableBuffer);
					SetFileData(tablesBrut, fileName);
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
	system("clear");

	return 0;
}
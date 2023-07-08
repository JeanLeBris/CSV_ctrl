#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/command.h"

#define COMMAND_CHAR_SIZE 255

command NewCommand(){
	return NULL;
}

int IsEmptyCommand(command commandList){
	if(commandList == NULL)
		return 1;
	else
		return 0;
}

command PushBackCommand(command commandList, char *commandInput){
	int i = 0;
	while(commandInput[i] != '\0'){
		commandElement *node = malloc(sizeof(commandElement));

		node->back = NULL;
		node->next = NULL;
		int j = 0;
		
		while(commandInput[i] != ' ' && commandInput[i] != '\0'){
			if(commandInput[i] < 32);
			else{
				node->value[j] = commandInput[i];
				j++;
			}
			i++;
		}
		if(commandInput[i] == ' ' || commandInput[i] == '\0'){
			node->value[j] = '\0';
			i++;
		}

		if(IsEmptyCommand(commandList)){
			commandList = malloc(sizeof(*commandList));

			commandList->lenght = 0;
			commandList->begin = node;
			commandList->end = node;
		}
		else{
			commandList->end->next = node;
			node->back = commandList->end;
			commandList->end = node;
		}

		commandList->lenght++;
	}

	return commandList;
}

command CleanCommand(command commandList){
	commandElement *buffer = NULL;
	commandList->begin = NULL;
	while(commandList->lenght > 1){
		buffer = commandList->end;
		commandList->end = commandList->end->back;
		commandList->end->next = NULL;
		buffer->back = NULL;
		commandList->lenght--;
		ClearCommandElement(buffer);
	}
	if(commandList->lenght == 1){
		ClearCommandElement(commandList->end);
		commandList->end = NULL;
		commandList->lenght--;
	}
	return commandList;
}

command ClearCommand(command commandList){
	free(CleanCommand(commandList));
	return NULL;
}

void PrintCommand(command commandList){
	commandElement *node = commandList->begin;

	printf(">>> ");
	while(node != NULL){
		printf("%s ", node->value);
		node = node->next;
	}
	printf("\n");
	printf("size : %d", commandList->lenght);
	printf("\n\n");
}

command InputCommand(){
	char entry[COMMAND_CHAR_SIZE];
	command commandList = NewCommand();

	printf("\n>>> ");
	fgets(entry, COMMAND_CHAR_SIZE, stdin);
	entry[strlen(entry) - 1] = '\0';
	commandList = PushBackCommand(commandList, entry);

	return commandList;
}

commandElement* PullFrontCommand(command commandList){
	commandElement *node = NULL;
	if(IsEmptyCommand(commandList) || commandList->lenght == 0){
		node = NULL;
	}
	else if(commandList->begin == commandList->end){
		node = commandList->begin;
		commandList->begin = NULL;
		commandList->end = NULL;
		commandList->lenght = 0;
	}
	else{
		node = commandList->begin;
		commandList->begin = commandList->begin->next;
		commandList->begin->back = NULL;
		node->next = NULL;
		commandList->lenght--;
	}
	return node;
}

void ClearCommandElement(commandElement *node){
	free(node);
}
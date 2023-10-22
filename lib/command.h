#ifndef __COMMAND__

#define __COMMAND__

typedef struct commandElement{
	char value[100];

	struct commandElement *back;
	struct commandElement *next;
}commandElement;

typedef struct command{
	int lenght;

	struct commandElement *begin;
	struct commandElement *end;
}*command;

command NewCommand();
int IsEmptyCommand(command commandList);
command PushBackCommand(command commandList, char *value);
command PushBackCommandByMultiple(command commandList, char *commandInput);
command CleanCommand(command commandList);
command ClearCommand(command commandList);
void PrintCommand(command commandList);
command InputCommand();
commandElement* PullFrontCommand(command commandList);
commandElement* GetCommandElement(command commandList, int index);
void ClearCommandElement(commandElement *node);

command CopyCommand(command commandList);

#endif
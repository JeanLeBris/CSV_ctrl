# CSV_ctrl

## Explainations

This repository is a small personal project to train in C programming
This project was originally made for Windows, so it may not work on Linux and Mac distributions

## How to install

All you have to do to install this program is to :
  1. clone the project in a folder by running the 'git clone https://github.com/JeanLeBris/CSV_ctrl.git' command
  2. launch the makefile by running the 'make exe' command to get the executable program or,
     launch the makefile by running the 'make debug' command to get the debuggable program
	3. add the executable directory to the PATH to use the program more efficiently

## How to use it

Make sure to put the csv files you want to read in the doc folder in the main directory (may be changed in future versions)

### print : Print a table

print [--input | -i] [input file]
	Print a full csv file

print [--input | -i] [input file] [--table | -t] [--all | -a | table name]
	Print all the tables from a csv file or a single table

print [--input | -i] [input file] [--table | -t] [table name] [--columns | --cols | -c] [--all | -a | column1, column2, ...]
	Print all the columns from a table of a csv file or print only the selected columns

print [parameters] [--output | -o] [output file]
	Save the generated table in an output file

print [parameters] [--output_mode | -om] [graphic | csv]
	Allow to choose the output format of the generated table
	The default format of a generated table on stdout output is graphic
	The default format of a generated table saved using the '-o' argument is csv

print [parameters] [--debug | -d]
	Print additional informations about the selected table

print [parameters] [--no_print | -np] 
	Disable the printing in the terminal

print [parameters] [--no_command_print | -ncp] 
	Disable the printing of the entered command in the terminal (print only the generated table)

print [parameters] [--no_color | -nc] 
	Disable the printing of the colors in the terminal

print [parameters] [--log | -l]
	Enable the save of the process in the log files

### create : Create or add new data

create [--input | -i] [input file]
	Create a new csv file

create [--input | -i] [input file] [--table | -t] [table name]
	Create a new table in the csv file

create [--input | -i] [input file] [--table | -t] [table name] [--columns | --cols | -c] [column1, column2, ...]
	Create new columns in the selected table from the csv file

create [--input | -i] [input file] [--table | -t] [table name] [--columns | --cols | -c] [column1, column2, ...] [--values | --vals | -v] [value1, value2, ...]
	Create a new line in the selected table from the csv file, attributing each value to its column

### modify : Modify a table

quit : Exit the program

help : Open the help

For more informations on how to use the program, please read fics/help.txt

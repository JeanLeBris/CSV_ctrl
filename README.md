# CSV_ctrl

![Capture 7](https://github.com/JeanLeBris/CSV_ctrl/assets/56840109/80023956-d5de-4b90-9f16-176a42cb4f6e)

## Explainations

This repository is a small personal project to train in C programming

This project was originally made for Windows and Linux distributions, so it may have unexpected results on MacOS

This project being a personal project, I update it on my free time, and a few bugs and issues may subsist

## How to install

All you have to do to install this program is to :
  1. clone the project in a folder by running the 'git clone https://github.com/JeanLeBris/CSV_ctrl.git' command
  2. run the makefile by running the 'make exe' command to get the executable program
  3. add the executable directory to the PATH to use the program more efficiently

To get a debuggable version of this program, you have to follow those instructions :
  1. run the makefile by running the 'make debug' command to get the debuggable program

To delete 'unnecessary' files, you have to follow those instructions :
  1. run the makefile by running the 'make clean' command to delete the object files

To delete all but the strict minimum files (the files on the git repository), you have to follow those instructions :
  1. run the makefile by running the 'make clear' command to keep only the original files

## How to use it

Each of the following commands can be used as command line arguments when calling the program to do the same process by respecting the following syntax :
	CSV_ctrl [command]

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

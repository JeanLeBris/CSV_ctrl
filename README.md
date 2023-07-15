# CSV_Controller

## Explainations

This repository is a small personal project to train in C programming
This project was originally made for Windows, so it may not work on Linux and Mac distributions

## How to install

All you have to do to install this program is to :
  1. clone the project in a folder by running the 'git clone https://github.com/JeanLeBris/CSV_Controller.git' command
  2. launch the makefile by running the 'make exe' command to get the executable program or,
     launch the makefile by running the 'make debug' command to get the debuggable program

## How to use it

Make sure to put the csv files you want to read in the doc folder in the main directory (may be changed in future versions)

print : Permet d'afficher les tableaux

        -file or -f [nom du fichier] : Argument permettant d'entrer le nom du fichier dont nous afficherons les données ou un tableau

        -table or -t [nom du tableau] : Argument permettant d'entrer le nom du tableau dont nous afficherons le contenu
        -table -all : Argument permettant d'entrer le nom du tableau dont nous afficherons le contenu

        -arguments or -args or -a [argument1, argument2, ...] : Argument permettant d'entrer les arguments dont nous afficherons le contenu
        -arguments -all : Argument permettant de choisir d'afficher tous les arguments du tableau

        -debug or -d : Argument permettant de choisir d'afficher les informations complémentaires du tableau

create : Permet de créer un tableau ou un fichier

        -file or -f [nom du fichier] : Argument permettant d'entrer le nom du fichier que nous créerons

        -table or -t [nom du tableau] : Argument permettant d'entrer le nom du tableau que nous créerons

        -arguments or -args or -a [nom des colonnes] : Argument permettant d'entrer le(s) nom(s) des colonnes que nous créerons

        -values or -vals or -v [nom des éléments] : Argument permettant d'entrer le(s) contenu(s) de la ligne que nous créerons

modify : Permet de modifier un tableau

quit : Permet de quitter le programme

help : Permet d'ouvrir l'aide du programme

For more informations on how to use the program, please read fics/help.txt

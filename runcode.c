#include <stdio.h>
#include <stdlib.h>

int main(){
    remove ("start");
    system("gcc main.c systemadmin.c pgadmin.c students.c profilemanage.c lecturer.c -o start");
    system("./start");
}



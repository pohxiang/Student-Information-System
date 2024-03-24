#ifndef pgadmin_h
#define pgadmin_h
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>


// Function Prototype
int menuProgrammeAdmin();
void createcourse();
void viewCourse();
void courseDelete();
int courseMenu();
void enrolstudent();
void enrollecturer();
void viewstudentprofile();

#define maxintakecode 30
#define maxcourseperintake 10
#define maxmodulename 100
#define courseinfosize 1000


#endif
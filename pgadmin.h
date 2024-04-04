#ifndef pgadmin_h
#define pgadmin_h
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Function Prototype
int menuProgrammeAdmin();
void createCourse();
void viewCourse();
void courseDelete();
int courseMenu();
void enrolstudent();
void enroltocoursemark(char *name, char *intakecode, int studentid);
void viewstudentprofile();
bool checkavailabilityofcourse(char *intakecode);

#define maxintakecode 30
#define maxcourseperintake 10
#define maxmodulename 100
#define courseinfosize 1000


#endif
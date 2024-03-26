#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "structs.h"


#define Max_students 100
#define Num_courses 5
#define FILENAME_ATTENDANCE "Attendance.txt"
#define FILENAME_MARKS "coursemark.txt"

void printLecturerMenu(struct StudentLect students[], int studentCount);
void readAttendance(struct StudentLect students[], int *studentCount);
void printAttendance(struct StudentLect students[], int *studentCount);
void updateAttendance(struct StudentLect students[], int studentCount);
void calcAttendance(struct StudentLect students[], int studentCount);
void checkMarks(const char* filename);
void readMarks(const char* filename, struct StudentLect students[], int *studentCount);
void updateMarks(struct StudentLect students[], int studentCount);

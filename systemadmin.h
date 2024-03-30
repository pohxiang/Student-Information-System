#ifndef systemadmin_h
#define systemadmin_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define MAXSIZE 100
#define MAX_PASSWORD_LENGTH 20

// Enumeration to represent user types
typedef enum {
    STUDENT,
    SYSTEM_ADMIN,
    LECTURER,
    PROGRAMME_ADMIN
} UserType;

// Structure to hold user data
typedef struct {
    int id;
    char name[50];
    char password[MAX_PASSWORD_LENGTH];
    double average;
    UserType type;
} User;


typedef struct {
    int student_id;
    char name[50];
    char course[5][20]; // Assuming each student has 5 modules
    float module_marks[5]; // Assuming each student has marks for 5 modules
    char module_grades[5]; // Corresponding grades for each module
    float cgpa;
} Student;

typedef struct {
    char grade;
    float grade_point;
} GradeScale;

// Function prototypes

#endif 

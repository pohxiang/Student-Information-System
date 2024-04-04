#ifndef systemadmin_h
#define systemadmin_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void displayMainMenu();
void addUser(User users[], int *size);
void removeUser(User users[], int *size);
void searchForUser();
void uploadDataFile(User users[], int *size);
void updateDataFile(User users[], int size);
void printUsers();
const char* userTypeToString(UserType type);
void changeGradeDefinition();
void storeGradeDefinition(int gradeDef[100], int size);
void readStudentMarksFile(const char* filename, Student students[], int *studentCount);
void calculate_student_performance(Student *student, int num_modules);
void display_leaderboard(Student students[], int num_students);
void studentgeneratereport();
char calculate_grade(float marks);
void searchAndPrintStudentByID(Student students[], int num_students, int searchID);
bool searchStudentID(Student students[], int num_students, int targetID);
float calculate_cgpa(float module_gpa[], int num_modules);
bool isExistingID(User users[], int size, int id);
void loadUsersFromFile(User users[], int *size) ;
#endif 
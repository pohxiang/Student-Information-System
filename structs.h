#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define Num_courses 5

struct logindetails{
  char line[200];
  char username[50];
  char password[50];
  int type;
};

struct studentprofile{
  char name[100];
  char intakecode[50];
  char contactnumber[15];
  char email[100];
  int studentid;
};

struct Student 
{
    char name[50];
    int id;
    char date[15];
    char course[20];
    int attendance;
    int totalClass;
};


struct lecturerprofile{
  char name[50];
  char enrolledcourse[50];
  char contactnumber[100];
  char email[100];
  int lecturerid;
};


struct StudentLect
{
    char name[50];
    int id;
    char date[15];
    char course[20];
    int attendance;  
    int totalClass;
    char modules[Num_courses][20];
    float marks[Num_courses];
};


struct Course
{
    char intakeCode[20];
    char module1[20];
    char module2[20];
    char module3[20];
    char module4[20];
    char module5[20];
};

struct AttendanceRecord {
        char course[50];
        char date[20];
        int attendance;
        int totalClass;
    };

struct marktograde{
  char grade[5];
  float gpa[5];
  float overallcgpa;
};



// admin

typedef enum {
    STUDENT,
    SYSTEM_ADMIN,
    LECTURER,
    PROGRAMME_ADMIN
} UserType;

// Structure to hold user data

#define MAX_PASSWORD_LENGTH 20

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



// Function Prototype
// clear screen


//Lecture
void printLecturerMenu(struct StudentLect students[], int studentCount);
void readAttendance(struct StudentLect students[], int *studentCount);
void printAttendance(struct StudentLect students[], int *studentCount);
void updateAttendance(struct StudentLect students[], int studentCount);
void calcAttendance(struct StudentLect students[], int studentCount);
void checkMarks(struct StudentLect students[], int *studentCount);
void readMarks(struct StudentLect students[], int *studentCount);
void updateMarks(struct StudentLect students[], int studentCount);


// Student
void viewprofileStudent(int id);
void menustudentupdatedata(int id);
void updatecontactnumstu(int id);
void updatemailstu(int id);
void viewenrolledcoursestudent(int id);
void viewattendance(int id);
void viewselfresult(int id);

//pg admin
int menuProgrammeAdmin();
void createCourse();
void viewCourse();
void courseDelete();
int courseMenu();
void enrolstudent();
void enrollecturer();
void enroltocoursemark(char *name, char *intakecode, int studentid);
void viewstudentprofile();
bool checkavailabilityofcourse(char *intakecode);
void enroltoattendance(char *name, int studentid, char * intakecode);


//main 
bool filecheck();
int login();
int menuProgrammeAdmin();
void loginmenu();
void clearscreen();

// Profile Manage
void studentprofilecreate(int id, char name[]);
void lecturerprofilecreate(int id, char name[]);
void removeStudentProfile(int id);
void removeLecturerProfile(int id);



// System Admin
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
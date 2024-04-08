#ifndef STRUCTS_H
#define STRUCTS_H

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



#endif
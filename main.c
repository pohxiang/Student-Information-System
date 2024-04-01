//  library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

//  header files
#include "structs.h"
#include "systemadmin.h"
#include "pgadmin.h"
#include "lecturer.h"
#include "students.h"

//  limits
#define MAXSIZE 100
#define MAX_PASSWORD_LENGTH 20

// secret login dont tell anyone ah
#define secretusername "root"
#define secretpassword "admin123"

// file path
#define fileCredentials "users.txt"
#define fileCourse "course.txt"
#define fileStudent "studentfile.txt"
#define fileAttendance "Attendance.txt"
#define fileLecturer "lecturerfile.txt"
#define fileCourseMark "coursemark.txt"
#define fileGradeDefinition "gradeDefinition.txt"

// Clear Screen
void clearscreen(){printf("\033[2J\033[1;1H");}
//void clearscreen(){system("clear");}

void displayMainMenu(void);

// File Checking
bool filecheck(){
    FILE *credfile = fopen(fileCredentials, "r");
    FILE *coursefile = fopen(fileCourse, "r");
    FILE *studentfile = fopen(fileStudent, "r");
    FILE *attendancefile = fopen(fileAttendance, "r");
    FILE *lecturerfile = fopen(fileLecturer,"r");
    FILE *coursemarkfile = fopen(fileCourseMark,"r");\
    FILE *gradedefinitionfile = fopen(fileGradeDefinition,"r");
    bool is_exist = false;
    if (credfile == NULL){printf("Users file not found\n"); printf("Creating new file\n");credfile = fopen(fileCredentials, "w");fclose(credfile);}
    else{is_exist = true;}
    if (coursefile == NULL){printf("Course file not found\n");printf("Creating new file\n"); coursefile = fopen(fileCourse, "w"); fclose(coursefile);}
    else{is_exist = true;}
    if (studentfile == NULL){printf("Student file not found\n"); printf("Creating new file\n"); studentfile = fopen(fileStudent, "w");fclose(studentfile);}
    else{is_exist = true;}
    if (attendancefile == NULL){printf("Attendance file not found\n"); printf("Creating new file\n"); attendancefile = fopen(fileAttendance, "w");fclose(attendancefile);}
    else{is_exist = true;}
    if (lecturerfile == NULL){printf("Lecturer file not found\n"); printf("Creating new file\n"); lecturerfile = fopen(fileAttendance, "w");fclose(lecturerfile);}
    else{is_exist = true;}
    if (coursemarkfile == NULL){printf("Course Mark file not found\n"); printf("Creating new file\n"); coursemarkfile = fopen(fileCourseMark, "w");fclose(coursemarkfile);}
    else{is_exist = true;}
    if (gradedefinitionfile == NULL){printf("Grade Definition file not found\n"); printf("Creating new file\n"); gradedefinitionfile = fopen(fileGradeDefinition, "w");fclose(gradedefinitionfile);}
    else{is_exist = true;}
    return is_exist; 
}

// Login Function
int login(){
    struct Student students[100];
    struct logindetails logindetails;
    FILE *usercred = fopen(fileCredentials, "r");
    int i=0;int studentcount = 0;
    // Clear buffer
    while (getchar() != '\n');

    // check the file bujian or not
    if (usercred == NULL){printf("File not found\n");return 0;}

    // take username and pass input
    printf("UserID: ");scanf("%s", logindetails.username);
    printf("Password: ");scanf("%s", logindetails.password);

    // check for secret login there or not lah
    if (strcmp(logindetails.username, secretusername) == 0 && strcmp(logindetails.password, secretpassword) == 0){clearscreen();printf("Bypass to system admin menu\n");displayMainMenu();fclose(usercred);return 0;}
        
    //split then compare 9 them
    while (fgets(logindetails.line, sizeof(logindetails.line), usercred)) {
        char *values[4];
        char *token = strtok(logindetails.line, " ");
        i = 0;
        while (token != NULL && i < 4) {
            values[i++] = token;
            token = strtok(NULL, " ");
        }

        if (i == 4) {
            char *storedid = values[0];
            char *storedpass = values[2];
            char *storedtype = values[3];

            if (strcmp(logindetails.username, storedid) == 0 && strcmp(logindetails.password, storedpass) == 0) {
                clearscreen();
                logindetails.type = atoi(storedtype);
                int id = atoi(logindetails.username);
                fclose(usercred);
                switch(logindetails.type){
                    case 0:
                    viewprofileStudent(id);break;
                    case 1:
                    displayMainMenu();break;
                    case 2:
                    const char* filename = fileCourseMark;
                    struct StudentLect students[100];
                    int studentcount = 0;
                    int choice = 0;
                    printLecturerMenu(students,studentcount);break;
                    case 3:
                    menuProgrammeAdmin();break;}
                fclose(usercred);

                return 0;}}}fclose(usercred);printf("Login Failed");return 0;}



// Login Menu 
void loginmenu() {
    int choice;
    while (1){
        clearscreen();
        printf("===============================================\n");
        printf("|            STUDENT INFORMATION SYSTEM       |\n");
        printf("===============================================\n");
        printf("| 1. Login                                    |\n");     
        printf("| 2. Quit Application                         |\n");
        printf("===============================================\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice. Please try again.\n\n");
            clearscreen();
            while (getchar() != '\n');
        } else {
            switch (choice) {
                case 1:login();break;
                case 2:printf("Goodbye!\n");sleep(2);clearscreen();remove("systeman");exit(0);break;      
            }
        }
    }
}




int main(){
    clearscreen();
    filecheck();
    if (filecheck() == false){printf("File not found corrupted\n");}
    loginmenu();
    return 0;
}


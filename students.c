#include "main.h"
#include "structs.h"
#include "systemadmin.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Function Prototype
void viewprofileStudent(int id);
void menustudentupdatedata(int id);
void updatecontactnumstu(int id);
void updatemailstu(int id);
void viewenrolledcoursestudent(int id);
void viewattendance(int id);
void viewselfresult(int id);



void viewprofileStudent(int id) {
    struct studentprofile studentprofile;
    FILE *studentfile = fopen("studentfile.txt", "r");
    
    while (fscanf(studentfile, "%d%s%s%s%s", &studentprofile.studentid, studentprofile.name, studentprofile.intakecode, studentprofile.contactnumber, studentprofile.email) != EOF) {

        if (id == studentprofile.studentid) {
            printf("\n+----------------------------------------------+\n");
            printf("|               Overview                       |\n");
            printf("+----------------------------------------------+\n");
            printf("| Name           : %-28s|\n", studentprofile.name);
            printf("| Student ID     : %-28d|\n", studentprofile.studentid);
            printf("| Intake Code    : %-28s|\n", studentprofile.intakecode);
            printf("| Contact Number : %-28s|\n", studentprofile.contactnumber);
            printf("| Email          : %-28s|\n", studentprofile.email);
            printf("+----------------------------------------------+\n");
            printf("| 1. View Attendace                            |\n");
            printf("| 2. View Enrolled Module                      |\n");
            printf("| 3. View Results                              |\n");
            printf("| 4. Update Personal Details                   |\n");
            printf("| 5. Exit                                      |\n");
            printf("+----------------------------------------------+\n");

            int choice;
            printf("Enter your choice: ");
            if(scanf("%d", &choice) != 1) {
                printf("Invalid input\n");
                while (getchar() != '\n');
                continue;
            }
            switch (choice){
                case 1:clearscreen();viewattendance(id);break;
                case 2:clearscreen();viewenrolledcoursestudent(id);break;
                case 3:clearscreen();viewselfresult(id);break;
                case 4:clearscreen();menustudentupdatedata(id);break;
                case 5:clearscreen();loginmenu();
            }
        }
    }
}

void menustudentupdatedata(int id) {
    int choice;
    printf("+----------------------------------------------+\n");
    printf("|               Update Data                    |\n");
    printf("+----------------------------------------------+\n");
    printf("| 1. Update Contact Number                     |\n");
    printf("| 2. Update Email                              |\n");
    printf("| 3. Back                                      |\n");
    printf("+----------------------------------------------+\n");
    printf("Enter your choice: ");
    if(scanf("%d", &choice) != 1) {
        printf("Invalid input\n");
        while (getchar() != '\n');
        return;
    }
    switch (choice){
        case 1:updatecontactnumstu(id);break;
        case 2:updatemailstu(id);break;
        case 3:viewprofileStudent(id);break;
    }
}

void updatecontactnumstu(int id) {
    struct studentprofile studentprofile;
    FILE *f = fopen("studentfile.txt", "r");
    FILE *ft = fopen("temp.txt", "w");
    int found = 0;
    char choice;

    if (f == NULL || ft == NULL) {printf("Error opening files.\n");return;}

    while (fscanf(f, "%d%s%s%s%s", &studentprofile.studentid, studentprofile.name, studentprofile.intakecode, studentprofile.contactnumber, studentprofile.email) != EOF) {
        if (id == studentprofile.studentid) {
            found = 1;
            printf("Your current contact number is: %s\n", studentprofile.contactnumber);
            printf("Do you want to change your contact number (y/n): ");
            if (scanf(" %c", &choice) != 1) {
                printf("Invalid choice. Please try again.\n\n");
                
                continue;
            }
            if (choice == 'y') {
                printf("Enter new contact number: ");
                scanf("%s", studentprofile.contactnumber);
            }
        }
        fprintf(ft, "%d %s %s %s %s\n", studentprofile.studentid, studentprofile.name, studentprofile.intakecode, studentprofile.contactnumber, studentprofile.email);
    }
    fclose(f);fclose(ft);
    if (!found) {printf("Student ID not found.\n");remove("temp.txt");}
    else {remove("studentfile.txt");rename("temp.txt", "studentfile.txt");printf("Contact number updated successfully.\n");}
}


void updatemailstu(int id){
    struct studentprofile studentprofile;
    FILE *f = fopen("studentfile.txt", "r");
    FILE *ft = fopen("temp.txt", "w");
    int found = 0;
    char choice;

    if (f == NULL || ft == NULL) {printf("Error opening files.\n");return;}

    while (fscanf(f, "%d%s%s%s%s", &studentprofile.studentid, studentprofile.name, studentprofile.intakecode, studentprofile.contactnumber, studentprofile.email) != EOF) {
        if (id == studentprofile.studentid) {
            found = 1;
            printf("Your current email is: %s\n", studentprofile.email);
            printf("Do you want to change your email (y/n): ");
            if (scanf(" %c", &choice) != 1) {printf("Invalid choice. Please try again.\n\n");}
            if (choice == 'y') {printf("Enter new email: ");scanf("%s", studentprofile.email);}
        }
        fprintf(ft, "%d %s %s %s %s\n", studentprofile.studentid, studentprofile.name, studentprofile.intakecode, studentprofile.contactnumber, studentprofile.email);
    }
    fclose(f);fclose(ft);
    if (!found) {printf("Student ID not found.\n");remove("temp.txt");}
    else {remove("studentfile.txt");rename("temp.txt", "studentfile.txt");printf("Email updated successfully.\n");}
}


void viewenrolledcoursestudent(int id){
    struct studentprofile studentprofile;
    struct Course Course;
    FILE *studentfile = fopen("studentfile.txt", "r");
    FILE *coursefile = fopen("course.txt", "r");

    while (fscanf(studentfile, "%d%s%s%s%s", &studentprofile.studentid, studentprofile.name, studentprofile.intakecode, studentprofile.contactnumber, studentprofile.email) != EOF) {
        if (id == studentprofile.studentid) {
            while (fscanf(coursefile, "%s%s%s%s%s%s", Course.intakeCode, Course.module1, Course.module2, Course.module3, Course.module4, Course.module5) != EOF) {
                if (strcmp(studentprofile.intakecode, Course.intakeCode) == 0) {
                    printf("\n+----------------------------------------------+\n");
                    printf("| Enrolled Courses                             |\n");
                    printf("+----------------------------------------------+\n");
                    printf("| Module 1       : %-28s|\n", Course.module1);
                    printf("| Module 2       : %-28s|\n", Course.module2);
                    printf("| Module 3       : %-28s|\n", Course.module3);
                    printf("| Module 4       : %-28s|\n", Course.module4);
                    printf("| Module 5       : %-28s|\n", Course.module5);
                    printf("+----------------------------------------------+\n");
                }
            }
            printf("Do you want to return to previous menu? (y/n): ");
            char choice;
            if (scanf(" %c", &choice) != 1) {printf("Invalid choice. Please try again.\n\n");}
            else if (choice == 'y' ) {clearscreen();viewprofileStudent(id);}
            else if (choice == 'n' ) {clearscreen();viewenrolledcoursestudent(id);}
        }
    }
}





void viewselfresult(int id){
    struct StudentLect studentLect;
    struct studentprofile studentprofile;
    struct marktograde marktograde;
    int i;
    FILE *coursemarkfile = fopen("coursemark.txt", "r");
    FILE *studentfile = fopen("studentfile.txt", "r");

    if (coursemarkfile == NULL || studentfile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    // Convert the marks in coursemark.txt to grade
    while (fscanf(studentfile, "%d%s%s%s%s", &studentprofile.studentid, studentprofile.name, studentprofile.intakecode, studentprofile.contactnumber, studentprofile.email) != EOF) {
        if (id == studentprofile.studentid) {
            while (fscanf(coursemarkfile, "%d %s %s %s %s %s %s %f %f %f %f %f", &studentLect.id, studentLect.name, studentLect.modules[1],studentLect.modules[2], studentLect.modules[3], studentLect.modules[4], studentLect.modules[5], &studentLect.marks[1], &studentLect.marks[2], &studentLect.marks[3], &studentLect.marks[4], &studentLect.marks[5]) != EOF) {
                if (id == studentLect.id) {
                    for (int i = 0; i < 5; i++){
                        // copy it into marktograde struct
                        marktograde.grade[i] = calculate_grade(studentLect.marks[i+1]);
                        marktograde.overallcgpa = calculate_cgpa(marktograde.grade[i], 5);
                    }
                }
            }            
        }
    }

    printf("\n+----------------------------------------------+\n");
    printf("|               Results                        |\n");
    printf("+----------------------------------------------+\n");
    printf("| Module 1       : %-28s|\n", studentLect.modules[1]);
    printf("| Grade          : %-28s|\n", marktograde.grade[0]);
    printf("| Module 2       : %-28s|\n", studentLect.modules[2]);
    printf("| Grade          : %-28s|\n", marktograde.grade[1]);
    printf("| Module 3       : %-28s|\n", studentLect.modules[3]);
    printf("| Grade          : %-28s|\n", marktograde.grade[2]);
    printf("| Module 4       : %-28s|\n", studentLect.modules[4]);
    printf("| Grade          : %-28s|\n", marktograde.grade[3]);
    printf("| Module 5       : %-28s|\n", studentLect.modules[5]);
    printf("| Grade          : %-28s|\n", marktograde.grade[4]);
    printf("| Overall CGPA   : %-28.2f|\n", marktograde.overallcgpa);
    printf("+----------------------------------------------+\n");

}

void viewattendance(int id){
    FILE *attendancefile = fopen("Attendance.txt", "r");
    struct StudentLect studentLect;
    struct studentprofile studentprofile;
    if (attendancefile == NULL) {printf("Error opening files.\n");return;}
    struct AttendanceRecord attendanceRecords[100]; 
    int recordCount = 0; 
    
    while (fscanf(attendancefile, "%d%s%s%s%d%d", &studentLect.id, studentLect.name, studentLect.date, studentLect.course ,&studentLect.attendance, &studentLect.totalClass) != EOF) {
        if (id == studentLect.id) {
            strcpy(attendanceRecords[recordCount].course, studentLect.course);
            strcpy(attendanceRecords[recordCount].date, studentLect.date);
            attendanceRecords[recordCount].attendance = studentLect.attendance;
            attendanceRecords[recordCount].totalClass = studentLect.totalClass;
            recordCount++;
        }
    }
    
    if (recordCount == 0) {
        printf("No attendance records found for the given ID.\n");
    } else {
        printf("\n+----------------------------------------------+\n");
        printf("|               Attendance                     |\n");
        printf("+----------------------------------------------+\n");
        
        for (int i = 0; i < recordCount; i++) {
            printf("| Course         : %-28s|\n", attendanceRecords[i].course);
            printf("| Date           : %-28s|\n", attendanceRecords[i].date);
            printf("| Attendance     : %-28d|\n", attendanceRecords[i].attendance);
            printf("| Total Class    : %-28d|\n", attendanceRecords[i].totalClass);
            printf("+----------------------------------------------+\n");
        }
    }
    
    printf("Do you want to return to the previous menu? (y/n): ");
    char choice;
    if (scanf(" %c", &choice) != 1) {printf("Invalid choice. Please try again.\n\n");}
     else if (choice == 'y') {clearscreen();viewprofileStudent(id);}
     else if (choice == 'n') {viewattendance(id);}
    fclose(attendancefile);
}
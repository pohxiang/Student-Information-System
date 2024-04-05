#include "main.h"
#include "structs.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define maxintakecode 30
#define maxcourseperintake 10
#define maxmodulename 100
#define courseinfosize 1000

// Function Prototype
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



// Programme Admin Menu
int menuProgrammeAdmin(){
  int choice;
  clearscreen();
  while (1){
    printf("=======================================================\n");
    printf("|               Programme Admin Menu                  |\n");
    printf("=======================================================\n");
    printf("| 1. View Student Profile                             |\n");
    printf("| 2. Course Management & Enrolment                    |\n");
    printf("| 3. Exit System                                      |\n");
    printf("=======================================================\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1){
      printf("Please enter the option within the menu\n");
      while (getchar() != '\n');
      clearscreen();
      continue;}
    else{
      switch (choice){
        case 1:clearscreen();viewstudentprofile();break;
        case 2:clearscreen();courseMenu();break;
        case 3:printf("Goodbye!\n");clearscreen();loginmenu();}
    }
  }
}

void viewstudentprofile(){
  struct studentprofile studentprofile;
  int studentid;
  printf("Enter Student ID: ");scanf("%d", &studentid);
  FILE *mainstudentfile = fopen("studentfile.txt", "r");
  while (fscanf(mainstudentfile, "%d %s %s %s %s\n", &studentprofile.studentid, studentprofile.name, studentprofile.intakecode, studentprofile.contactnumber, studentprofile.email) != EOF){
    if (studentprofile.studentid == studentid){
      printf("\n+----------------------------------------------+\n");
      printf("|               Student Profile                  |\n");
      printf("+----------------------------------------------+\n");
      printf("| Name           : %-28s|\n", studentprofile.name);
      printf("| Student ID     : %-28d|\n", studentprofile.studentid);
      printf("| Intake Code    : %-28s|\n", studentprofile.intakecode);
      printf("| Contact Number : %-28s|\n", studentprofile.contactnumber);
      printf("| Email          : %-28s|\n", studentprofile.email);
      printf("+----------------------------------------------+\n");
      printf("\n");
      printf("Do you want to return to previous menu? (y/n): ");
      char choice;
      scanf(" %c", &choice);
      if (choice == 'y'){
        fclose(mainstudentfile);break;
      }
    }
  }
}


bool checkavailabilityofcourse(char *intakecode){
  struct Course course;
  FILE *maincoursefile = fopen("course.txt", "r");
  while (fscanf(maincoursefile, "%s %s %s %s %s %s\n", course.intakeCode, course.module1, course.module2, course.module3, course.module4, course.module5) != EOF){
    if (strcmp(course.intakeCode, intakecode) == 0){
      fclose(maincoursefile);
      return true;
    }
  }
  fclose(maincoursefile);
  return false;
}


void createCourse(){
  struct Course course;
  FILE *maincoursefile = fopen("course.txt", "a");
  printf("Enter Intake Code: ");scanf("%s", course.intakeCode);
  if (checkavailabilityofcourse(course.intakeCode) == true){
    printf("Course already exists\n");
  }
  else{
    printf("Enter Module 1: ");scanf("%s", course.module1);
    printf("Enter Module 2: ");scanf("%s", course.module2);
    printf("Enter Module 3: ");scanf("%s", course.module3);
    printf("Enter Module 4: ");scanf("%s", course.module4);
    printf("Enter Module 5: ");scanf("%s", course.module5);
    fprintf(maincoursefile, "%s %s %s %s %s %s\n", course.intakeCode, course.module1, course.module2, course.module3, course.module4, course.module5);
    fclose(maincoursefile);
    printf("Course added successfully\n");
  }
}


void updateCourse(){
  struct Course course;
  FILE *maincoursefile = fopen("course.txt", "r");
  FILE *tempcoursefile = fopen("temp.txt", "w");
  char intakeCode[10];
  printf("Enter Intake Code: ");
  scanf("%s", intakeCode);
  while (fscanf(maincoursefile, "%s %s %s %s %s %s\n", course.intakeCode, course.module1, course.module2, course.module3, course.module4, course.module5) != EOF){
    if (strcmp(course.intakeCode, intakeCode) == 0){
      printf("Enter Module 1: ");scanf("%s", course.module1);
      printf("Enter Module 2: ");scanf("%s", course.module2);
      printf("Enter Module 3: ");scanf("%s", course.module3);
      printf("Enter Module 4: ");scanf("%s", course.module4);
      printf("Enter Module 5: ");scanf("%s", course.module5);
      fprintf(tempcoursefile, "%s %s %s %s %s %s\n", course.intakeCode, course.module1, course.module2, course.module3, course.module4, course.module5);
    }
    else{
      fprintf(tempcoursefile, "%s %s %s %s %s %s\n", course.intakeCode, course.module1, course.module2, course.module3, course.module4, course.module5);
    }
  }
  fclose(maincoursefile);
  fclose(tempcoursefile);
  remove("course.txt");
  rename("temp.txt", "course.txt");
}

void viewCourse(){
  struct Course course;
  char intakecode[20];
  FILE *maincourse = fopen("course.txt", "r");
  
  printf("Please enter the intake code to view: ");
  scanf("%s", intakecode);
  
  while (fscanf(maincourse, "%s %s %s %s %s %s\n", course.intakeCode, course.module1, course.module2, course.module3, course.module4, course.module5 ) != EOF){
    if (strcmp(intakecode, course.intakeCode) == 0){
      printf("\n+=======================================+\n");
      printf("|Intake Code: %-26s|", course.intakeCode);
      printf("\n+=======================================+\n");
      printf("|Module 1   : %-26s|\n", course.module1);
      printf("|Module 2   : %-26s|\n", course.module2);
      printf("|Module 3   : %-26s|\n", course.module3);
      printf("|Module 4   : %-26s|\n", course.module4);
      printf("|Module 5   : %-26s|", course.module5);
      printf("\n========================================+\n");
      printf("\n");
      printf("Do you want to return to the previous menu? (y/n): ");
      char choice;
      scanf(" %c", &choice);
      if (choice == 'y'){
        fclose(maincourse);
        break;
      }
    }
  }
}


void courseDelete(){
  struct Course course;
  FILE *maincoursefile = fopen("course.txt", "r");
  FILE *tempcoursefile = fopen("temp.txt", "w");
  char intakeCode[10];
  printf("Enter Intake Code: ");
  scanf("%s", intakeCode);
  while (fscanf(maincoursefile, "%s %s %s %s %s %s\n", course.intakeCode, course.module1, course.module2, course.module3, course.module4, course.module5) != EOF){
    if (strcmp(course.intakeCode, intakeCode) == 0){
      continue;
    }
    else{
      fprintf(tempcoursefile, "%s %s %s %s %s %s\n", course.intakeCode, course.module1, course.module2, course.module3, course.module4, course.module5);
    }
  }
  fclose(maincoursefile);
  fclose(tempcoursefile);
  remove("course.txt");
  rename("temp.txt", "course.txt");
  printf("Course deleted successfully\n");

}




void enrolstudent(){
  int studentid;
  struct studentprofile student;

  printf("Enter Student ID: ");
  scanf("%d", &studentid);

  FILE *mainstudentfile = fopen("studentfile.txt", "r");
  if (mainstudentfile == NULL) {
    perror("Error opening studentfile.txt");
    return;
  }

  FILE *tempstudentfile = fopen("temp.txt", "w");
  if (tempstudentfile == NULL) {
    perror("Error opening temp.txt");
    fclose(mainstudentfile);
    return;
  }

  while (fscanf(mainstudentfile, "%d %s %s %s %s\n", &student.studentid, student.name, student.intakecode, student.contactnumber, student.email) == 5){
    if (student.studentid == studentid){
      printf("Enter Intake Code: ");
      scanf("%s", student.intakecode);
      fprintf(tempstudentfile, "%d %s %s %s %s\n", student.studentid, student.name, student.intakecode, student.contactnumber, student.email);
      enroltocoursemark(student.name, student.intakecode, student.studentid);
      enroltoattendance(student.name, student.studentid, student.intakecode);
    }
    else{
      fprintf(tempstudentfile, "%d %s %s %s %s\n", student.studentid, student.name, student.intakecode, student.contactnumber, student.email);
    }
  }
  fclose(mainstudentfile);
  fclose(tempstudentfile);

  if (remove("studentfile.txt") != 0) {
    perror("Error removing studentfile.txt");
    return;
  }

  if (rename("temp.txt", "studentfile.txt") != 0) {
    perror("Error renaming temp.txt to studentfile.txt");
    return;
  }

  printf("Student enrolled successfully\n");
}

void enroltocoursemark(char *name, char *intakecode, int studentid){
  struct Course course;

  FILE *maincoursefile = fopen("course.txt", "r");
  if (maincoursefile == NULL) {
    perror("Error opening course.txt");
    return;
  }

  FILE *coursemarkfile = fopen("coursemark.txt", "a");
  if (coursemarkfile == NULL) {
    perror("Error opening coursemark.txt");
    fclose(maincoursefile);
    return;
  }

  while (fscanf(maincoursefile, "%s %s %s %s %s %s\n", course.intakeCode, course.module1, course.module2, course.module3, course.module4, course.module5) == 6){
    if (strcmp(course.intakeCode, intakecode) == 0){
      fprintf(coursemarkfile, "%d %s %s %s %s %s %s %s %.2f %.2f %.2f %.2f %.2f\n", studentid, name, course.intakeCode, course.module1, course.module2, course.module3, course.module4, course.module5, 0.0, 0.0, 0.0, 0.0, 0.0);
    }
  }

  fclose(maincoursefile);
  fclose(coursemarkfile);
}

void enroltoattendance(char *name, int studentid, char *intakecode){
  struct StudentLect studentlect;
  struct Course course;
  int i;
  FILE *attendancefile = fopen("Attendance.txt", "a");
  FILE *maincoursefile = fopen("course.txt", "r");
  while(fscanf(maincoursefile, "%s %s %s %s %s %s\n", course.intakeCode, course.module1, course.module2, course.module3, course.module4, course.module5) == 6){
    if (strcmp(course.intakeCode, intakecode) == 0){
      char* modules[] = {course.module1, course.module2, course.module3, course.module4, course.module5};
      for (i = 0; i < Num_courses; i++){
        strcpy(studentlect.name, name);
        studentlect.id = studentid;
        strcpy(studentlect.date, "N/A");
        strcpy(studentlect.modules[i], modules[i]);
        studentlect.attendance = 0;
        studentlect.totalClass = 0;
        fprintf(attendancefile, "%d %s %s %s %d %d\n", studentlect.id, studentlect.name, studentlect.modules[i], studentlect.date, studentlect.attendance, studentlect.totalClass);
      }
    }
  }
  fclose(maincoursefile);
  fclose(attendancefile);
}



void enrollecturer(){
  struct lecturerprofile lecturer;
  int lecturerid;
  printf("Enter Lecturer ID to assign course: ");
  scanf("%d", &lecturerid);
  FILE *mainlecturerfile = fopen("lecturerfile.txt", "r");
  FILE *templecturerfile = fopen("temp.txt", "w");
  while (fscanf(mainlecturerfile, "%d %s %s %s %s\n", &lecturer.lecturerid, lecturer.name, lecturer.enrolledcourse, lecturer.contactnumber, lecturer.email) != EOF){
    if (lecturer.lecturerid == lecturerid){
      printf("Enter Course to assign: ");
      scanf("%s", lecturer.enrolledcourse);
      fprintf(templecturerfile, "%d %s %s %s %s\n", lecturer.lecturerid, lecturer.name, lecturer.enrolledcourse, lecturer.contactnumber, lecturer.email);
    }
    else{
      fprintf(templecturerfile, "%d %s %s %s %s\n", lecturer.lecturerid, lecturer.name, lecturer.enrolledcourse, lecturer.contactnumber, lecturer.email);
    }
  }
  fclose(mainlecturerfile);
  fclose(templecturerfile);
  remove("lecturerfile.txt");
  rename("temp.txt", "lecturerfile.txt");
  printf("Lecturer assigned to course successfully\n");
}



int courseMenu(){
  int choice;
  while (1){
    printf("=======================================================\n");
    printf("|          Course Management & Enrolment              |\n");
    printf("=======================================================\n");
    printf("| 1. Add Course                                       |\n");
    printf("| 2. Update Course                                    |\n");
    printf("| 3. Delete course                                    |\n");
    printf("| 4. View Course                                      |\n");
    printf("| 5. Enrol Course for Student                         |\n");
    printf("| 6. Enrol Course for Lecturer                        |\n");
    printf("| 7. Exit                                             |\n");
    printf("=======================================================\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1){
      printf("Please enter the option within the menu\n");
      while (getchar() != '\n');
      continue;}
    else{
      switch (choice){
        case 1:clearscreen();createCourse();break;
        case 2:clearscreen();updateCourse();break;
        case 3:clearscreen();courseDelete();break;
        case 4:clearscreen();viewCourse();break;
        case 5:clearscreen();enrolstudent();break;
        case 6:clearscreen();enrollecturer();return 0;
        case 7:clearscreen();menuProgrammeAdmin();return 0;
      }
    }
  }
}


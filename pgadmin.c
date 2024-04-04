#include "pgadmin.h"
#include "main.h"
#include "structs.h"

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
      fclose(maincoursefile);
      fclose (tempcoursefile);
      remove("course.txt");
      rename ("temp.txt", "course.txt");

    }
    else{
      fprintf(tempcoursefile, "%s %s %s %s %s %s\n", course.intakeCode, course.module1, course.module2, course.module3, course.module4, course.module5);
      fclose(maincoursefile);
      fclose(tempcoursefile);
      remove("course.txt");
      rename ("temp.txt", "course.txt");
    }
  }
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



void enrolstudnet(){
  struct studentprofile studentprofile;
  FILE *mainstudentfile = fopen("studentfile.txt", "w");
  int studentid; char intakecode[20];
  while (fscanf(mainstudentfile, "%d %s %s %s %s\n", &studentprofile.studentid, studentprofile.name, studentprofile.intakecode, studentprofile.contactnumber, studentprofile.email) != EOF){
    printf("Enter Student ID: ");scanf("%d", &studentid);
    printf("Enter Intake Code: ");scanf("%s", intakecode);
    fprintf(mainstudentfile, "%d %s %s %s %s\n", studentprofile.studentid, studentprofile.name, studentprofile.intakecode, studentprofile.contactnumber, studentprofile.email);
    fclose(mainstudentfile);
    printf("Student enrolled successfully\n");
  }
}

void enroltocoursemark(){

}


void enrollecturer(){

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
        case 5:clearscreen();enrolstudent();return 0;
        //case 6:clearscreen();enrollecturer();return 0;
        case 7:clearscreen();menuProgrammeAdmin();return 0;
      }
    }
  }
}


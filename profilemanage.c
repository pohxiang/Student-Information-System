#include "profilemanage.h"
#include "structs.h"
#include "systemadmin.h"
#define studentinfofile "studentfile.txt"
#define lecturerinfofile "lecturerfile.txt"


// get the student id and name which is returned from adding user in systemadmin file

void studentprofilecreate(int id, char name[]){
    struct studentprofile studentprofile;
    studentprofile.studentid = id;
    strcpy(studentprofile.name, name);
    strcpy(studentprofile.intakecode, "N/A");
    printf("Enter your contact number: ");
    scanf("%s", studentprofile.contactnumber);
    printf("Enter your email: ");
    scanf("%s", studentprofile.email);
    FILE *studentfile = fopen(studentinfofile, "a");
    fprintf(studentfile, "%d %s %s %s %s\n", studentprofile.studentid, studentprofile.name, studentprofile.intakecode, studentprofile.contactnumber, studentprofile.email);
    fclose(studentfile);
}


void lecturerprofilecreate(int id, char name[]){
    struct lecturerprofile lecturerprofile;
    lecturerprofile.lecturerid = id;
    strcpy(lecturerprofile.name, name);
    strcpy(lecturerprofile.enrolledcourse, "N/A");
    printf("Enter your contact number: ");
    scanf("%s", lecturerprofile.contactnumber);
    printf("Enter your email: ");
    scanf("%s", lecturerprofile.email);
    FILE *lecturerfile = fopen(lecturerinfofile, "a");
    fprintf(lecturerfile, "%d %s %s %s %s\n", lecturerprofile.lecturerid, lecturerprofile.name,lecturerprofile.enrolledcourse, lecturerprofile.contactnumber, lecturerprofile.email);
    fclose(lecturerfile);
}

void removeStudentProfile(int id){
    struct studentprofile studentprofile;
    FILE *f = fopen(studentinfofile, "r");
    FILE *ft = fopen("temp.txt", "w");
    int found = 0;
    if (f == NULL || ft == NULL) {
        printf("Error opening files.\n");
        return;
    }
    while (fscanf(f, "%d%s%s%s%s", &studentprofile.studentid, studentprofile.name, studentprofile.intakecode, studentprofile.contactnumber, studentprofile.email) != EOF) {
        if (id == studentprofile.studentid) {
            found = 1;
        } else {
            fprintf(ft, "%d %s %s %s %s\n", studentprofile.studentid, studentprofile.name, studentprofile.intakecode, studentprofile.contactnumber, studentprofile.email);
        }
    }
    fclose(f);
    fclose(ft);
    if (!found) {
        printf("Student ID not found.\n");
        remove("temp.txt");
    } else {
        remove(studentinfofile);
        rename("temp.txt", studentinfofile);
        printf("Student profile removed successfully.\n");
    }
}

// remove the lecturer profile when the user is removed from the systemadmin file
void removeLecturerProfile(int id){
    struct lecturerprofile lecturerprofile;
    FILE *f = fopen(lecturerinfofile, "r");
    FILE *ft = fopen("temp.txt", "w");
    int found = 0;
    if (f == NULL || ft == NULL) {
        printf("Error opening files.\n");
        return;
    }
    while (fscanf(f, "%d%s%s%s%s", &lecturerprofile.lecturerid, lecturerprofile.name, lecturerprofile.enrolledcourse, lecturerprofile.contactnumber, lecturerprofile.email) != EOF) {
        if (id == lecturerprofile.lecturerid) {
            found = 1;
        } else {
            fprintf(ft, "%d %s %s %s %s\n", lecturerprofile.lecturerid, lecturerprofile.name, lecturerprofile.enrolledcourse, lecturerprofile.contactnumber, lecturerprofile.email);
        }
    }
    fclose(f);
    fclose(ft);
    if (!found) {
        printf("Lecturer ID not found.\n");
        remove("temp.txt");
    } else {
        remove(lecturerinfofile);
        rename("temp.txt", lecturerinfofile);
        printf("Lecturer profile removed successfully.\n");
    }
}
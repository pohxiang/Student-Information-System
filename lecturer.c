#include "structs.h"
#define Max_students 100
#define Num_courses 5
#define FILENAME_ATTENDANCE "Attendance.txt"
#define FILENAME_MARKS "coursemark.txt"
 
void readAttendance(struct StudentLect students[], int *studentCount)
{
    FILE *file = fopen("Attendance.txt", "r");
 
    if (file == NULL)
    {
        printf("Error opening file %s...\n", "Attendance.txt");
        return;
    }
 
    *studentCount = 0;
    while(*studentCount < Max_students && fscanf(file, "%d %s %s %s %d %d", &students[*studentCount].id, students[*studentCount].name, students[*studentCount].date, students[*studentCount].course, &students[*studentCount].attendance, &students[*studentCount].totalClass) == 6)
    {
        (*studentCount)++;
    }
}
 
void printAttendance(struct StudentLect students[], int *studentCount)
{
    FILE *file = fopen("Attendance.txt","r");
 
    if (file == NULL)
    {
        printf("Eror opening file %s...\n", "Attendance.txt");
        return;
    }
 
    *studentCount = 0;
    while(*studentCount < Max_students && fscanf(file, "%d %s %s %s %d %d", &students[*studentCount].id, students[*studentCount].name, students[*studentCount].date, students[*studentCount].course, &students[*studentCount].attendance, &students[*studentCount].totalClass) == 6)
    {
        printf("%d %s %s %s %d %d\n", students[*studentCount].id, students[*studentCount].name, students[*studentCount].date, students[*studentCount].course, students[*studentCount].attendance, students[*studentCount].totalClass);
        (*studentCount)++;
       
    }
 
    fclose(file);
}
 
void updateAttendance(struct StudentLect students[], int studentCount)
{
    int studentID;
    char whichcourse[20];
    char newDate[15];
    int newAttendance;
 
    printAttendance(students, &studentCount);
 
    while (1)
    {
        int updated = 0;
 
        printf("Enter studentID to update (enter '-1' to stop): ");
        scanf("%d", &studentID);
 
        if (studentID == -1)
        {
            return;
        }
 
        printf("Enter the course to update: ");
        scanf("%s", whichcourse);
 
        for (int i = 0; i < studentCount; i++)
        {
            if (students[i].id == studentID && strcmp(students[i].course, whichcourse) == 0)
            {
                printf("Enter the new date (YYYY-MM-DD): ");
                scanf("%s", newDate);
 
                printf("Enter the new attendance: ");
                scanf("%d", &newAttendance);
 
                strcpy(students[i].date, newDate);
                students[i].attendance += newAttendance;
                students[i].totalClass++;
 
                updated = 1;
                printf("Student data updated successfully.\n");
                break;
            }
        }
 
        if (!updated)
        {
            printf("Students not found.\n");
        }
 
        FILE *file = fopen("Attendance.txt", "r+");
 
        if (file == NULL)
        {
            printf("Error opening file %s...\n", "Attendance.txt");
            return;
        }
 
        fseek(file, 0, SEEK_SET);
 
        for (int i = 0; i < studentCount; i++)
        {
            fprintf(file, "%d %s %s %s %d %d\n", students[i].id, students[i].name, students[i].date, students[i].course, students[i].attendance, students[i].totalClass);
        }
 
        fclose(file);
    }
}
 
void calcAttendance(struct StudentLect students[], int studentCount)
{
    int studentID;
    int foundStudent = 0;
 
    printf("Enter the ID of the student to show attendance: ");
    scanf("%d", &studentID);
 
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].id == studentID)
        {
            foundStudent = 1;
 
            float totalPercentage = 0.0;
            int numModules = 0;
 
            printf("Attendance for %s (ID: %d):\n", students[i].name, students[i].id);
 
            for (int j = 0; j < studentCount; j++)
            {
                if (students[j].id == studentID && students[j].totalClass > 0)
                {
                    float totalClass = students[j].totalClass;
                    float attendance = students[j].attendance;
                    float percentage = (attendance / totalClass) *100;
 
                    printf("   %-10s: %.2f%%\n", students[j].course, percentage);
 
                    totalPercentage += percentage;
                    numModules++;
                }
            }
 
            if (numModules > 0)
            {
                float averagePercentage = totalPercentage / numModules;
                printf("The average attendance percentage for %s: %.2f%%\n", students[i].name, averagePercentage);
 
            }
 
            else{
                printf("No modules found for the student.\n");
            }
 
            break;
        }
    }  
 
    if (!foundStudent)
    {
        printf("Student not found.\n");
    }    
}
 
void readMarks(struct StudentLect students[], int *studentCount)
{
    FILE *file = fopen("coursemark.txt", "r");
   
    if (file == NULL)
    {
        printf("Error opening file %s...\n","coursemark.txt");
        return;
    }
 
     while (fscanf(file, "%d", &students[*studentCount].id) == 1)
    {
        fscanf(file, "%s", students[*studentCount].name);
 
        for (int i = 0; i < Num_courses; i++)
        {
            fscanf(file, "%s",students[*studentCount].modules[i]);
        }
 
        for (int i = 0; i < Num_courses; i++)
        {
            fscanf(file, "%f", &students[*studentCount].marks[i]);
        }
 
        (*studentCount)++;
 
        if (*studentCount >= Max_students)
        {
            printf("Students Maxed. Please dont add more niggers, no space in cafeteria!!!\n");
            break;
        }
    }
 
}
 
void checkMarks(struct StudentLect students[], int *studentCount)
{
    FILE *file = fopen("coursemark.txt", "r");
 
    if (file == NULL)
    {
        printf("Error opening file %s...\n","coursemark.txt");
        return;
    }
   
   
    int searchID;
    int found = 0;
 
    printf("Enter student ID to check marks: ");
    scanf("%d", &searchID);
 
    while (fscanf(file, "%d", &students[*studentCount].id) == 1)
    {
        fscanf(file, "%s", students[*studentCount].name);
 
        for (int i = 0; i < Num_courses; i++)
        {
            fscanf(file, "%s",students[*studentCount].modules[i]);
        }
 
        for (int i = 0; i < Num_courses; i++)
        {
            fscanf(file, "%f", &students[*studentCount].marks[i]);
        }
 
        if(students[*studentCount].id == searchID)
        {
            printf("Student ID: %d\n", students[*studentCount].id);
            printf("Student Name: %s\n", students[*studentCount].name);
            printf("Courses and Marks:\n");
            for (int i = 0; i < Num_courses; i++)
            {
                printf("%-20s%.2f\n", students[*studentCount].modules[i], students[*studentCount].marks[i]);
            }
            printf("\n");
            found = 1;
            break;
        }
 
        (*studentCount)++;
       
        if (*studentCount >= Max_students)
        {
            printf("Students Maxed.\n");
            break;
        }
    }
 
    if (!found)
    {
        printf("Student with ID %d not found.\n",searchID);
    }
 
    fclose(file);
 
}
 
void updateMarks(struct StudentLect students[], int studentCount)
{
    int searchID;
    char whichmodule[20];
    float newmark;
 
    while (1)
    {
        FILE *file = fopen("coursemark.txt", "r+");
        FILE *tempFile = fopen("temp.txt", "w+");
 
        if (file == NULL || tempFile == NULL)
        {
            printf("Error opening file...\n");
            return;
        }
 
        printf("Enter student ID to update mark (Enter -1 to stop): ");
        scanf("%d", &searchID);
 
        if (searchID == -1)
        {
            fclose(file);
            fclose(tempFile);
            break; // Exit loop if user enters -1
        }
 
        int found = 0;
 
        while (fscanf(file, "%d", &students[studentCount].id) == 1)
        {
            fscanf(file, "%s", students[studentCount].name);
 
            for (int i = 0; i < Num_courses; i++)
            {
                fscanf(file, "%s", students[studentCount].modules[i]);
            }
 
            for (int i = 0; i < Num_courses; i++)
            {
                fscanf(file, "%f", &students[studentCount].marks[i]);
            }
 
            if (students[studentCount].id == searchID)
            {
                found = 1;
                printf("Enter the course: ");
                scanf("%s", whichmodule);
 
                int foundModule = -1;
                for (int i = 0; i < Num_courses; i++)
                {
                    if (strcmp(students[studentCount].modules[i], whichmodule) == 0)
                    {
                        foundModule = i;
                        break;
                    }
                }
 
                if (foundModule != -1)
                {
                    printf("Enter new marks: ");
                    while (scanf("%f", &newmark) != 1 || newmark < 0 || newmark > 100)
                    {
                        printf("Invalid input. Please enter valid mark: \n");
                        while (getchar() != '\n');
                    }
 
                    students[studentCount].marks[foundModule] = newmark;
                    printf("Marks for student ID %d in module %s updated successfully.\n", searchID, whichmodule);
                }
                else
                {
                    printf("Module not found for student ID %d.\n", searchID);
                }
            }
 
            fprintf(tempFile, "%d %s", students[studentCount].id, students[studentCount].name);
            for (int j = 0; j < Num_courses; j++)
            {
                fprintf(tempFile, " %s", students[studentCount].modules[j]);
            }
            for (int j = 0; j < Num_courses; j++)
            {
                fprintf(tempFile, " %.2f", students[studentCount].marks[j]);
            }
            fprintf(tempFile, "\n");
        }
 
        fclose(file);
        fclose(tempFile);
 
        remove("coursemark.txt");
        rename("temp.txt", "coursemark.txt");
 
        if (!found)
        {
            printf("Student ID %d not found.\n", searchID);
        }
    }
}
 
 
 
 
 
void printLecturerMenu(struct StudentLect students[], int studentCount)
{
    int choice;
 
    readAttendance(students, &studentCount);
    printf("=======================================================\n");
    printf("|               Lecturer Menu                         |\n");
    printf("=======================================================\n");
    printf("| 1. Print student attendance                         |\n");
    printf("| 2. Update student attendance                        |\n");
    printf("| 3. Print student course marks                       |\n");
    printf("| 4. Update student course marks                      |\n");
    printf("| 5. Exit System                                      |\n");
    printf("=======================================================\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    getchar();
 
    switch (choice)
    {
        case 1:
            calcAttendance(students, studentCount);
            printLecturerMenu(students, studentCount);
            break;
 
        case 2:
            updateAttendance(students, studentCount);
            printLecturerMenu(students, studentCount);
            break;
 
        case 3:
            checkMarks(students, &studentCount);
            printLecturerMenu(students, studentCount);
            break;
 
        case 4:
            updateMarks(students, studentCount);
            printLecturerMenu(students, studentCount);
            break;
 
        case 5:
            printf("Quitting Lecturer Menu\n");
            return;
 
        default:
            printf("Invalid choice. Please try again.\n\n");
            break;
    }
}
 

#include "lecturer.h"
#include "main.h"


void readAttendance(struct StudentLect students[], int *studentCount)
{
    FILE *file = fopen(FILENAME_ATTENDANCE, "r");

    if (file == NULL)
    {
        printf("Error opening file %s...\n", FILENAME_ATTENDANCE);
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
    FILE *file = fopen(FILENAME_ATTENDANCE,"r");

    if (file == NULL)
    {
        printf("Eror opening file %s...\n", FILENAME_ATTENDANCE);
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

        FILE *file = fopen(FILENAME_ATTENDANCE, "r+");

        if (file == NULL)
        {
            printf("Error opening file %s...\n", FILENAME_ATTENDANCE);
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

void checkMarks(const char* filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error opening file %s...\n",filename);
        return;
    }

    struct StudentLect students;
    int studentCount = 0;
    int searchID;
    int found = 0;

    printf("Enter student ID to check marks: ");
    scanf("%d", &searchID);

    while (fscanf(file, "%d %s", &students.id, students.name) == 2)
    {
        for (int i = 0; i < Num_courses; i++)
        {
            fscanf(file, "%s",students.courseM[i]);
        }

        for (int i = 0; i < Num_courses; i++)
        {
            fscanf(file, "%f", &students.marks[i]);
        }

        if(students.id == searchID) 
        {
            printf("Student ID: %d\n", students.id);
            printf("Student Name: %s\n", students.name);
            printf("Courses and Marks:\n");
            for (int i = 0; i < Num_courses; i++)
            {
                printf("%-20s%.2f\n", students.courseM[i], students.marks[i]);
            }
            printf("\n");
            found = 1;
            break;
        }

        studentCount++;
        
        if (studentCount >= Max_students)
        {
            printf("Students Maxed. Please dont add more niggers, no space in cafeteria!!!\n");
            break;
        }
    }

    if (!found) 
    {
        printf("Student with ID %d not found.\n",searchID);
    }

    fclose(file);

}

void readMarks(const char* filename, struct StudentLect students[], int *studentCount)
{
    FILE *file = fopen(filename, "r");
    
    if (file == NULL)
    {
        printf("Error opening file %s...\n",filename);
        return;
    }

    while ((*studentCount) < Max_students && fscanf(file, "%d %s", &students[*studentCount].id, students[*studentCount].name) == 2)
    {
        for (int i = 0; i < Num_courses; i++)
        {
            fscanf(file, "%s",students[*studentCount].courseM[i]);
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

void updateMarks(const char* filename, struct StudentLect students[], int studentCount)
{
    int studentID;
    char whichcourse[20];
    float newmark;
    while (1)
    {
        printf("Enter the ID of the student to update (enter -1 to stop): ");
        if (scanf("%d", &studentID) != 1)
        {
            while (getchar() != '\n');
            printf("Invalid input. Please try again.\n");
            continue;
        }

        if (studentID == -1) 
        {
            return;
        }

        int findStudent = -1;
        for (int i = 0; i < studentCount; i++)
        {
            if (students[i].id == studentID)
            {
                findStudent = i;
                break;
            }
        }

        if (findStudent == -1)
        {
            printf("Student not found. Enter a valid student ID.\n");
            continue;
        }

        printf("Enter the course to update: ");
        scanf("%s", whichcourse);

        int updated = 0;

        for (int j = 0; j < Num_courses; j++)
        {
            if (strcmp(students[findStudent].courseM[j], whichcourse) == 0)
            {
                printf("Enter the new marks for %s: ", whichcourse);
                while (scanf("%f", &newmark) != 1 || newmark < 0 || newmark > 100)
                {
                    printf("Invalid input. Please enter a valid mark: \n");
                    while (getchar() != '\n');
                }

                students[findStudent].marks[j] = newmark;
                updated = 1;
                printf("Student mark updated successfully.\n");
                break;
            }
        }

        if (!updated)
        {
            printf("Student or course not found.\n");
        }

        FILE *file = fopen(filename, "w"); 

        if (file == NULL)
        {
            printf("Error opening file %s...\n", filename);
            return;
        }

        for (int i = 0; i < studentCount; i++)
        {
            fprintf(file, "%d %s", students[i].id, students[i].name);

            for (int j = 0; j < Num_courses; j++)
            {
                fprintf(file, " %s", students[i].courseM[j]);
            }

            for (int j = 0; j < Num_courses; j++)
            {
                fprintf(file, " %.2f", students[i].marks[j]);
            }

            fprintf(file, "\n");
        }

        fclose(file);
    }
}

void printLecturerMenu(struct StudentLect students[], int studentCount)
{
    int choice;

    readAttendance(students, &studentCount);
    readMarks(FILENAME_MARKS, students, &studentCount);
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
            clearscreen();
            calcAttendance(students, studentCount);
            printLecturerMenu(students, studentCount);
            break;

        case 2:
            clearscreen();
            updateAttendance(students, studentCount);
            printLecturerMenu(students, studentCount);
            break;

        case 3:
            clearscreen();
            checkMarks(FILENAME_MARKS);
            printLecturerMenu(students, studentCount);
            break;

        case 4:
            clearscreen();
            updateMarks(FILENAME_MARKS, students, studentCount);
            printLecturerMenu(students, studentCount);
            break;

        case 5:
            printf("Goodbye!\n");sleep(2);clearscreen();remove("systeman");exit(0);break;

        default:
            printf("Invalid choice. Please try again.\n\n");
            break;
    }
}

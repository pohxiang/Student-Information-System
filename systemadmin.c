#include "structs.h"
#define coursemarkfile "coursemark.txt"
#define MAXSIZE 100
User users[MAXSIZE];
int n = 0;




void displayMainMenu() {
    int choice;
        printf("=======================================================\n");
        printf("|               System Admin Menu                     |\n");
        printf("=======================================================\n");
        printf("| 1. Add a User                                       |\n");
        printf("| 2. Remove a User                                    |\n");
        printf("| 3. Search for a User                                |\n");
        printf("| 4. Print User List                                  |\n");
        printf("| 5. Define Grading System                            |\n");
        printf("| 6. Generate Student Report                          |\n");
        printf("| 7. Exit                                             |\n");
        printf("=======================================================\n");    
    printf("\nEnter your choice: ");
    scanf("%d[^\n]", &choice);
    getchar();

    switch (choice) {
        case 1:
            addUser(users, &n);break;
            
        case 2:
            removeUser(users, &n);break;
            
        case 3:
            searchForUser();break;
            
        case 4:
            printUsers();break;
            
        case 5:
            changeGradeDefinition();clearscreen();loginmenu();

        case 6:
            studentgeneratereport();loginmenu();

        case 7:
            printf("Goodbye!\n");clearscreen();loginmenu();break;
            
        default:
            printf("Invalid choice. Please try again.\n\n");displayMainMenu();break;   
    }
}



bool isExistingID(User users[], int size, int id) {
    for (int i = 0; i < size; i++) {
        if (users[i].id == id) {
            return true; // ID already exists
        }
    }
    return false; // ID doesn't exist
}
 
void loadUsersFromFile(User users[], int *size) {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
 
    while ((*size < MAXSIZE) && fscanf(file, "%d %s %s %d", &users[*size].id, users[*size].name, users[*size].password, (int *)&users[*size].type) != EOF) {
        (*size)++;
    }
 
    fclose(file);
}
 
void addUser(User users[], int *size) {
    if (*size < MAXSIZE) {
        loadUsersFromFile(users, size); // Load existing users from file
 
        int newID;
        bool duplicateID;
       
        do {
            duplicateID = false;
            printf("Enter ID for the User: ");
            scanf("%d", &newID);
           
            if (isExistingID(users, *size, newID)) {
                printf("User with ID %d already exists. Please enter a different ID.\n", newID);
                duplicateID = true;
            }
        } while (duplicateID);
 
        users[*size].id = newID;
 
        printf("Enter name for the User: ");
        scanf("%s", users[*size].name);
        printf("Enter password for the User: ");
        scanf("%s", users[*size].password);
        printf("Enter type for the User (0 for Student, 1 for System_Admin, 2 for Lecturer, 3 for Programme Admin): ");
        scanf("%d", (int *)&users[*size].type);
 
        (*size)++;
        printf("User added successfully.\n");
 
        FILE *file = fopen("users.txt", "a");
        if (file == NULL) {
            printf("Error opening file\n");
            return;
        }
        fprintf(file, "%d %s %s %d\n", users[*size - 1].id, users[*size - 1].name, users[*size - 1].password, users[*size - 1].type);
        fclose(file);
 
        if (users[*size - 1].type == 0) {
            studentprofilecreate(users[*size - 1].id, users[*size - 1].name);
        } else if (users[*size - 1].type == 2) {
            lecturerprofilecreate(users[*size - 1].id, users[*size - 1].name);
        }
    } else {
        printf("The system is full. Cannot add more Users.\n");
    }
    displayMainMenu();
}
 
 
void removeUser(User users[], int *size) {
    int idToRemove;
    printf("Enter ID of the User to remove: ");
    scanf("%d", &idToRemove);
 
    FILE *inputFile = fopen("users.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening file users.txt\n");
        return;
    }
 
    FILE *tempFile = fopen("temp2.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file\n");
        fclose(inputFile);
        return;
    }
 
    User user;
    int found = 0;
 
    while (fscanf(inputFile, "%d %s %s %d", &user.id, user.name, user.password, (int*)&user.type) != EOF) {
        if (user.id != idToRemove) {
            fprintf(tempFile, "%d %s %s %d\n", user.id, user.name, user.password, (int)user.type);
        } else {
            found = 1;
        }
    }
 
    fclose(inputFile);
    fclose(tempFile);
   
    if (remove("users.txt") != 0) {
        perror("Error removing file");
        return;
    }
    if (rename("temp2.txt", "users.txt") != 0) {
        perror("Error renaming file");
        return;
    }
 
    // Update the users array in memory
    *size = 0;
    loadUsersFromFile(users, size);
 
    if (found) {
        printf("User with ID %d removed successfully.\n\n", idToRemove);
    } else {
        printf("User with ID %d not found.\n\n", idToRemove);
    }
 
    displayMainMenu();
}
 



void uploadDataFile(User users[], int *size) {
    FILE *file = fopen("users.txt", "r");
    if (file) {
        while ((*size) < MAXSIZE && fscanf(file, "%d %s %s %d", &users[*size].id, users[*size].name, users[*size].password, (int*)&users[*size].type) != EOF) {
            (*size)++;
        }
        fclose(file);
        printf("Data loaded from file successfully.\n\n");
    } else {
        printf("Error: Unable to open file.\n\n");
    }
}



void updateDataFile(User users[], int size) {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d %s %s %d\n", users[i].id, users[i].name, users[i].password, (int)users[i].type);
    }
    fclose(file);
}

// to print users that are in the text file
void printUsers(){
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {printf("Error opening file\n");return;}
    int usertype;
    User users;
    usertype = users.type;
    while (fscanf(file, "%d %s %s %d", &users.id, users.name, users.password, &usertype) != EOF) {
        printf("ID: %d\n", users.id);
        printf("Name: %s\n", users.name);
        printf("Password: %s\n", users.password);
        printf("Type: %s\n", userTypeToString((UserType)usertype));
        printf("\n");
    }
    fclose(file);
    displayMainMenu();
}

void searchForUser(){
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {printf("Error opening file\n");return;}
    User users;
    int searchID,usertype;
    usertype = users.type;
    printf("Enter ID to search for: ");
    scanf("%d", &searchID);
    while (fscanf(file, "%d %s %s %d", &users.id, users.name, users.password, &usertype) != EOF) {
        if (users.id == searchID) {
            printf("ID: %d\n", users.id);
            printf("Name: %s\n", users.name);
            printf("Password: %s\n", users.password);
            printf("Type: %s\n", userTypeToString((UserType)usertype));
            printf("\n");
            fclose(file);
            displayMainMenu();
            return;
        }
    }
    printf("User with ID %d not found.\n", searchID);
    fclose(file);
    displayMainMenu();
}

const char* userTypeToString(UserType type) {
    switch (type) {
        case STUDENT:
            return "Student";
        case SYSTEM_ADMIN:
            return "System Admin";
        case LECTURER:
            return "Lecturer";
        case PROGRAMME_ADMIN:
            return "Programme Admin";
        default:
            return "Unknown";
    }
}


GradeScale grading_system[] = {
    {'A', 4.0},
    {'B', 3.0},
    {'C', 2.0},
    {'D', 1.0},
    {'F', 0.0}
};

void changeGradeDefinition() {
    FILE *file;
    file = fopen("gradeDefinition.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int gradeDef[100];
    int i = 0;
    char G[] = {'A', 'B', 'C', 'D', 'F'};

    while (!feof(file)) {
        fscanf(file, "%d\n", &gradeDef[i]);
        printf("%d\nWhat would you like to change the minimum grade for %c to? :", gradeDef[i], G[i]);
        scanf("%d", &gradeDef[i]);
        i++;
    }
    printf("End of file.%d\n", gradeDef[3]);
    fclose(file);

    storeGradeDefinition(gradeDef, i);
}

void storeGradeDefinition(int gradeDef[100], int size) {
    FILE *file;
    file = fopen("gradeDefinition.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", gradeDef[i]);
    }

    fclose(file);displayMainMenu();
}


// Read student marks from file

void readStudentMarksFile(const char* filename, Student students[], int *studentCount) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s...\n", filename);
        return;
    }

    int i = 0;
    while (fscanf(file, "%d", &students[i].student_id) == 1) {
        fscanf(file, "%s", students[i].name);
        for (int j = 0; j < 5; j++) {
            fscanf(file, "%s", students[i].course[j]);
        }
        for (int j = 0; j < 5; j++) {
            fscanf(file, "%f", &students[i].module_marks[j]);
        }
        (*studentCount)++;
        i++;
    }
    fclose(file);
}

char calculate_grade(float marks) {
        FILE *file;
        file = fopen("gradeDefinition.txt", "r");
        if (file == NULL) {
            printf("Error opening file.\n");
            return 0;
        }

        int gradeDef[100];
        int i = 0;
        while (!feof(file)) {
            fscanf(file, "%d\n", &gradeDef[i]);
            i++;
        }
        fclose(file);
        
        if (marks >= gradeDef[0]) {
            return 'A';
        } else if (marks >= gradeDef[1]) {
            return 'B';
        } else if (marks >= gradeDef[2]) {
            return 'C';
        } else if (marks >= gradeDef[3]) {
            return 'D';
        } else {
            return 'F';
        }
}

float calculate_cgpa(float module_gpa[], int num_modules) {
    float total_grade_points = 0;
    for (int i = 0; i < num_modules; i++) {
        total_grade_points += module_gpa[i];
    }
    return total_grade_points / num_modules;
}

void calculate_student_performance(Student *student, int num_modules) {
    float total_grade_points = 0;
    for (int i = 0; i < 5; i++) {
        student->module_grades[i] = calculate_grade(student->module_marks[i]);
        // Find corresponding grade point from grading system
        for (int j = 0; j < sizeof(grading_system) / sizeof(grading_system[0]); j++) {
            if (student->module_grades[i] == grading_system[j].grade) {
                total_grade_points += grading_system[j].grade_point;
                break;
            }
        }
    }
    student->cgpa = total_grade_points / 5.0; // Assuming 5 modules
}

void display_leaderboard(Student students[], int num_students) {
    printf("Leaderboard:\n");
    printf("Rank\tStudent ID\tName\t\tCGPA\n");
    // Sort students based on CGPA (Bubble sort)
    for (int i = 0; i < num_students - 1; i++) {
        for (int j = 0; j < num_students - i - 1; j++) {
            if (students[j].cgpa < students[j + 1].cgpa) {
                // Swap students
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    // Display leaderboard
    for (int i = 0; i < num_students; i++) {
        printf("%d\t%d\t\t%s\t\t%.2f\n", i + 1, students[i].student_id, students[i].name, students[i].cgpa);
    }
}

bool searchStudentID(Student students[], int num_students, int targetID) {
    for (int i = 0; i < num_students; i++) {
        if (students[i].student_id == targetID) {
            return true; // Return true if found
        }
    }
    return false; // Return false if not found
}

void searchAndPrintStudentByID(Student students[], int num_students, int searchID) {
        if (searchStudentID(students, num_students, searchID)) {
            // Find and print the student with the given ID
            for (int i = 0; i < num_students; i++) {
                if (students[i].student_id == searchID) {
                    printf("Student ID: %d\n", students[i].student_id);
                    printf("Name: %s\n", students[i].name);
                    printf("CGPA: %.2f\n", students[i].cgpa);
                    printf("Modules: ");
                    for (int j = 0; j < 5; j++) {
                        printf("%s ", students[i].course[j]);
                    }
                    printf("\n");
                    printf("Module Grades: ");
                    for (int j = 0; j < 5; j++) {
                        printf("%c ", students[i].module_grades[j]);
                    }
                    printf("\n");
                    printf("Module Marks: ");
                    for (int j = 0; j < 5; j++) {
                        printf("%.2f ", students[i].module_marks[j]);
                    }
                    printf("\n");
                    break;
                }
            }
        } else {
            printf("Student ID %d not found.\n", searchID);
        }
    }




void studentgeneratereport(){
    int searchID;
    const char* filename = "coursemark.txt";
    Student students[100];
    int studentCount = 0;

    readStudentMarksFile(filename, students, &studentCount);
    for (int i = 0; i < studentCount; i++) {
        calculate_student_performance(&students[i], 5);
    }
    display_leaderboard(students, studentCount);
    printf("1. Search Student by ID\n2. Return to Menu\n");
    int choice;
    scanf("%d", &choice);
    switch (choice){
        case 1:
            printf("Enter Student ID: ");scanf("%d", &searchID);
            searchAndPrintStudentByID(students, studentCount, searchID);break;
        case 2:
            displayMainMenu();break;
    }
}   



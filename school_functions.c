#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "school_functions.h"
#define MAX_SUBJECTS 10
#define MAX_LENGTH 100

//ADD A STUDENT
// changed all scanf() to fgets() for safety purposes
void addstudent(struct Student **head, int *count)
{
    struct Student* newStudent =malloc(sizeof(struct Student));
    if (newStudent == NULL) {
        printf("Error: Out of memory\r\n");
        exit(-1);
    }

    // have adapted student id to be based off the student count, so it is always a unique identifier
    newStudent->sid = *count;
    printf("Student id: %d\n", *count);

    printf("Please enter their first name: ");
    char *firstname = malloc(MAX_LENGTH);
    if (firstname == NULL) {
        printf("Error: Out of memory\r\n");
        exit(-1);
    }
    getUserInput(&firstname);
    newStudent->firstname = firstname;

    printf("Please enter their last name: ");
    char *lastname = malloc(MAX_LENGTH);
    if (lastname == NULL) {
        printf("Error: Out of memory\r\n");
        exit(-1);
    }
    getUserInput(&lastname);
    newStudent->lastname = lastname;

    newStudent->next=NULL;

    newStudent->grades = NULL;

    if (*head == NULL) {
        *head = malloc(sizeof(struct Student));
    }
    if (*head!=NULL) {
        newStudent->next=*head;
    }
    else {
        printf("Error: Out of memory\r\n");
        exit(-1);
    }
    
    *head=newStudent;
    *count += 1;
    printf("%s %s added successfully\n\n", firstname, lastname);
}

//Print a student
void printstudent(struct Student **head)
{
    struct Student* student=*head;
    printf("----- Students data is displayed below-----\n");
    while (student->next!=NULL)
    {
        //go to next node and print
        printf("        Student id is -> %d\n",student->sid);
        printf("Student first name is -> %s\n",student->firstname);
        printf(" Student last name is -> %s\n\n",student->lastname);
        student=student->next;
    }
    printf("-----------------------------\n"); 
}

// ADD TEACHER
void addTeacher(struct Teacher **head, int *count)
{
    struct Teacher* newTeacher =malloc(sizeof(struct Teacher));
    if (newTeacher == NULL) {
        printf("Error: Out of memory\r\n");
        exit(-1);
    }

    newTeacher->tid = *count;
    printf("Teacher id: %d\n", *count);

    printf("Please enter the teacher's name: ");
    char *teacherName = malloc(MAX_LENGTH);
    if (teacherName == NULL) {
        printf("Error: Out of memory\r\n");
        exit(-1);
    }
    getUserInput(&teacherName);
    newTeacher->teachername = teacherName;

    printf("Please enter the subject %s teaches: ", teacherName);
    char *subjectName = malloc(MAX_LENGTH);
    if (subjectName == NULL) {
        printf("Error: Out of memory\r\n");
        exit(-1);
    }
    getUserInput(&subjectName);

    // check if inputted subject already exists, if so then free the memory and exit this function
    if (subjectExists(*head, subjectName) == 1) {
        printf("Subject %s already exists. Multiple teachers for the same subject are currently unsupported - please provide a unique subject when creating a new teacher. Returning to menu...\n", subjectName);
        free(newTeacher);
        free(subjectName);
        free(teacherName);
    }

    newTeacher->subjectname = subjectName;

    newTeacher->next = NULL;

    if (*head == NULL) {
        *head = malloc(sizeof(tteacher));
        (*head)->next = NULL;
    }
    if (*head == NULL) {
        printf("Error: Not enough memory available to add teacher to list.\n");
		exit(-1);
    } 

    newTeacher->next = *head;
    *head = newTeacher;

    printf("Teacher ID: %d - %s, %s - Succesfully Added\n\n", (*head)->tid, (*head)->teachername, (*head)->subjectname );
    *count += 1;
}

//Print a student
void printTeachers(struct Teacher **head)
{
    struct Teacher *teacher = (*head);
    printf("----- Teachers data is displayed below-----\n");
    while (teacher->next!=NULL)
    {
        //go to next node and print
        printf("       Teacher id is -> %d\n",teacher->tid);
        printf("     Teacher name is -> %s\n",teacher->teachername);
        printf("Teacher's Subject is -> %s\n\n",teacher->subjectname);
        teacher=teacher->next;
    }
    printf("-----------------------------\n"); 
}

// Assign Grades to Student
void assignGrade(struct Student **studentList, struct Teacher **teacherList)
{
    // Prompt the user for the ID of the student
    printf("Please enter the student's ID: ");
    char *studentID = malloc(10);
    if (studentID == NULL) {
        printf("Error: Out of memory\r\n");
        exit(-1);
    }
    getUserInput(&studentID);
    int studentIDInt = strtol(studentID, NULL, 10);

    // Go through list of students and check if a student with this ID exists
    struct Student *currentStudent = *studentList;
    while (currentStudent->next != NULL) {
        if (currentStudent->sid == studentIDInt) {
            printf("Student found: %s %s\n", currentStudent->firstname, currentStudent->lastname);
            break; // if the student exists exit this
        }
        currentStudent = currentStudent->next;
    }
    if (currentStudent->next == NULL) {
        printf("No Student Found. Exiting...\n");
        exit(-1);
    }
    
    // create a list of grades, iterate through teachers and add grades for each subject the student studies
    int gradecount = 0;
    struct Teacher *currentTeacher = (*teacherList);

    // Go through teacher list and ask if the student studies this subject
    while (currentTeacher != NULL) {

        printf("Working 1\n");

        printf("%s\n", currentTeacher->teachername);

        printf("Working 2\n");

        if (currentTeacher != NULL) {
            printf("Does %s %s study %s? Please answer yes or no (Y/N): ", currentStudent->firstname, currentStudent->lastname, currentTeacher->subjectname);
        }
        else {
            break;
        }
        char userOption;
        fgets(&userOption, 5, stdin);
        // If the user selects YES then prompt the user for the grade the student achieved
        if (userOption == 'Y') {
            printf("What grade did they achieve? Please input a grade from 1-9: ");
            char gradegiven;
            fgets(&gradegiven, 5, stdin);

            printf("Working\n");

            // Save a new Grade struct to the array of pointers to grade structs
            // currentStudent->grades[gradecount - 1] = malloc(sizeof(struct Grade *));
            // currentStudent->grades[gradecount - 1]->subjectname = currentTeacher->subjectname;

            // printf("Working 1.5\n");

            // currentStudent->grades[gradecount - 1]->gradegiven = gradegiven;

            printf("Working 2\n");
            gradecount++;

        }
        currentTeacher = currentTeacher->next;

        printf("Working 3\n");
    }
    
}

void assignGrade2(struct Student **studentList, struct Teacher **teacherList)
{
    // Prompt the user for the ID of the student
    printf("Please enter the student's ID: ");
    char *studentID = malloc(10);
    if (studentID == NULL) {
        printf("Error: Out of memory\r\n");
        exit(-1);
    }
    getUserInput(&studentID);
    int studentIDInt = strtol(studentID, NULL, 10);

    // Go through list of students and check if a student with this ID exists
    struct Student *currentStudent = *studentList;
    while (currentStudent->next != NULL) {
        if (currentStudent->sid == studentIDInt) {
            printf("Student found: %s %s\n", currentStudent->firstname, currentStudent->lastname);
            break; // if student exists, go to this label
        }
        currentStudent = currentStudent->next;
    }
    if (currentStudent->next == NULL) {
        printf("No Student Found. Exiting...\n");
        exit(-1);
    }
    
    // create a list of grades, iterate through teachers and add grades for each subject the student studies
    int gradecount = 0;

    // Go through teacher list and ask if the student studies this subject
    struct Teacher *teacher = (*teacherList);

    while (teacher->next != NULL)
    {
        //go to next node and ask if student studies this subject
        printf("Does %s %s study %s? Please answer yes or no (Y/N): ", currentStudent->firstname, currentStudent->lastname, teacher->subjectname);
        char *userOption = malloc(10);
        getUserInput(&userOption);
        // printf("%zu\n", sizeof(userOption));
        // printf("%c\n", userOption[0]); 
        printf("%s\n", userOption);
        if(strncasecmp(userOption, "Y", 1) == 0) {
            printf("What grade did they achieve? Please input a grade from 1-9: ");
            char *userInputGrade = malloc(10);
            getUserInput(&userInputGrade);

            printf("%s\n", userInputGrade);
            
            currentStudent->grades = realloc(currentStudent->grades, (gradecount+1) * sizeof(struct Grade *));
            // null check

            currentStudent->grades[gradecount] = malloc(sizeof(struct Grade));
            // null check

            currentStudent->grades[gradecount]->subjectname = malloc(strlen(teacher->subjectname));
            currentStudent->grades[gradecount]->gradegiven = malloc(strlen(userInputGrade));
            // null check

            strlcpy(currentStudent->grades[gradecount]->subjectname, teacher->subjectname, MAX_LENGTH);
            strlcpy(currentStudent->grades[gradecount]->gradegiven, userInputGrade, MAX_LENGTH);

            printf("%s: %s\n",currentStudent->grades[gradecount]->subjectname, currentStudent->grades[gradecount]->gradegiven);
            gradecount++;
        } 
        teacher=teacher->next;
        printf("Working...\n");
    }
    currentStudent->gradecount = malloc(sizeof(int));
    currentStudent->gradecount = gradecount;
    
}

void assignGrade3(struct Student **studentList, struct Teacher **teacherList, int teacherCount)
{
    // Prompt the user for the ID of the student
    printf("Please enter the student's ID: ");
    char *studentID = malloc(10);
    if (studentID == NULL) {
        printf("Error: Out of memory\r\n");
        exit(-1);
    }
    getUserInput(&studentID);
    int studentIDInt = strtol(studentID, NULL, 10);

    // Go through list of students and check if a student with this ID exists
    struct Student *currentStudent = *studentList;
    while (currentStudent->next != NULL) {
        if (currentStudent->sid == studentIDInt) {
            printf("Student found: %s %s\n", currentStudent->firstname, currentStudent->lastname);
            break; // if student exists, go to this label
        }
        currentStudent = currentStudent->next;
    }
    if (currentStudent->next == NULL) {
        printf("No Student Found. Exiting...\n");
        exit(-1);
    }
    
    // create a list of grades, iterate through teachers and add grades for each subject the student studies
    int gradecount = 0;

    // Go through teacher list and ask if the student studies this subject
    struct Teacher *teacher = (*teacherList);

    struct Grade *studentGrades = currentStudent->grades;
    studentGrades = (struct Grade *)malloc(sizeof(struct Grade));


    for (int i = 0; i < teacherCount; i++)
    {
        //go to next node and ask if student studies this subject
        printf("Does %s %s study %s? Please answer yes or no (Y/N): ", currentStudent->firstname, currentStudent->lastname, teacher->subjectname);
        char userOption;
        if (fgets(&userOption, 10, stdin) == NULL) {
			printf("Input Error: Failed to read input stream.");
            exit(-1);
		}

        struct Grade *newGrade = malloc(sizeof(struct Grade));
        switch (userOption) {
            case 'Y': 
                printf("What grade did they achieve? Please input a grade from 1-9: ");
                char userInputGrade;
                fgets(&userInputGrade, 5, stdin);
                
                // make a new grade struct with parameters
                
                newGrade->subjectname = teacher->subjectname;
                newGrade->gradegiven = userInputGrade;
                printf("Working 1\n");

                // Save a new Grade struct to the array of grade structs
                currentStudent->grades[gradecount] = malloc(sizeof(struct Grade *));
                if (currentStudent->grades[gradecount] == NULL) {
                    printf("Error: Out of memory\n");
                    exit(-1);
                }
                currentStudent->grades[gradecount] = newGrade;

                // printf("%s: %c\n",currentStudent->grades[gradecount]->subjectname, currentStudent->grades[gradecount - 1]->gradegiven);
                gradecount++;
                printf("Working 2\n");
                currentStudent->grades = realloc(currentStudent->grades, gradecount *sizeof(struct Grade));

                break;
            default:
                printf("Next teacher...\n");
                break;
        }
        teacher=teacher->next;
        printf("Working...\n");
    }
    
}

void printStudentGrades(struct Student **head)
{
    struct Student* student=*head;
    printf("----- Students Grades data is displayed below-----\n");
    while (student->next!=NULL)
    {
        //go to next node and print
        printf("Student ID: %d - ",student->sid);
        printf("%s %s\n",student->firstname, student->lastname);
        for (int i = 0 ; i < student->gradecount; i++) {
            printf("%s: %s\n", student->grades[i]->subjectname, student->grades[i]->gradegiven);
        }
        if (student->gradecount == 0) {
            printf("(None so far)\n");
        }
        printf("\n");
        student=student->next;
    }
    printf("-----------------------------\n"); 
}

void findTeachersBySubName(struct Teacher **head)
{
    // Prompt user for subject name
    char *subjectName = malloc(MAX_LENGTH);
    if (subjectName == NULL) {
        printf("Error: Out of memory\r\n");
        exit(-1);
    }
    printf("Please enter subject name: ");
    getUserInput(&subjectName);

    // Loop through teachers until teacher with matching subject found
    struct Teacher *teacher = *head;
    while (teacher->next != NULL)
    {
        if (strncasecmp(subjectName, teacher->subjectname, strlen(subjectName)) == 0) {
            printf("Teacher found: %s, %s\n", teacher->teachername, teacher->subjectname);
            return;
        }
        else {
            teacher = teacher->next;
        }
    }
    // if no teacher is found then tell user to add teacher using menu
    printf("No teacher for that subject found. Add one using Menu Option 2.\n");

}

void findStudentBySubName(struct Student **head, struct Teacher **teacherList) 
{
    // Prompt user for name of subject
    char *subjectName = malloc(MAX_LENGTH);
    if (subjectName == NULL) {
        printf("Error: Out of memory\r\n");
        exit(-1);
    }
    printf("Please enter subject name: ");
    getUserInput(&subjectName);

    // check if the subject exists, if not then return to menu
    if (subjectExists(*teacherList, subjectName) != 1) {
        printf("Subject '%s' does not exist. Please add it via Menu Option 2.\n", subjectName);
        return;
    }

    // Loop through students
    printf("Students that study %s:\n", subjectName);
    int numOfStudents = 0;
    struct Student *student = *head;
    while (student->next != NULL)
    {
        // check for each student if the provided subject name matches any of the subjects they do - if they do then print the student with their results
        for (int i = 0; i < student->gradecount; i++) {
            if (strncasecmp(subjectName, student->grades[i]->subjectname, strlen(subjectName)) == 0) {
                printf("%s %s - Grade: %s\n", student->firstname, student->lastname, student->grades[i]->gradegiven);
                numOfStudents++;
            }
        }
        student = student->next;
    }
    if (numOfStudents == 0) {
        printf("No students found.\n");
    }
}

void findStudentGradeByStudentIdSubName(struct Student **head, struct Teacher **teacherList) 
{
    // Prompt the user for the ID of the student
    printf("Please enter the student's ID: ");
    char *studentID = malloc(10);
    if (studentID == NULL) {
        printf("Error: Out of memory\r\n");
        exit(-1);
    }
    getUserInput(&studentID);
    int studentIDInt = strtol(studentID, NULL, 10);

    // Go through list of students and check if a student with this ID exists
    struct Student *currentStudent = *head;
    while (currentStudent->next != NULL) {
        if (currentStudent->sid == studentIDInt) {
            printf("Student found: %s %s\n", currentStudent->firstname, currentStudent->lastname);
            break; // if student exists, go to this label
        }
        currentStudent = currentStudent->next;
    }
    if (currentStudent->next == NULL) {
        printf("No Student Found. Returning to menu...\n");
        return;
    }

    // Prompt the user for the name of the subject
    char *subjectName = malloc(MAX_LENGTH);
    if (subjectName == NULL) {
        printf("Error: Out of memory\r\n");
        exit(-1);
    }
    printf("Please enter subject name: ");
    getUserInput(&subjectName);

    // check if the subject exists, if not then return to menu
    if (subjectExists(*teacherList, subjectName) != 1) {
        printf("Subject '%s' does not exist. Please add it via Menu Option 2.\n", subjectName);
        return;
    }

    // loop through all the grades in the student's grades array until the subject matching the provided subject name is found, and print their results
    for (int i = 0; i < currentStudent->gradecount; i++) {
        if (strncasecmp(subjectName, currentStudent->grades[i]->subjectname, strlen(subjectName)) == 0) {
            printf("%s %s - Grade: %s\n", currentStudent->firstname, currentStudent->lastname, currentStudent->grades[i]->gradegiven);
            return;
        }
    }

    // if matching subject is not found, just print that the student does not do this subject
    printf("%s does not do %s. ", currentStudent->firstname, subjectName);

}

void findStudentsByTeacher(struct Teacher **teacherList, struct Student **studentList)
{  
    // Prompt the user for the ID of the teacher
    printf("Please enter the teacher's ID: ");
    char *teacherID = malloc(10);
    if (teacherID == NULL) {
        printf("Error: Out of memory\r\n");
        exit(-1);
    }
    getUserInput(&teacherID);
    int teacherIDInt = strtol(teacherID, NULL, 10);

    // Go through list of teachers and check if a teacher with this ID exists
    struct Teacher *currentTeacher = *teacherList;
    while (currentTeacher->next != NULL) {
        if (currentTeacher->tid == teacherIDInt) {
            printf("Teacher found: %s, %s\n", currentTeacher->teachername, currentTeacher->subjectname);
            break; // if student exists, go to this label
        }
        currentTeacher = currentTeacher->next;
    }
    if (currentTeacher->next == NULL) {
        printf("No Teacher Found. Returning to menu...\n");
        return;
    }
    // Loop through students
    printf("Students taught by %s:\n", currentTeacher->teachername);
    int numOfStudents = 0;
    struct Student *student = *studentList;
    while (student->next != NULL)
    {
        // check for each student if the provided subject name matches any of the subjects they do - if they do then print the student with their results
        for (int i = 0; i < student->gradecount; i++) {
            if (strncasecmp(currentTeacher->subjectname, student->grades[i]->subjectname, strlen(currentTeacher->subjectname)) == 0) {
                printf("%s %s - Grade: %s\n", student->firstname, student->lastname, student->grades[i]->gradegiven);
                numOfStudents++;
            }
        }
        student = student->next;
    }
    if (numOfStudents == 0) {
        printf("No students found.\n");
    }

}

/* HELPER FUNCTIONS */ 

// Get user input
void getUserInput(char **input) {
	int error = 0;
	do {
		if (fgets(*input, MAX_LENGTH, stdin) == NULL) {
			printf("Input Error: Failed to read input stream. Please try again.");
			error = 1;
		} 
		else {
			// replace terminating newline character with terminating null character
			char *newline = strrchr(*input, '\n');
			if (newline) {
				*newline = '\0';
			}
			error = 0;
		}
	} while (error == 1);
}

int subjectExists(struct Teacher *teacherList, char *subjectName) {
    // if there is no teacherList yet, then just return 0 to indicate subject does not exist
    if (teacherList == NULL) {
        return 0;
    }
    struct Teacher *currentTeacher = teacherList;
    // loop through the linked list, checking for if the subject name provided corresponds with any of the subjects in the list
    while (currentTeacher->next != NULL) {
        if (strncasecmp(currentTeacher->subjectname, subjectName, 100) == 0) {
            // if it exists, return 1 to show it exists
            return 1;
        }
        currentTeacher = currentTeacher->next;
    }
    return 0;
}

// Delete List
void destroy_list_teachers(struct Teacher **head) {
    struct Teacher *next_node = NULL;
    // repeatedly remove the first node of the list until the last node remains
    while ((*head)->next != NULL) {
        next_node = (*head)->next; // get the next node and store in next_node
	    free((*head)->subjectname);
        free((*head)->teachername);
        free((*head)->next);
        free(*head); // free the head to release the memory of the current node
	    *head = next_node; // set the head to point at the previously next node
    }
    // free the head, the final node, to delete the list
    free((*head)->subjectname);
    free((*head)->teachername);
    free((*head)->next);
    free(*head);
    head = NULL;
}

void destroy_list_students(struct Student **head) {
    struct Student *next_node = NULL;
    // repeatedly remove the first node of the list until the last node remains
    while ((*head)->next != NULL) {
        next_node = (*head)->next; // get the next node and store in next_node
	    free((*head)->firstname);
        free((*head)->lastname);
        free((*head)->next);
        for (int i = 0; i < (*head)->gradecount; i++) {
            free((*head)->grades[i]->subjectname);
            free((*head)->grades[i]->gradegiven);
            free((*head)->grades[i]);
        }
        free((*head)->grades);
        free(*head); // free the head to release the memory of the current node
	    *head = next_node; // set the head to point at the previously next node
    }
    // free the head, the final node, to delete the list
    free((*head)->firstname);
    free((*head)->lastname);
    free((*head)->next);
    for (int i = 0; i < (*head)->gradecount; i++) {
        free((*head)->grades[i]->subjectname);
        free((*head)->grades[i]->gradegiven);
        free((*head)->grades[i]);
    }
    free((*head)->grades);
    free(*head);
    head = NULL;
}
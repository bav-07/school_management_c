#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "school_functions.h"
#include <string.h>


// Main function definition
int main()
{
    // student list head   
    struct Student *studentListHead = NULL;
    int studentCount = 0;

    // teacher list head
    struct Teacher *teacherListHead = NULL;
    int teacherCount = 0;
    
    int nos;
    int n;
    char *nchar = malloc(10);

    char choice;
    
    while (1)
    {   printf("\t **Choose your action**\n");
        printf("\t Press 1 to add a student\n");
        printf("\t Press 2 to add a teacher\n");
        printf("\t Press 3 to assign grade to student\n");
        printf("\t Press 4 to find students by subject name\n");
        printf("\t Press 5 to find teachers by subject name\n");
        printf("\t Press 6 to find a student grade by student_id and subject name\n");
        printf("\t Press 7 to find students by teacher id\n");
        printf("\t Press 8 to exit\n");
        printf("\nEnter Choice :\n");
        fgets(&choice, 5, stdin);
    
        switch (choice) {
            case '1':
                // Add a student
                printf("Enter the number of students you want to insert: ");
                
                fgets(nchar, 100, stdin);
                n = strtol(nchar, NULL, 10);
                printf("-----------------------------\n");
                // createing a linked list for n numbers
                for (int i = 0; i < n; i++)
                {
                    printf("Enter the student's details: \n");
                    addstudent(&studentListHead, &studentCount);
                }
                printstudent(&studentListHead);
                break;
            case '2':
                printf("Enter the number of teachers you want to insert: ");
                fgets(nchar, 100, stdin);
                n = strtol(nchar, NULL, 10);
                if (n == 0 || n == 0L) {
                    printf("Please enter a valid integer number greater than 0.\n");
                    break;
                }
                printf("-----------------------------\n");
                for (int i = 0; i < n; i++)
                {
                    printf("Enter the teachers' details: \n");
                    addTeacher(&teacherListHead, &teacherCount);
                }
                printTeachers(&teacherListHead);
                break;
            case '3':
                if (teacherCount == 0) {
                    printf("Please add teachers first.\n");
                    break;
                }
                if (studentCount == 0) {
                    printf("Please add students first.\n");
                    break;
                }
                assignGrade2(&studentListHead, &teacherListHead);
                printStudentGrades(&studentListHead);
                break;
            case '4':
                findStudentBySubName(&studentListHead, &teacherListHead);
                printf("-----------------------------\n");            
                break;
            case '5':
                findTeachersBySubName(&teacherListHead);
                printf("-----------------------------\n");
                break;
            case '6':
                findStudentGradeByStudentIdSubName(&studentListHead, &teacherListHead);
                printf("-----------------------------\n");
                break;
            case '7':
                findStudentsByTeacher(&teacherListHead, &studentListHead);
                printf("-----------------------------\n");
                break;
            case '8':
                destroy_list_teachers(&teacherListHead);
                destroy_list_students(&studentListHead);
                free(nchar);
                exit(1);
                break;
            default:
                printf("Invalid Input: Please select a valid input from the following:\n");

        }     
    }
    return 0;
}









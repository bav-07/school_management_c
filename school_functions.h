#define MAX_SUBJECTS 10

// Had to modify the char [] to char * for dynamic sizing across all structs
typedef struct Grade
{
    /* Grades Structure */
    char *gradegiven;
    char *subjectname;
}tgrade;

typedef struct Student
{
    /*Student Structure*/
    int sid;
    char* firstname;
    char* lastname;
    struct Grade **grades;
    struct Student *next;
    int gradecount;
}tstudent;

typedef struct Teacher
{
    /* Teacher Structure */
    int tid;
    char *teachername;
    char *subjectname;
    struct Teacher *next;
}tteacher;

//create a student
void addstudent(struct Student **head, int *count);
//print a student
void printstudent(struct Student **head);
//create a teacher
void addTeacher(struct Teacher **head, int *count);
void printTeachers(struct Teacher **head);

void assignGrade2(struct Student **studentList, struct Teacher **teacherList);

void findStudentBySubName(struct Student **head, struct Teacher **teacherList);
void findTeachersBySubName(struct Teacher **head);
void findStudentGradeByStudentIdSubName(struct Student **head, struct Teacher **teacherList);
void findStudentsByTeacher(struct Teacher **teacherList, struct Student **studentList);
void findTeachersByStudent(struct Teacher **teacherList, struct Student **studentList);

void getUserInput(char **input);
int subjectExists(struct Teacher *teacherList, char *subjectName);
void printStudentGrades(struct Student **head);

void destroy_list_teachers(struct Teacher **head);
void destroy_list_students(struct Student **head);

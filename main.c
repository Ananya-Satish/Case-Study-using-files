#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[50];
    float exam1_marks[5];
    float exam2_marks[5];
    char grade1;
    char grade2;
};

struct Student* createStudent();
void inputStudentData(struct Student *student);
float calculateAverage(float marks[], int size);
char gradeAssignment(float avg);
void generateGradeCard(struct Student *student);
void destroyStudent(struct Student *student);
void storeStudentData(struct Student *student);
void searchStudentData(const char *name);

int main() {
    int num_students;
    printf("Enter the number of students: ");
    scanf("%d", &num_students);

    for (int i = 0; i < num_students; i++) {
        struct Student *student = createStudent();

        printf("\nStudent %d:\n\n", i + 1);
        inputStudentData(student);

        float avg1 = calculateAverage(student->exam1_marks, 5);
        float avg2 = calculateAverage(student->exam2_marks, 5);

        student->grade1 = gradeAssignment(avg1);
        student->grade2 = gradeAssignment(avg2);

        generateGradeCard(student);
        storeStudentData(student);

        destroyStudent(student);
    }

    searchStudentData("Alice");

    return 0;
}

struct Student* createStudent() {
    struct Student *student = (struct Student*)malloc(sizeof(struct Student));
    if (student == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return student;
}

void inputStudentData(struct Student *student) {
    printf("Enter student name: ");
    scanf("%s", student->name);

    printf("Enter marks for exam 1: ");
    for (int i = 0; i < 5; i++) {
        scanf("%f", &student->exam1_marks[i]);
    }

    printf("Enter marks for exam 2: ");
    for (int i = 0; i < 5; i++) {
        scanf("%f", &student->exam2_marks[i]);
    }
}

float calculateAverage(float marks[], int size) {
    float sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += marks[i];
    }
    return sum / size;
}

char gradeAssignment(float avg) {
    if (avg >= 90) {
        return 'A';
    } else if (avg >= 80) {
        return 'B';
    } else if (avg >= 70) {
        return 'C';
    } else if (avg >= 60) {
        return 'D';
    } else {
        return 'F';
    }
}

void generateGradeCard(struct Student *student) {
    printf("\nName: %s\n", student->name);
    printf("Grade for exam 1: %c\n", student->grade1);
    printf("Grade for exam 2: %c\n", student->grade2);
}

void destroyStudent(struct Student *student) {
    free(student);
}

void storeStudentData(struct Student *student) {
    FILE *fp;
    fp = fopen("student_data.txt", "a");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "%s %.2f %.2f %.2f %.2f %.2f %.2f %c %c\n",
            student->name,
            student->exam1_marks[0], student->exam1_marks[1], student->exam1_marks[2], student->exam1_marks[3], student->exam1_marks[4],
            student->exam2_marks[0], student->exam2_marks[1], student->exam2_marks[2], student->exam2_marks[3], student->exam2_marks[4],
            student->grade1, student->grade2);
    fclose(fp);
}

void searchStudentData(const char *name) {
    FILE *fp;
    char student_name[50];
    float exam1_marks[5], exam2_marks[5];
    char grade1, grade2;
    int found = 0;

    fp = fopen("student_data.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(fp, "%s %f %f %f %f %f %f %c %c", student_name,
                  &exam1_marks[0], &exam1_marks[1], &exam1_marks[2], &exam1_marks[3], &exam1_marks[4],
                  &exam2_marks[0], &exam2_marks[1], &exam2_marks[2], &exam2_marks[3], &exam2_marks[4],
                  &grade1, &grade2) != EOF) {
        if (strcmp(student_name, name) == 0) {
            printf("\nName: %s\n", student_name);
            printf("Exam 1 marks: %.2f %.2f %.2f %.2f %.2f\n", exam1_marks[0], exam1_marks[1], exam1_marks[2], exam1_marks[3], exam1_marks[4]);
            printf("Exam 2 marks: %.2f %.2f %.2f %.2f %.2f\n", exam2_marks[0], exam2_marks[1], exam2_marks[2], exam2_marks[3], exam2_marks[4]);
            printf("Grade for exam 1: %c\n", grade1);
            printf("Grade for exam 2: %c\n", grade2);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found\n");
    }

    fclose(fp);
}

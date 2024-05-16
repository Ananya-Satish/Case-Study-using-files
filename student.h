#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

const char *subject_names[] = {"Physics", "PSWC", "Mathematics", "Electrical", "Mechanical"};

void inputStudentData(struct Student *student, FILE *fp) {
    student->name = (char *)malloc(50 * sizeof(char));
    if (student->name == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter student name: ");
    scanf("%s", student->name);

    fprintf(fp, "%s ", student->name);

    student->exam1_marks = (float *)malloc(5 * sizeof(float));
    if (student->exam1_marks == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter marks for exam 1:\n");
    for (int i = 0; i < 5; i++) {
        printf("Enter marks for %s: ", subject_names[i]);
        scanf("%f", &student->exam1_marks[i]);
        fprintf(fp, "%.2f ", student->exam1_marks[i]);
    }

    student->exam2_marks = (float *)malloc(5 * sizeof(float));
    if (student->exam2_marks == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter marks for exam 2:\n");
    for (int i = 0; i < 5; i++) {
        printf("Enter marks for %s: ", subject_names[i]);
        scanf("%f", &student->exam2_marks[i]);
        fprintf(fp, "%.2f ", student->exam2_marks[i]);
    }
    fprintf(fp, "\n");
}

void storeStudentData(struct Student *student) {
    FILE *fp = fopen("student_data.txt", "a");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    inputStudentData(student, fp);
    fclose(fp);
}

void searchStudentData(const char *name) {
    FILE *fp = fopen("student_data.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    char student_name[50];
    float exam1_marks[5], exam2_marks[5];

    while (fscanf(fp, "%s", student_name) != EOF) {
        if (strcmp(student_name, name) == 0) {
            printf("Name: %s\n", student_name);

            for (int i = 0; i < 5; i++) {
                fscanf(fp, "%f", &exam1_marks[i]);
                printf("Exam 1 %s: %.2f\n", subject_names[i], exam1_marks[i]);
            }

            for (int i = 0; i < 5; i++) {
                fscanf(fp, "%f", &exam2_marks[i]);
                printf("Exam 2 %s: %.2f\n", subject_names[i], exam2_marks[i]);
            }
            break;
        } else {
            for (int i = 0; i < 10; i++) {
                float dummy;
                fscanf(fp, "%f", &dummy);
            }
        }
    }

    fclose(fp);
}

float calculateAverage(float *marks, int size) {
    float sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += marks[i];
    }
    return sum / size;
}

char gradeAssignment(float avg) {
    if (avg >= 90) {
        return 'S';
    } else if (avg >= 80) {
        return 'A';
    } else if (avg >= 70) {
        return 'B';
    } else if (avg >= 60) {
        return 'C';
    } else if (avg >= 50) {
        return 'D';
    } else if (avg >= 40) {
        return 'E';
    } else {
        return 'F';
    }
}

void generateGradeCard(struct Student *student) {
    printf("\n===== Grade Card =====\n");
    printf("Name: %s\n", student->name);

    float avg1 = calculateAverage(student->exam1_marks, 5);
    float avg2 = calculateAverage(student->exam2_marks, 5);

    printf("Exam 1 Grade: %c\n", gradeAssignment(avg1));
    printf("Exam 2 Grade: %c\n", gradeAssignment(avg2));
}

void freeStudentMemory(struct Student *student) {
    free(student->name);
    free(student->exam1_marks);
    free(student->exam2_marks);
}

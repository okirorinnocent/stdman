/**
 * STUDENT PERFORMANCE MANAGEMENT SYSTEM
 * Semester GPA Calculator
 *
 * Author: Okiror Innocent
 * EMPLOYMENT: COMPUTER SCIENCE STUDENT
 * Institution: Mbarara University of Science and Technology (MUST)
 * Description: Lightweight tool to calculate semester GPA based on
 *               the university grading scale .
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LEN 100
#define MAX_CODE_LEN 20
#define BUFFER_SIZE 256

/* Represents an academic course module */
typedef struct
{
    char code[MAX_CODE_LEN];
    int credits;
    float score;
    float gp;
    char letter[3]; /* Accommodates 2-character grades like "B+" plus null terminator */
} Course;

/* Function prototypes */
void get_valid_string(const char *prompt, char *output, size_t max_size);
float get_valid_float(const char *prompt, float min_val, float max_val);
int get_valid_int(const char *prompt, int min_val);
void calculate_grade_point(float score, float *gp, char *letter);
void to_upper_string(char *str);

int main(void)
{

    printf(" UNIVERSITY SEMESTER ACADEMIC PERFORMANCE CALCULATOR\n");

    char student_name[MAX_NAME_LEN];
    get_valid_string("Enter Student Full Name: ", student_name, sizeof(student_name));

    int course_count = get_valid_int("Enter number of courses taken this semester: ", 1);

    /* Dynamically allocate memory for the courses based on user input */
    Course *courses = (Course *)malloc(course_count * sizeof(Course));
    if (courses == NULL)
    {
        fprintf(stderr, "[!] Memory allocation failed. Exiting...\n");
        return EXIT_FAILURE;
    }

    int total_credit_units = 0;
    float total_weighted_points = 0.0f;

    /* Collect information for each course module */
    for (int i = 0; i < course_count; i++)
    {
        printf("\n--- Course %d Entry ---\n", i + 1);

        get_valid_string("Course Code (e.g., CS1101): ", courses[i].code, sizeof(courses[i].code));
        to_upper_string(courses[i].code);

        courses[i].credits = get_valid_int("Credit units: ", 1);
        courses[i].score = get_valid_float("Final Score Percentage (0-100): ", 0.0f, 100.0f);

        /* Map percentage score to GP and letter grade */
        calculate_grade_point(courses[i].score, &courses[i].gp, courses[i].letter);

        /* Accumulate totals */
        total_credit_units += courses[i].credits;
        total_weighted_points += courses[i].gp * courses[i].credits;
    }

    /* Calculate credit-weighted GPA */
    float gpa = (total_credit_units > 0) ? (total_weighted_points / total_credit_units) : 0.0f;

    /* Format and display student name in uppercase */
    to_upper_string(student_name);

    /* Output formatted academic transcript summary */

    printf("ACADEMIC PERFORMANCE FOR: %s\n", student_name);

    printf("%-10s | %-8s | %-10s | %-6s | GP\n", "CODE", "CREDITS", "SCORE", "GRADE");

    for (int i = 0; i < course_count; i++)
    {
        printf("%-10s | %-8d | %-10.1f | %-6s | %.1f\n",
               courses[i].code,
               courses[i].credits,
               courses[i].score,
               courses[i].letter,
               courses[i].gp);
    }

    printf("Total Credit Units : %d\n", total_credit_units);
    printf("Semester GPA       : %.2f/5.00\n", gpa);

    /* Free dynamically allocated array */
    free(courses);
    courses = NULL;

    return EXIT_SUCCESS;
}

/**
 * Prompts for input and guarantees a non-empty, trimmed string response.
 */
void get_valid_string(const char *prompt, char *output, size_t max_size)
{
    char buffer[BUFFER_SIZE];

    while (1)
    {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            printf("\n[!] Input stream interrupted. Exiting...\n");
            exit(EXIT_FAILURE);
        }

        /* Remove trailing newline character */
        buffer[strcspn(buffer, "\n")] = '\0';

        /* Trim leading whitespace */
        char *start = buffer;
        while (isspace((unsigned char)*start))
        {
            start++;
        }

        /* Verify that string is non-empty after trimming */
        if (*start != '\0')
        {
            strncpy(output, start, max_size - 1);
            output[max_size - 1] = '\0'; /* Ensure string termination */
            return;
        }

        printf("[!] Input cannot be empty. Please try again.\n");
    }
}

/**
 * Prompts for a floating-point number and validates its bounds.
 */
float get_valid_float(const char *prompt, float min_val, float max_val)
{
    char buffer[BUFFER_SIZE];
    float value;
    char extra;

    while (1)
    {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            printf("\n[!] Input stream interrupted. Exiting...\n");
            exit(EXIT_FAILURE);
        }

        /* Ensure input contains valid float data and no trailing non-space characters */
        if (sscanf(buffer, "%f %c", &value, &extra) == 1)
        {
            if (value >= min_val && value <= max_val)
            {
                return value;
            }
            printf("[!] Input must be between %.1f and %.1f.\n", min_val, max_val);
        }
        else
        {
            printf("[!] Invalid input. Please enter a valid number.\n");
        }
    }
}

/**
 * Prompts for an integer and ensures it meets a minimum value threshold.
 */
int get_valid_int(const char *prompt, int min_val)
{
    char buffer[BUFFER_SIZE];
    int value;
    char extra;

    while (1)
    {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            printf("\n[!] Input stream interrupted. Exiting...\n");
            exit(EXIT_FAILURE);
        }

        /* Validate integer type input without trailing non-space chars */
        if (sscanf(buffer, "%d %c", &value, &extra) == 1)
        {
            if (value >= min_val)
            {
                return value;
            }
            printf("[!] Number must be at least %d.\n", min_val);
        }
        else
        {
            printf("[!] Invalid input. Please enter a whole integer.\n");
        }
    }
}

/**
 * Translates a raw percentage score into Grade Points (0.0 to 5.0 scale) and Letter Grades.
 */
void calculate_grade_point(float score, float *gp, char *letter)
{
    if (score >= 80.0f)
    {
        *gp = 5.0f;
        strcpy(letter, "A");
    }
    else if (score >= 75.0f)
    {
        *gp = 4.5f;
        strcpy(letter, "B+");
    }
    else if (score >= 70.0f)
    {
        *gp = 4.0f;
        strcpy(letter, "B");
    }
    else if (score >= 65.0f)
    {
        *gp = 3.5f;
        strcpy(letter, "C+");
    }
    else if (score >= 60.0f)
    {
        *gp = 3.0f;
        strcpy(letter, "C");
    }
    else if (score >= 55.0f)
    {
        *gp = 2.5f;
        strcpy(letter, "D+");
    }
    else if (score >= 50.0f)
    {
        *gp = 2.0f;
        strcpy(letter, "D");
    }
    else
    {
        *gp = 0.0f;
        strcpy(letter, "F");
    }
}

/**
 * Helper function to convert a null-terminated string to uppercase in place.
 */
void to_upper_string(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = (char)toupper((unsigned char)str[i]);
    }
}
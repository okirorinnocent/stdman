#include <stdio.h>

int main(void)
{
    char student_name[100];
    int course_count;

    printf("--- MUST SEMESTER GPA CALCULATOR ---\n");

    printf("Enter Student Full Name: ");
    scanf(" %[^\n]", student_name);

    printf("Enter number of courses taken: ");
    scanf("%d", &course_count);

    // Fixed array size to keep things simple without dynamic memory
    char code[20][20];
    int credits[20];
    float score[20];
    float gp[20];
    char letter[20][3];

    int total_credits = 0;
    float total_weighted_points = 0.0;

    // Collect details for each course
    for (int i = 0; i < course_count; i++)
    {
        printf("\n--- Course %d Entry ---\n", i + 1);

        printf("Course Code: ");
        scanf("%s", code[i]);

        printf("Credit Units: ");
        scanf("%d", &credits[i]);

        printf("Score Percentage (0-100): ");
        scanf("%f", &score[i]);

        // Calculate Grade Point and Letter Grade
        if (score[i] >= 80.0)
        {
            gp[i] = 5.0;
            letter[i][0] = 'A';
            letter[i][1] = '\0';
        }
        else if (score[i] >= 75.0)
        {
            gp[i] = 4.5;
            letter[i][0] = 'B';
            letter[i][1] = '+';
            letter[i][2] = '\0';
        }
        else if (score[i] >= 70.0)
        {
            gp[i] = 4.0;
            letter[i][0] = 'B';
            letter[i][1] = '\0';
        }
        else if (score[i] >= 65.0)
        {
            gp[i] = 3.5;
            letter[i][0] = 'C';
            letter[i][1] = '+';
            letter[i][2] = '\0';
        }
        else if (score[i] >= 60.0)
        {
            gp[i] = 3.0;
            letter[i][0] = 'C';
            letter[i][1] = '\0';
        }
        else if (score[i] >= 55.0)
        {
            gp[i] = 2.5;
            letter[i][0] = 'D';
            letter[i][1] = '+';
            letter[i][2] = '\0';
        }
        else if (score[i] >= 50.0)
        {
            gp[i] = 2.0;
            letter[i][0] = 'D';
            letter[i][1] = '\0';
        }
        else
        {
            gp[i] = 0.0;
            letter[i][0] = 'F';
            letter[i][1] = '\0';
        }

        total_credits += credits[i];
        total_weighted_points += gp[i] * credits[i];
    }

    // Calculate GPA
    float gpa = 0.0;
    if (total_credits > 0)
    {
        gpa = total_weighted_points / total_credits;
    }

    // Output Summary
    printf("\n====================================\n");
    printf("ACADEMIC PERFORMANCE FOR: %s\n", student_name);
    printf("====================================\n");
    printf("CODE       | CREDITS  | SCORE      | GRADE  | GP\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < course_count; i++)
    {
        printf("%-10s | %-8d | %-10.1f | %-6s | %.1f\n",
               code[i], credits[i], score[i], letter[i], gp[i]);
    }

    printf("--------------------------------------------------\n");
    printf("Total Credit Units : %d\n", total_credits);
    printf("Semester GPA       : %.2f / 5.00\n", gpa);

    return 0;
    // tythtyjhgj
}
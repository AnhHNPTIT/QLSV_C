#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct Student
{
    char StudentID[255];
    char FirstName[255];
    char LastName[255];
    char Gender[255];
    char DOB[255];
    char ClassName[255];
    char Country[255];
};

struct Subject
{
    char SubjectID[255];
    char SubjectName[255];
    int Credit;
};

struct Score
{
    char StudentID[255];
    char SubjectID[255];
    float Score;
};

struct Student students[1500];
struct Subject subjects[1500];
struct Score scores[1500];
int numberStudents, numberSubjects, numberScores;

int readFileStudent() 
{
    int i = 0;
    FILE * fp = fopen ("dssv.csv", "r"); 

    char tmp[255];
    fgets(tmp, 255, fp);
    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", students[i].StudentID, students[i].FirstName, students[i].LastName, students[i].Gender, students[i].DOB, students[i].ClassName, students[i].Country) != EOF)
    {
        i = i + 1;  
    }
    
    fclose (fp);
    return i;
}

int readFileSubject(struct Subject subjects[]) 
{
    int i = 0;
    FILE * fp = fopen ("dsmh.csv", "r"); 

    char tmp[255];
    fgets(tmp, 255, fp);
    while (fscanf(fp, "%[^,],%[^,],%d\n", subjects[i].SubjectID, subjects[i].SubjectName, &subjects[i].Credit) != EOF)
    {
        i = i + 1;  
    }
  
    fclose (fp);
    return i;
}

int readFileScore(struct Score scores[]) 
{    
    int i = 0;
    FILE * fp = fopen ("diem.csv", "r"); 

    char tmp[255];
    fgets(tmp, 255, fp);
    while (fscanf(fp, "%[^,],%[^,],%f\n", scores[i].StudentID, scores[i].SubjectID, &scores[i].Score) != EOF)
    {
        i = i + 1;  
    }
 
    fclose (fp);
    return i;
}

void writeStudents(struct Student array[], int n)
{
    FILE * fp = fopen ("result.csv", "w");  
    for (int i = 0; i < n - 1; i++) {
        fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", students[i].StudentID, students[i].FirstName, students[i].LastName, students[i].Gender, students[i].DOB, students[i].ClassName, students[i].Country);
    }
    fprintf(fp, "%s,%s,%s,%s,%s,%s,%s", students[n-1].StudentID, students[n-1].FirstName, students[n-1].LastName, students[n-1].Gender, students[n-1].DOB, students[n-1].ClassName, students[n-1].Country);
    fclose (fp);
}

bool listStudentsByClassName(char str[]) 
{
    struct Student array[1500];
    int count = 0;
    
    for (int i = 0; i < numberStudents; i++) {
        if (strcmp(students[i].ClassName, str) == 0) {
            array[count++] = students[i];
        }
    }

    writeStudents(array, count);
    return true;
}

bool compareString(char str1[], char str2[])
{
    if (strlen(str1) != strlen(str2))
    {
        return false;
    }
    else 
    {
        for (int i = 0; i < strlen(str1); i++)
        {
            if (tolower(str1[i]) != tolower(str2[i]))
            {
                return false;
            }
        }
        return true;
    }
}

bool countStudents(char str[]) {
    int count = 0;
    FILE * fp = fopen ("result.csv", "w");  

    for (int i = 0; i < numberStudents; i++) 
    {
        if (compareString(str, "female") || compareString(str, "male")) 
        {
            if (compareString(students[i].Gender, str))
            {
                count = count + 1;
            }
        }
        else
        {
            return false;
        }
    }

    fprintf(fp, "%d", count);
    fclose (fp);
    return true;    
}

void swap(struct Student *stu1, struct Student *stu2)
{
    struct Student tmp;
    tmp = *stu1;
    *stu1 = *stu2;
    *stu2 = tmp;
}

bool sortStudents(char str[])
{
    for (int i = 0; i < numberStudents - 1; i++) 
    {
        for (int j = i + 1; j < numberStudents; j++) 
        {
            if (compareString(str, "asc")) 
            {
                if ((strcmp(students[i].FirstName, students[j].FirstName) > 0))
                {
                    swap(&students[i], &students[j]); 
                }
                else {
                    if ((strcmp(students[i].FirstName, students[j].FirstName) == 0 && strcmp(students[i].DOB, students[j].DOB) > 0))
                    {
                        swap(&students[i], &students[j]);
                    }
                    else 
                    {
                        if ((strcmp(students[i].DOB, students[j].DOB) == 0 && strcmp(students[i].LastName, students[j].LastName) > 0))
                        {
                            swap(&students[i], &students[j]);
                        }
                        else
                        {
                            if ((strcmp(students[i].LastName, students[j].LastName) == 0 && strcmp(students[i].Country, students[j].Country) > 0))
                            {
                                swap(&students[i], &students[j]);
                            }
                        }
                    }
                } 
            }
            else if(compareString(str, "desc")) 
            {
                if ((strcmp(students[i].FirstName, students[j].FirstName) < 0))
                {
                    swap(&students[i], &students[j]); 
                }
                else {
                    if ((strcmp(students[i].FirstName, students[j].FirstName) == 0 && strcmp(students[i].DOB, students[j].DOB) < 0))
                    {
                        swap(&students[i], &students[j]);
                    }
                    else 
                    {
                        if ((strcmp(students[i].DOB, students[j].DOB) == 0 && strcmp(students[i].LastName, students[j].LastName) < 0))
                        {
                            swap(&students[i], &students[j]);
                        }
                        else
                        {
                            if ((strcmp(students[i].LastName, students[j].LastName) == 0 && strcmp(students[i].Country, students[j].Country) < 0))
                            {
                                swap(&students[i], &students[j]);
                            }
                        }
                    }
                }
            }
            else
            {
                return false;
            }
        }
    }

    writeStudents(students, numberStudents);
    return true;
}

bool listStudentsByCountry(char str[]) 
{
    struct Student array[1500];
    int count = 0;

    for (int i = 0; i < numberStudents; i++) {
        if (compareString(students[i].Country, str))
        {
            array[count++] = students[i];
        }
    }

    writeStudents(array, count);
    return true;
}

int countSpaceChar(char str[])
{
    int count = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == ' ') 
        {
            count = count + 1;
        }
    }
    return count;
}

bool runCommand(char str[]) { 
    if (countSpaceChar(str) != 1) {
        return false;
    }

    char space[2] = " ";
    char *cmd = strtok(str, space);
    char *param = strtok(NULL, space); 

    if (param != NULL) {
        if (compareString(cmd, "list")) {
            return listStudentsByClassName(param);
        }
        else if (compareString(cmd, "count")) {
            return countStudents(param);
        }
        else if (compareString(cmd, "sort")) {
            return sortStudents(param);
        }
        else if(compareString(cmd, "country")) {
            return listStudentsByCountry(param);
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

char * standardString(char str[]) 
{
    for (int i = 0; i < strlen(str); i++)
    {
        str[i] = tolower(str[i]);
        if (str[i] == '\n')
        {
            str[i] = '\0';
        }
    }
    return str;
}

void writeLog()
{
    FILE * fp = fopen ("log.txt", "w");  
    fprintf(fp, "%d %d %d", numberStudents, numberSubjects, numberScores);
    fclose (fp);
}

void writeError()
{
    FILE * fp = fopen ("error.txt", "w");  
    fprintf(fp, "%s", "invalid command");
    fclose (fp);
}

int main()
{
    numberStudents = readFileStudent(students);
    numberSubjects = readFileSubject(subjects);
    numberScores = readFileScore(scores);
    writeLog();

    char command[255];
    fflush(stdin);
    fgets(command, 255, stdin);
    standardString(command);

    int result = runCommand(command);
    if (!result) {
        writeError();
    }

    return 0;
}
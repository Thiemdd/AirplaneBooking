#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

// Read all customer list in Customer.txt and return to an array output[i]
char **readCusfile(int *count)
{
    char **CustomerList;
    CustomerList = (char **)malloc(sizeof(char *));
    FILE *R;
    int i = 0;
    *count = 0;
    char line[100];
    R = fopen("customer.txt", "r");
    while (fgets(line, sizeof(line), R))
    {
        CustomerList = (char **)realloc(CustomerList, ((*count) + 1) * sizeof(char *));
        CustomerList[*count] = (char *)malloc(sizeof(line));
        strcpy(CustomerList[*count], line);
        CustomerList[*count][strcspn(CustomerList[*count], "\n")] = '\0';
        (*count)++;
    }
    fclose(R);
    return CustomerList;
}

int main()
{
    char **output;
    int count;
    output = readCusfile(&count);
    printf("%d", count);
    for (int i = 0; i < count; i++)
    {
        printf("%s", output[i]);
    }
    return 0;
}

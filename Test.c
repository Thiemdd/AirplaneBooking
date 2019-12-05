#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

char **readCusfile()
{
    char **CustomerList;
    CustomerList = (char **)malloc(sizeof(char *));
    FILE *R;
    int i = 0, count = 0;
    char line[100];
    R = fopen("customer.txt", "r");
    while (fgets(line, sizeof(line), R))
    {
        CustomerList = (char **)realloc(CustomerList, (count + 1)*sizeof(char*));
        CustomerList[count] = (char *)malloc(sizeof(line));
        strcpy(CustomerList[count], line);
        count++;
    }
    fclose(R);
    return CustomerList;
}

int main()
{
    char **output;
    output = readCusfile();
	// printf("\n");
    printf(output[1]);
    return 0;
}

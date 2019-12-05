#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

// Read customer list in Customer.txt and get a 2D array
char **readCusfile(int *count)
{
    FILE *R;
    char line[100];
    char **CustomerList;
    CustomerList = (char **)malloc(sizeof(char *));
    *count = 0;
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

char *getithline(char fileName[200], int targetLine)
{
    FILE *S;
    char directory[200] = "";
    strcat(directory, ".\\Tickets\\");
    strcat(directory, fileName);
    // Vị trí của dòng hiện tại
    int tmpcount = 1;
    // Dòng lấy ra được lưu vào đây
    char *line = (char *)malloc(200 * sizeof(char));
    // Mở file
    S = fopen(directory, "r+");
    // Đọc lần lượt từng dòng cho đến hết
    while (fgets(line, 100 * sizeof(char), S))
    {
        // Tại vị trí dòng cần đọc, thực hiện nhánh 'if'
        if (tmpcount == targetLine)
        {
            break;
        }
        tmpcount++;
    }
    fclose(S);
    // Trả về giá trị của dòng cần trích thông tin
    return line;
}

// int *GetTicName()
// {
//     char **CusList;
//     int linecount;
//     CusList = readCusfile(&linecount);
//     FILE *R1;
//     for (int i = 0; i < linecount; i++)
//     {
//         R1 = fopen(CusList[i], "r");
//     }
//     return 0;
// }
int main()
{
    char **output;
    char *output1;
    int count;
    output = readCusfile(&count);
    output1 = getithline(output[1], 2);
    printf("%s", output1);
    return 0;
}

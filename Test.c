#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

// Read customer list in Customer.txt and get all files into a 2D array
char **readCusfile()
{
    FILE *R;
    char line[100];
    char **CustomerList;
    CustomerList = (char **)malloc(sizeof(char *));
    int count = 0;
    R = fopen("customer.txt", "r");
    while (fgets(line, sizeof(line), R))
    {

        CustomerList = (char **)realloc(CustomerList, (count + 1) * sizeof(char *));
        CustomerList[count] = (char *)malloc(sizeof(line));
        strcpy(CustomerList[count], line);
        strtok(CustomerList[count], "\n");
        count++;
        //CustomerList[count-1][strcspn(CustomerList[count], "\n")] = '\0';
        // (*count)++;
    }
    fclose(R);
    return CustomerList;
}
int countLine(const char *filename)
{
    FILE *R;
    char c;
    // char line[100];
    // char **CustomerList;
    // CustomerList = (char **)malloc(sizeof(char *));
    int count = 1;
    R = fopen(filename, "r");
    for (c = fgetc(R); c != EOF; c = fgetc(R))
    {
        if (c == '\n')
            count++;
    }
    return count;
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

// char *getInfor()
// {
//     char** list = readCusfile()
// }

int main()
{
    char **output;
    char *output1;
    char *output2;
    output = readCusfile();
    for (int i = 0; i < countLine("Customer.txt"); i++)
    {
        output2 = getithline(output[i], 1);
        printf("%s", output2);
    }
    // printf("%s\n", output[2]);
}
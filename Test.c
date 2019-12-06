#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

// Đọc tất cả các dòng trong Customer.txt và lưu vào 1 mảng
char **readfile(const char *filename)
{
    FILE *R;
    char line[100];
    char **CustomerList;
    CustomerList = (char **)malloc(sizeof(char *));
    int count = 0;
    R = fopen(filename, "r");
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
    // Trả các tên file trong Cusfile về CustomerList
    return CustomerList;
}

// Đếm số dòng của 1 file
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

// Lấy ra dòng thứ i của 1 file
char *getithline(char fileName[200], int targetLine)
{
    FILE *S;
    // Lấy ra đường dẫn
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
    char **arrfilenames;
    char *line1;
    char *line5;
    char sameflight[300];
    // char **sameline;
    // Đọc tất cả các dòng trong Customer.txt và lưu vào output
    arrfilenames = readfile("Customer.txt");
    // Vòng lặp đếm tất cả các file trong Customer.txt
    for (int i = 0; i < countLine("Customer.txt"); i++)
    {
        // Lưu dòng thứ 1 của tất cả các file có trong Customer.txt vào line1
        line1 = getithline(arrfilenames[i], 1);
        // Lưu dòng thứ 5 của tất cả các file có trong Customer.txt vào line5
        line5 = getithline(arrfilenames[i], 5);
        // Vòng lặp đếm tất cả các dòng của line1
        for (int j = 0; j < i; j++)
        {
            for (int k = 0; k < j; k++)
            {
                // Nếu dòng 1 và dòng 5 của file giống nhau thì cho các file đó vào 1 xâu
                if ((strcmp(getithline(arrfilenames[k], 1), getithline(arrfilenames[j], 1)) == 0) && (strcmp(getithline(arrfilenames[k], 5), getithline(arrfilenames[j], 5)) == 0))
                {
                    sprintf(sameflight, "%s", arrfilenames[j]);
                }
            }
        }
        printf("%s", sameflight);
    }
}
// printf("%s\n", output[2]);

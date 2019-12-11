#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include "Declaration.h"
#include "Struct.c"

// struct Flight sameflight[100];

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
            strtok(line, "\n");
            break;
        }
        tmpcount++;
    }
    fclose(S);
    // Trả về giá trị của dòng cần trích thông tin
    return line;
}

// Lấy ra những ghế đã đặt
// int mainn()
// {
//     char **arrfilenames;
//     char *line1;
//     char *line5;
//     char *s;
//     int seatCount = 0;
//     // Đọc tất cả các dòng trong Customer.txt và lưu vào output
//     arrfilenames = readfile("Customer.txt");
//     // Vòng lặp đếm tất cả các file trong Customer.txt
//     for (int i = 0; i < countLine("Customer.txt"); i++)
//     {
//         for (int j = 0; j < countLine("Customer.txt"); j++)
//         {
//             if ((strcmp(getithline(arrfilenames[j], 1), person[5].route) == 0) && (strcmp(getithline(arrfilenames[j], 5), person.flightDate) == 0))
//             {
//                 s = realloc(s, (seatCount + 1) * sizeof(int));
//                 s[seatCount] = int(getithline(filename[j], 6));
//             }
//         }
//     }
//     // printf("%s", sameflight);
// }

int isSameFlight(char *route, char *flightDate, char *filename)
{
    if (strcmp(route, getithline(filename, 1)) == 0 && strcmp(flightDate, getithline(filename, 5)) == 0)
    {
        return 1;
    }
    return 0;
}

int *getBookedSeat(char *route, char *flightDate)
{
    int *s = (int *)malloc(1*sizeof(int));
    s[0] = 100;
    int seatCount = 0;
    char **ticketList;
    ticketList = readfile("Customer.txt");
    for (int i = 0; i < countLine("Customer.txt"); i++)
    {

        if (isSameFlight(route, flightDate, ticketList[i]) == 1)
        {
            s[seatCount] = atoi(getithline(ticketList[i], 6));
            seatCount += 1;
            s = (int *)realloc(s, seatCount * sizeof(int));
        }
    }
    return s;
}

int main()
{
    char **ticketList;
    ticketList = readfile("Customer.txt");
    int line = countLine("Customer.txt") - 1;
    int *bookedSeatNo;
    bookedSeatNo = getBookedSeat("Da Nang - Ha Noi", "2/2/2020");
    printf("Success");
    printf("%d", bookedSeatNo[0]);
    return 0;
}
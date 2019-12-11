#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct Flight sameflight[100];

// Đọc tất cả các dòng trong Customer.txt và lưu vào 1 mảng
char **Readfile(char *filename)
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
int countLine(char *filename)
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
char *getithline(char *fileName, int targetLine)
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
    int *s;
    s = (int *)malloc(1 * sizeof(int));
    s[0] = 100;
    int seatCount = 0;
    char **ticketList;
    char *tmp;
    ticketList = Readfile("Customer.txt");
    for (int i = 0; i < countLine("Customer.txt") - 1; i++)
    {
        if (isSameFlight(route, flightDate, ticketList[i]) == 1)
        {
            seatCount += 1;
            s = (int *)realloc(s, seatCount * sizeof(int));
            tmp = getithline(ticketList[i], 6);
            strtok(tmp, "\n");
            s[seatCount - 1] = atoi(tmp);
        }
    }
    return s;
}

int main()
{
    int *no;
    no = getBookedSeat("Hanoi - HCM City", "2/2/2020");
    printf("%d", no[0]);
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include "Declaration.h"
#include "Struct.c"

// To store number of days in all months from January to Dec
int monthDays[12] = {31, 28, 31, 30, 31, 30,
					 31, 31, 30, 31, 30, 31};

char fRoute[10][30];

struct TicketForm person[300];

int num = 0, id2 = 1000;

//Main
int main()
{
	int choice1, choice2, i, originalPrice = 0;
	int x = 0;
	char idc[30];
	RouteList();

	while (x != 6)
	{
		choice1 = Menu();
		switch (choice1)
		{
		case 1:
			ChangePrice();
			break;
		case 2:
			ChangeTime();
			break;
		case 3:
			ReservedTicket();
			break;
		case 4:
			choice2 = Choice(&originalPrice);
			Booking(choice2, originalPrice);
			num++;
			break;
		case 5:
			printf("Enter your ticket ID: ");
			scanf("%s", &idc);
			Cancel(idc);
			break;
		case 6:
			x = 6;
			printf("Thank you for using our service!");
			printf("\n        ______________\n");
			break;
		default:
			printf("Choice not available\n");
			break;
		}
	}
}

// Lấy ra dòng thứ i của 1 file
char *getithline(char fileName[50], int targetLine)
{
	FILE *S;
	// Lấy ra đường dẫn
	char directory[200] = "";
	strcpy(directory, ".\\Tickets\\");
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

//Print choices
int Menu()
{
	int choice1 = 0;
	printf("Please choose your option: ");
	printf("\n                 Simple Flight Ticket Booking System\n");
	printf(" ==================================================================\n");
	printf("||             1- To edit price of ticket (only admin):           ||\n");
	printf("||             2- To edit flight schedule (only admin):           ||\n");
	printf("||             3- To view reserved tickets(only admin):           ||\n");
	printf("||             4- To book ticket:                                 ||\n");
	printf("||             5- To cancel the ticket:                           ||\n");
	printf("||             6- Exit system:                                    ||\n");
	printf(" ==================================================================\n");
	printf("  Enter your choice: ");
	fflush(stdin);
	scanf("%d", &choice1);
	return choice1;
}

//Change price
void ChangePrice()
{
	int set = 0, j = 0;
	FILE *f;
	FILE *fTemp;
	char buffer[100], nPrice[10];
	char path[] = "FlightSchedule.txt";
	int line = 0, count = 0;
	char pass[20], pak[] = "pass";

	printf("Enter the password:  ");
	scanf("%s", &pass);
	if (strcmp(pass, pak) == 0)
	{
		printf("Choose the route you want to change original price of ticket: \n");
		for (j = 0; j < 6; j = j + 2)
		{
			printf("\t%d. %-30s %d. %-30s\n", j + 1, fRoute[j], j + 2, fRoute[j + 1]);
		}
		scanf("%d", &set);
		while (set < 1 || set > 6)
		{
			printf("\nChoice is invalid, please choose another option: ");
			scanf("%d", &set);
		}
		strcat(fRoute[set - 1], "\n");
		f = fopen(path, "r");
		if (!f)
			printf("cannot open file");
		fTemp = fopen("replace.tmp", "w");
		printf("Set the new price for the route: ");
		fflush(stdin);
		scanf("%s", &nPrice);
		while (strcmp(fRoute[set - 1], fgets(buffer, sizeof(buffer), f)) != 0)
		{
			line++;
		}
		rewind(f);
		while (fgets(buffer, sizeof(buffer), f))
		{
			count++;
			if (count == line + 2)
			{
				fputs(nPrice, fTemp);
				fputs("\n", fTemp);
			}
			else
				fputs(buffer, fTemp);
		}
		fclose(f);
		fclose(fTemp);
		remove(path);
		rename("replace.tmp", path);
		fRoute[set - 1][strcspn(fRoute[set - 1], "\n")] = 0;
		printf("Price of the flight '%s' has been change to %s\n", fRoute[set - 1], nPrice);
		system("pause");
		system("cls");
	}
	else
		printf("The entered password is wrong!\n\n");
}
//change flight time
void ChangeTime()
{
	int set = 0, i, j = 0, hour, min;
	FILE *f;
	FILE *fTemp;
	char buffer[100], nTime[10], apm[10];
	char path[] = "FlightSchedule.txt";
	int line = 0, count = 0;
	char pass[20], pak[] = "pass";

	printf("Enter the password:  ");
	scanf("%s", &pass);
	if (strcmp(pass, pak) == 0)
	{
		printf("Choose the route you want to change flight time: \n");
		for (j = 0; j < 6; j = j + 2)
		{
			printf("\t%d. %-30s %d. %-30s\n", j + 1, fRoute[j], j + 2, fRoute[j + 1]);
		}
		scanf("%d", &set);
		while (set < 1 || set > 6)
		{
			printf("\nChoice is invalid, please choose another option: ");
			scanf("%d", &set);
		}
		strcat(fRoute[set - 1], "\n");
		f = fopen(path, "r");
		if (!f)
			printf("cannot open file");
		fTemp = fopen("replace.tmp", "w");
		printf("Set the new flight time for the route (HH:MM - 12 hour format ): ");
		fflush(stdin);
		scanf("%d%*c%d", &hour, &min);
		while (((hour < 1) || (hour > 12)) || ((min < 1) || (min > 59)))
		{
			printf("\nTime invalid");
			printf("Set the new flight time for the route (HH:MM - 12 hour format ): ");
			fflush(stdin);
			scanf("%d%*c%d", &hour, &min);
		}

		printf("1: AM                   2. PM\n");
		scanf("%d", &i);

		while (i < 1 || i > 2)
		{
			printf("Choice not available!\n");
			printf("1: AM                   2. PM\n");
			scanf("%d", &i);
		}
		if (i == 1)
			strcpy(apm, "AM");
		if (i == 2)
			strcpy(apm, "PM");
		sprintf(nTime, "%d:%d %s", hour, min, apm);
		while (strcmp(fRoute[set - 1], fgets(buffer, sizeof(buffer), f)) != 0)
		{
			line++;
		}
		rewind(f);
		while (fgets(buffer, sizeof(buffer), f))
		{
			count++;
			if (count == line + 3)
			{
				fputs(nTime, fTemp);
				fputs("\n", fTemp);
			}
			else
				fputs(buffer, fTemp);
		}
		fclose(f);
		fclose(fTemp);
		remove(path);
		rename("replace.tmp", path);
		fRoute[set - 1][strcspn(fRoute[set - 1], "\n")] = 0;
		printf("time of the flight '%s' has been change to %s\n", fRoute[set - 1], nTime);
		system("pause");
		system("cls");
	}
	else
		printf("The entered password is wrong!\n\n");
}

//Route choice
int Choice(int *price)
{
	int i = 0, count = 0, j = 0, choice = 0;
	char line[50];

	//choose route
	printf("Please choose the route: \n");
	for (j = 0; j < 6; j = j + 2)
	{
		printf("\t%d. %-30s %d. %-30s\n", j + 1, fRoute[j], j + 2, fRoute[j + 1]);
	}
	printf("\nType in your option: ");
	scanf("%d", &choice);
	while (choice < 1 || choice > 6)
	{
		printf("\nChoice is invalid, please choose another option: ");
		scanf("%d", &choice);
	}
	strcpy(person[num].route, fRoute[choice - 1]);

	//Get price of the route
	FILE *f;
	f = fopen("FlightSchedule.txt", "r");
	if (!f)
		printf("cannot open file");
	while (fgets(line, sizeof(line), f))
	{
		count++;
		if (count == (3 + (choice - 1) * 5))
		{
			fscanf(f, "%d", &*price);
		}
	}
	fclose(f);

	//Get flight schedule
	count = 0;
	f = fopen("FlightSchedule.txt", "r");
	if (!f)
		printf("cannot open file");
	while (fgets(line, sizeof(line), f))
	{
		count++;
		if (count == (5 + (choice - 1) * 5))
		{
			line[strcspn(line, "\n")] = 0;
			sprintf(person[num].time, line);
		}
	}
	printf("flight time: %s", person[num].time);
	fclose(f);
	return choice;
}

//booking ticket
void Booking(int choice, int oPrice)
{
	int array[48];
	int seatCardinality;
	struct Date current, flight;
	int i, j, validate = 0;
	int price = 0;
	GetSystemDate(&current.d, &current.m, &current.y);
	sprintf(person[num].purchaseDate, "%d/%d/%d", current.d, current.m, current.y);
	do
	{
		printf("\nFlight date (DD/MM/YYYY): ");
		scanf("%d%*c%d%*c%d", &flight.d, &flight.m, &flight.y);
		validate = ValidateTime(flight.d, flight.m, flight.y);
		while (validate == 0)
		{
			printf("\nDate invalid. Please type again");
			printf("\nFlight date (DD/MM/YYYY): ");
			scanf("%d%*c%d%*c%d", &flight.d, &flight.m, &flight.y);
			validate = ValidateTime(flight.d, flight.m, flight.y);
		}
		validate = CompareTime(flight.d, flight.m, flight.y, current.d, current.m, current.y);
		if (validate == 0)
			printf("\nDate invalid. Please type again");
	} while (validate == 0);

	sprintf(person[num].purchaseDate, "%d/%d/%d", current.d, current.m, current.y);
	sprintf(person[num].flightDate, "%d/%d/%d", flight.d, flight.m, flight.y);

	printf("\nPlease enter your name: ");
	scanf(" %19[^\n]%*[^\n]", &person[num].name);
	printf("Please enter your identity number: ");
	scanf("%s", &person[num].identity);
	printf("\n\t\t =========");
	printf("\n\t\t| COCKPIT |");
	int *bookedSeatNo = getBookedSeat(person[num].route, person[num].flightDate, &seatCardinality);
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 4; j++)
		{
			array[i * 4 + j] = i * 4 + j + 1;
		}
	}
	if (bookedSeatNo[0] != 100)
	{
		for (i = 0; i < seatCardinality; i++)
		{
			array[bookedSeatNo[i] - 1] = 0;
		}
	}

	printf("\n\t\t =========\n\n");
	printf("\t _________Business________\n");
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("\t %d", array[i * 4 + j]);
			if (j % 4 == 3)
			{
				printf("\n");
			}
		}
	};
	printf("\t _________Economy__________\n");
	for (i = 4; i < 12; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("\t %d", array[i * 4 + j]);
			if (j % 4 == 3)
			{
				printf("\n");
			}
		}
	}

	int valiseat = 0;
	do
	{
		printf("\nWhich seat number do you want? \n");
		scanf("%d", &j);
		j -= 1;
		if (j > 47 || j < 0)
			valiseat = 0;
		else
			valiseat = 1;
		while (valiseat == 0)
		{
			printf("Sorry, this seat is unavailable! Please choose another seat.\n");
			printf("Please re-enter seat number: ");
			scanf("%d", &j);
			if (j > 47 || j < 0)
				valiseat = 0;
			else
				valiseat = 1;
		}
		if (array[j] == 0)
		{
			printf("Sorry, this seat is unavailable! Please choose another seat.\n");
			valiseat = 0;
		}
		else
			valiseat = 1;
	} while (valiseat == 0);

	array[j] = 1;

	person[num].seat = j + 1;
	if (j >= 0 && j <= 15)
		strcpy(person[num].class, "Business");
	if (j >= 16 && j <= 47)
		strcpy(person[num].class, "Economy");
	price = TotalPrice(oPrice, current, flight);

	person[num].totalPrice = price;

	Ticket(id2, oPrice);
	Cusfile(id2);
	id2++;
	system("pause");
	system("cls");
}

float TotalPrice(int original, struct Date dt1, struct Date dt2)
{
	int week, delta = 0;
	int total = 0;
	float fee1, fee2, fee3;
	//int p, w, delta = 0;
	week = Weekday(dt1.d, dt1.m, dt1.y);
	delta = DateDifference(dt1, dt2);

	if ((week == 0) || (week == 5) || (week == 6))
		fee1 = original * 30 / 100;
	else
		fee1 = 0;

	if (delta <= 30)
		fee2 = original * 10 / 100;
	else if (delta > 30 && delta <= 60)
		fee2 = original * 7 / 100;
	else
		fee2 = 0;

	if (strcmp(person[num].class, "Business") == 0)
		fee3 = original * 20 / 100;
	else
		fee3 = 0;
	total = original + fee1 + fee2 + fee3;
	return total;
}

//Cancel the ticket
void Cancel(char identity[30])
{
	FILE *f;
	FILE *fTemp;
	char buffer[30];
	int line = 0, count = 0;
	char path[] = "Customer.txt";
	char filename[20];
	char directory[300];
	sprintf(filename, "%s.txt", identity);
	strcpy(directory, ".\\Tickets\\");
	strcat(directory, filename);
	if (remove(directory) == 0)
		printf("Cancel ticket successfully!\n");

	f = fopen(path, "r");
	if (!f)
		printf("cannot open file");
	fTemp = fopen("replace.tmp", "w");

	strcat(filename, "\n");
	while (strcmp(filename, fgets(buffer, sizeof(buffer), f)) != 0)
	{
		line++;
	}
	rewind(f);
	while (fgets(buffer, sizeof(buffer), f))
	{
		count++;
		if (count == line + 1)
		{
		}
		else
			fputs(buffer, fTemp);
	}
	fclose(f);
	fclose(fTemp);
	remove("Customer.txt");
	rename("replace.tmp", "Customer.txt");
	system("pause");
	system("cls");
}

//Reserved ticket
void ReservedTicket()
{
	char pass[10], pak[] = "pass";
	char path[] = "Customer.txt";
	char *line1;
	char *line2;
	char *line3;
	char *line5;
	char *line6;
	char **arrfilenames;
	printf("Enter the password to see details: ");
	scanf("%s", &pass);
	if (strcmp(pass, pak) == 0)
	{
		arrfilenames = Readfile(path);

		for (int i = 0; i < (countLine(path) - 1); i++)
		{
			// Lưu dòng thứ i của tất cả các file có trong Customer.txt vào linei
			line1 = getithline(arrfilenames[i], 1);
			line2 = getithline(arrfilenames[i], 2);
			line3 = getithline(arrfilenames[i], 3);
			line5 = getithline(arrfilenames[i], 5);
			line6 = getithline(arrfilenames[i], 6);
			printf("\nCustomer '%s', ID number '%s', booked seat '%s' on the route '%s', flight date: %s\n", line2, line3, line6, line1, line5);
		}
	}
	else
		printf("Entered password is wrong \n");
	system("PAUSE");
	system("cls");
}

// Đọc tất cả các dòng trong Customer.txt và lưu vào 1 mảng
char **Readfile(const char *filename)
{
	FILE *R;
	char line[100];
	char **customerList;
	customerList = (char **)malloc(sizeof(char *));
	int count = 0;
	R = fopen(filename, "r");
	while (fgets(line, sizeof(line), R))
	{
		customerList = (char **)realloc(customerList, (count + 1) * sizeof(char *));
		customerList[count] = (char *)malloc(sizeof(line));
		strcpy(customerList[count], line);
		strtok(customerList[count], "\n");
		count++;
	}
	fclose(R);
	// Trả các tên file trong Cusfile về CustomerList
	return customerList;
}

// Đếm số dòng của 1 file
int countLine(const char *filename)
{
	FILE *R;
	char c;
	int count = 1;
	R = fopen(filename, "r");
	if (!R)
		printf("cannot open file");
	for (c = fgetc(R); c != EOF; c = fgetc(R))
	{
		if (c == '\n')
			count++;
	}
	fclose(R);
	return count;
}

//Ticket
void Ticket(int id2, int original)
{
	system("cls");
	printf("\n\n\n");
	printf("\t                     Booking ticket successfully!");
	printf("\n\n");
	printf("\t        ------------------AIRPLANE TICKET-----------------\n");
	printf("\t=====================================================================\n");
	printf("\t Booking ID : %s         	 Route : %s\n", person[num].identity, person[num].route);
	printf("\t Customer   : %s\n", person[num].name);
	printf("\t\t\t                       Purchase Date    : %s\n", person[num].purchaseDate);
	printf("\t\t\t                       Flight Date      : %s\n", person[num].flightDate);
	printf("\t\t\t			Time      : %s\n", person[num].time);
	printf("\t Seat Class: %-12s            	Seats No. : %d  \n", person[num].class, person[num].seat);
	printf("\t Original price: %d      		Total price (including fee) : %d  \n\n", original, person[num].totalPrice);
	printf("\t=====================================================================\n");
	return;
}

//Print each ticket into a ticket file
void Cusfile(int id2)
{
	FILE *C;
	FILE *D;
	char filename[20];
	char directory[300];
	char s[300];
	sprintf(filename, "%s.txt", person[num].identity);
	strcpy(directory, ".\\Tickets\\");
	strcat(directory, filename);
	C = fopen(directory, "w");
	sprintf(s, "%s\n%s\n%s\n%s\n%s\n%d\n%d", person[num].route, person[num].name, person[num].identity,
			person[num].purchaseDate, person[num].flightDate, person[num].seat, person[num].totalPrice);
	fputs(s, C);

	//Print customer list into Customer.txt
	D = fopen("Customer.txt", "a+");
	strcat(filename, "\n");
	fputs(filename, D);
	fclose(C);
	fclose(D);
}

//Get route list from file and assign to array
void RouteList()
{
	int i = 0, count = 0;
	char line[50];
	FILE *f;
	f = fopen("FlightSchedule.txt", "r");
	if (!f)
		printf("cannot open file");
	while (fgets(line, sizeof(line), f))
	{
		count++;
		for (i = 0; i < 6; i++)
		{
			if (count == 3 + 5 * i)
			{
				line[strcspn(line, "\n")] = 0;
				strcpy(fRoute[i], line);
			}
		}
	}
	fclose(f);
}

//Get system time
void GetSystemDate(int *d, int *m, int *y)
{
	SYSTEMTIME stime;
	GetLocalTime(&stime);
	*d = stime.wDay;
	*m = stime.wMonth;
	*y = stime.wYear;
};

//find weekday of flight date using Sakamoto's method
int Weekday(int d, int m, int y)
{
	int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

// Counts number of leap years before the given date
int countLeapYears(struct Date d)
{
	int years = d.y;
	if (d.m <= 2)
		years--;
	return years / 4 - years / 100 + years / 400;
}

//Returns number of days between two given dates
int DateDifference(struct Date dt1, struct Date dt2)
{
	long int n1 = dt1.y * 365 + dt1.d;

	for (int i = 0; i < dt1.m - 1; i++)
		n1 += monthDays[i];

	n1 += countLeapYears(dt1);

	long int n2 = dt2.y * 365 + dt2.d;
	for (int i = 0; i < dt2.m - 1; i++)
		n2 += monthDays[i];
	n2 += countLeapYears(dt2);

	// return difference between two counts
	return (n2 - n1);
}

// validate date (Check date is valid or not)
int ValidateTime(int dd, int mm, int yy)
{
	int validate = 0;
	//Check validation of dd, mm ,yy
	//check year
	if (yy >= 1900 && yy <= 2030)
	{
		//check month
		if (mm >= 1 && mm <= 12)
		{
			//check days
			if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
				validate = 1;
			else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
				validate = 1;
			else if ((dd >= 1 && dd <= 28) && (mm == 2))
				validate = 1;
			else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
				validate = 1;
			else
				validate = 0;
		}
		else
		{
			validate = 0;
		}
	}
	else
	{
		validate = 0;
	}

	return validate;
}

//compare to current date
int CompareTime(int dd, int mm, int yy, int cd, int cm, int cy)
{
	int validate = 0;
	if (yy == cy)
	{
		if (mm > cm)
			validate = 1;
		else if (mm == cm)
		{
			if (dd >= cd)
				validate = 1;
			else
				validate = 0;
		}
		else
			validate = 0;
	}
	else if (yy > cy)
		validate = 1;
	else
		validate = 0;
	return validate;
}

int isSameFlight(char *route, char *flightDate, char *filename)
{
	if (strcmp(route, getithline(filename, 1)) == 0 && strcmp(flightDate, getithline(filename, 5)) == 0)
	{
		return 1;
	}
	return 0;
}

int *getBookedSeat(char *route, char *flightDate, int *seatCardinality)
{
	int *s;
	s = (int *)malloc(2 * sizeof(int));
	s[0] = 100;
	*seatCardinality = 0;
	int seatCount = 0;
	char **ticketList;
	char *tmp;
	ticketList = Readfile("Customer.txt");
	for (int i = 0; i < countLine("Customer.txt") - 1; i++)
	{
		if (isSameFlight(route, flightDate, ticketList[i]) == 1)
		{
			seatCount += 1;
			*seatCardinality += 1;
			s = (int *)realloc(s, seatCount * sizeof(int));
			tmp = getithline(ticketList[i], 6);
			strtok(tmp, "\n");
			s[seatCount - 1] = atoi(tmp);
		}
	}
	return s;
}
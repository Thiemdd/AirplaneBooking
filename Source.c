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

int count = 0;
//  id2 = 1000;

//Main
int main()
{
	int choice1, choice2, **seat, i, price = 0;
	seat = (int **)calloc(49, sizeof(int *));
	for (i = 0; i < 6; i++)
		*(seat + i) = (int *)calloc(49, sizeof(int));
	int x = 0;

	RouteList();

	while (x != 6)
	{
		choice1 = Menu();
		switch (choice1)
		{
		case 1:
			ChangePrice();
			break;
		case 3:
			ReservedTicket(price);
			break;
		case 4:
			choice2 = Choice(&price);
			Booking(seat[choice2 - 1], choice2, price);
			count++;
			_getch();
			break;
		case 5:
			char idc[30];
			printf("Enter your ticket ID: ");
			scanf("%s", &idc);
			Delfile(idc);
			break;
		case 6:
			x = 6;
			printf("Thank you for using our service!");
			printf("\n        ______________\n");
			break;
		default:
			printf("Choice not available\n");
			system("cls");
		}
		break;
	}
}

//Print choices
int Menu()
{
	int choice1;
	printf("Please choose your option: ");
	printf("\n                 Simple Flight Ticket Booking System\n");
	printf(" ==================================================================\n");
	printf("||             1- To edit price of ticket (only admin):           ||\n");
	printf("||             2- To edit flight schedule (only admin):           ||\n");
	printf("||             3- To view reserved tickets(only admin):           ||\n");
	printf("||             4- To book ticket:                                 ||\n");
	printf("||             5- To cancel the ticket:                           ||\n");
	printf("||             6- Exit system:                                    ||\n");
	printf("||================================================================||\n");
	printf("  Enter your choice: ");
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
	char path[20] = "FlightSchedule.txt";
	int line = 0, count = 0;
	char pass[20], pak[20] = "pass";

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
		if (set < 1 && set > 6)
		{
			printf("\nChoice is invalid, please choice another option: ");
			scanf("%d", &set);
		}
		strcat(fRoute[set - 1], "\n");
		f = fopen(path, "r");
		if (!f)
			printf("cannot open file");
		fTemp = fopen("replace.tmp", "w");
		printf("Set the new price for the route: ");
		scanf("%s", &nPrice);
		fflush(stdin);
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

//Route choice
int Choice(int *price)
{
	int choice = 0, i = 0, count = 0, j = 0, tPrice = 0;
	char line[50];
	FILE *f;
	printf("Please choose the route: \n");
	for (j = 0; j < 6; j = j + 2)
	{
		printf("\t%d. %-30s %d. %-30s\n", j + 1, fRoute[j], j + 2, fRoute[j + 1]);
	}
	printf("\nType in your option: ");
	scanf("%d", &choice);
	if (choice < 1 && choice > 6)
	{
		printf("\nChoice is invalid, please choice another option: ");
		scanf("%d", &choice);
	}
	strcpy(person[count].route, fRoute[choice - 1]);

	//Get price of the route
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
	return choice;
}

//booking ticket
void Booking(int *array, int choice, int price)
{
	int i, j, currentD, currentM, currentY, d, m, y;
	printf("\nWhat day you want to depart? (DD/MM/YYYY): "); //Se phai viet them code dieu kien
															 //cho ngay thang nam nhap vao
	scanf("%d%*c%d%*c%d", &d, &m, &y);
	fflush(stdin);
	printf("\nPlease enter your name: ");
	scanf(" %19[^\n]%*[^\n]", &person[count].name);
	printf("Please enter your identity number: ");
	scanf("%s", &person[count].identity);
	printf("\n\t\t =========");
	printf("\n\t\t| COCKPIT |");
	printf("\n\t\t =========\n\n");
	printf("\t _________Business________\n");
	for (i = 1; i <= 16; i++)
	{
		if (array[i] == 0)
			printf("\t %d", i);
		else
			printf("\t *");
		if (i % 4 == 0)
			printf("\n\n");
	};
	printf("\t _________Economy__________\n");
	for (i = 17; i <= 48; i++)
	{
		if (array[i] == 0)
			printf("\t %d", i);
		else
			printf("\t *");
		if (i % 4 == 0)
			printf("\n");
	}
	printf("\nWhich seat number you want? \n");
	scanf("%d", &j);
	if (j > 48 || j < 1)
	{
		printf("Seat number is unavailable in this flight\n");
		printf("Please re-enter seat number: ");
		scanf("%d", &j);
	}
	if (array[j] == 1)
	{
		printf("Sorry, this ticket is already booked! Please choose another seat.\n");
		scanf("%d", &j);
	}
	else
		array[j] = 1;
	person[count].seat = j;
	if (j >= 1 && j <= 16)
		strcpy(person[count].class, "Business");
	if (j >= 17 && j <= 48)
		strcpy(person[count].class, "Economy");

	GetSystemDate(&currentD, &currentM, &currentY);
	Ticket(person[count].route, person[count].name, person[count].identity, j, price, currentD, currentM, currentY, d, m, y);
	Cusfile(person[count].route, person[count].name, person[count].identity, j, price, currentD, currentM, currentY, d, m, y);
}

//Reserved ticket
void ReservedTicket(int price)
{
	int i;
	char pass[10], pak[10] = "pass";
	printf("Enter the password to see details: ");
	scanf("%s", &pass);
	if (strcmp(pass, pak) == 0)
	{
		if (count == 0)
			printf("There is no ticket booked yet\n");
		else
			for (i = 0; i < count; i++)
			{
				printf("seat no: %d is booked by %s booking id is %d, ticket price: %d\n", person[i].seat, person[i].name, person[i].id, price);
			}
	}
	else
		printf("Entered password is wrong \n");
	system("PAUSE");
	system("cls");
}

//Ticket
void Ticket(char route[30], char name[30], char identity[30], int seat, int price, int cd, int cm, int cy, int d, int m, int y)
{
	system("cls");
	printf("\t                     Booking ticket successfully!");
	printf("\n\n");
	printf("\t       ---------------------AIRPLANE TICKET-------------------\n");
	printf("\t=====================================================================\n");
	printf("\t Booking ID : %s\t\t\tRoute : %s\n", person[count].identity, person[count].route);
	printf("\t Customer  : %s\n", person[count].name);
	printf("\t\t\t                       Purchase Date    : %d/%d/%d\n", cd, cm, cy);
	printf("\t\t\t                       Flight Date      : %d/%d/%d\n", d, m, y);
	printf("\t                                              Time      : 08:00pm\n");
	printf("\t Seat Class: %-12s                     Seats No. : %d  \n", person[count].class, seat);
	printf("\t                                              Price     : %d  \n\n", price);
	// person[count].id = id2;
	printf("\t=====================================================================\n");
	return;
}

//Get route list from file and assign to array
void RouteList()
{
	//Get route list
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

//calculate date difference

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

//Print each ticket into a file

int idx = 0;

void Cusfile(char route[30], char name[30], char identity[30], int seat, int price, int currentD, int currentM, int currentY, int d, int m, int y)
{
	FILE *C;
	char filename[20];
	char directory[300];
	char s[300];
	sprintf(filename, "%s.txt", identity);
	strcat(directory, ".\\Tickets\\");
	strcat(directory, filename);
	C = fopen(directory, "w+");
	// idx = idx + 1;
	sprintf(s, "%s\n%s\n%s\n%d/%d/%d\n%d/%d/%d\n%d\n%d", route, name, identity, currentD, currentM, currentY, d, m, y, seat, price);
	fputs(s, C);
	fclose(C);
}

//Cancel the ticket
void Delfile(char identity[30])
{
	char filename[20];
	char directory[300];
	sprintf(filename, "%s.txt", identity);
	strcat(directory, ".\\Tickets\\");
	strcat(directory, filename);
	if (remove(directory) == 0)
		printf("Cancel ticket successfully!\n");
}
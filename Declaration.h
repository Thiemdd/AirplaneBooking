#pragma once


int Menu(void);
int Choice(int*);
void ChangePrice();
int ChangeFightDate();
void ReservedTicket(int);
int TotalPrice();
void Booking(int*, int, int);
void Cancel();
void Ticket(char[30], char[30], char[30], int, int, int, int, int, int, int, int);
void RouteList();
void GetSystemDate(int* , int* , int*);
int Weekday(int, int, int);
int DateDifference();
void readCusfile();
void Cusfile(char[30], char[30], char[30], int, int, int, int, int, int, int, int);
void Delfile(char[30]);
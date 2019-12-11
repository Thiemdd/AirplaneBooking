#pragma once

int Menu(void);
int Choice(int *);
void ChangePrice();
int ChangeFightDate();
void ReservedTicket();
float TotalPrice(int, struct Date, struct Date);
void Booking(int, int);
void Cancel(char[30]);
void Ticket(int, int);
void Cusfile(int);

//other small function

char **Readfile(const char *);
char *getithline(char[50], int);
int countLine(const char *);
void RouteList(void);
void GetSystemDate(int *, int *, int *);
int Weekday(int, int, int);
int countLeapYears(Date);
int DateDifference(struct Date,  struct Date);
int ValidateTime(int, int, int);
int CompareTime(int, int, int, int, int, int);
int isSameFlight(char *, char *, char *);
int *getBookedSeat(char[30], char[30]);
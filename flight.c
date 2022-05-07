#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void optionsSelected(int selectedOptions);
void selectOption();
void intializeFlight();
char generateSeating();
int parsingString();

const int availableFlights[2] = {101, 102};
const int size = sizeof availableFlights / sizeof availableFlights[0];
char fileNames[2][10] = {"101.txt", "102.txt"};

int flightSeating[size][2][10][10] = {};
int unAvialableSeats[size][2][10][10] = {};
int flightSeatingRows[size][2] = {};
int flightSeatingColumns[size][2] = {};

static int PRICE_ECONOMY[size] = {1000, 1000};
static int PRICE_BUSINESS[size] = {2000, 2000};
int selectedFlight = 0;

char bookedSeats[size][100] = {};
int bookedIds[100][6] = {0};
int amountCollected[100] = {0};
int seatBookedById[100][100][2] = {0};
int bookedFlightAndClass[100][2] = {0};
static int uniqueId = 0;
int businessClass[size][3] = {};
int economyClass[size][3] = {};

int main()
{
    printf("Flight booking system \n");
    intializeFlight();
    printf("Please select any options \n");
    selectOption();
    return 0;
}

void intializeFlight()
{
    printf("Initializing flight ...\n");

    for (size_t a = 0; a < sizeof(fileNames) / sizeof(fileNames[0]); a++)
    {
        printf("Reading flight seats %d \n", availableFlights[a]);
        FILE *file = fopen(fileNames[a], "r");
        int integers[10];

        int i = 0;
        int num;

        char business[10] = {0};
        char economy[10] = {0};

        int BindexPosition = 0;
        int EindexPosition = 0;

        char seating[100];
        char LEFT;
        char RIGHT;
        char MIDDLE = 'M';

        if (NULL == file)
        {
            printf("file can't be opened \n");
        }
        else
        {
            while (fscanf(file, "%d", &num) != EOF)
            {
                integers[i] = num;
                i++;
            }

            for (int j = 0; j < i; j++)
            {
                if (j == 3 || j == 7)
                {
                    flightSeatingRows[a][j == 3 ? 0 : 1] = integers[j];
                    continue;
                }
                if (j < 4)
                {
                    if (j != 3)
                    {
                        businessClass[a][j] = integers[j];
                        switch (j)
                        {
                        case 0:
                            LEFT = 'W';
                            RIGHT = 'A';
                            break;
                        case 1:
                            LEFT = 'A';
                            RIGHT = 'A';
                            break;
                        case 2:
                            LEFT = 'A';
                            RIGHT = 'W';
                            break;
                        }
                        for (int m = 0; m < integers[j]; m++)
                        {
                            if (m == 0)
                            {
                                business[BindexPosition] = LEFT;
                            }
                            else if (m + 1 == integers[j])
                            {
                                business[BindexPosition] = RIGHT;
                            }
                            else
                            {
                                business[BindexPosition] = MIDDLE;
                            }
                            BindexPosition = BindexPosition + 1;
                        }
                    }
                }
                else
                {
                    if (j != 7)
                    {
                        economyClass[a][j - 4] = integers[j];
                        switch (j - 4)
                        {
                        case 0:
                            LEFT = 'W';
                            RIGHT = 'A';
                            break;
                        case 1:
                            LEFT = 'A';
                            RIGHT = 'A';
                            break;
                        case 2:
                            LEFT = 'A';
                            RIGHT = 'W';
                            break;
                        }
                        for (int m = 0; m < integers[j]; m++)
                        {
                            if (m == 0)
                            {
                                economy[EindexPosition] = LEFT;
                            }
                            else if (m + 1 == integers[j])
                            {
                                economy[EindexPosition] = RIGHT;
                            }
                            else
                            {
                                economy[EindexPosition] = MIDDLE;
                            }
                            EindexPosition = EindexPosition + 1;
                        }
                    }
                }
            }

            for (int b = 0; b < size; b++)
            {
                flightSeatingColumns[b][0] = BindexPosition;
                flightSeatingColumns[b][1] = EindexPosition;
                if (flightSeatingRows[b][0] > 0)
                {
                    for (int d = 0; d < flightSeatingRows[b][0]; d++)
                    {
                        for (int ww = 0; ww < BindexPosition; ww++)
                        {
                            flightSeating[b][0][d][ww] = business[ww];
                            unAvialableSeats[b][0][d][ww] = flightSeating[b][0][d][ww];
                        }
                    }
                    for (int d = 0; d < flightSeatingRows[b][1]; d++)
                    {
                        for (int ww = 0; ww < EindexPosition; ww++)
                        {
                            flightSeating[b][1][d][ww] = economy[ww];
                            unAvialableSeats[b][1][d][ww] = flightSeating[b][1][d][ww];
                        }
                    }
                }
            }

            fclose(file);
        }
    }
}

void selectOption()
{
    int selectedOption;
options:
    printf("1.Book \n2.Cancel\n3.Print\n4.Print by Id \nEnter option: ");
    scanf("%d", &selectedOption);
    if (selectedOption > 4)
    {
        printf("Please enter valid option: \n \n");
        goto options;
    }
    else
    {
        optionsSelected(selectedOption);
    }
}

void optionsSelected(int selectedOption)
{
    int renter;
    int selectedFlight;
    int selectClass;
    int numberOfBookings;
    char mealsAdded;
    int numberOfSeats;
    char seatsEntered[] = {};
    int rows[100];
    int columns[100];
    switch (selectedOption)
    {
    case 1:
        printf("Booking \n");
        printf("Please select flight \n1.101\n2.102\n");
        scanf("%d", &selectedFlight);
        if (selectedFlight == 1 || selectedFlight == 2)
        {

            printf("Please select class \n1.Business\n2.Economy\n");
            scanf("%d", &selectClass);
            if (selectClass == 1 || selectClass == 2)
            {
                printf("Do you want meals for this booking? (y/n) \n");
                scanf(" %c", &mealsAdded);

                printf("Enter number of seats\n");
                scanf("%d", &numberOfSeats);
                for (int o = 0; o < numberOfSeats; o++)
                {
                getRows:
                    printf("\n Seat No: %d \n", o + 1);
                    printf("Enter row\n");
                    scanf(" %d", &rows[o]);
                    printf("Enter columns \n");
                    scanf(" %d", &columns[o]);
                    if (flightSeating[selectedFlight - 1][selectClass - 1][rows[o] - 1][columns[o] - 1] == 'W' ||
                        flightSeating[selectedFlight - 1][selectClass - 1][rows[o] - 1][columns[o] - 1] == 'A' ||
                        flightSeating[selectedFlight - 1][selectClass - 1][rows[o] - 1][columns[o] - 1] == 'W')
                    {
                        size_t bookedSize = sizeof(uniqueId) / sizeof(int);
                        for (int l = 0; l < bookedSize; l++)
                        {
                            size_t bookedSize2 = sizeof(seatBookedById[l]) / sizeof(int);
                            for (int m = 0; m < bookedSize2; m++)
                            {
                                if (seatBookedById[l][m][0] == rows[o] &&
                                    seatBookedById[l][m][1] == columns[o])
                                {
                                    printf("Already booked. Try again!!");
                                    goto getRows;
                                }
                                else
                                {
                                    unAvialableSeats[selectedFlight - 1][selectClass - 1][rows[o] - 1][columns[o] - 1] = 1;
                                }
                            }
                        }
                    }
                    else
                    {
                        printf("Enter seats are not available. Try again!!");
                        goto getRows;
                    }
                }
                int totalAmout = 0;
                size_t uniqueSize = sizeof(uniqueId) / sizeof(int);
                for (int f = 0; f < numberOfSeats; f++)
                {
                    // Along with each booking, provide an option to book meal at an additional cost of 200 per passenger
                    int businessAmt = (PRICE_BUSINESS[selectedFlight - 1] * numberOfSeats) + (mealsAdded == 'y' ? numberOfSeats * 200 : 0);
                    int economyAmt = (PRICE_ECONOMY[selectedFlight - 1] * numberOfSeats) + (mealsAdded == 'y' ? numberOfSeats * 200 : 0);
                    totalAmout = selectClass == 1 ? businessAmt : economyAmt;
                    // Aisle and Window seats will cost INR 100 more
                    if (flightSeating[selectedFlight - 1][selectClass - 1][rows[f] - 1][columns[f] - 1] == 'W' || flightSeating[selectedFlight - 1][selectClass - 1][rows[f] - 1][columns[f] - 1] == 'A')
                    {
                        totalAmout += 100;
                    }
                    seatBookedById[uniqueSize - 1][f][0] = rows[f];
                    seatBookedById[uniqueSize - 1][f][1] = columns[f];
                }

                bookedFlightAndClass[uniqueSize - 1][0] = selectedFlight - 1;
                bookedFlightAndClass[uniqueSize - 1][1] = selectClass - 1;

                if (selectClass == 1)
                {
                    PRICE_BUSINESS[selectedFlight - 1] += 200;
                }
                else
                {
                    PRICE_ECONOMY[selectedFlight - 1] += 100;
                }
                amountCollected[uniqueSize - 1] = totalAmout;

                printf("Booked successfully. Total amout to pay: %d \n", totalAmout);
                printf("Your booked id is: %d \n ", uniqueId + 1);
                uniqueId = uniqueId + 1;
                selectOption();
            }
            else
            {
                printf("Please select valid input");
            }
        }
        else
        {
            printf("Please select valid flight");
        }
        break;
    case 2:
        printf("Cancel \n");
        int i, pos;
        printf("Plesase enter your booking id to cancel: ");
        scanf(" %d", &pos);
        size_t bookedSize = sizeof(uniqueId) / sizeof(int);
        if (bookedSize < 0 || bookedSize > size)
        {
            printf("Invalid id! Please enter position between 1 to %zu", bookedSize);
        }
        else
        {
            for (i = pos - 1; i < size - 1; i++)
            {
                unAvialableSeats[bookedFlightAndClass[bookedSize - 1][0]][bookedFlightAndClass[bookedSize - 1][1]][seatBookedById[bookedSize][i][0]][seatBookedById[bookedSize][i][1]] = flightSeating[bookedFlightAndClass[bookedSize - 1][0]][bookedFlightAndClass[bookedSize - 1][1]][seatBookedById[bookedSize][i][0]][seatBookedById[bookedSize][i][1]];

                printf("Cancelled seat: %d  %d \n", seatBookedById[i][pos][0] + 1, seatBookedById[i][pos][1] + 1);
                seatBookedById[bookedSize][i][0] = seatBookedById[bookedSize + 1][i][0];
                seatBookedById[bookedSize][i][1] = seatBookedById[bookedSize + 1][i][1];
                printf("Amount Refund will be %d \n", amountCollected[bookedSize - 1] - 200);
                amountCollected[bookedSize - 1] = amountCollected[bookedSize + 1];
                bookedFlightAndClass[bookedSize - 1][0] = bookedFlightAndClass[bookedSize + 1][0];
                bookedFlightAndClass[bookedSize - 1][1] = bookedFlightAndClass[bookedSize + 1][1];
            }
            uniqueId--;
        }

        break;
    case 3:
        printf("Print  \n");
        for (int h = 0; h < size; h++)
        {
            printf("\nflight %d \n", availableFlights[h]);

            for (int k = 0; k < flightSeatingRows[h][0]; k++)
            {
                printf("\n");
                size_t bookedSize = sizeof(unAvialableSeats[h][0][k]) / sizeof(int);
                for (int l = 0; l < bookedSize; l++)
                {
                    printf("\t");

                    printf("%c", unAvialableSeats[h][0][k][l]);
                }
            }

            for (int k = 0; k < flightSeatingRows[h][1]; k++)
            {
                printf("\n");
                size_t bookedSize = sizeof(unAvialableSeats[h][0][k]) / sizeof(int);
                for (int l = 0; l < bookedSize; l++)
                {
                    printf("\t");

                    printf("%c", unAvialableSeats[h][1][k][l]);
                }
            }
        }

        break;
    case 4:
        printf("Print ticket \n");
        break;
    }
}

// Evren ERGEN
// 21300781
// CS 201 Homework 1
// Section 2

#ifndef BOXOFFICE_H
#define BOXOFFICE_H
#include <string>
using namespace std;

class BoxOffice
{
    public:
        BoxOffice();
        ~BoxOffice();
        void addTheater(int theaterId, string movieName, int numRows, int numSeatPerRow);
        void removeTheater(int theaterId);
        void showAllTheaters();
        void showTheater(int theaterId);
        int makeReservation(int theaterId, int numAudiences, char *seatRow, int *seatCol);
        void cancelReservation(int resCode);
        void showReservation(int resCode);

    protected:
    private:
        int* theaterSizeRow;
		int* theaterSizeCol;
		int* available;
		int* theaters;
		int* codeIndex;
		int* time;
		int* canceled;

		string* seats;
		string* reservations;
		string* theaterNames;

		int** resCol;
		string** resRow;

        bool removed;

        int cancelTimer;
        int code;
		int size;
};

#endif // BOXOFFICE_H

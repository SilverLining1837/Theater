

#include "BoxOffice.h"
#include <string>
#include <iostream>
using namespace std;

BoxOffice::BoxOffice()
{
//Default constructor
    theaters = NULL;
    theaterNames = NULL;
	theaterSizeRow = NULL;
	theaterSizeCol = NULL;
	seats = NULL;
	available = NULL;
	reservations = NULL;
	canceled = NULL;
	codeIndex = NULL;
	time = NULL;
    resCol = NULL;
    resRow = NULL;
    removed = false;
	size = 0;
	code = 0;
	cancelTimer = 0;
}

BoxOffice::~BoxOffice()
{
    // Destructor for deleting pointers
    for(int i = 0; i < code; i++){
            delete []resCol[i];
            delete []resRow[i];
    }
    delete []resCol;
    delete []resRow;
    delete []theaterSizeRow;
    delete []theaterSizeCol;
    delete []available;
    delete []theaters;
    delete []codeIndex;
    delete []time;
    delete []canceled;
    delete []reservations;
    delete []seats;
    delete []theaterNames;
}

void BoxOffice::addTheater(int theaterId, string movieName, int numRows, int numSeatPerRow){
    // Checks if theater already exists
    for(int i = 0;i < size;i++)
	{
		if(theaterId == theaters[i])
		{
			cout << "Theater "<< theaterId << "(" << theaterNames[i] << ") already exists"<<endl;
			return;
		}
	}
    // If there is no theater in office, allocates memory from heap for every pointers
	if(size == 0)
	{
		theaters = new int[1];
		seats = new string[1];
        available = new int[1];
		theaterNames = new string[1];
		theaterSizeRow = new int[1];
        theaterSizeCol = new int[1];
        theaterSizeRow[0] = numRows;
        theaterSizeCol[0] = numSeatPerRow;
		theaters[0] = theaterId;
		theaterNames[0] =  movieName;
        available[0] = numRows*numSeatPerRow;
        for(int i = 0; i < available[0]; i++){
            seats[0] += "o";
        }
		size++;
	}
	else
	{
	    // Moving pointer array into bigger one in order to expand the office
        int* theatersTemp = new int[size+1];
		string* theaterNamesTemp = new string[size+1];
		int* availableTemp = new int[size+1];
		string* seatsTemp = new string[size+1];
		int* theaterSizeColTemp = new int[size+1];
		int* theaterSizeRowTemp = new int[size+1];

        // Taking informations from the old theater arrays
		for(int i = 0;i < size;i++)
		{
				theatersTemp[i]=theaters[i];
				theaterNamesTemp[i]=theaterNames[i];
				theaterSizeRowTemp[i] = theaterSizeRow[i];
                theaterSizeColTemp[i] = theaterSizeCol[i];
				seatsTemp[i] = seats[i];
				availableTemp[i] = available[i];

		}

        // Adding the last theater into the new pointer array
        theatersTemp[size]=theaterId;
        theaterNamesTemp[size]=movieName;
        theaterSizeRowTemp[size] = numRows;
        theaterSizeColTemp[size] = numSeatPerRow;
        availableTemp[size] = numRows*numSeatPerRow;

        // Adjusting seats as available
        for(int i = 0; i < availableTemp[size]; i++){
            seatsTemp[size] += "o";
        }
        // Deleting extra pointer in order not to leak any memory
        delete []theaters;
		delete []theaterSizeCol;
		delete []theaterSizeRow;
		delete []available;
        delete []seats;
        delete []theaterNames;

        // Changing the pointees of main pointers from temporary ones
		theaters = theatersTemp;
		theaterNames = theaterNamesTemp;
		theaterSizeRow = theaterSizeRowTemp;
		theaterSizeCol = theaterSizeColTemp;
		seats = seatsTemp;
		available = availableTemp;
		size++;

	}

	// Confirmation
	cout << "Theater " << theaterId << " (" << movieName << ") has been added" << endl;
}



void BoxOffice::removeTheater(int theaterId){
    bool check=false;
	int find;
	string theaterName;

	// Finding the theater and keep its index to use
	for(int i = 0; i < size; i++)
	{
		if(theaterId==theaters[i])
		{
			check=true;
			find = i;
			theaterName = theaterNames[i];
		}
	}

	// If there is no compatible theater, warns the user
	if(check==false)
	{
		cout << "Theater " << theaterId << " does not exist"<< endl;
		return;
	}

    // If size is one, destroys pointees
	if(size == 1)
	{
		for(int i = 0; i < code; i++){
            delete []resCol[i];
            delete []resRow[i];
    }
        delete []resCol;
        delete []resRow;
        delete []theaterSizeRow;
        delete []theaterSizeCol;
        delete []available;
        delete []theaters;
        delete []codeIndex;
        delete []time;
        delete []canceled;
        delete []reservations;
        delete []seats;
        delete []theaterNames;
		size--;
	}
	else
	{
	    // Exact the same for adding theater except removing the size by one
		int* theatersTemp = new int[size-1];
		string* theaterNamesTemp = new string[size-1];
		int* theaterSizeColTemp = new int[size-1];
		int* theaterSizeRowTemp = new int[size-1];
		int* availableTemp = new int[size-1];
		string* seatsTemp = new string[size-1];
		int j=0;
		for(int i = 0;i < size; i++)
		{
			if(find!=i)
			{
				theatersTemp[j] = theaters[i];
				theaterNamesTemp[j] = theaterNames[i];
				theaterSizeRowTemp[j] = theaterSizeRow[i];
                theaterSizeColTemp[j] = theaterSizeCol[i];
				availableTemp[j] = available[i];
                seatsTemp[j] = seats[i];
				j++;
			}
		}
        for(int i = 0; i < code; i++){
            if(theaters[codeIndex[i]] == theaters[find]){
                removed = true;
                cancelReservation(i+1);
            }
		}

		// Deleting extra pointees from heap
		delete []theaters;
		delete []theaterSizeCol;
		delete []theaterSizeRow;
		delete []available;
        delete []seats;
        delete []theaterNames;
		theaters = theatersTemp;
		theaterNames = theaterNamesTemp;
		theaterSizeRow = theaterSizeRowTemp;
		theaterSizeCol = theaterSizeColTemp;
		seats = seatsTemp;
		available = availableTemp;
		size--;

	}


	cout<<"Theater " << theaterId << " (" << theaterName << ") and all of its reservations are canceled" << endl;
}
void BoxOffice::showAllTheaters(){

    // Warns user that there is no theater in the office
    if(size == 0)
		cout << "No movie theaters in the system!"<<endl;
	else
	{
	    // Shows theaters by ID's, names and available seats
        cout << "Theaters currently in the system:" << endl;
		for(int i = 0;i < size; i++)
		{
			cout << "Theater " << theaters[i] << " (" << theaterNames[i] << "): " << available[i] << " available seats " << endl;
		}
	}
}
void BoxOffice::showTheater(int theaterId){
    bool check = false;
    int find;
    string theaterName;

    // Checking and keeping the index of theater if it exists
    for(int i = 0; i < size; i++){
        if(theaterId == theaters[i]){
            check = true;
            find = i;
            theaterName = theaterNames[i];
        }
    }

    // Return anything if there is no theater at specified index
    if (check == false){
            cout << "Theater " << theaterId << " does not exist" << endl;
            return;
    }

    // Showing available seats
    cout << "Theater " << theaterId << " (" << theaterName << ") has " << available[find] << " available seats" << endl;
    for(int i = 0; i < theaterSizeCol[find]; i++){
        cout << "\t" << i+1 << " ";
    }
    cout << endl;
    int k = 0;
    string c = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Creating the theater saloon with available/taken seats
    for(int i = 0; i < theaterSizeRow[find]; i++){
        cout << c[i] << "\t";
        for(int j = 0; j < theaterSizeCol[find]; j++){
            cout << seats[find][k] << "\t";
            k++;
        }
        cout << endl;
    }

}
int BoxOffice::makeReservation(int theaterId, int numAudiences, char *seatRow, int *seatCol){
    bool check = false;
    int find;
    string theaterName;
    string seat;
    for(int i = 0; i < size; i++){
        // Checking the theater
        if(theaterId == theaters[i]){
            check = true;
            find = i;
            theaterName = theaterNames[i];
        }
    }
    // Does nothing if there is no theater at this ID
    if(check == false){
            cout << "Theater " << theaterId << " does not exist" << endl;
            return -1;
    }
        // Checks if there is enough space for audience first
    if(numAudiences > available[find]){
        cout << "Theater " << theaterId << " (" << theaterName << ") does not have enough space for " << numAudiences << " audiences" << endl;
        return -1;
    }

    for(int i = 0; i < numAudiences; i++){
        // Checks if there is enough space for row
        if((seatRow[i]-'A')>theaterSizeRow[find]){
            cout << "There is not enough row for reservation!";
            return -1;
        }
    }
    for(int i = 0; i < numAudiences; i++){
        // Checks the column number and reservation
        if(seatCol[i]>theaterSizeCol[find]){
            cout << "There is not enough column for reservation!";
            return -1;
        }
    }


    int* reserve = new int[numAudiences];

    // If there is enough space, it holds the numbers of reserved places numerically
    for(int i = 0; i < numAudiences; i++){
        reserve[i] = (seatRow[i]-'A')*theaterSizeCol[find]+seatCol[i]-1;
    }

    // If any of the seats has been taken, returns and warns the user
    for(int i = 0; i < numAudiences; i++){
        if(seats[find].at(reserve[i]) == 'x'){
            cout << "Seat " << seatRow[i] << "" << seatCol[i] <<" has already been taken" << endl;
            delete []reserve;
            return -1;
        }
    }

    // Decreasing the number of available seats if the reservation can be made
    available[find]-=numAudiences;


    // Changing the available seats to taken ones
    for(int i = 0; i < numAudiences; i++){
        seats[find][reserve[i]] = 'x';
    }

    // Deleting the reserve array for memory leak
    delete []reserve;

    // Holding the reservation informations for all office and theaters
    if(code == 0){
        codeIndex = new int[1];
        resCol = new int*[1];
        resRow = new string*[1];
        time = new int[1];
        time[0] = numAudiences;
        codeIndex[0] = find;
        resRow[0] = new string[numAudiences];
        resCol[0] = new int[numAudiences];

        for(int i = 0; i < numAudiences; i++){
            resCol[0][i] = seatCol[i];
            resRow[0][i] = seatRow[i];
        }
    }

    else{
        int* codeIndexTemp = new int[code+1];
        string** resRowTemp = new string*[code+1];
        int** resColTemp = new int*[code+1];
        int* timeTemp = new int[code+1];

        for(int i = 0; i < code; i++){
            resRowTemp[i] = new string[time[i]];
            resColTemp[i] = new int[time[i]];
        }
        resRowTemp[code] = new string[numAudiences];
        resColTemp[code] = new int [numAudiences];
        for(int i = 0; i < code; i++){
            codeIndexTemp[i] = codeIndex[i];
            timeTemp[i] = time[i];
            for(int j= 0; j < time[i];j++){
                resRowTemp[i][j] = resRow[i][j];
                resColTemp[i][j] = resCol[i][j];
            }
        }
        codeIndexTemp[code] = find;
        timeTemp[code] = numAudiences;
        for(int j = 0; j < numAudiences;j++){
            resRowTemp[code][j] = seatRow[j];
            resColTemp[code][j] = seatCol[j];
        }

        // After taking all information from older arrays, delete them for memory leak
        delete []codeIndex;
        for(int k = 0; k < code; k++){
            delete []resCol[k];
            delete []resRow[k];
        }
        delete []resCol;
        delete []resRow;
        delete []time;
        codeIndex = codeIndexTemp;
        resRow = resRowTemp;
        resCol = resColTemp;
        time = timeTemp;
    }
    // Gives a code and increments the code for new reservations
    code++;
    return code;
}


void BoxOffice::cancelReservation(int resCode){
    // Checking if the code is in wanted scope
   if(resCode <= code && resCode > 0){
        if(!removed){
            // If remove theater function calls this function, it does not print the message out
            cout << "Reservation for seats ";
            for(int i = 0; i < time[resCode-1]; i++ ){
                cout << resRow[resCode-1][i] << resCol[resCode-1][i] << " ";
            }
            cout << "is canceled in Theater " << theaters[codeIndex[resCode-1]] << " (" << theaterNames[codeIndex[resCode-1]] << ")" << endl;
            removed = false;
        }

        // Taking reservation that wanted to be canceled information
        int* reserve = new int[time[resCode-1]];
        for(int i = 0; i < time[resCode-1]; i++){
            if(resRow[resCode-1][i] == "A"){
               reserve[i] = resCol[resCode-1][i]-1;
            }
            else if(resRow[resCode-1][i] == "B"){
                reserve[i] = theaterSizeCol[codeIndex[resCode-1]]+resCol[resCode-1][i]-1;
            }
            else if(resRow[resCode-1][i] == "C"){
                reserve[i] = 2*theaterSizeCol[codeIndex[resCode-1]]+resCol[resCode-1][i]-1;
            }
            else if(resRow[resCode-1][i] == "D"){
                reserve[i] = 3*theaterSizeCol[codeIndex[resCode-1]]+resCol[resCode-1][i]-1;
            }
            else if(resRow[resCode-1][i] == "E"){
                reserve[i] = 4*theaterSizeCol[codeIndex[resCode-1]]+resCol[resCode-1][i]-1;
            }
            else if(resRow[resCode-1][i] == "F"){
                reserve[i] = 5*theaterSizeCol[codeIndex[resCode-1]]+resCol[resCode-1][i]-1;
            }
            else if(resRow[resCode-1][i] == "H"){
                reserve[i] = 6*theaterSizeCol[codeIndex[resCode-1]]+resCol[resCode-1][i]-1;
            }
            else if(resRow[resCode-1][i] == "I"){
                reserve[i] = 7*theaterSizeCol[codeIndex[resCode-1]]+resCol[resCode-1][i]-1;
            }
            else if(resRow[resCode-1][i] == "J"){
                reserve[i] = 8*theaterSizeCol[codeIndex[resCode-1]]+resCol[resCode-1][i]-1;
            }
            else if(resRow[resCode-1][i] == "K"){
                reserve[i] = 9*theaterSizeCol[codeIndex[resCode-1]]+resCol[resCode-1][i]-1;
            }
            else if(resRow[resCode-1][i] == "L"){
                reserve[i] = 10*theaterSizeCol[codeIndex[resCode-1]]+resCol[resCode-1][i]-1;
            }
            else if(resRow[resCode-1][i] == "M"){
                reserve[i] = 11*theaterSizeCol[codeIndex[resCode-1]]+resCol[resCode-1][i]-1;
            }
            else if(resRow[resCode-1][i] == "N"){
                reserve[i] = 12*theaterSizeCol[codeIndex[resCode-1]]+resCol[resCode-1][i]-1;
            }
        }

        // Changing seats as available
        for(int i = 0; i < time[resCode-1]; i++){
            seats[codeIndex[resCode-1]][reserve[i]] = 'o';
        }

        // Avoiding memory leaks
        delete []reserve;
        available[codeIndex[resCode-1]]+=time[resCode-1];
        if(cancelTimer == 0){
            canceled = new int[1];
            canceled[0] = resCode;
        }
        else{
            // Creating an array for canceled reservations
            int* canceledTemp = new int[cancelTimer+1];
            for(int i = 0; i < cancelTimer; i++){
                canceledTemp[i] = canceled[i];
            }
            delete []canceled;
            canceledTemp[cancelTimer] = resCode;
            canceled = canceledTemp;
        }
        cancelTimer++;
    }
    else
        cout << "No reservations are found under code " << resCode << endl;


}
void BoxOffice::showReservation(int resCode){
    // Checking the code
    if(resCode <= code && resCode > 0){

        for(int i = 0; i < cancelTimer; i++){
            if(canceled[i] == resCode){
                cout << "No reservations are found under code " << resCode << endl;
                return;
            }
        }
        // Showing the reservation
        cout << "Reservations under code " << resCode << " in Theater " << theaters[codeIndex[resCode-1]] << " (" << theaterNames[codeIndex[resCode-1]] << "): ";

        for(int i = 0; i < time[resCode-1]; i++ ){
            // Showing which seats are reserved by this code
            cout << resRow[resCode-1][i] << resCol[resCode-1][i] << " ";
        }
        cout << endl;
    }

    else{
        cout << "No reservations are found under code " << resCode << endl;
        return;
    }
}

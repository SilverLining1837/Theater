


#include "BoxOffice.h"
#include <string>
#include <iostream>
using namespace std;

int main(){
    BoxOffice R;
    R.showAllTheaters();
    R.addTheater(10425, "Ted", 4, 3);
    R.addTheater(8234, "Cloud Atlas", 8, 3);
    R.addTheater(9176, "Hope Springs", 6, 2);
    cout << endl;
    R.showAllTheaters();
    cout << endl;
    R.addTheater(10425, "Skyfall", 8, 6);
    cout << endl;
    R.showAllTheaters();
    cout << endl;
    R.showTheater(10425);
    cout << endl;
    char rowRes1[4] = {'A','B','B','C'};
    int colRes1[4] = {3,3,1,1};
    int code1 = R.makeReservation(10425,4,rowRes1,colRes1);
    if(code1!=-1)
        cout << "Your reservation code is " << code1 << endl;

    cout << endl;
    R.showTheater(10425);
    cout << endl;
    char rowRes2[2] = {'A','D'};
    int colRes2[2] = {2,3};
    int code2 = R.makeReservation(10425,2,rowRes2,colRes2);
    if(code2!=-1)
        cout << "Your reservation code is " << code2 << endl;
    cout << endl;
    R.showTheater(10425);
    cout << endl;
    char rowRes3[2] = {'B','A'};
    int colRes3[2] = {2,3};
    int code3 = R.makeReservation(10425,2,rowRes3,colRes3);
    if(code3!=-1)
        cout << "Your reservation code is " << code3 << endl;

    cout << endl;
    R.showTheater(10425);
    cout << endl;
    char rowRes4[7] = {'A','B','C','C', 'A', 'B', 'D'};
    int colRes4[7] = {1,2,2,3,2,1,2};
    int code4 = R.makeReservation(10425,7,rowRes4,colRes4);
    if(code4!=-1)
        cout << "Your reservation code is " << code4 << endl;
    cout << endl;
    R.showTheater(10425);
    cout << endl;
    R.showAllTheaters();
    cout << endl;
    R.showReservation(code1);
    R.showReservation(100);
    R.cancelReservation(code2);
    cout << endl;
    R.showTheater(10425);
    cout << endl;
    R.showAllTheaters();
    cout << endl;
    R.cancelReservation(300);
    cout << endl;
    R.removeTheater(8234);
    R.showTheater(8234);
    cout << endl;
    R.showAllTheaters();
    cout << endl;
    R.removeTheater(674);
    cout << endl;
    R.showAllTheaters();
    cout << endl;
    R.removeTheater(10425);
    cout << endl;
    R.showReservation(code1);
    cout << endl;
    R.showAllTheaters();
    cout << endl;
    BoxOffice R2;

    R2.showAllTheaters();
    R2.addTheater(9176,"Skyfall", 3, 3);
    cout << endl;
    R2.showAllTheaters();
    return 0;
}

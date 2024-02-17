#include<iostream>
#include<fstream>
#include <iomanip>

#include "bus.h"
#include "ticket.h"
#include "utils.h"
using namespace std;

void Bus:: addBus(){
    fstream busFileStream;
    system("cls");
    printHeading("ADD BUS");

    cout << "\n\t\t\t\t\t\tEnter Bus Number: ";
    cin.ignore();
    cin>>busNo;
    cout << "\n\t\t\t\t\t\tEnter Source: ";
    cin>>source;
    cout << "\n\t\t\t\t\t\tEnter Destination: ";
    cin>>destination;
    cout << "\n\t\t\t\t\t\tEnter Source Time: ";
    cin>>sourceTime;
    cout << "\n\t\t\t\t\t\tEnter Destination Time: ";
    cin>>destinationTime;
    cout << "\n\t\t\t\t\t\tEnter Bus Fare: ";
    cin>>busFare;

    busFileStream.open("buses.dat", ios::out| ios::app | ios::binary);

    if (!busFileStream) {
        cout << "\n\t\t\t\t\t\tError: Unable to open file.\n";
        return;
    }
    // Move the file pointer to the end of the file
    busFileStream.seekp(0, ios::end);
    busFileStream.write((char *)this, sizeof(*this));
    busFileStream.close();

    cout << "\n\t\t\t\t\t\t\t\t\t\tBus Added Successfully...!!!:-> \n";
}

void Bus::showBusDetails(){
    cout << "\t\t\t\t\t\t-----------------------------------------------\n";
    cout << "\t\t\t\t\t\t Bus No: " << getBusNo();
    cout << "\n\t\t\t\t\t\t Source: " << getSource();
    cout << "\n\t\t\t\t\t\t Destination: " << getDestination();
    cout << "\n\t\t\t\t\t\t Time: " << getSourceTime() << " - " << getDestinationTime();
    cout << "\n\t\t\t\t\t\t Total Seats: " << getMaxSeats();
    cout << "\n\t\t\t\t\t\t Seats Remaining: " << (getMaxSeats() - getBookedSeats());
    cout << fixed << setprecision(2);
    cout << "\n\t\t\t\t\t\t Bus Fare: " << getBusFare();
    cout << "\n\t\t\t\t\t\t-----------------------------------------------\n";
    cout << "\n";
}

void Bus:: showAllBus(){
    system("cls");
    fstream busFileStream;

    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
    if (!busFileStream)
        cout << "\n\t\t\t\tFile Not Found...!!!";
    else{
        printHeading("BUSES");
        busFileStream.read((char *)this, sizeof(*this));

        while (!busFileStream.eof()){
            showBusDetails();
            busFileStream.read((char *)this, sizeof(*this));
        }
        busFileStream.close();
    }
}

void Bus:: viewBusDetails(){
    system("cls");

    string bNo;
    bool chk = 0;
    fstream busFileStream;

    printHeading("VIEW BUS INFO");
    cout << "\n\t\t\t\t\t\tEnter Bus Number: ";
    cin.ignore();
    cin>>bNo;

    system("cls");
    printHeading("BUS INFO");

    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
    if (busFileStream.fail()){
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else{
        busFileStream.read((char *)this, sizeof(*this));
        while (!busFileStream.eof()){  //true if file has been reached
            if (getBusNo()==bNo){
                showBusDetails();
                chk = 1;
            }
            busFileStream.read((char *)this, sizeof(*this));
        }
        if (!chk){
            cout << "\n\t\t\t\t\t\tBus Not Found...!!\n";
        }
        busFileStream.close();
    }
}

void Bus:: editBus(){
    system("cls");

    string bNo;
    int chk = 0;

    fstream busFileStream, tempFileStream;

    printHeading("EDIT BUS");
    cout << "\n\t\t\t\t\t\tEnter Bus Number: ";
    cin.ignore();
    cin>>bNo;

    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);

    if (busFileStream.fail()){
        cout << "\n\t\t\t\t\t\tCan't Open File...!!\n";
    }

    else{
        tempFileStream.open("temp.dat", ios::out | ios::app | ios::binary);

        busFileStream.read((char *)this, sizeof(*this));
        while (!busFileStream.eof()){
            if (getBusNo()==bNo){
                system("cls");
                printHeading("EDIT BUS");

                showBusDetails();
                string s, d, sTime, dTime;
                double fare;
                cout << "\n\t\t\t\t\t\tEnter Source: ";
                cin>>s;
                cout << "\n\t\t\t\t\t\tEnter Destination: ";
                cin>>d;
                cout << "\n\t\t\t\t\t\tEnter Source Time: ";
                cin>>sTime;
                cout << "\n\t\t\t\t\t\tEnter Destination Time: ";
                cin>>dTime;
                cout << "\n\t\t\t\t\t\tEnter Bus Fare: ";
                cin.ignore();
                cin >> fare;
                setSource(s);
                setDestination(d);
                setSourceTime(sTime);
                setDestinationTime(dTime);
                setBusFare(fare);
                tempFileStream.write(reinterpret_cast<const char*>(this), sizeof(this));

                chk = 1;
            }
            else{
                tempFileStream.write(reinterpret_cast<const char*>(this), sizeof(this));
            }
            busFileStream.read((char *)this, sizeof(*this));
        }

        if (chk = 1){
            cout << "\n\t\t\t\t\t\tBus Updated Successfully...!!\n";
        }
        else
        {
            cout << "\n\t\t\t\t\t\tBus Not Found...!!\n";
        }

        busFileStream.close();
        tempFileStream.close();
        remove("buses.dat");
        rename("temp.dat", "buses.dat");
    }
}

void Bus:: deleteBus(){
    system("cls");

    string bNo;
    bool chk = 0;
    fstream busFileStream, tempFileStream;

    printHeading("DELETE BUS");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter Bus No:-> ";
    cin.ignore();
    cin>>bNo;

    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);

    if (busFileStream.fail()){
        cout << "\n\\t\t\t\t\t\tCan't Open File...!!";
        system("pause");
    }

    else{
        tempFileStream.open("temp.dat", ios::out | ios::app | ios::binary);
        busFileStream.read((char *)this, sizeof(*this));
        while (!busFileStream.eof())
        {
            if (getBusNo()==bNo)
                tempFileStream.write((char *)this, sizeof(*this));
            
            else
                chk = 1;
            
            busFileStream.read((char *)this, sizeof(*this));
        }

        if (chk == 0)
            cout << "\n\t\t\t\t\t\tBus Not Found...!!\n";
        
        else
            cout << "\n\t\t\t\t\t\tBus Deleted...!!\n";

        busFileStream.close();
        tempFileStream.close();
        remove("buses.dat");
        rename("temp.dat", "buses.dat");
    }
}
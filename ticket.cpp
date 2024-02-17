#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>

#include "ticket.h"
#include "bus.h"
#include "utils.h"

using namespace std;

void Ticket::generateTicket(string n, Bus b){
    name=n;
    pnrNo= generatePNR(99999).c_str();
    date= getCurrentDate().c_str();
    bus = b;
}

void Ticket::displayTicket(){
    cout << "\t\t\t\t\t\t-------------------------------------------------\n";
    cout << "\t\t\t\t\t\t Name: " << getName();
    cout << "\n\t\t\t\t\t\t PNR No: " << getPnrNo();
    cout << "\n\t\t\t\t\t\t Bus No: " << bus.getBusNo();
    cout << "\n\t\t\t\t\t\t Seat No.: " << bus.getBookedSeats();
    cout << "\n\t\t\t\t\t\t Date: " << getDate();
    cout << "\n\t\t\t\t\t\t From: " << bus.getSource();
    cout << "\n\t\t\t\t\t\t To: " << bus.getDestination();
    cout << "\n\t\t\t\t\t\t Source Time: " << bus.getSourceTime();
    cout << "\n\t\t\t\t\t\t Destination Time: " << bus.getDestinationTime();
    cout << fixed << setprecision(2);
    cout << "\n\t\t\t\t\t\t Bus Fare: " << bus.getBusFare();
    cout << "\n\t\t\t\t\t\t-------------------------------------------------\n";
    cout << "\n";
}

void Ticket::bookTicket(){
    system("cls");

    string from, to;
    bool chk = 0;
    Bus b;
    fstream busFileStream, ticketFileStream, tempFileStream;

    printHeading("BOOK TICKET");

    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
    if (busFileStream.fail())
        cout << "\n\t\t\t\t\t\tCan't Open File...!!\n";

    else{
        cout << "\n\t\t\t\t\t\tEnter Source: ";
        cin.ignore();
        cin>>from;
        cout << "\n\t\t\t\t\t\tEnter Destination: ";
        cin>>to;

        system("cls");
        printHeading("AVAILABLE BUSES");

        busFileStream.read((char *)&b, sizeof(b));
        while (!busFileStream.eof()){
            if (b.getSource()==from && b.getDestination()==to){
                b.showBusDetails();
                chk = 1;
            }
            busFileStream.read((char *)&b, sizeof(b));
        }

        busFileStream.close();

        if (chk == 0)
            cout << "\n\t\t\t\t\t\tNo Buses Found...!!\n";
        else{
            string bNo;
            int booked = 0;

            cout << "\n\t\t\t\t\t\tEnter Bus Number: ";
            cin>>bNo;

            busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
            tempFileStream.open("temp.dat", ios::out | ios::app | ios::binary);

            busFileStream.read((char *)&b, sizeof(b));
            while (!busFileStream.eof()){
                if (b.getSource()==from && b.getDestination()==to && b.getBusNo()==bNo){
                    if (b.getBookedSeats() >= 40){
                        cout << "\n\t\t\t\t\t\tSeat not available...!!\n";
                        break;
                    }
                    else{
                        system("cls");
                        printHeading("BOOK TICKET");
                        string n;
                        cout << "\n\t\t\t\t\t\tEnter Customer Name : ";
                        cin>>n;
                        b.setBookedSeats();
                        generateTicket(n, b);
                        ticketFileStream.open("tickets.dat", ios::out | ios::app | ios::binary);
                        ticketFileStream.write((char *)this, sizeof(*this));
                        ticketFileStream.close();
                        tempFileStream.write((char *)&b, sizeof(b));

                        booked = 1;
                        system("cls");
                        printHeading("BOOKING DETAILS");
                        displayTicket();
                        cout << "\n\t\t\t\t\t\tTicket Booked Successfully...!!\n";
                    }
                }
                else
                    tempFileStream.write((char *)&b, sizeof(b));
                
                busFileStream.read((char *)&b, sizeof(b));
            }

            if (booked == 1){
                busFileStream.close();
                tempFileStream.close();
                remove("buses.dat");
                rename("temp.dat", "buses.dat");
            }
        }
        busFileStream.close();
    }
}

void Ticket::cancelTicket(){
    system("cls");

    string pnr;
    bool chk = 0;

    fstream busFileStream, ticketFileStream, tempFileStream, busTempFileStream;

    printHeading("CANCEL TICKET");
    cout << "\n\t\t\t\t\t\t\t\t\t\tEnter PNR Number:-> ";
    cin.ignore();
    cin>>pnr;

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    tempFileStream.open("temp.dat", ios::out | ios::app | ios::binary);

    if (ticketFileStream.fail())
        cout << "\n\t\t\t\t\t\t\t\t\t\tCan't Open File...!!\n";

    else{
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof()){
            if (getPnrNo()==pnr)
                tempFileStream.write((char *)this, sizeof(*this));
            
            else{
                Bus b;
                busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
                busTempFileStream.open("bustemp.dat", ios::out | ios::app | ios::binary);

                busFileStream.read((char *)&b, sizeof(b));
                while (!busFileStream.eof()){
                    if (b.getBusNo()==bus.getBusNo()){
                        b.setCancelTicket();
                        busTempFileStream.write((char *)&b, sizeof(b));
                    }
                    else
                        busTempFileStream.write((char *)&b, sizeof(b));
                    
                    busFileStream.read((char *)&b, sizeof(b));
                }
                busFileStream.close();
                busTempFileStream.close();
                remove("buses.dat");
                rename("bustemp.dat", "buses.dat");
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0){
            ticketFileStream.close();
            tempFileStream.close();
            cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Not Found...!!\n";
        }
        else{
            ticketFileStream.close();
            tempFileStream.close();
            remove("tickets.dat");
            rename("temp.dat", "tickets.dat");
            cout << "\n\t\t\t\t\t\t\t\t\t\tTicket Cancelled...!!\n";
        }
    }
}


void Ticket::editTicket(){
    system("cls");
    string pnr;
    int chk = 0;
    fstream ticketFileStream, tempFileStream;

    printHeading("EDIT TICKET");
    cout << "\n\t\t\t\t\t\tEnter PNR Number:-> ";
    cin.ignore();
    cin>>pnr;

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);

    if (ticketFileStream.fail())
        cout << "\n\t\t\t\t\t\tCan't Open File...!!\n";

    else{
        tempFileStream.open("temp.dat", ios::out | ios::app | ios::binary);

        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof()){
            if (getPnrNo()==pnr){
                system("cls");
                printHeading("EDIT TICKET");

                displayTicket();
                string n;
                cout << "\n\t\t\t\t\t\tEnter Passenger Name :-> ";
                cin>>n;
                setName(n);
                tempFileStream.write((char *)this, sizeof(*this));

                chk = 1;
            }
            else
                tempFileStream.write((char *)this, sizeof(*this));
            
            ticketFileStream.read((char *)this, sizeof(*this));
        }

        if (chk = 1)
            cout << "\n\t\t\t\t\t\tTicket Updated Successfully...!!\n";
        
        else
            cout << "\n\t\t\t\t\t\tTicket Not Found...!!\n";

        ticketFileStream.close();
        tempFileStream.close();
        remove("tickets.dat");
        rename("temp.dat", "tickets.dat");
    }
}

void Ticket::showTicketsByPNR(){
    system("cls");

    string pnr;
    bool chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY PNR");
    cout << "\n\t\t\t\t\t\tEnter PNR Number:-> ";
    cin.ignore();
    cin>>pnr;

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
        cout << "\n\t\t\t\t\t\tCan't Open File...!!\n";

    else{
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof()){
            if (getPnrNo()==pnr){
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
            cout << "\n\t\t\t\t\t\tNo Bookings...!!\n";
        
        ticketFileStream.close();
    }
}

void Ticket::showTicketsByName(){
    system("cls");

    string n;
    bool chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY NAME");
    cout << "\n\t\t\t\t\t\tEnter Passenger Name: ";
    cin.ignore();
    cin>>n;

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
        cout << "\n\t\t\t\t\t\tCan't Open File...!!\n";

    else{
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof()){
            if (getName()==n){
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
            cout << "\n\t\t\t\t\t\tNo Bookings...!!\n";

        ticketFileStream.close();
    }
}

void Ticket::showTicketsByBus(){
    system("cls");

    string bNo;
    bool chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY NAME");
    cout << "\n\t\t\t\t\t\tEnter Bus Number:-> ";
    cin.ignore();
    cin>>bNo;

    system("cls");
    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
        cout << "\n\t\t\t\t\t\tCan't Open File...!!\n";

    else{
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof()){
            if (bus.getBusNo()==bNo){
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
            cout << "\n\t\t\t\t\t\tNo Bookings...!!\n";
        
        ticketFileStream.close();
    }
}

void Ticket::showTicketsBySource(){
    system("cls");

    string s;
    bool chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY SOURCE");
    cout << "\n\t\t\t\t\t\tEnter Source:-> ";
    cin.ignore();
    cin>>s;

    system("cls");
    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
        cout << "\n\t\t\t\t\t\tCan't Open File...!!\n";

    else{
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof()){
            if (bus.getSource()==s){
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
            cout << "\n\t\t\t\t\t\tNo Bookings...!!\n";
        
        ticketFileStream.close();
    }
}

void Ticket::showTicketsByDestination(){
    system("cls");

    string d;
    bool chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY DESTINATION");
    cout << "\n\t\t\t\t\t\tEnter Destination:-> ";
    cin.ignore();
    cin>>d;

    system("cls");
    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
        cout << "\n\t\t\t\t\t\tCan't Open File...!!\n";

    else{
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof()){
            if (bus.getDestination()==d){
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
            cout << "\n\t\t\t\t\t\tNo Bookings...!!\n";
        
        ticketFileStream.close();
    }
}

void Ticket::showAllTickets(){
    system("cls");
    fstream ticketFileStream;

    system("cls");
    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
        cout << "\n\t\t\t\t\t\tCan't Open File...!!\n";

    else{
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof()){
            displayTicket();
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        ticketFileStream.close();
    }
}
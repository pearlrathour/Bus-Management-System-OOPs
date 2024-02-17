#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include "bus.h"

class Ticket{
    private:
        string name, pnrNo, date;
        Bus bus;

    public:
        void generateTicket(string, Bus);
        void displayTicket();
        void bookTicket();
        void cancelTicket();
        void editTicket();
        void showTicketsByPNR();
        void showTicketsByName();
        void showTicketsByBus();
        void showTicketsBySource();
        void showTicketsByDestination();
        void showAllTickets();

        // GETTERS
        string getName(){
            return name;
        }

        string getPnrNo(){
            return pnrNo;
        }

        string getDate(){
            return date;
        }

        // SETTERS
        void setName(string n){
            name=n;
        }
    };

#endif
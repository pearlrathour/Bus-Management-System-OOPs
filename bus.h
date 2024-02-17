#ifndef BUS_H
#define BUS_H

#include<iostream>
using namespace std;

class Bus{
    private:
        int maxSeats, bookedSeats;
        double busFare;
        string busNo, source, destination, sourceTime, destinationTime;

    public:
        //Constructor
        Bus(){
            busNo="";
            maxSeats=40;
            bookedSeats=0;
            busFare=0.0;
            source="";
            destination="";
            sourceTime="";
            destinationTime="";
        }

        //Methods
        void addBus();
        void showAllBus();
        void showBusDetails();
        void viewBusDetails();
        void deleteBus();
        void editBus();

        //Getters
        string getBusNo(){
            return busNo;
        }

        string getSource(){
            return source;
        }

        string getDestination(){
            return destination;
        }

        string getSourceTime(){
            return sourceTime;
        }

        string getDestinationTime(){
            return destinationTime;
        }

        int getBookedSeats(){
            return bookedSeats;
        }

        int getMaxSeats(){
            return maxSeats;
        }

        double getBusFare(){
            return busFare;
        }

        //Setters
        void setBookedSeats(){
            bookedSeats++;
        }

        void setCancelTicket(){ 
            bookedSeats--;
        }


        void setSource(string s){
            source=s;
        }

        void setDestination(string d){
            destination=d;
        }

        void setSourceTime(string st){
            sourceTime=st;
        }

        void setDestinationTime(string dt){
            destinationTime=dt;
        }

        void setBusFare(double f){
            busFare=f;
        }
};

#endif
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;


class Ticket{
private:
    string UserName;
    string Date;
    string FlightName;
    string Place;
    int Price;
    bool IsBooked;
    int ID;

public:
    Ticket(const string& UserName, const string& Date, const string& FlightName, const string& Place, const int& Price)
        : UserName(UserName), Date(Date), FlightName(FlightName), Place(Place), Price(Price), IsBooked(false){}

    string GetUserName() const{
        return UserName;
    }

    bool GetIsBooked() const{
        return IsBooked;
    }

    string GetDate() const{
        return Date;
    }

    string GetFlightName() const{
        return FlightName;
    }

    string GetPlace() const{
        return Place;
    }

    int GetPrice() const{
        return Price;
    }

    int GetID() const{
        return ID;
    }

    void SetID(int newID){
        ID = newID;
    }

    void SetUserName(const string& newUserName){
        UserName = newUserName;
        IsBooked = true;
    }

    void DeleteBooking() {
        UserName = "";
        IsBooked = false;
    }
};


class User{
private:
    string UserName;
    vector<Ticket> tickets;
public:
    User(const string& UserName): UserName(UserName){}

    string GetUserName() const{
        return UserName;
    }

    vector<Ticket>& UserTickets(){
        return tickets;
    }

    void addTicket(const Ticket& ticket){
        tickets.push_back(ticket);
    }
};


class Airplane{
private:
    vector<Ticket> tickets;
    string Date;
    string flightName;
    int TotalSize;

public:
    Airplane(const string& flightName, string& Date, int& TotalSize): flightName(flightName), Date(Date){}

    void setTotalSize(const int& total) {
        TotalSize = total;
    }

    void addTicket(const Ticket& newTicket) {
        tickets.push_back(newTicket);
    }

    string getDate() const {
        return Date;
    }

    string getFlightName() const {
        return flightName;
    }

    vector<Ticket> getTickets() const {
        return tickets;
    }

    vector<Ticket> SeatAvailability() const {
        vector<Ticket> availableTickets;
        for (const auto& ticket : tickets) {
            if (ticket.GetIsBooked() == false && ticket.GetUserName() == "-") {
                availableTickets.push_back(ticket);
            }
        }
        return availableTickets;
    }

    void BookSeat(const string& UserName, const string& Place, int& ID, vector<Ticket>* IsBookedTickets, vector<User>* users) {
        for (auto & ticket : tickets) {
            if (ticket.GetPlace() == Place && ticket.GetIsBooked()) {
                ticket.SetUserName(UserName);
                ticket.SetID(ID);
                IsBookedTickets->push_back(ticket);
                bool UserFound = false;
                for (auto & user : *users) {
                    if (user.GetUserName() == UserName) {
                        user.addTicket(ticket);
                        UserFound = true;
                        break;
                    }
                }
                if (!UserFound) {
                    User newUser(UserName);
                    newUser.addTicket(ticket);
                    users->push_back(move(newUser));
                }
                cout << "Confirmed with ID " << ID << endl;
                return;
            }
        }
        cout << "Seat not available or already booked." << endl;
    }

    void ReturnTicketByID(const int ticketId) {
        for (auto& ticket : tickets) {
            if (ticket.GetID() == ticketId) {
                ticket.DeleteBooking();
                return;
            }
        }
    }
};





class ConfigReader{

};

class FileHandler{

};

class AirlineSystem{
private:
    vector<Ticket> Tickets;
    vector<User> Users;
public:


};

int main() {
//    AirlineSystem system("/home/nastia/CLionProjects/OOPD_first/Data.txt");
    string command;
    while (true){
        cout << "Choose the command:\n1)check\n2)book\n3)return\n4)viewID\n5)viewUsername\n6)exit" << endl;
        cin >> command;
        if (command == "check"){
            // у нас перевірка доступності місць
        }
        else if (command == "book"){
            // бронювати
        }
        else if (command == "return"){
            // повертати білет
        }
        else if (command == "viewID"){
            // користувач вводить iD і йому висвічує вся потрібна інфа
        }
        else if (command == "viewUsername"){
            // користувач вводить ім'я і висвічується інфа йому
        }
        else if (command == "exit"){
            break;
        }
        else{
            printf("You don't have this command\n");
        }
    }


    return 0;
}
















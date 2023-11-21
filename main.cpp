#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Airplane{

};

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
    Ticket(const string& UserName, const string& Date, const string& FlightName, const string Place, const int& Price)
        : UserName(UserName), Date(Date), FlightName(FlightName), Place(Place), Price(Price), IsBooked(false){}

    string GetUserName() const{
        return UserName;
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

    bool Book() {
        if (!IsBooked) {
            IsBooked = true;
            return true;
        }
        return false;
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
















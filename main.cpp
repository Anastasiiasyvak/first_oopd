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
    string place;
    int price;
    bool IsBooked;
    int ID;

public:
    Ticket(const string& UserName, const string& Date, const string& FlightName, const string place, const int& price)
        : UserName(UserName), Date(Date), FlightName(FlightName), place(place), price(price), IsBooked(false){}

    string GetUserName() const{
        return this->UserName;
    }

    string GetDate() const{
        return this->Date;
    }

    string GetFlightName() const{
        return this->FlightName;
    }

    string GetPlace() const{
        return this->place;
    }

    int GetPrice() const{
        return this->price;
    }

    int GetID() const{
        return this->ID;
    }

    void SetID(int ID){
        this->ID = ID;
    }

    void SetUserName(const string& UserName){
        this->UserName = UserName;
        this->IsBooked = true;
    }

};

class ConfigReader{

};

class FileHandler{

};

class AirlineSystem{

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
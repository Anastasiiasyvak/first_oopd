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
    Ticket(const string& UserName, const string& Date,  const string& Place,  const string& FlightName,const int& Price)
        : UserName(UserName), Date(Date), Place(Place), FlightName(FlightName),  Price(Price), IsBooked(true){}

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

    void SetUserName(const string& Name){
        UserName = Name;
        IsBooked = false;
    }

    void DeleteBooking() {
        UserName = "-";
        IsBooked = true;
    }
};


class User{
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
    Airplane(const string& flightName,string& Date): flightName(flightName), Date(Date){}

    void SetTotalSize(const int& total) {
        TotalSize = total;
    }

    void AddTicket(const Ticket& newTicket) {
        tickets.push_back(newTicket);
    }

    string GetDate() const {
        return Date;
    }

    string GetFlightName() const {
        return flightName;
    }

    vector<Ticket> GetTickets() const {
        return tickets;
    }

    vector<Ticket> SeatAvailability() const {
        vector<Ticket> availableTickets;
        for (const auto& ticket : tickets) {
            if (ticket.GetIsBooked() == true && ticket.GetUserName() == "-") {
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


class ConfigReader {
public:

    vector<Airplane> SaveFlights(const string& filePath) {
        ifstream file(filePath);
        vector<Airplane> flights;
        string line;

        if (!file.is_open()) {
            cout << "Error opening file" << endl;
            return flights;
        }

        getline(file, line);
        while (getline(file, line)){
            stringstream lineStream(line);
            string Date, FlightName;
            int seatsPerRow, startRow, endRow;
            float price;
            char sign, seatLetter;
            vector<pair<int, int>> priceSections;

            lineStream >> Date >> FlightName >> seatsPerRow;
            Airplane flight(FlightName, Date);

            while (lineStream >> startRow >> sign >> endRow >> price >> sign) {
                for (int i = startRow; i <= endRow; ++i) {
                    for (int j = 0; j < seatsPerRow; ++j) {
                        seatLetter = 'A' + j;
                        string seat = to_string(i) + seatLetter;
                        Ticket ticket("-", Date, seat, FlightName, price);
                        flight.AddTicket(ticket);
                    }
                }
            }
            flight.SetTotalSize(seatsPerRow * endRow);
            flights.push_back(move(flight));
        }

        return flights;
    }
};


class AirlineSystem {
private:
    vector<Airplane> flights;
    vector<User> users;
    vector<Ticket> bookedTickets;
    int newID = 11111;

    void downloadAirplanes(const string& filePath) {
        ConfigReader configReader;
        flights = move(configReader.SaveFlights(filePath));
    }


public:
    AirlineSystem(const string& configFilePath) {
        downloadAirplanes(configFilePath);
    }

    void check() {
        string Date, FlightName;
        cout << "Enter date and flight name: ";
        cin >> Date >> FlightName;

        for (auto& airplane : flights) {
            if (airplane.GetDate() == Date && airplane.GetFlightName() == FlightName) {
                auto availableTickets = airplane.SeatAvailability();
                if (availableTickets.empty()) {
                    cout << "No available seats." << endl;
                } else {
                    cout << "Available seats:" << endl;
                    for (auto& ticket : availableTickets) {
                        cout << "Seat: " << ticket.GetPlace() << ", Price: $" << ticket.GetPrice() << endl;
                    }
                }
                return;
            }
        }
        cout << "Flight not found." << endl;
    }

    void book() {
        string passengerName, date, flightNumber, seatNumber;
        cout << "Enter user name, date, flight name, and seat: " << endl;
        cin >> passengerName >> date >> flightNumber >> seatNumber;

        for (auto &airplane : flights) {
            if (airplane.GetDate() == date && airplane.GetFlightName() == flightNumber) {
                airplane.BookSeat(passengerName, seatNumber, newID, &bookedTickets, &users);
                newID++;
                return;
            }
        }

        {

        }
        cout << "Flight not found or seat number is not correct." << endl;
    }

    void commandReturn() {
        int idCheck;
        cout << "Enter ID: " << endl;
        cin >> idCheck;

        for (auto& airplane : flights) {
            for (auto& ticket : airplane.GetTickets()) {
                if (ticket.GetID() == idCheck && !ticket.GetIsBooked()) {
                    airplane.ReturnTicketByID(idCheck);
                    deleteUserTicket(ticket);
                    removeTicketFromBookedTickets(idCheck);
                    cout << "Confirmed " << ticket.GetPrice() << "$" << " refund for " << ticket.GetUserName() << endl;
                    return;
                }
            }
        }
        cout << "Ticket with the given ID not found." << endl;
    }

    void deleteUserTicket(const Ticket& ticket) {
        for (auto& user : users) {
            if (user.GetUserName() == ticket.GetUserName()) {
                vector<Ticket>& userTickets = user.UserTickets();
                for (auto ticketIterator = userTickets.begin(); ticketIterator != userTickets.end(); ++ticketIterator) {
                    if ((*ticketIterator).GetID() == ticket.GetID()) {
                        userTickets.erase(ticketIterator);
                        break;
                    }
                }
                break;
            }
        }
    }

    void removeTicketFromBookedTickets(int& ticketId) {
        for (auto ticketIterator = bookedTickets.begin(); ticketIterator != bookedTickets.end(); ++ticketIterator) {
            if ((*ticketIterator).GetID() == ticketId) {
                bookedTickets.erase(ticketIterator);
                return;
            }
        }
    }

    void viewID() {
        int idCheck;
        cout << "Enter ID: ";
        cin >> idCheck;

        for (const auto& ticket : bookedTickets) {
            if (ticket.GetID() == idCheck) {
                cout << "Ticket details: Flight " << ticket.GetFlightName() << ", Date: " << ticket.GetDate()
                     << ", Seat: " << ticket.GetPlace() << ", Price: $" << ticket.GetPrice() << endl;
                return;
            }
        }
        cout << "Ticket with given ID not found." << endl;
    }

    void viewName() {
        string userName;
        cout << "Enter passenger name: ";
        cin >> userName;

        for (auto& passenger : users) {
            if (passenger.GetUserName() == userName) {
                vector<Ticket>& tickets = passenger.UserTickets();
                cout << "Tickets for " << userName << ":" << endl;
                for (auto& ticket : tickets) {
                    cout << "Flight " << ticket.GetFlightName() << ", Date: " << ticket.GetDate()
                         << ", Seat: " << ticket.GetPlace() << ", Price: $" << ticket.GetPrice() << endl;
                }
                return;
            }
        }
        cout << "No tickets found for passenger: " << userName << endl;
    }

};

int main() {
    AirlineSystem airlineSystem("/home/nastia/CLionProjects/OOPD_first/Data.txt");
    string command;
    while (true){
        cout << "Choose the command:\n1)check\n2)book\n3)return\n4)viewID\n5)viewUsername\n6)exit" << endl;
        cin >> command;
        if (command == "check") {
            airlineSystem.check();
        } else if (command == "book") {
            airlineSystem.book();
        } else if (command == "return") {
            airlineSystem.commandReturn();
        } else if (command == "viewID") {
            airlineSystem.viewID();
        } else if (command == "viewName") {
            airlineSystem.viewName();
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
















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
    Airplane(const string& Date,const string& flightName, int& TotalSize): flightName(flightName), Date(Date){}

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

        while (getline(file, line)){
            stringstream lineStream(line);
            string Date, FlightName;
            int seatsPerRow, startRow, endRow;
            float price;
            char sign, seatLetter;
            vector<pair<int, int>> priceSections;

            lineStream >> Date >> FlightName >> seatsPerRow;
            Airplane flight(Date, FlightName, seatsPerRow);

            while (lineStream >> startRow >> sign >> endRow >> price >> sign) {
                for (int i = startRow; i <= endRow; ++i) {
                    for (int j = 0; j < seatsPerRow; ++j) {
                        seatLetter = 'A' + j;
                        string seat = to_string(i) + seatLetter;
                        Ticket ticket("-", Date, seat, FlightName, price);
                        flight.addTicket(ticket);
                    }
                }
            }
            flight.setTotalSize(seatsPerRow * endRow);
            flights.push_back(move(flight));
        }

        return flights;
    }
};


class AirlineSystem {
private:
    vector<Airplane> airplanes;
    vector<User> passengers;
    vector<Ticket> bookedTickets;
    int nextId = 111;

    void loadAirplanes(const string& filePath) {
        ConfigReader reader;
        airplanes = move(reader.SaveFlights(filePath));
    }

public:
    AirlineSystem(const string& configFilePath) {
        loadAirplanes(configFilePath);
    }

    void check() {
        string Date, FlightName;
        cout << "Enter date and flight number (example: 11.12.2022 FQ12): ";
        cin >> Date >> FlightName;

        for (auto& airplane : airplanes) {
            if (airplane.getDate() == Date && airplane.getFlightName() == FlightName) {
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
        cout << "Enter passenger name, date, flight number, and seat number (example: John 11.12.2022 FQ12 1A): " << endl;
        cin >> passengerName >> date >> flightNumber >> seatNumber;

        for (auto &airplane : airplanes) {
            if (airplane.getDate() == date && airplane.getFlightName() == flightNumber) {
                airplane.BookSeat(passengerName, seatNumber, nextId, &bookedTickets, &passengers);
                nextId++;
                return;
            }
        }

        {

        }
        cout << "Flight not found or seat number is incorrect." << endl;
    }

    void commandReturn() {
        int idCheck;
        cout << "Enter confirmation ID: " << endl;
        cin >> idCheck;

        for (auto& airplane : airplanes) {
            for (auto& ticket : airplane.getTickets()) {
                if (ticket.GetID() == idCheck && !ticket.GetIsBooked()) {
                    airplane.ReturnTicketByID(idCheck);
                    removeTicketFromPassenger(ticket);
                    removeTicketFromBookedTickets(idCheck);
                    cout << "Confirmed " << ticket.GetPrice() << "$" << " refund for " << ticket.GetUserName() << endl;
                    return;
                }
            }
        }
        cout << "Ticket with the given ID not found." << endl;
    }

    void removeTicketFromPassenger(const Ticket& ticket) {
        for (auto& passenger : passengers) {
            if (passenger.GetUserName() == ticket.GetUserName()) {
                vector<Ticket>& passengerTickets = passenger.UserTickets();
                for (auto it = passengerTickets.begin(); it != passengerTickets.end(); ++it) {
                    if (it->GetID() == ticket.GetID()) {
                        passengerTickets.erase(it);
                        break;
                    }
                }
                break;
            }
        }
    }

    void removeTicketFromBookedTickets(int& ticketId) {
        for (auto it = bookedTickets.begin(); it != bookedTickets.end(); ++it) {
            if (it->GetID() == ticketId) {
                bookedTickets.erase(it);
                return;
            }
        }
    }

    void view() {
        int idCheck;
        cout << "Enter confirmation ID: ";
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

    void all() {
        string passengerName;
        cout << "Enter passenger name: ";
        cin >> passengerName;

        for (auto& passenger : passengers) {
            if (passenger.GetUserName() == passengerName) {
                vector<Ticket>& tickets = passenger.UserTickets();
                cout << "Tickets for " << passengerName << ":" << endl;
                for (auto& ticket : tickets) {
                    cout << "Flight " << ticket.GetFlightName() << ", Date: " << ticket.GetDate()
                         << ", Seat: " << ticket.GetPlace() << ", Price: $" << ticket.GetPrice() << endl;
                }
                return;
            }
        }
        cout << "No tickets found for passenger: " << passengerName << endl;
    }

};

int main() {
    AirlineSystem system("/home/nastia/CLionProjects/OOPD_first/Data.txt");
    string command;
    while (true){
        cout << "Choose the command:\n1)check\n2)book\n3)return\n4)viewID\n5)viewUsername\n6)exit" << endl;
        cin >> command;
        if (command == "check") {
            system.check();
        } else if (command == "book") {
            system.book();
        } else if (command == "return") {
            system.commandReturn();
        } else if (command == "view") {
            system.view();
        } else if (command == "all") {
            system.all();
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
















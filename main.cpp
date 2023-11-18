#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Airplane{

};

class Ticket{

};

class ConfigReader{

};

class FileHandler{

};

class AirlineSystem{

};

int main() {
    AirlineSystem system("/home/nastia/CLionProjects/OOPD_first/Data.txt");
    string command;
    while (true){
        cout << "Choose the command:\n1)check\n2)book\n3)return\n4)viewID\n5)viewUsername\n6)exit" << std::endl;
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

#include <bits/stdc++.h>
using namespace std;

class Passenger {
public:
    int id;
    string name;
    string coach;

    Passenger() {} // default constructor

    Passenger(int id, string name, string coach) {
        this->id = id;
        this->name = name;
        this->coach = coach;
    }
};

class Train {
public:
    int no;
    string name;
    int seatsSleeper, seatsAC;
    map<int, Passenger> bookedPassengers;

    Train() { // ✅ default constructor
        no = 0;
        name = "";
        seatsSleeper = 0;
        seatsAC = 0;
    }

    Train(int no, string name, int sl, int ac) {
        this->no = no;
        this->name = name;
        seatsSleeper = sl;
        seatsAC = ac;
    }

    bool bookTicket(Passenger p) {
        if (p.coach == "SL") {
            if (seatsSleeper > 0) {
                bookedPassengers[p.id] = p;
                seatsSleeper--;
                return true;
            }
        } else if (p.coach == "AC") {
            if (seatsAC > 0) {
                bookedPassengers[p.id] = p;
                seatsAC--;
                return true;
            }
        }
        return false;
    }

    void displayPassengers() {
        cout << "Train " << no << " - " << name << "\nPassengers:\n";
        for (auto &it : bookedPassengers) {
            cout << "ID: " << it.second.id 
                 << ", Name: " << it.second.name 
                 << ", Coach: " << it.second.coach << "\n";
        }
    }
};

int main() {
    map<int, Train> trains;

    // ✅ Use emplace (no default construction issue)
    trains.emplace(101, Train(101, "Chennai Express", 5, 3));
    trains.emplace(102, Train(102, "Coimbatore Express", 5, 3));

    cout << "Welcome to Railway Reservation System\n";

    int choice;
    while (true) {
        cout << "\n1. Book Ticket\n2. Show Passengers\n3. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            int trainNo, id;
            string pname, coach;
            cout << "Enter Train No: ";
            cin >> trainNo;

            if (trains.find(trainNo) == trains.end()) {
                cout << "Invalid Train Number!\n";
                continue;
            }

            cout << "Enter Passenger ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> pname;
            cout << "Enter Coach (SL/AC): ";
            cin >> coach;

            Passenger p(id, pname, coach);
            Train &tr = trains[trainNo];

            if (tr.bookTicket(p)) {
                cout << "Ticket booked successfully!\n";
            } else {
                cout << "No seats available in " << coach << " class.\n";
            }
        }
        else if (choice == 2) {
            int trainNo;
            cout << "Enter Train No: ";
            cin >> trainNo;

            if (trains.find(trainNo) == trains.end()) {
                cout << "Invalid Train Number!\n";
                continue;
            }
            trains[trainNo].displayPassengers();
        }
        else if (choice == 3) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}

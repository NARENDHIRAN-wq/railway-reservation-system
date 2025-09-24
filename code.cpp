#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Passenger {
    string name;
    int age;
    string classType;
    int fare;
};

class Train {
public:
    int no;
    string name;
    int seatsSleeper, seatsAC;
    map<int, Passenger> bookedPassengers;

    Train(int no, string name, int sl, int ac) {
        this->no = no;
        this->name = name;
        seatsSleeper = sl;
        seatsAC = ac;
    }

    void showAvailability() {
        cout << "Train " << name << " availability:\n";
        cout << "Sleeper seats: " << seatsSleeper << "\n";
        cout << "AC seats: " << seatsAC << "\n";
    }

    bool bookTicket(Passenger p) {
        if (p.classType == "SLEEPER" && seatsSleeper > 0) {
            seatsSleeper--;
            bookedPassengers[bookedPassengers.size() + 1] = p;
            return true;
        } else if (p.classType == "AC" && seatsAC > 0) {
            seatsAC--;
            bookedPassengers[bookedPassengers.size() + 1] = p;
            return true;
        } else {
            return false;
        }
    }

    bool cancelTicket(int ticketNo) {
        if (bookedPassengers.find(ticketNo) != bookedPassengers.end()) {
            if (bookedPassengers[ticketNo].classType == "SLEEPER")
                seatsSleeper++;
            else
                seatsAC++;
            bookedPassengers.erase(ticketNo);
            return true;
        }
        return false;
    }
};

string toUpper(string s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

int main() {
    map<int, Train> trains;
    trains[101] = Train(101, "Chennai Express", 5, 3);
    trains[102] = Train(102, "Coimbatore Express", 5, 3);

    vector<string> stations = {
        "CHENNAI", "ARAKONAM", "VILLUPURAM", "TRICHY",
        "NAMAKKAL", "SALAM", "ERODE", "COIMBATORE"
    };
    map<pair<string,string>, int> distance;

    // Distance between consecutive stations
    for (int i = 0; i < stations.size() - 1; i++) {
        distance[{stations[i], stations[i+1]}] = 100 + i*20; // example km
        distance[{stations[i+1], stations[i]}] = 100 + i*20; // reverse direction
    }

    while (true) {
        cout << "\n1. Book Ticket\n2. Cancel Ticket\n3. Check Availability\n4. Exit\nChoose: ";
        int choice; cin >> choice;
        cin.ignore();

        if (choice == 4) break;

        int trainNo;
        cout << "Enter train number: ";
        cin >> trainNo;
        cin.ignore();

        if (trains.find(trainNo) == trains.end()) {
            cout << "Invalid train number!\n";
            continue;
        }

        Train &tr = trains[trainNo];

        if (choice == 3) {
            tr.showAvailability();
        } else if (choice == 1) {
            string src, dest, classType, name;
            int age;
            cout << "Enter source station: "; getline(cin, src);
            cout << "Enter destination station: "; getline(cin, dest);
            src = toUpper(src); dest = toUpper(dest);

            if (distance.find({src,dest}) == distance.end()) {
                cout << "Invalid route!\n"; continue;
            }

            int km = distance[{src,dest}];
            cout << "Enter passenger name: "; getline(cin, name);
            cout << "Enter age: "; cin >> age; cin.ignore();
            cout << "Enter class (Sleeper/AC): "; getline(cin, classType);
            classType = toUpper(classType);

            int fare = (classType=="AC") ? km*2 : km*1;

            Passenger p = {name, age, classType, fare};

            if (tr.bookTicket(p)) {
                cout << "Ticket booked! Fare: " << fare << "\n";
            } else {
                cout << "No seats available in selected class!\n";
            }
        } else if (choice == 2) {
            int ticketNo;
            cout << "Enter ticket number to cancel: ";
            cin >> ticketNo; cin.ignore();
            if (tr.cancelTicket(ticketNo)) {
                cout << "Ticket cancelled successfully.\n";
            } else {
                cout << "Invalid ticket number!\n";
            }
        }
    }

    cout << "Thank you for using Railway Reservation System!\n";
    return 0;
}

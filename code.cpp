#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Passenger structure
struct Passenger {
    string passenger_name;
    int age;
    string class_type;
    int fare;
};

// Train class
class Train {
public:
    int train_no;
    string train_name;
    int seats_sleeper;
    int seats_ac;
    map<int, Passenger> booked_passengers;

    // Default constructor
    Train() {
        train_no = 0;
        train_name = "";
        seats_sleeper = 0;
        seats_ac = 0;
    }

    // Parameterized constructor
    Train(int no, string name, int sl, int ac) {
        train_no = no;
        train_name = name;
        seats_sleeper = sl;
        seats_ac = ac;
    }

    void showAvailability() {
        cout << "Train No: " << train_no << ", Train Name: " << train_name << "\n";
        cout << "Sleeper seats: " << seats_sleeper << ", AC seats: " << seats_ac << "\n";
    }

    bool bookTicket(Passenger p) {
        if (p.class_type == "SLEEPER" && seats_sleeper > 0) {
            seats_sleeper--;
            booked_passengers[booked_passengers.size() + 1] = p;
            return true;
        } else if (p.class_type == "AC" && seats_ac > 0) {
            seats_ac--;
            booked_passengers[booked_passengers.size() + 1] = p;
            return true;
        } else {
            return false;
        }
    }

    bool cancelTicket(int ticket_no) {
        if (booked_passengers.find(ticket_no) != booked_passengers.end()) {
            if (booked_passengers[ticket_no].class_type == "SLEEPER")
                seats_sleeper++;
            else
                seats_ac++;
            booked_passengers.erase(ticket_no);
            return true;
        }
        return false;
    }
};

// Utility to convert string to uppercase
string toUpper(string s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

int main() {
    map<int, Train> trains;

    // Initialize trains
    trains.insert({101, Train(101, "Chennai Express", 5, 3)});
    trains.insert({102, Train(102, "Coimbatore Express", 5, 3)});

    // Stations
    vector<string> stations = {
        "CHENNAI", "ARAKONAM", "VILLUPURAM", "TRICHY",
        "NAMAKKAL", "SALEM", "ERODE", "COIMBATORE"
    };

    // Distance between stations
    map<pair<string, string>, int> distance;
    for (int i = 0; i < (int)stations.size(); i++) {
        int dist = 0;
        for (int j = i + 1; j < (int)stations.size(); j++) {
            dist += 100 + (j - 1) * 20;  // example distance formula
            distance[{stations[i], stations[j]}] = dist;
            distance[{stations[j], stations[i]}] = dist; // reverse
        }
    }

    while (true) {
        cout << "\n1. Book Ticket\n2. Cancel Ticket\n3. Check Availability\n4. Exit\nChoose: ";
        int choice; cin >> choice;
        cin.ignore();

        if (choice == 4) break;

        if (choice == 3) {
            // Show availability of all trains
            for (auto &t : trains) t.second.showAvailability();
        } 
        else if (choice == 1) {
            string src, dest, class_type, passenger_name;
            int age;

            cout << "Enter source station: "; getline(cin, src);
            cout << "Enter destination station: "; getline(cin, dest);
            src = toUpper(src); dest = toUpper(dest);

            if (distance.find({src, dest}) == distance.end()) {
                cout << "Invalid route!\n";
                continue;
            }

            // Show trains available with train number
            cout << "Available trains for " << src << " to " << dest << ":\n";
            for (auto &t : trains) {
                t.second.showAvailability();
            }

            int km = distance[{src, dest}];
            cout << "Enter passenger name: "; getline(cin, passenger_name);
            cout << "Enter age: "; cin >> age; cin.ignore();
            cout << "Enter class (Sleeper/AC): "; getline(cin, class_type);
            class_type = toUpper(class_type);

            int fare = (class_type == "AC") ? km * 2 : km * 1;

            Passenger p = {passenger_name, age, class_type, fare};

            int train_no;
            cout << "Enter train number to book: "; cin >> train_no; cin.ignore();

            if (trains.find(train_no) == trains.end()) {
                cout << "Invalid train number!\n";
                continue;
            }

            if (trains[train_no].bookTicket(p)) {
                cout << "Ticket booked! Fare: " << fare << "\n";
            } else {
                cout << "No seats available in selected class!\n";
            }
        } 
        else if (choice == 2) {
            int train_no, ticket_no;
            cout << "Enter train number: "; cin >> train_no; cin.ignore();
            cout << "Enter ticket number to cancel: "; cin >> ticket_no; cin.ignore();

            if (trains.find(train_no) != trains.end() && trains[train_no].cancelTicket(ticket_no)) {
                cout << "Ticket cancelled successfully.\n";
            } else {
                cout << "Invalid train number or ticket number!\n";
            }
        }
    }

    cout << "Thank you for using Railway Reservation System!\n";
    return 0;
}

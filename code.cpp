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
    int ticketNo;
};

class Train {
public:
    int no;
    string name;
    int seatsSleeper, seatsAC;
    map<int, Passenger> bookedPassengers;
    int ticketCounter; // unique ticket counter

    // Default constructor
    Train() {
        no = 0;
        name = "";
        seatsSleeper = 0;
        seatsAC = 0;
        ticketCounter = 0;
    }

    // Parameterized constructor
    Train(int no, string name, int sl, int ac) {
        this->no = no;
        this->name = name;
        seatsSleeper = sl;
        seatsAC = ac;
        ticketCounter = 0;
    }

    void showAvailability() {
        cout << "Train " << name << " availability:\n";
        cout << "Sleeper seats: " << seatsSleeper << "\n";
        cout << "AC seats: " << seatsAC << "\n";
    }

    bool bookTicket(Passenger p) {
        if (p.classType == "SLEEPER" && seatsSleeper > 0) {
            seatsSleeper--;
        } else if (p.classType == "AC" && seatsAC > 0) {
            seatsAC--;
        } else {
            return false;
        }
        // Generate unique ticket number
        ticketCounter++;
        p.ticketNo = ticketCounter;
        bookedPassengers[p.ticketNo] = p;
        cout << "✅ Ticket booked! Ticket No: " << p.ticketNo
             << " | Fare: " << p.fare << "\n";
        return true;
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
    trains.emplace(101, Train(101, "Chennai Express", 5, 3));
    trains.emplace(102, Train(102, "Coimbatore Express", 5, 3));

    vector<string> stations = {
        "CHENNAI", "ARAKONAM", "VILLUPURAM", "TRICHY",
        "NAMAKKAL", "SALEM", "ERODE", "COIMBATORE"
    };

    map<pair<string,string>, int> distance;

    // Build distance for all possible station pairs
    for (int i = 0; i < (int)stations.size(); i++) {
        int dist = 0;
        for (int j = i + 1; j < (int)stations.size(); j++) {
            dist += 100 + (j-1)*20;  // add distance of segment (example formula)
            distance[{stations[i], stations[j]}] = dist;
            distance[{stations[j], stations[i]}] = dist; // reverse
        }
    }

    while (true) {
        cout << "\n--- Railway Reservation System ---\n";
        cout << "1. Book Ticket\n2. Cancel Ticket\n3. Check Availability\n4. Exit\nChoose: ";
        int choice; cin >> choice;
        cin.ignore();

        if (choice == 4) break;

        int trainNo;
        cout << "Enter train number: ";
        cin >> trainNo;
        cin.ignore();

        if (trains.find(trainNo) == trains.end()) {
            cout << "❌ Invalid train number!\n";
            continue;
        }

        Train &tr = trains[trainNo];

        if (choice == 3) {
            tr.showAvailability();
        } else if (choice == 1) {
            string src, dest, classType, name;
            int age;

            cout << "\nAvailable stations:\n";
            for (auto &s : stations) cout << "- " << s << "\n";

            cout << "Enter source station: "; getline(cin, src);
            cout << "Enter destination station: "; getline(cin, dest);
            src = toUpper(src); dest = toUpper(dest);

            if (distance.find({src,dest}) == distance.end()) {
                cout << "❌ Invalid route!\n"; continue;
            }

            int km = distance[{src,dest}];
            cout << "Enter passenger name: "; getline(cin, name);
            cout << "Enter age: "; cin >> age; cin.ignore();
            cout << "Enter class (Sleeper/AC): "; getline(cin, classType);
            classType = toUpper(classType);

            int fare = (classType=="AC") ? km*2 : km*1;

            Passenger p = {name, age, classType, fare, 0};

            if (!tr.bookTicket(p)) {
                cout << "❌ No seats available in selected class!\n";
            }
        } else if (choice == 2) {
            int ticketNo;
            cout << "Enter ticket number to cancel: ";
            cin >> ticketNo; cin.ignore();
            if (tr.cancelTicket(ticketNo)) {
                cout << "✅ Ticket cancelled successfully.\n";
            } else {
                cout << "❌ Invalid ticket number!\n";
            }
        }
    }

    cout << "🙏 Thank you for using Railway Reservation System!\n";
    return 0;
}

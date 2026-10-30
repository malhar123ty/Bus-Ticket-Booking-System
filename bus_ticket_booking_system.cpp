
#include <iostream>
#include <string>
#include <queue>
using namespace std;

const int TOTAL_SEATS = 50;
const int TOTAL_ROUTES = 6;

// Structure to store passenger details
struct Passenger
{
    int bookingID;
    string name;
    int age;
    char gender;
    int seatNo;
    double baseFare;
    double finalFare;
};

// Structure to store seat details
struct Seat
{
    bool occupied;
    Passenger passenger;
};

// Structure to store bus details
struct Bus
{
    string route;
    double fare;
    Seat seats[TOTAL_SEATS];
    queue<Passenger> waitingList;
};

Bus buses[TOTAL_ROUTES];
int nextBookingID = 1001;

// Initialize all routes and seats
void initializeSystem()
{
    string routes[6] = {
        "Pune to Mumbai",
        "Pune to Nashik",
        "Pune to Nagpur",
        "Pune to Jalgaon",
        "Pune to Sangli",
        "Pune to Kolhapur"
    };

    double fares[6] = {500, 350, 900, 600, 400, 450};

    for (int i = 0; i < TOTAL_ROUTES; i++)
    {
        buses[i].route = routes[i];
        buses[i].fare = fares[i];

        for (int j = 0; j < TOTAL_SEATS; j++)
        {
            buses[i].seats[j].occupied = false;
        }
    }
}

// Display available routes
void displayRoutes()
{
    cout << "\n===== AVAILABLE BUS ROUTES =====\n";

    for (int i = 0; i < TOTAL_ROUTES; i++)
    {
        cout << i + 1 << ". " << buses[i].route
             << " | Fare: Rs. " << buses[i].fare << endl;
    }
}

// Select a route
int selectRoute()
{
    displayRoutes();

    int choice;
    cout << "Enter route number (1-6): ";
    cin >> choice;

    if (choice < 1 || choice > 6)
    {
        cout << "Invalid route!\n";
        return -1;
    }

    return choice - 1;
}

// Calculate fare using project rules
double calculateFare(Passenger p, double fare)
{
    if (p.age >= 65)
    {
        cout << "Senior citizen discount: 100%\n";
        return 0;
    }
    else if (p.gender == 'F' || p.gender == 'f')
    {
        cout << "Women discount: 50%\n";
        return fare * 0.50;
    }
    else if (p.age < 21)
    {
        cout << "Student discount: 20% (demo rule)\n";
        return fare * 0.80;
    }
    else
    {
        return fare;
    }
}

// Find an available seat
// Seats 1-13: Senior citizens
// Seats 14-25: Women
// Seats 26-50: General
int findAvailableSeat(Bus &bus, Passenger p)
{
    int start, end;

    if (p.age >= 65)
    {
        start = 0;
        end = 13;
    }
    else if (p.gender == 'F' || p.gender == 'f')
    {
        start = 13;
        end = 25;
    }
    else
    {
        start = 25;
        end = 50;
    }

    // Search preferred reserved category or general seats
    for (int i = start; i < end; i++)
    {
        if (bus.seats[i].occupied == false)
        {
            return i;
        }
    }

    // Search general seats if reserved seats are full
    if (start < 25)
    {
        for (int i = 25; i < 50; i++)
        {
            if (bus.seats[i].occupied == false)
            {
                return i;
            }
        }
    }

    // Use remaining reserved seats if necessary
    for (int i = 0; i < 25; i++)
    {
        if (bus.seats[i].occupied == false)
        {
            return i;
        }
    }

    return -1;
}

// Confirm a booking
void confirmBooking(Bus &bus, Passenger p, int seatIndex)
{
    p.seatNo = seatIndex + 1;

    bus.seats[seatIndex].occupied = true;
    bus.seats[seatIndex].passenger = p;

    cout << "\n===== TICKET CONFIRMED =====\n";
    cout << "Booking ID: " << p.bookingID << endl;
    cout << "Name: " << p.name << endl;
    cout << "Route: " << bus.route << endl;
    cout << "Seat Number: " << p.seatNo << endl;
    cout << "Base Fare: Rs. " << p.baseFare << endl;
    cout << "Final Fare: Rs. " << p.finalFare << endl;
    cout << "Status: CONFIRMED\n";
}

// Book a ticket
void bookTicket()
{
    int routeIndex = selectRoute();

    if (routeIndex == -1)
    {
        return;
    }

    Bus &bus = buses[routeIndex];
    Passenger p;

    p.bookingID = nextBookingID++;
    p.seatNo = 0;
    p.baseFare = bus.fare;

    cout << "Enter passenger name: ";
    cin.ignore();
    getline(cin, p.name);

    cout << "Enter age: ";
    cin >> p.age;

    if (p.age < 0 || p.age > 120)
    {
        cout << "Invalid age!\n";
        return;
    }

    cout << "Enter gender (M/F/O): ";
    cin >> p.gender;

    if (p.gender != 'M' && p.gender != 'm' &&
        p.gender != 'F' && p.gender != 'f' &&
        p.gender != 'O' && p.gender != 'o')
    {
        cout << "Invalid gender!\n";
        return;
    }

    p.finalFare = calculateFare(p, bus.fare);

    int seatIndex = findAvailableSeat(bus, p);

    if (seatIndex != -1)
    {
        confirmBooking(bus, p, seatIndex);
    }
    else
    {
        bus.waitingList.push(p);

        cout << "\nAll seats are booked!\n";
        cout << "Booking ID: " << p.bookingID << endl;
        cout << "Passenger: " << p.name << endl;
        cout << "Waiting-list position: "
             << bus.waitingList.size() << endl;
        cout << "Status: WAITING\n";
    }
}

// Display seat availability
void displaySeats()
{
    int routeIndex = selectRoute();

    if (routeIndex == -1)
    {
        return;
    }

    Bus &bus = buses[routeIndex];

    cout << "\n===== SEAT AVAILABILITY =====\n";
    cout << bus.route << endl;
    cout << "A = Available, B = Booked\n\n";

    for (int i = 0; i < TOTAL_SEATS; i++)
    {
        cout << i + 1 << "["
             << (bus.seats[i].occupied ? "B" : "A")
             << "] ";

        if ((i + 1) % 5 == 0)
        {
            cout << endl;
        }
    }
}

// Display confirmed bookings
void displayBookings()
{
    int routeIndex = selectRoute();

    if (routeIndex == -1)
    {
        return;
    }

    Bus &bus = buses[routeIndex];
    bool found = false;

    cout << "\n===== CONFIRMED BOOKINGS =====\n";

    for (int i = 0; i < TOTAL_SEATS; i++)
    {
        if (bus.seats[i].occupied)
        {
            Passenger p = bus.seats[i].passenger;

            cout << "ID: " << p.bookingID
                 << " | Name: " << p.name
                 << " | Seat: " << p.seatNo
                 << " | Fare: Rs. " << p.finalFare << endl;

            found = true;
        }
    }

    if (!found)
    {
        cout << "No confirmed bookings.\n";
    }
}

// Display waiting list in FIFO order
void displayWaitingList()
{
    int routeIndex = selectRoute();

    if (routeIndex == -1)
    {
        return;
    }

    queue<Passenger> temp = buses[routeIndex].waitingList;

    cout << "\n===== WAITING LIST =====\n";

    if (temp.empty())
    {
        cout << "Waiting list is empty.\n";
        return;
    }

    int position = 1;

    while (!temp.empty())
    {
        Passenger p = temp.front();

        cout << position++ << ". Booking ID: "
             << p.bookingID << " | Name: " << p.name << endl;

        temp.pop();
    }
}

// Promote the first waiting passenger
void promoteWaitingPassenger(Bus &bus)
{
    if (bus.waitingList.empty())
    {
        return;
    }

    queue<Passenger> temp;
    bool promoted = false;

    while (!bus.waitingList.empty())
    {
        Passenger p = bus.waitingList.front();
        bus.waitingList.pop();

        int seatIndex = findAvailableSeat(bus, p);

        if (!promoted && seatIndex != -1)
        {
            confirmBooking(bus, p, seatIndex);
            cout << "Passenger promoted from waiting list!\n";
            promoted = true;
        }
        else
        {
            temp.push(p);
        }
    }

    bus.waitingList = temp;
}

// Cancel a ticket
void cancelTicket()
{
    int routeIndex = selectRoute();

    if (routeIndex == -1)
    {
        return;
    }

    Bus &bus = buses[routeIndex];

    int id;
    cout << "Enter booking ID to cancel: ";
    cin >> id;

    // Search confirmed bookings
    for (int i = 0; i < TOTAL_SEATS; i++)
    {
        if (bus.seats[i].occupied &&
            bus.seats[i].passenger.bookingID == id)
        {
            bus.seats[i].occupied = false;

            cout << "Ticket cancelled successfully.\n";

            promoteWaitingPassenger(bus);
            return;
        }
    }

    // Search waiting list
    queue<Passenger> temp;
    bool found = false;

    while (!bus.waitingList.empty())
    {
        Passenger p = bus.waitingList.front();
        bus.waitingList.pop();

        if (p.bookingID == id && !found)
        {
            found = true;
        }
        else
        {
            temp.push(p);
        }
    }

    bus.waitingList = temp;

    if (found)
    {
        cout << "Waiting-list booking cancelled.\n";
    }
    else
    {
        cout << "Booking ID not found.\n";
    }
}

// Search passenger by booking ID
void searchPassenger()
{
    int id;

    cout << "Enter booking ID: ";
    cin >> id;

    for (int r = 0; r < TOTAL_ROUTES; r++)
    {
        for (int s = 0; s < TOTAL_SEATS; s++)
        {
            if (buses[r].seats[s].occupied &&
                buses[r].seats[s].passenger.bookingID == id)
            {
                Passenger p = buses[r].seats[s].passenger;

                cout << "\nPassenger found!\n";
                cout << "Name: " << p.name << endl;
                cout << "Route: " << buses[r].route << endl;
                cout << "Seat: " << p.seatNo << endl;
                cout << "Fare: Rs. " << p.finalFare << endl;
                cout << "Status: CONFIRMED\n";
                return;
            }
        }

        queue<Passenger> temp = buses[r].waitingList;

        while (!temp.empty())
        {
            Passenger p = temp.front();
            temp.pop();

            if (p.bookingID == id)
            {
                cout << "\nPassenger found!\n";
                cout << "Name: " << p.name << endl;
                cout << "Route: " << buses[r].route << endl;
                cout << "Status: WAITING\n";
                return;
            }
        }
    }

    cout << "Booking ID not found.\n";
}

// Display occupancy report
void displayReport()
{
    cout << "\n===== BUS OCCUPANCY REPORT =====\n";

    for (int r = 0; r < TOTAL_ROUTES; r++)
    {
        int booked = 0;
        double revenue = 0;

        for (int s = 0; s < TOTAL_SEATS; s++)
        {
            if (buses[r].seats[s].occupied)
            {
                booked++;
                revenue += buses[r].seats[s].passenger.finalFare;
            }
        }

        cout << "\nRoute: " << buses[r].route << endl;
        cout << "Booked seats: " << booked << "/50\n";
        cout << "Available seats: " << 50 - booked << endl;
        cout << "Waiting passengers: "
             << buses[r].waitingList.size() << endl;
        cout << "Total revenue: Rs. " << revenue << endl;
    }
}

// Main function
int main()
{
    initializeSystem();

    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << " MAHARASHTRA BUS BOOKING SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Display Routes\n";
        cout << "2. View Seat Availability\n";
        cout << "3. Book Ticket\n";
        cout << "4. View Confirmed Bookings\n";
        cout << "5. View Waiting List\n";
        cout << "6. Cancel Ticket\n";
        cout << "7. Search Passenger\n";
        cout << "8. Occupancy Report\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        switch (choice)
        {
            case 1:
                displayRoutes();
                break;

            case 2:
                displaySeats();
                break;

            case 3:
                bookTicket();
                break;

            case 4:
                displayBookings();
                break;

            case 5:
                displayWaitingList();
                break;

            case 6:
                cancelTicket();
                break;

            case 7:
                searchPassenger();
                break;

            case 8:
                displayReport();
                break;

            case 9:
                cout << "Thank you for using the system!\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 9);

    return 0;
}

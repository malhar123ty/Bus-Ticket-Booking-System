# Bus Ticket Booking System

A console-based Bus Ticket Booking System developed using C++ as a Data Structures and Algorithms (DSA) project.

The system simulates a basic bus reservation process, allowing users to book tickets, view seat availability, cancel reservations, manage waiting lists, and search for passengers.

## Project Overview

The Bus Ticket Booking System is designed to demonstrate the use of fundamental C++ programming concepts and data structures in a real-world application.

It provides a simple menu-driven interface through which users can manage bus reservations for multiple routes.

## Features

- **Bus Routes:** Supports 6 routes originating from Pune.
- **Seat Management:** Each bus has 50 seats.
- **Ticket Booking:** Allows passengers to book tickets by entering their details.
- **Fare Calculation:** Calculates ticket fares based on the passenger's age and gender using the project's demonstration discount rules.
- **Seat Allocation:** Automatically assigns an available seat.
- **Waiting List:** Adds passengers to a waiting list when all seats are occupied.
- **Ticket Cancellation:** Allows confirmed bookings and waiting-list entries to be cancelled.
- **Waiting List Promotion:** Promotes a waiting passenger when a confirmed ticket is cancelled.
- **Passenger Search:** Searches for passengers using their booking ID.
- **Seat Availability:** Displays the current seat status of a bus.
- **Booking Report:** Displays booking details and basic revenue information.

## Bus Routes

The system supports the following routes:

| Route No. | Route           |
| --------- | --------------- |
| 1         | Pune – Mumbai   |
| 2         | Pune – Nashik   |
| 3         | Pune – Nagpur   |
| 4         | Pune – Jalgaon  |
| 5         | Pune – Sangli   |
| 6         | Pune – Kolhapur |

Each route has a bus with 50 seats.

## Data Structures Used

| Data Structure       | Purpose                                     |
| -------------------- | ------------------------------------------- |
| Array                | Stores bus information and seat details     |
| Structure (`struct`) | Represents passengers, seats, and buses     |
| Queue                | Manages passengers in the waiting list      |
| Functions            | Organizes the program into reusable modules |
| Switch-case          | Implements the menu-driven interface        |

## Technologies Used

- C++
- Standard Template Library (STL)
- Arrays
- Structures
- Queue
- Functions
- Conditional statements and loops

## How to Run

### 1. Clone the repository

```bash
git clone https://github.com/malhar123ty/Bus-Ticket-Booking-System.git
```

### 2. Navigate to the project directory

```bash
cd Bus-Ticket-Booking-System
```

### 3. Compile the program

Using g++:

```bash
g++ main.cpp -o bus_ticket_booking_system.exe
```

### 4. Run the program

On Windows:

```bash
bus_ticket_booking_system.exe
```

On Linux or macOS:

```bash
./bus_ticket_booking_system
```

## Project Limitations

- The system stores booking information in memory and does not retain it after the program exits.
- The program uses predefined routes and fares.
- Seat allocation is automatic.
- Fare discounts are demonstration rules and do not represent official bus operator policies.
- The system is currently a console-based application.

## Future Improvements

- Add file handling to save booking information permanently.
- Allow users to select their preferred seats.
- Improve input validation and error handling.
- Add a graphical user interface.
- Introduce user login and authentication.
- Add bus schedules and departure times.
- Implement a more advanced reservation and waiting-list system.

## Learning Outcomes

Through this project, we learned how to:

- Apply C++ programming concepts to a real-world problem.
- Use arrays and structures to organize data.
- Implement a queue for waiting-list management.
- Develop a menu-driven application using switch-case.
- Design functions for modular programming.
- Understand the basic workflow of a ticket reservation system.

## Contributors

- Malhar Joshi
- Mahi Kasliwal
- Pratham Moon
- Pratham Nahar

## License

This project was developed for educational purposes as part of a Data Structures and Algorithms project.

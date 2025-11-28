Blood Donation & Emergency Matching System

A C language-based console application designed to help users find blood donors efficiently. Users can register, log in, post blood requests, search for donors by blood group and area, view notifications, and manage donation history. Admin-level functionality (special account) is also supported for enhanced tracking.

Features
User Features

Registration & Login: Users can create an account or log in using their email and password.

Post Blood Request: Search for available donors by blood group and area.

Donor Matching: Search for donors by blood group.

Donor Search: Search donors by area.

Notifications: Special notifications for the admin/special account.

Donation History: Track blood donation events (for admin/special account).

Admin/Special Account

AURONIX account (team.auronix@gmail.com / AuRoNiX5) can view special notifications and donation history.

Donor Management

Add New Donor: Users can add new donors to the system (stored in memory and persisted in donors.dat).

Built-in Donors

The system comes with predefined donors for testing and demonstration:

Abdur Rahman – A+, Dhanmondi

Hakim – A+, Gulshan

Munna – AB+, Uttara

Hena – A+, Baridhara

Rumana – AB+, Banani

Additional donors can be added interactively.

File Storage

users.dat: Stores registered users (email and password).

donors.dat: Stores donor information in the format: Name|Blood|Phone|Area.

Requirements

C Compiler (GCC/Clang/Visual Studio)

Console/terminal access

Windows or Linux/macOS terminal (supports cls or clear command automatically)

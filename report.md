
# **SUBJECT- Object Oriented Programming in C++**
## **TITLE – Project For Vehicle Parking Management**

### Problem Statement -
    Now-a-days, with increase in population and urbanization, the number of private vehicles has been
increased tremendously, especially in big cities. Due to which, the problem of unmanaged parking
area arises. Many times, these parking areas are limited and do not offer to accommodate a large
number of vehicles. The parking areas in crowded and well secured places like societies, buildings,
theaters, malls, industrial sites require to maintain the records of parked vehicles in an efficient way
such as the records can be stored securely and can be retrieved easily when required. Maintaining a
physical file for this task can be time consuming, likely to have manual errors and missing
information, it can be risky and the stored data can be lost forever. Also this can lead to severe real
time security issues. It also becomes difficult to maintain the record of all earned money from parked
vehicles due to various reasons such as different payment methods, a large set of vehicles, different
vehicle types and respective cost, etc.

There is a need of a system which can store the data of all parked vehicles and perform needed
activities such as adding new entry with accurate time stamp, allotting a slot, searching, updating,
deleting, listing and checking earned money. Also the file must be secure such as it cannot be
opened from outside the program, only the program can read, write to the file. The data stored
inside the file must be secure and cannot be accessed directly. The file can have a large number of
entries, hence, all the data should be hidden from the user and only the required data should be
exposed to the user. The program should perform all necessary operations mentioned above in a
simple manner by which the data can be operated quickly, requiring less time.


### Objective-
The aim of this project is to implement various concepts of Object Oriented Programming in a
real world based application using language C++. The main objective of the project for Vehicle
Parking Management is to provide and mange vehicles by their type and create and edit permanent
log files of the driven data. In our project we provide following utilities-

1) Add new vehicle

2) Search for a vehicle

3) Delete an existing vehicle

4) Update a vehicle

5) List all vehicles available in log file

6) Check earned money from log file

### Remarks -
    Single Inheritance has been used in project where Class VehicleType is base class and Class
Vehicle is inherited class. There is another class named EarnedMoney which is accessed by class
Vehicle using a Friend function.

The class VehicleType distinguishes all the types of vehicles like car, two-wheeler, bus, which can 
be parked in the parking slot.

The class Vehicle is derived from class VehicleType which has all the information about an
individual vehicle object like – VehicleNo., parking_slot, model, drivername, dateime.
This class has 9 member functions which can be called to perform various actions on data.

The function **addparkslot()** is a static function used to increment value of static variable *parking_slot*

The function **delparkslot()** is a static function used to decrement value of static variable *parking_slot*

The function **setvehicle()** takes input from user to get all the data of a new vehicle.

The function **showvehicle()** prints out all the information entered about the vehicle instance.

The function **addvehicle()** adds the data of the new entry to the log file "addvehicle_data.txt".

The function **getvehiclelist()** reads log file and shows all saved data from file "addvehicle_data.txt".

The function **searchvehicle(int vehicleNo)** searches a vehicle by its *vehicleNo.*

The function **deletevehicle(int vehicleNo)** deletes a vehicle by its *vehicleNo.*

The function **updatevehicle(int vehicleNo)** updates an existing vehicle by its *vehicleNo.*
.
The class EarnedMoney has 4 member functions from which one function called addmoney
() is a friend function. This function takes two objects of class EarnedMoney as parameter and adds
new entries for earned money to file "earnedmoney.txt".

Here we are working with two .txt files-
1) "addvehicle_data.txt".
2) "earnedmoney.txt".

*The various concepts we have used are* – manipulators, classes and object, friend function, static
variable and static function, constructor, member function, passing object as a parameter, call by
reference, THIS pointer, single inheritance, file handling, function within function, use of functions
and classes included in time header file, etc.

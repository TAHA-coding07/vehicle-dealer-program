#include <iostream>
#include <cstring>
using namespace std;

// Forward declaration for friend function
class Vehicle;

// Dealer class implementing Singleton pattern with static functions
class Dealer {
private:
    static Dealer *instance;
    string dealerName;

    // Private constructor
    Dealer() : dealerName("Sapphire Vehicle Dealer") {}

public:
    static Dealer* getInstance() {
        if (!instance)
            instance = new Dealer();
        return instance;
    }

    void displayDealerName() {
        cout << "Dealer Name: " << dealerName << endl;
    }
};

// Initialize static member
Dealer* Dealer::instance = nullptr;

// Vehicle class definition with various constructor types
class Vehicle {
protected:
    string brand;
    int price;
    int *mileage;

public:
    // Default constructor
    Vehicle() : brand("Unknown"), price(0), mileage(new int(0)) {
        cout << "Default Constructor called for Vehicle" << endl;
    }

    // Parameterized constructor
    Vehicle(string b, int p, int m = 0) : brand(b), price(p), mileage(new int(m)) {
        cout << "Parameterized Constructor called for Vehicle" << endl;
    }

    // Copy constructor
    Vehicle(const Vehicle &v) : brand(v.brand), price(v.price), mileage(new int(*v.mileage)) {
        cout << "Copy Constructor called for Vehicle" << endl;
    }

    // Destructor
    ~Vehicle() {
        cout << "Destructor called for Vehicle" << endl;
        delete mileage;
    }

    // Friend function to display vehicle details
    friend void showVehicleDetails(const Vehicle &v);

    // Unary operator overloading
    void operator++() {
        ++(*mileage);
        cout << "Mileage incremented by 1" << endl;
    }

    // Binary operator overloading
    Vehicle operator+(const Vehicle &v) {
        return Vehicle(brand + " & " + v.brand, price + v.price, *mileage + *v.mileage);
    }

    // Subscript operator overloading
    char operator[](int index) const {
        return brand[index];
    }

    // Static function
    static void showTotalVehicles(int count) {
        cout << "Total vehicles available: " << count << endl;
    }

    // Setter for mileage (pass by reference)
    void setMileage(int &m) {
        *mileage = m;
    }

    // Getter for mileage (return by reference)
    int& getMileage() {
        return *mileage;
    }

    // Virtual function
    virtual void displayInfo() {
        cout << "Vehicle Brand: " << brand << ", Price: $" << price << ", Mileage: " << *mileage << endl;
    }
};

// Friend function to access private members of Vehicle
void showVehicleDetails(const Vehicle &v) {
    cout << "Brand: " << v.brand << ", Price: $" << v.price << ", Mileage: " << *v.mileage << " km" << endl;
}

// Car class inheriting from Vehicle (single level inheritance)
class Car : public Vehicle {
private:
    string carType;

public:
    // Parameterized constructor with default argument
    Car(string b, int p, int m, string type = "Sedan") : Vehicle(b, p, m), carType(type) {}

    // Overridden function
    void displayInfo() override {
        Vehicle::displayInfo();
        cout << "Car Type: " << carType << endl;
    }
};

// ElectricCar class inheriting from Car (multi-level inheritance)
class ElectricCar : public Car {
private:
    int batteryCapacity;

public:
    ElectricCar(string b, int p, int m, int battery, string type = "Electric") 
        : Car(b, p, m, type), batteryCapacity(battery) {}

    void displayInfo() override {
        Car::displayInfo();
        cout << "Battery Capacity: " << batteryCapacity << " kWh" << endl;
    }
};

// Truck class for multiple inheritance example
class Truck {
public:
    int loadCapacity;

    Truck(int capacity) : loadCapacity(capacity) {}

    void showLoadCapacity() {
        cout << "Load Capacity: " << loadCapacity << " tons" << endl;
    }
};

// HybridVehicle class inheriting from both Vehicle and Truck (hybrid inheritance)
class HybridVehicle : public Vehicle, public Truck {
private:
    string fuelType;

public:
    HybridVehicle(string b, int p, int m, int capacity, string fuel = "Hybrid") 
        : Vehicle(b, p, m), Truck(capacity), fuelType(fuel) {}

    void displayInfo() override {
        Vehicle::displayInfo();
        cout << "Fuel Type: " << fuelType << endl;
        showLoadCapacity();
    }
};

// Main function
int main() {
    Dealer *dealer = Dealer::getInstance();
    dealer->displayDealerName();

    // Get user input for a Vehicle
    string brand;
    int price, mileage, batteryCapacity, loadCapacity;
    string carType, fuelType;

    cout << "Enter vehicle brand: ";
    cin >> brand;
    cout << "Enter vehicle price: ";
    cin >> price;
    cout << "Enter vehicle mileage: ";
    cin >> mileage;

    Vehicle vehicle1(brand, price, mileage);
    showVehicleDetails(vehicle1);

    cout << "\n--- Car Information ---" << endl;
    cout << "Enter car brand: ";
    cin >> brand;
    cout << "Enter car price: ";
    cin >> price;
    cout << "Enter car mileage: ";
    cin >> mileage;
    cout << "Enter car type (e.g., SUV, Sedan): ";
    cin >> carType;

    Car car1(brand, price, mileage, carType);
    car1.displayInfo();

    cout << "\n--- Electric Car Information ---" << endl;
    cout << "Enter electric car brand: ";
    cin >> brand;
    cout << "Enter electric car price: ";
    cin >> price;
    cout << "Enter electric car mileage: ";
    cin >> mileage;
    cout << "Enter battery capacity (kWh): ";
    cin >> batteryCapacity;

    ElectricCar ecar1(brand, price, mileage, batteryCapacity);
    ecar1.displayInfo();

    cout << "\n--- Hybrid Vehicle Information ---" << endl;
    cout << "Enter hybrid vehicle brand: ";
    cin >> brand;
    cout << "Enter hybrid vehicle price: ";
    cin >> price;
    cout << "Enter hybrid vehicle mileage: ";
    cin >> mileage;
    cout << "Enter load capacity (tons): ";
    cin >> loadCapacity;
    cout << "Enter fuel type (e.g., Hybrid, Petrol): ";
    cin >> fuelType;

    HybridVehicle hybrid1(brand, price, mileage, loadCapacity, fuelType);
    hybrid1.displayInfo();

    // Unary and binary operator overload usage
    ++vehicle1;
    Vehicle vehicle2("BMW", 35000, 20000);
    Vehicle combinedVehicle = vehicle1 + vehicle2;
    showVehicleDetails(combinedVehicle);

    // Accessing overloaded subscript operator
    cout << "First character of brand in vehicle1: " << vehicle1[0] << endl;

    // Dynamic memory allocation and deallocation through constructor and destructor
    int newMileage = 18000;
    vehicle1.setMileage(newMileage);
    cout << "Updated Mileage (via pass by reference): " << vehicle1.getMileage() << " km" << endl;

    // Static function
    Vehicle::showTotalVehicles(4);

    return 0;
}

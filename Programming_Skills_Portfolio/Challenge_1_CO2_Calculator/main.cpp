#include <iostream>
#include <limits>
// Get the journey distance from the user
double getDistance() {
    double distance;

    do {
    std::cout << "Enter journey distance in miles: ";
    if (!(std::cin >> distance)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    distance = -1;
    std::cout << "Invalid input. Please enter a number.\n";
}
} while (distance < 0);

    return distance;
}
// Get the fuel type from the user
char getFuelType() {
    char fuelType;

    do {
    std::cout << "Enter fuel type (P for petrol, D for diesel): ";
    std::cin >> fuelType;
} while (fuelType != 'P' && fuelType != 'p' &&
         fuelType != 'D' && fuelType != 'd');

    return fuelType;
}
// Calculate CO2 emissions based on distance and fuel type
double calculateCO2(double distance, char fuelType) {
    const double fuelConsumption = 9.66;
    const double petrolEmission = 2.31;
    const double dieselEmission = 2.68;

    double litresUsed = (distance / 100.0) * fuelConsumption;

    if (fuelType == 'P' || fuelType == 'p') {
        return litresUsed * petrolEmission;
    } else {
        return litresUsed * dieselEmission;
    }
}
// Entry point of the CO2 Calculator
int main() {
    std::cout << "=== CO2 Emissions Calculator ===\n";
    std::cout << "Calculate emissions for petrol or diesel journeys.\n";
    double distance = getDistance();
    char fuelType = getFuelType();

    double emissions = calculateCO2(distance, fuelType);

    std::cout << "\nEstimated CO2 emissions: "
              << emissions << " kg\n";
    return 0;
}
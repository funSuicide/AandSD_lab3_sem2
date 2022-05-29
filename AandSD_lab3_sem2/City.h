#include <string>
#include <iostream>

class City {
	std::string nameCity;
	unsigned int countResidents;
public:
	City(const std::string& nameCity, unsigned int countResidents) {
		this->nameCity = nameCity; 
		this->countResidents = countResidents;
	}
	void PrintCity() const {
		std::cout << "City: " << nameCity << "(" << countResidents << ")";
	}
};

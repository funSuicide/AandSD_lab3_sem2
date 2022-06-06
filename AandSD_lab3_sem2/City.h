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
	bool operator == (const City& tmpCity) {
		return ((countResidents == tmpCity.countResidents) && (nameCity == tmpCity.nameCity));
	}
	std::string GetName() const {
		return nameCity;
	}
};

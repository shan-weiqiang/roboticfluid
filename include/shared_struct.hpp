#include <string>
#include <array>
#include <vector>
#include <iostream>

// Custom Owner class
class Owner {
public:
    // Data members (public)
    std::string name_;
    int age_;

    // Getters and Setters
    std::string getName() const { return name_; }
    void setName(const std::string& name) { name_ = name; }
    int getAge() const { return age_; }
    void setAge(int age) { age_ = age; }
};

// Modified Pet class
class Pet {
public:
    // Data members (all public)
    std::string name;
    int age;
    float weight;
    double height;
    bool isVaccinated;
    char gender;
    std::array<int, 3> favoriteNumbers;
    std::array<float, 2> coordinates;
    std::vector<std::string> tricks;
    std::vector<int> scores;
    Owner owner;
    std::array<Owner, 2> multipleOwners;
    std::vector<Owner> ownerList;

    // Methods (all public)
    void bark() { std::cout << name << " barks!\n"; }

    // Setters and Getters for all data members
    std::string getName() const { return name; }
    void setName(const std::string& n) { name = n; }

    int getAge() const { return age; }
    void setAge(int a) { age = a; }

    float getWeight() const { return weight; }
    void setWeight(float w) { weight = w; }

    double getHeight() const { return height; }
    void setHeight(double h) { height = h; }

    bool getIsVaccinated() const { return isVaccinated; }
    void setIsVaccinated(bool v) { isVaccinated = v; }

    char getGender() const { return gender; }
    void setGender(char g) { gender = g; }

    const std::array<int, 3>& getFavoriteNumbers() const { return favoriteNumbers; }
    void setFavoriteNumbers(const std::array<int, 3>& fn) { favoriteNumbers = fn; }

    const std::array<float, 2>& getCoordinates() const { return coordinates; }
    void setCoordinates(const std::array<float, 2>& c) { coordinates = c; }

    const std::vector<std::string>& getTricks() const { return tricks; }
    void setTricks(const std::vector<std::string>& t) { tricks = t; }

    const std::vector<int>& getScores() const { return scores; }
    void setScores(const std::vector<int>& s) { scores = s; }

    const Owner& getOwner() const { return owner; }
    void setOwner(const Owner& o) { owner = o; }

    const std::array<Owner, 2>& getMultipleOwners() const { return multipleOwners; }
    void setMultipleOwners(const std::array<Owner, 2>& mo) { multipleOwners = mo; }

    const std::vector<Owner>& getOwnerList() const { return ownerList; }
    void setOwnerList(const std::vector<Owner>& ol) { ownerList = ol; }

    // New methods
    std::string serialize() const; // Serialize and return string
    void deserialize(const std::string& src); // Deserialize from src
};
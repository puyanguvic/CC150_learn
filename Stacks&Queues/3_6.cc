#include <iostream>
#include <string>
#include <list>
#include <stdexcept>

class Animal {
public:
    enum Type { DOG, CAT };

    Animal(Type type, std::string name, int order) 
        : type(type), name(name), order(order) {}

    Type getType() const { return type; }
    std::string getName() const { return name; }
    int getOrder() const { return order; }

private:
    Type type;
    std::string name;
    int order;
};

class AnimalShelter {
private:
    std::list<Animal> dogs;
    std::list<Animal> cats;
    int order;

public:
    AnimalShelter() : order(0) {}

    void enqueue(Animal::Type type, const std::string& name) {
        if (type == Animal::DOG) {
            dogs.emplace_back(Animal::DOG, name, order++);
        } else {
            cats.emplace_back(Animal::CAT, name, order++);
        }
    }

    Animal dequeueAny() {
        if (dogs.empty() && cats.empty()) {
            throw std::runtime_error("No animals available");
        }

        if (dogs.empty()) {
            return dequeueCat();
        }

        if (cats.empty()) {
            return dequeueDog();
        }

        if (dogs.front().getOrder() < cats.front().getOrder()) {
            return dequeueDog();
        } else {
            return dequeueCat();
        }
    }

    Animal dequeueDog() {
        if (dogs.empty()) {
            throw std::runtime_error("No dogs available");
        }
        Animal dog = dogs.front();
        dogs.pop_front();
        return dog;
    }

    Animal dequeueCat() {
        if (cats.empty()) {
            throw std::runtime_error("No cats available");
        }
        Animal cat = cats.front();
        cats.pop_front();
        return cat;
    }
};

// Test function
void testAnimalShelter() {
    AnimalShelter shelter;

    std::cout << "Enqueueing animals...\n";
    shelter.enqueue(Animal::DOG, "Rex");
    shelter.enqueue(Animal::CAT, "Whiskers");
    shelter.enqueue(Animal::DOG, "Buddy");
    shelter.enqueue(Animal::CAT, "Mittens");
    shelter.enqueue(Animal::DOG, "Max");

    std::cout << "\nDequeuing any animal: ";
    Animal animal = shelter.dequeueAny();
    std::cout << animal.getName() << " (" << (animal.getType() == Animal::DOG ? "Dog" : "Cat") << ")\n";

    std::cout << "Dequeuing a dog: ";
    animal = shelter.dequeueDog();
    std::cout << animal.getName() << "\n";

    std::cout << "Dequeuing a cat: ";
    animal = shelter.dequeueCat();
    std::cout << animal.getName() << "\n";

    std::cout << "\nDequeuing remaining animals:\n";
    try {
        while (true) {
            animal = shelter.dequeueAny();
            std::cout << animal.getName() << " (" << (animal.getType() == Animal::DOG ? "Dog" : "Cat") << ")\n";
        }
    } catch (const std::runtime_error& e) {
        std::cout << "Shelter is empty: " << e.what() << std::endl;
    }
}

int main() {
    testAnimalShelter();
    return 0;
}
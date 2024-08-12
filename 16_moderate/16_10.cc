#include <iostream>
#include <vector>
#include <algorithm>

struct Person {
    int birth;
    int death;
    Person(int b, int d) : birth(b), death(d) {}
};

class LivingPeople {
public:
    static int maxAliveYear(std::vector<Person>& people, int min_year = 1900, int max_year = 2000) {
        std::vector<int> population_change(max_year - min_year + 2, 0);

        for (const Person& person : people) {
            population_change[person.birth - min_year]++;
            population_change[person.death - min_year + 1]--;
        }

        int max_alive = 0;
        int max_alive_year = min_year;
        int current_alive = 0;

        for (int year = min_year; year <= max_year; year++) {
            current_alive += population_change[year - min_year];
            if (current_alive > max_alive) {
                max_alive = current_alive;
                max_alive_year = year;
            }
        }

        return max_alive_year;
    }
};

int main() {
    std::vector<Person> people = {
        Person(1900, 1950),
        Person(1910, 1960),
        Person(1920, 1970),
        Person(1905, 1955),
        Person(1930, 1980),
        Person(1940, 1990),
        Person(1950, 2000)
    };

    int year = LivingPeople::maxAliveYear(people);
    std::cout << "Year with most people alive: " << year << std::endl;

    return 0;
}
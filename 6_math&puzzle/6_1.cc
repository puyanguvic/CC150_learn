#include <iostream>
#include <vector>
#include <iomanip>

int findHeavyBottle(const std::vector<double>& weights) {
    double expectedWeight = 0;
    for (int i = 1; i <= 20; ++i) {
        expectedWeight += i * 1.0;
    }

    double actualWeight = 0;
    for (int i = 0; i < weights.size(); ++i) {
        actualWeight += weights[i] * (i + 1);
    }

    double difference = actualWeight - expectedWeight;
    int heavyBottle = static_cast<int>(difference / 0.1);
    return heavyBottle;
}

int main() {
    // Assume we have the weights from the bottles
    std::vector<double> weights = {
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.1
    };

    int heavyBottle = findHeavyBottle(weights);
    std::cout << "The heavy bottle is bottle number: " << heavyBottle + 1 << std::endl;

    return 0;
}

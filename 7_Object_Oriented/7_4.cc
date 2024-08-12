#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <thread>
#include <chrono>

enum class VehicleType { Car, Motorcycle, Bus };
enum class ParkingSpotType { Small, Medium, Large };

class Vehicle {
public:
    Vehicle(VehicleType type, std::string licensePlate)
        : m_type(type), m_licensePlate(licensePlate) {}
    virtual ~Vehicle() = default;

    VehicleType getType() const { return m_type; }
    std::string getLicensePlate() const { return m_licensePlate; }

private:
    VehicleType m_type;
    std::string m_licensePlate;
};

class Car : public Vehicle {
public:
    Car(std::string licensePlate) : Vehicle(VehicleType::Car, licensePlate) {}
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(std::string licensePlate) : Vehicle(VehicleType::Motorcycle, licensePlate) {}
};

class Bus : public Vehicle {
public:
    Bus(std::string licensePlate) : Vehicle(VehicleType::Bus, licensePlate) {}
};

class ParkingSpot {
public:
    ParkingSpot(ParkingSpotType type, int number)
        : m_type(type), m_number(number), m_free(true), m_vehicle(nullptr) {}

    bool isFree() const { return m_free; }
    bool canFitVehicle(const Vehicle& vehicle) const {
        // 实现判断车辆是否适合此停车位的逻辑
        return true; // 简化示例
    }

    void parkVehicle(Vehicle* vehicle) {
        m_vehicle = vehicle;
        m_free = false;
    }

    void removeVehicle() {
        m_vehicle = nullptr;
        m_free = true;
    }

private:
    ParkingSpotType m_type;
    int m_number;
    bool m_free;
    Vehicle* m_vehicle;
};

class ParkingFloor {
public:
    ParkingFloor(int floorNumber, int numSmall, int numMedium, int numLarge) 
        : m_floorNumber(floorNumber) {
        for (int i = 0; i < numSmall; ++i) {
            m_spots.push_back(ParkingSpot(ParkingSpotType::Small, i));
        }
        for (int i = 0; i < numMedium; ++i) {
            m_spots.push_back(ParkingSpot(ParkingSpotType::Medium, numSmall + i));
        }
        for (int i = 0; i < numLarge; ++i) {
            m_spots.push_back(ParkingSpot(ParkingSpotType::Large, numSmall + numMedium + i));
        }
    }

    ParkingSpot* findAvailableSpot(const Vehicle& vehicle) {
        for (auto& spot : m_spots) {
            if (spot.isFree() && spot.canFitVehicle(vehicle)) {
                return &spot;
            }
        }
        return nullptr;
    }

private:
    int m_floorNumber;
    std::vector<ParkingSpot> m_spots;
};

class ParkingTicket {
public:
    ParkingTicket(const Vehicle& vehicle, ParkingSpot* spot, time_t entryTime)
        : m_vehicle(vehicle), m_spot(spot), m_entryTime(entryTime) {}

    const Vehicle& getVehicle() const { return m_vehicle; }
    ParkingSpot* getSpot() const { return m_spot; }
    time_t getEntryTime() const { return m_entryTime; }

private:
    const Vehicle& m_vehicle;
    ParkingSpot* m_spot;
    time_t m_entryTime;
};

class ParkingRate {
public:
    static double calculateFee(const ParkingTicket& ticket, time_t exitTime) {
        // 实现停车费用计算逻辑
        return 10.0; // 简化示例，固定费用
    }
};

class ParkingLot {
public:
    ParkingLot(int numFloors, int numSpotsPerFloor) {
        for (int i = 0; i < numFloors; ++i) {
            m_floors.push_back(ParkingFloor(i, numSpotsPerFloor/3, numSpotsPerFloor/3, numSpotsPerFloor/3));
        }
    }

    ParkingTicket* parkVehicle(Vehicle& vehicle) {
        for (auto& floor : m_floors) {
            ParkingSpot* spot = floor.findAvailableSpot(vehicle);
            if (spot) {
                spot->parkVehicle(&vehicle);
                ParkingTicket* ticket = new ParkingTicket(vehicle, spot, time(nullptr));
                m_activeTickets[vehicle.getLicensePlate()] = ticket;
                return ticket;
            }
        }
        return nullptr; // 没有可用的停车位
    }

    double unpackVehicle(const std::string& licensePlate) {
        auto it = m_activeTickets.find(licensePlate);
        if (it == m_activeTickets.end()) {
            return -1; // 没有找到对应的停车票
        }

        ParkingTicket* ticket = it->second;
        time_t exitTime = time(nullptr);
        double fee = ParkingRate::calculateFee(*ticket, exitTime);

        ticket->getSpot()->removeVehicle();
        m_activeTickets.erase(it);
        delete ticket;

        return fee;
    }

private:
    std::vector<ParkingFloor> m_floors;
    std::unordered_map<std::string, ParkingTicket*> m_activeTickets;
};

int main() {
    ParkingLot parkingLot(3, 30); // 3层，每层30个停车位

    Car car1("ABC123");
    Car car2("DEF456");
    Motorcycle motorcycle("GHI789");

    ParkingTicket* ticket1 = parkingLot.parkVehicle(car1);
    ParkingTicket* ticket2 = parkingLot.parkVehicle(car2);
    ParkingTicket* ticket3 = parkingLot.parkVehicle(motorcycle);

    if (ticket1) std::cout << "Car1 parked successfully" << std::endl;
    if (ticket2) std::cout << "Car2 parked successfully" << std::endl;
    if (ticket3) std::cout << "Motorcycle parked successfully" << std::endl;

    // 模拟一些时间过去
    std::this_thread::sleep_for(std::chrono::seconds(10));

    double fee1 = parkingLot.unpackVehicle("ABC123");
    double fee2 = parkingLot.unpackVehicle("DEF456");
    double fee3 = parkingLot.unpackVehicle("GHI789");

    std::cout << "Car1 parking fee: " << fee1 << std::endl;
    std::cout << "Car2 parking fee: " << fee2 << std::endl;
    std::cout << "Motorcycle parking fee: " << fee3 << std::endl;

    return 0;
}
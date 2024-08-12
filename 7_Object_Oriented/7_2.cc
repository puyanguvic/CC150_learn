#include <iostream>
#include <vector>
#include <queue>
#include <map>

enum class Rank { Respondent, Manager, Director };

class Call {
public:
    Call(int id) : m_id(id) {}
    int getId() const { return m_id; }

private:
    int m_id;
};

class Employee {
public:
    Employee(Rank rank) : m_rank(rank), m_free(true) {}
    virtual ~Employee() = default;

    bool isFree() const { return m_free; }
    void setFree(bool free) { m_free = free; }
    Rank getRank() const { return m_rank; }

    virtual bool handleCall(Call* call) {
        std::cout << "Employee handling call " << call->getId() << std::endl;
        return true; // 假设所有呼叫都能被处理
    }

protected:
    Rank m_rank;
    bool m_free;
};

class Respondent : public Employee {
public:
    Respondent() : Employee(Rank::Respondent) {}
};

class Manager : public Employee {
public:
    Manager() : Employee(Rank::Manager) {}
};

class Director : public Employee {
public:
    Director() : Employee(Rank::Director) {}
};

class CallCenter {
public:
    CallCenter(int respondents, int managers, int directors) {
        for (int i = 0; i < respondents; ++i) {
            m_employees[Rank::Respondent].push_back(new Respondent());
        }
        for (int i = 0; i < managers; ++i) {
            m_employees[Rank::Manager].push_back(new Manager());
        }
        for (int i = 0; i < directors; ++i) {
            m_employees[Rank::Director].push_back(new Director());
        }
    }

    ~CallCenter() {
        for (const auto& pair : m_employees) {
            for (Employee* emp : pair.second) {
                delete emp;
            }
        }
    }

    bool dispatchCall(Call* call) {
        for (const auto& rank : {Rank::Respondent, Rank::Manager, Rank::Director}) {
            for (Employee* emp : m_employees[rank]) {
                if (emp->isFree()) {
                    emp->setFree(false);
                    if (emp->handleCall(call)) {
                        emp->setFree(true);
                        return true;
                    }
                    emp->setFree(true);
                    break; // 尝试下一级别的员工
                }
            }
        }
        return false; // 所有员工都忙或无法处理
    }

private:
    std::map<Rank, std::vector<Employee*>> m_employees;
};

int main() {
    CallCenter callCenter(5, 3, 1); // 5个接线员，3个经理，1个主管

    std::queue<Call> calls;
    for (int i = 1; i <= 10; ++i) {
        calls.push(Call(i));
    }

    while (!calls.empty()) {
        Call* call = &calls.front();
        if (callCenter.dispatchCall(call)) {
            std::cout << "Call " << call->getId() << " handled successfully" << std::endl;
        } else {
            std::cout << "Call " << call->getId() << " could not be handled" << std::endl;
        }
        calls.pop();
    }

    return 0;
}
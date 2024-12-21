#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <vector>
#include <memory>
#include <iostream>
using namespace std;

class Subject {
public:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* observer) {
        if (!observer) {
            cout << "Invalid observer\n";
            return;
        }
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

protected:
    void notify(const Event* event) {
        for (auto observer : observers) {
            if (!observer) {
                cout << "Error \n";
                continue;
            }
            observer->onNotify(event);
        }
    }
};

#endif

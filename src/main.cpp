/**
 * Title: Lab 33:  Toll Plaza
 * Description: 4 lanes of toll booth hell.
 * Author: Nick Galvez
 * Class: COMSC-210
 *
 */

#include <iostream>
#include <deque>
#include <string>
#include <memory>
#include <codecvt> // Include for codecvt_utf8
#include "Car.h"

const int ICON_MIN = 0x1F695, ICON_MAX = 0x1F6C0;

/**
 * Add an emoji or other properties to the car
 */
class CarDecorator
{
private:
    shared_ptr<Car> car;
    wchar_t emoji;

public:
    CarDecorator(shared_ptr<Car> car)
    {
        this->car = car;
        // https://unicode.org/emoji/charts/full-emoji-list.html
        // assign a car emoji to the car, starting from 0x1F695.
        // emoji = static_cast<wchar_t>(arc4random() % (ICON_MAX - ICON_MIN + 1) + ICON_MIN);
        // emoji = arc4random() % (ICON_MAX - ICON_MIN + 1) + ICON_MIN;
        emoji = 0x1F695; // I wanted each car to have a unique emoji, but it wasn't working.
    }
    wchar_t getIcon() { return static_cast<wchar_t>(emoji); }
    string printIcon()
    {
        // Not sure what's going on here, but I don't think it's printing an icon correctly.
        wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
        return converter.to_bytes(emoji);
    }
    void print()
    {
        cout << "[" << car->getYear() << " " << car->getMake() << " " << car->getTransponder() << "] ";
        cout << printIcon() << endl;
    }
};

/**
 * Wrap the car and the decorator into a single object
 */
class CarWrapper
{
private:
    shared_ptr<Car> car;
    shared_ptr<CarDecorator> decorator;

public:
    CarWrapper()
    {
        this->car = make_shared<Car>();
        this->decorator = make_shared<CarDecorator>(this->car);
    }
    CarWrapper(shared_ptr<Car> car)
    {
        this->car = car;
        this->decorator = make_shared<CarDecorator>(this->car);
    }
    // get the car pointer
    shared_ptr<Car> getCar() { return this->car; }
    // get the decorator pointer
    shared_ptr<CarDecorator> getDecorator() { return this->decorator; }
};

using namespace std;

const int INITIAL_CARS = 2, NUM_LANES = 4,
          PROB_CAR_JOINS = 39, PROB_CAR_LEAVES = 46, PROB_CAR_CHANGES_LANES = 15;

/**
 * Print the queue of cars
 */
void printQueue(array<deque<CarWrapper>, NUM_LANES> &lanes)
{
    for (int i = 0; i < NUM_LANES; i++)
    {
        deque<CarWrapper> &cars = lanes[i];
        cout << "Lane " << i + 1 << ": " << endl;
        if (cars.empty())
        {
            cout << "  [EMPTY]" << endl;
            continue;
        }
        for (size_t i = 0; i < cars.size(); i++)
        {
            cout << "  ";
            cars[i].getDecorator()->print();
        }
    }
    cout << endl;
}

/**
 * Move the cars through through time, as the occupants grow ever older in the Kafkaesque nightmare of the superhighway system.
 */
bool timeMarchesOn(array<deque<CarWrapper>, NUM_LANES> &lanes)
{
    int lanesEmpty = 0;
    for (int i = 0; i < NUM_LANES; i++)
    {
        deque<CarWrapper> &cars = lanes[i];
        if (cars.size() < 1)
        {
            // Incriment empty lanes
            lanesEmpty++;
            // skip this loop.
            // cout << "[Lane "<< i+1 << "] -" << endl;
            continue;
        }
        // Run this first or there could be an exception
        // 15% probability that the car at the head of the line changes lanes
        if (arc4random() % 100 < PROB_CAR_CHANGES_LANES)
        {
            cout << "[Lane " << i + 1 << "] Changed: ";
            CarWrapper car = cars.back();
            cars.pop_back();
            // pick a lane, but only if it's next to the car's current lane

            int newLane = i;
            while (newLane == i || newLane < i - 1 || newLane > i + 1 || newLane < 0 || newLane >= NUM_LANES)
            {
                newLane = arc4random() % NUM_LANES;
            }
            cout << "Sisyphus here moves from lane " << i + 1 << " to lane " << newLane + 1 << ": ";
            car.getDecorator()->print();
            lanes[newLane].push_back(car);
        }

        // 55% probability that the car at the head of the line pays its toll and leaves the toll booth
        // But if there are no cars, don't try to pop one.
        if (arc4random() % 100 < PROB_CAR_LEAVES && cars.size() > 0)
        {
            cout << "[Lane " << i + 1 << "] Paid: ";
            cars.front().getDecorator()->print();
            cars.pop_front();
        }
        // 45% probability that another car joins the line for the toll booth
        if (arc4random() % 100 < PROB_CAR_JOINS)
        {
            cars.push_back(CarWrapper());
            cout << "[Lane " << i + 1 << "] Joined: ";
            cars.back().getDecorator()->print();
        }
    }
    cout << "Queue:" << endl;
    printQueue(lanes);
    // If all lanes are empty, return false
    return lanesEmpty < NUM_LANES;
}

int main()
{
    // Set the locale to enable UTF-8 output. I guess this is why the vscode terminal doesn't display emojis.
    locale::global(locale("en_US.UTF-8"));
    wcout.imbue(locale());
    // Not sure if this works on all terminal emulators.

    // Set up the queue of cars
    // Set up lanes
    array<deque<CarWrapper>, NUM_LANES> lanes;
    int time = 0;

    for (int i = 0; i < NUM_LANES; i++)
    {
        for (size_t j = 0; j < INITIAL_CARS; j++)
        {
            lanes[i].push_front(CarWrapper());
        }
    }
    // Print intial queue
    cout << "Initial Queue:" << endl;
    printQueue(lanes);

    cout << endl << "Time: 0" << endl;
    // Run the simulation
    while (timeMarchesOn(lanes) == true)
    {
        time++;
        cout << "Time: " << time << endl;
    }

    cout << "All cars have left the toll booth." << endl;

    return 0;
}
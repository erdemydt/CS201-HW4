// Name: Erdem Pülat
// ID: 22103566 Section: 2
#ifndef ZOOMAP_H
#define ZOOMAP_H
#include <string>
#include <iostream>
#include "LinkedList.h"
using namespace std;
struct Cage
{
    string name;
    double possiblity;
    bool isLooked = false;
    LinkedList<Cage> nexts;
    bool operator<(const Cage &other) const
    {
        return this->name < other.name;
    }
    bool operator==(const Cage &other) const
    {
        return this->name == other.name;
    }
    bool operator!=(const Cage &other) const
    {
        return this->name != other.name;
    }
    void reset(){
        isLooked = false;
    }
    friend std::ostream &operator<<(std::ostream &os, const Cage &obj)
    {
        os << obj.name;
        return os;
    }
    Cage(){
        name = "";
        possiblity = 0;
        isLooked = false;
    }
    Cage(const Cage& other) {
        this->name = other.name;
        this->isLooked = other.isLooked;
        this->possiblity = other.possiblity; 
    }
    ~Cage(){
        nexts.~LinkedList();
    }
};
class ZooMap
{
private:
    LinkedList<Cage> cages;
    int totalNumOfCages;
    void resetPaths(){
        Node<Cage>* headd = cages.getHead();
        while (headd!= nullptr)
        {
            headd->data.reset();
            headd = headd->next;
        }
        
    }
public:
    ZooMap(const string cageFile, const string zooFile);
    ~ZooMap();
    void displayAllCages() const;
    void displayAdjacentCages(const string cageName) const;
    void displayZooMap() const;
    void findSafestPath(const string startCage, const string endCage);
    void findMostDangerousPath(const string startCage, const string endCage);
};
#endif
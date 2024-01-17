// Name: Erdem Pülat
// ID: 22103566 Section: 2
#include "ZooMap.h"
#include "Stack.h"
#include <sstream>
#include <fstream>
#include <iomanip>

struct Path
{
    string pathstr;
    double possiblity;
    bool operator<(const Path &other) const
    {
        return this->possiblity < other.possiblity;
    }
    bool operator==(const Path &other) const
    {
        return this->possiblity == other.possiblity;
    }
    bool operator!=(const Path &other) const
    {
        return this->possiblity != other.possiblity;
    }
};

ZooMap::ZooMap(const string cageFile, const string zooFile)
{
    ifstream cageFi(cageFile);
    ifstream zooFi(zooFile);
    this->totalNumOfCages = 0;
    int cageCount = 0;
    int connectionCount = 0;
    if (!cageFi.is_open())
    {
        cerr << "Error opening the file." << endl;
    }
    else
    {
        string line;

        while (getline(cageFi, line))
        {
            size_t ind = line.find(';');
            string lol[] = {
                line.substr(0, ind),
                line.substr(ind + 1)};
            Cage temp;
            temp.name = lol[0];
            temp.possiblity = stod(lol[1]);
            cages.insert(temp);
            cageCount++;
        }

        cageFi.close();
    }
    if (!zooFi.is_open())
    {
        cerr << "Error opening the file." << endl;
    }
    else
    {
        string line;
        while (getline(zooFi, line))
        {

            size_t ind = line.find(';');
            string lol[] = {
                line.substr(0, ind),
                line.substr(ind + 1)};
            Cage temp;
            Cage temp2;

            temp.name = lol[0];
            temp2.name = lol[1];
            int index1 = cages.contains(temp);
            int index2 = cages.contains(temp2);
            if (index1 != -1 && index2 != -1)
            {
                if (cages.get(index1)->data.nexts.contains(temp2) == -1)
                {
                    temp2.possiblity = cages.get(index2)->data.possiblity;
                    cages.get(index1)->data.nexts.insert(temp2);
                }
            }
            connectionCount++;
        }
        zooFi.close();
    }
    this->totalNumOfCages = cageCount;
    cout << cageCount << " cages and " << connectionCount << " connections have been loaded." << endl;
}
ZooMap::~ZooMap()
{
    cages.~LinkedList();
}
void ZooMap::displayAllCages() const
{
    cout << "The cages in the zoo are:" << endl;
    Node<Cage> *headptr = cages.getHead();
    while (headptr != nullptr)
    {
        cout << headptr->data.name << ",";
        if (headptr->next != nullptr)
        {
            cout << " ";
        }

        headptr = headptr->next;
    }
    cout << endl;
}

void ZooMap::displayAdjacentCages(const string cageName) const
{
    Cage temp;
    temp.name = cageName;
    int index = cages.contains(temp);
    if (index != -1)
    {
        cout << "The cages adjacent to " << cageName << " are:" << endl;
        cout << cageName << " ->";
        Node<Cage> *headptr = cages.get(index)->data.nexts.getHead();
        while (headptr != nullptr)
        {
            cout <<" "<< headptr->data << ",";
          
            headptr = headptr->next;
        }
        cout << endl;
    }
}

void ZooMap::displayZooMap() const
{
    cout << "The whole zoo map is:" << endl;
    Node<Cage> *headpp = cages.getHead();
    while (headpp != nullptr)
    {
        Node<Cage> *secondHead = headpp->data.nexts.getHead();
        cout << headpp->data;
        cout << " ->";
        while (secondHead != nullptr)
        {
            cout << " "<<secondHead->data << ",";

            secondHead = secondHead->next;
        }
        headpp = headpp->next;
        cout << endl;
    }
}

void ZooMap::findSafestPath(const string startCage, const string endCage)
{

    // initial logic
    std::cout << std::fixed << std::setprecision(6);
    Cage start;
    start.name = startCage;
    Cage end;
    end.name = endCage;
    double possiblityTotal = 1;
    LinkedList<Path> possiblities;
    Stack<Cage> myStack(20);
    int index1 = cages.contains(start);
    int index2 = cages.contains(end);
    // locating cages
    Cage *startC = &cages.get(index1)->data;
    Cage *endC = &cages.get(index2)->data;
    startC->isLooked = true;
    start.isLooked = true;

    // start
    myStack.push(*startC);
    while (!myStack.isEmpty())
    {

        Node<Cage> *headptr = cages.get(myStack.peek())->nexts.getHead();
        if (headptr == nullptr)
        {
            myStack.pop();
        }
        else
        {
            Cage *trialPtr = cages.get(headptr->data);
            bool hasBeenLookedAt = trialPtr->isLooked;

            while (headptr != nullptr && hasBeenLookedAt)
            {

                headptr = headptr->next;
                if (headptr != nullptr)
                {
                    trialPtr = cages.get(headptr->data);
                    hasBeenLookedAt = trialPtr->isLooked;
                }
            }
            if (headptr == nullptr)
            {
                myStack.pop();
            }
            else
            {
                if (headptr->data == *endC)
                {

                    Stack<Cage> tempStack(totalNumOfCages);
                    string pathstr = "";
                    possiblityTotal *= startC->possiblity;
                    pathstr += startC->name;
                    pathstr += " -> ";
                    possiblityTotal *= endC->possiblity;
                    while (myStack.peek() != *startC)
                    {
                        Cage tempCage = myStack.pop();
                        possiblityTotal *= tempCage.possiblity;
                        tempStack.push(tempCage);
                    }
                    while (!tempStack.isEmpty())
                    {
                        Cage tempCage = tempStack.pop();
                        pathstr += tempCage.name;
                        pathstr += " -> ";
                        myStack.push(tempCage);
                    }
                    pathstr += endC->name;
                    Path tempPath;
                    tempPath.pathstr = pathstr;
                    tempPath.possiblity = possiblityTotal;
                    myStack.pop();
                    possiblities.insert(tempPath);
                    possiblityTotal = 1;
                }
                else
                {

                    Cage *tempPtr = cages.get(headptr->data);

                    tempPtr->isLooked = true;
                    myStack.push(*tempPtr);
                }
            }
        }
    }
    if (possiblities.getHead() != nullptr)
    {
        cout << "Safest path from " << startC->name << " to " << endC->name << " is:" << endl;
        Node<Path> *headdbl = possiblities.getHead();
        Node<Path> *headdblprev;
        while (headdbl != nullptr)
        {
            headdblprev = headdbl;
            headdbl = headdbl->getNext();
        }
        cout << headdblprev->data.pathstr << endl;
        cout << "Probability: " << headdblprev->data.possiblity << endl;
        // cout << possiblityTotal << endl;
    }
    else
    {
        cout << "No path exists from " << startC->name << " to " << endC->name << "." << endl;
    }
    resetPaths();
}
void ZooMap::findMostDangerousPath(const string startCage, const string endCage)
{

    // initial logic
    std::cout << std::fixed << std::setprecision(6);
    Cage start;
    start.name = startCage;
    Cage end;
    end.name = endCage;
    double possiblityTotal = 1;
    LinkedList<Path> possiblities;
    Stack<Cage> myStack(20);
    int index1 = cages.contains(start);
    int index2 = cages.contains(end);
    // locating cages
    Cage *startC = &cages.get(index1)->data;
    Cage *endC = &cages.get(index2)->data;
    startC->isLooked = true;
    start.isLooked = true;

    // start
    myStack.push(*startC);
    while (!myStack.isEmpty())
    {

        Node<Cage> *headptr = cages.get(myStack.peek())->nexts.getHead();
        if (headptr == nullptr)
        {
            myStack.pop();
        }
        else
        {
            Cage *trialPtr = cages.get(headptr->data);
            bool hasBeenLookedAt = trialPtr->isLooked;

            while (headptr != nullptr && hasBeenLookedAt)
            {

                headptr = headptr->next;
                if (headptr != nullptr)
                {
                    trialPtr = cages.get(headptr->data);
                    hasBeenLookedAt = trialPtr->isLooked;
                }
            }
            if (headptr == nullptr)
            {
                myStack.pop();
            }
            else
            {
                if (headptr->data == *endC)
                {

                    Stack<Cage> tempStack(totalNumOfCages);
                    string pathstr = "";
                    possiblityTotal *= startC->possiblity;
                    pathstr += startC->name;
                    pathstr += " -> ";
                    possiblityTotal *= endC->possiblity;
                    while (myStack.peek() != *startC)
                    {
                        Cage tempCage = myStack.pop();
                        possiblityTotal *= tempCage.possiblity;
                        tempStack.push(tempCage);
                    }
                    while (!tempStack.isEmpty())
                    {
                        Cage tempCage = tempStack.pop();
                        pathstr += tempCage.name;
                        pathstr += " -> ";
                        myStack.push(tempCage);
                    }
                    pathstr += endC->name;
                    Path tempPath;
                    tempPath.pathstr = pathstr;
                    tempPath.possiblity = possiblityTotal;
                    myStack.pop();
                    possiblities.insert(tempPath);
                    possiblityTotal = 1;
                }
                else
                {

                    Cage *tempPtr = cages.get(headptr->data);

                    tempPtr->isLooked = true;
                    myStack.push(*tempPtr);
                }
            }
        }
    }
    if (possiblities.getHead() != nullptr)
    {
        cout << "Most dangerous path from " << startC->name << " to " << endC->name << " is:" << endl;
        Node<Path> *headdbl = possiblities.getHead();

        cout << headdbl->data.pathstr << endl;
        cout << "Probability: " << headdbl->data.possiblity << endl;

    }
    else
    {
        cout << "No path exists from " << startC->name << " to " << endC->name << "." << endl;
    }
    resetPaths();
}

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include "config.h"
#include "config.cpp"

using namespace std;


class Ticket
{
public:
    int id;
    string name;
    int priority;
    string description;
    time_t creationTime;
    string status;
    Ticket *next;
    Ticket()
    {
    }

    Ticket(int i, const string &n, int p, const string &d)
        : id(i), name(n), priority(p), description(d),
          creationTime(time(nullptr)), status("open"), next(nullptr) {}
    void displayTicket() const
    {
        cout << "Ticket ID: " << id << "\n";
        cout << "Name: " << name << "\n";
        cout << "Priority: " << priority << "\n";
        cout << "Description: " << description << "\n";

        cout << "Creation Time: " << ctime(&creationTime);

        cout << "Status: " << status << "\n";
    }
};
class Stack
{
private:
    Ticket *arr;
    int capacity;
    int top;

public:
    Stack() : top(-1), capacity(0), arr(nullptr) {}

    void setSize(int n)
    {
        capacity = n;
        arr = new Ticket[capacity];
    }

    ~Stack()
    {
        delete[] arr;
    }

    bool isEmpty() const
    {
        return top == -1;
    }

    bool isFull() const
    {
        return top == capacity - 1;
    }

    void push(const Ticket &value)
    { // Accept by reference
        if (isFull())
        {
            cout << "Stack is full\n";
            return;
        }
        arr[++top] = value;
    }

    Ticket pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty\n";
            return Ticket(); // Return default Ticket on empty stack
        }
        return arr[top--];
    }

    Ticket peek() const
    {
        if (isEmpty())
        {
            cout << "Stack is empty\n";
            return Ticket();
        }
        return arr[top];
    }

    void print() const
    {
        if (isEmpty())
        {
            cout << "Stack is empty\n";
            return;
        }
        for (int i = 0; i <= top; ++i)
        {
            cout << arr[i].id << " ";
        }
        cout << endl;
    }
};
class Queue {
private:
    int front, rear;
    int size;
    Ticket** queue;  // Array of Ticket pointers

public:
    Queue() : front(-1), rear(-1), size(0), queue(nullptr) {}

    void setSize(int n) {
        size = n;
        queue = new Ticket*[size];
    }

    ~Queue() {
        delete[] queue;
    }

    void enqueue(Ticket* value) {
        if (rear == size - 1) {
            cout << "Queue is full. Cannot enqueue.\n";
        } else {
            if (front == -1) {
                front = 0;
            }
            rear++;
            queue[rear] = value;
            cout << "Ticket ID " << value->id << " enqueued to the queue.\n";
        }
    }

    void dequeue() {
        if (front == -1 || front > rear) {
            cout << "Queue is empty. Cannot dequeue.\n";
        } else {
            cout << "Ticket ID " << queue[front]->id << " dequeued from the queue.\n";
            front++;
        }
    }

    Ticket* peekFront() {
        if (front == -1 || front > rear) {
            cout << "Queue is empty.\n";
            return nullptr;
        }
        return queue[front];
    }

    bool isEmpty() {
        return (front == -1 || front > rear);
    }
};


class Agent
{
public:
    int id;
    string name;
    vector<Ticket> assignedTickets;
    int numOfTicket;
    bool available;
    Agent() : id(0), name("Asad Jafri"), available(true), numOfTicket(0)
    {
    }
    bool isfull()
    {
        if (numOfTicket >= 5)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool assignTicket(Ticket *t)
    {
        if (!isfull())
        {
            assignedTickets.push_back(*t);
            numOfTicket++;
        }
        else
        {
            cout << "Agent not available!" << "\n";
            return false;
        }
        return true ;
    }
    void removeTicket(Ticket *t)
    {
        for (int i = 0; i < numOfTicket; i++)
        { 
            if (assignedTickets[i].id == t->id)
            {
                assignedTickets.erase(assignedTickets.begin() + i);
                numOfTicket--;
                return;
            }
        }
    }
    void displayAllTicket()
    {
        for (int i = 0; i < numOfTicket; i++)
        {
            assignedTickets[i].displayTicket();
        }
    }
    bool status()
    {
        return available;
    }
};

class TicketManager
{
private:
    Ticket *head;

public:
    TicketManager() : head(nullptr)
    {
    }

    void addTicket(int id, const string &cust_name, int p, const string &d)
    {
        Ticket *newTicket = new Ticket(id, cust_name, p, d);
        if (!head)
        {
            head = newTicket;
        }
        else
        {
            Ticket *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newTicket;
        }
        cout << "Ticket added: ID " << id << endl;
    }

    void removeTicket(int id)
    {
        Ticket *curr = head;
        Ticket *prev = nullptr;
        while (curr && curr->id != id)
        {
            prev = curr;
            curr = curr->next;
        }
        if (!curr)
        {
            cout << "Ticket not found: ID " << id << endl;
            return;
        }
        if (prev)
        {
            prev->next = curr->next;
        }
        else
        {
            head = curr->next;
        }
        delete curr;
        cout << "Ticket removed: ID " << id << endl;
    }

    void searchTicket(const string &query)
    {
        int ticketID = -1;
        if (isdigit(query[0]))
        {
            ticketID = stoi(query);
        }

        Ticket *curr = head;
        while (curr)
        {
            if (curr->id == ticketID || curr->name == query)
            {
                cout << "Ticket found: ID " << curr->id << ", Customer: " << curr->name << ", Status: " << curr->status << endl;
                return;
            }
            curr = curr->next;
        }
        cout << "Ticket not found for query: " << query << endl;
    }

    void printTickets()
    {
        Ticket *curr = head;
        while (curr)
        {
            cout << "Ticket ID: " << curr->id << ", Customer: " << curr->name
                 << ", Priority: " << curr->priority << ", Status: " << curr->status << endl;
            curr = curr->next;
        }
    }

    void sortTickets()
    {
        if (defaultsort == "bubblesort")
        {
            bubbleSort();
        }
        else if (advancesort == "quicksort")
        {
            quickSort(head);
        }
        cout << "Tickets sorted." << endl;
    }

    void bubbleSort()
    {
        bool swapped;
        do
        {
            swapped = false;
            Ticket *curr = head;
            while (curr && curr->next)
            {
                if (curr->priority > curr->next->priority)
                {
                    swap(curr->id, curr->next->id);
                    swap(curr->name, curr->next->name);
                    swap(curr->priority, curr->next->priority);
                    swap(curr->description, curr->next->description);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);
    }

    void quickSort(Ticket *start)
    {
        if (!start)
            return;
        Ticket *pivot = partition(start);
        quickSort(start);
        quickSort(pivot->next);
    }

    Ticket *partition(Ticket *start)
    {
        int pivotValue = start->priority;
        Ticket *lessHead = nullptr;
        Ticket *lessTail = nullptr;
        Ticket *equalHead = nullptr;
        Ticket *equalTail = nullptr;
        Ticket *greaterHead = nullptr;
        Ticket *greaterTail = nullptr;

        Ticket *curr = start;
        while (curr)
        {
            if (curr->priority < pivotValue)
            {
                if (!lessHead)
                {
                    lessHead = curr;
                    lessTail = curr;
                }
                else
                {
                    lessTail->next = curr;
                    lessTail = curr;
                }
            }
            else if (curr->priority == pivotValue)
            {
                if (!equalHead)
                {
                    equalHead = curr;
                    equalTail = curr;
                }
                else
                {
                    equalTail->next = curr;
                    equalTail = curr;
                }
            }
            else
            {
                if (!greaterHead)
                {
                    greaterHead = curr;
                    greaterTail = curr;
                }
                else
                {
                    greaterTail->next = curr;
                    greaterTail = curr;
                }
            }
            curr = curr->next;
        }

        if (lessTail)
            lessTail->next = nullptr;
        if (equalTail)
            equalTail->next = nullptr;
        if (greaterTail)
            greaterTail->next = nullptr;

        if (lessHead)
        {
            head = lessHead;
            lessTail->next = equalHead;
        }
        else
        {
            head = equalHead;
        }

        if (equalHead)
            equalTail->next = greaterHead;
        return equalTail ? equalTail : greaterHead;
    }

    ~TicketManager()
    {
        while (head)
        {
            Ticket *temp = head;
            head = head->next;
            delete temp;
        }
    }
};
class TransactionLog {
public:
    Stack s;
    Queue q;

    TransactionLog() {
        s.setSize(5);
        q.setSize(10);
    }

    void assignTicket(Ticket* T, Agent* a) {
        bool flag = a->assignTicket(T);
        if (!flag) {
            q.enqueue(T); 
        }
        s.push(*T); 
    }

    void removeTicket(Ticket* T, Agent* a) {
        a->removeTicket(T);
        s.pop(); 
    }

    ~TransactionLog() {
        
    }
};

int main()
{
    cout << "Welcome to OneStop Management System!" << "\n"
         << "\n";
    cout << "First, you need to tell us your preferred sort and search algorithms. Your data can be processed accordingly." << "\n";
    initializeConfig();
    TransactionLog tr;
    TicketManager manager;
    Agent agent;

    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Add Ticket\n";
        cout << "2. Remove Ticket\n";
        cout << "3. Search Ticket\n";
        cout << "4. Print All Tickets\n";
        cout << "5. Sort Tickets\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int id, priority;
            string name, description;
            cout << "Enter Ticket ID: ";
            cin >> id;
            cout << "Enter Customer Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Priority (1 = High, 2 = Medium, 3 = Low): ";
            cin >> priority;
            cout << "Enter Description: ";
            cin.ignore();
            getline(cin, description);
            manager.addTicket(id, name, priority, description);
            break;
        }
        case 2:
        {
            int id;
            cout << "Enter Ticket ID to remove: ";
            cin >> id;
            manager.removeTicket(id);
            break;
        }
        case 3:
        {
            string query;
            cout << "Enter Ticket ID or Customer Name to search: ";
            cin.ignore();
            getline(cin, query);
            manager.searchTicket(query);
            break;
        }
        case 4:
            manager.printTickets();
            break;

        case 5:
            manager.sortTickets();
            manager.printTickets();
            break;
        case 6:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }   
    } while (choice != 6);

    return 0;
}

#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>
#include "config.h"
#include "config.cpp"

using namespace std;

class Ticket {
public:
    int id;
    string name;
    int priority;
    string description;
    time_t creationTime;
    string status;
    Ticket* next;

    Ticket(int i, const string& n, int p, const string& d)
        : id(i), name(n), priority(p), description(d),
          creationTime(time(nullptr)), status("open"), next(nullptr) {}
};

class Agent {
public:
    int id;
    string name;
    Ticket* assignedTickets;
    bool available;

    Agent() : id(0), name(""), assignedTickets(nullptr), available(true) {}
    Agent(int i, const string& n) : id(i), name(n), assignedTickets(nullptr), available(true) {}
};

class TicketManager {
private:
    Ticket* head;
    Agent agents[10];
    int agentCount;

public: 
    TicketManager() : head(nullptr), agentCount(0) {}

    void addTicket(int id, const string& cust_name, int p, const string& d) {
        Ticket* newTicket = new Ticket(id, cust_name, p, d);
        if (!head) {
            head = newTicket;
        } else {
            Ticket* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newTicket;
        }
        cout << "Ticket added: ID " << id << endl;
        assignTicketToAgent(newTicket);
    }

    void removeTicket(int id) {
        Ticket* curr = head;
        Ticket* prev = nullptr;
        while (curr && curr->id != id) {
            prev = curr;
            curr = curr->next;
        }
        if (!curr) {
            cout << "Ticket not found: ID " << id << endl;
            return;
        }
        if (prev) {
            prev->next = curr->next;
        } else {
            head = curr->next;
        }
        delete curr;
        cout << "Ticket removed: ID " << id << endl;
    }

    void assignTicketToAgent(Ticket* ticket) {
        for (int i = 0; i < agentCount; i++) {
            if (agents[i].available) {
                Ticket* agentTicket = agents[i].assignedTickets;
                if (!agentTicket) {
                    agents[i].assignedTickets = ticket;
                } else {
                    while (agentTicket->next) {
                        agentTicket = agentTicket->next;
                    }
                    agentTicket->next = ticket;
                }
                cout << "Assigned Ticket ID " << ticket->id << " to Agent " << agents[i].name << endl;
                return;
            }
        }
        cout << "No available agents to assign Ticket ID " << ticket->id << endl;
    }

    void searchTicket(const string& query) {
        int ticketID = -1;
        if (isdigit(query[0])) {
            ticketID = stoi(query);
        }

        Ticket* curr = head;
        while (curr) {
            if (curr->id == ticketID || curr->name == query) {
                cout << "Ticket found: ID " << curr->id << ", Customer: " << curr->name << ", Status: " << curr->status << endl;
                return;
            }
            curr = curr->next;
        }
        cout << "Ticket not found for query: " << query << endl;
    }

    void printTickets() {
        Ticket* curr = head;
        while (curr) {
            cout << "Ticket ID: " << curr->id << ", Customer: " << curr->name
                 << ", Priority: " << curr->priority << ", Status: " << curr->status << endl;
            curr = curr->next;
        }
    }

    void addAgent(int id, const string& name) {
        if (agentCount < 10) {
            agents[agentCount++] = Agent(id, name);
            cout << "Agent added: ID " << id << ", Name " << name << endl;
        } else {
            cout << "Max agents reached!" << endl;
        }
    }

    void sortTickets() {
        if (defaultsort == "bubblesort") {
            bubbleSort();
        } else if (advancesort == "quicksort") {
            quickSort(head);
        }
        cout << "Tickets sorted." << endl;
    }

    void bubbleSort() {
        bool swapped;
        do {
            swapped = false;
            Ticket* curr = head;
            while (curr && curr->next) {
                if (curr->priority > curr->next->priority) {
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

    void quickSort(Ticket* start) {
        if (!start) return;
        Ticket* pivot = partition(start);
        quickSort(start);
        quickSort(pivot->next);
    }

    Ticket* partition(Ticket* start) {
        int pivotValue = start->priority;
        Ticket* lessHead = nullptr;
        Ticket* lessTail = nullptr;
        Ticket* equalHead = nullptr;
        Ticket* equalTail = nullptr;
        Ticket* greaterHead = nullptr;
        Ticket* greaterTail = nullptr;

        Ticket* curr = start;
        while (curr) {
            if (curr->priority < pivotValue) {
                if (!lessHead) {
                    lessHead = curr;
                    lessTail = curr;
                } else {
                    lessTail->next = curr;
                    lessTail = curr;
                }
            } else if (curr->priority == pivotValue) {
                if (!equalHead) {
                    equalHead = curr;
                    equalTail = curr;
                } else {
                    equalTail->next = curr;
                    equalTail = curr;
                }
            } else {
                if (!greaterHead) {
                    greaterHead = curr;
                    greaterTail = curr;
                } else {
                    greaterTail->next = curr;
                    greaterTail = curr;
                }
            }
            curr = curr->next;
        }

        if (lessTail) lessTail->next = nullptr;
        if (equalTail) equalTail->next = nullptr;
        if (greaterTail) greaterTail->next = nullptr;

        if (lessHead) {
            head = lessHead;
            lessTail->next = equalHead;
        } else {
            head = equalHead;
        }

        if (equalHead) equalTail->next = greaterHead;
        return equalTail ? equalTail : greaterHead;
    }

    ~TicketManager() {
        while (head) {
            Ticket* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    cout << "Welcome to OneStop Management System!" << "\n" << "\n";
    cout << "First, you need to tell us your preferred sort and search algorithms. Your data can be processed accordingly." << "\n";
    initializeConfig();

    TicketManager manager;

    manager.addAgent(1, "IT Support");
    manager.addAgent(2, "Admin Support");
    manager.addAgent(3, "Accounts Support");
    manager.addAgent(4, "Academic Support 1");
    manager.addAgent(5, "Academic Support 2");
    manager.addAgent(6, "Academic Support 3");

    manager.addTicket(1, "Alice", 1, "IT issue");
    manager.addTicket(2, "Bob", 2, "Account question");
    manager.addTicket(3, "Charlie", 3, "General inquiry");
    manager.addTicket(4, "Dave", 1, "Network problem");
    manager.addTicket(5, "Eve", 1, "Login issue");

    manager.printTickets();

    manager.removeTicket(2);

    manager.searchTicket("1");
    manager.searchTicket("Alice");

    cout << "Sorting tickets:" << endl;
    manager.sortTickets();
    manager.printTickets();

    return 0;
}

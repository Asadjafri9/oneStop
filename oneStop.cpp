#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include "config.h"
#include "config.cpp"
#include <chrono>
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
            return Ticket();
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
class Queue
{

public:
    int front, rear;
    int size;
    Ticket **queue;

    Queue() : front(-1), rear(-1), size(0), queue(nullptr) {}

    void setSize(int n)
    {
        size = n;
        queue = new Ticket *[size];
    }

    ~Queue()
    {
        delete[] queue;
    }

    Ticket *peekFront() const
    {
        if (front == -1 || front > rear)
        {
            cout << "Queue is empty.\n";
            return nullptr;
        }
        return queue[front];
    }
    void enqueue(Ticket *value)
    {
        if (rear == size - 1)
        {
            cout << "Queue is full. Cannot enqueue.\n";
        }
        else
        {
            if (front == -1)
            {
                front = 0;
            }
            rear++;
            queue[rear] = value;
            cout << "Ticket ID " << value->id << " enqueued to the queue.\n";
        }
    }

    void dequeue()
    {
        if (front == -1 || front > rear)
        {
            cout << "Queue is empty. Cannot dequeue.\n";
        }
        else
        {
            cout << "Ticket ID " << queue[front]->id << " dequeued from the queue.\n";
            front++;
        }
    }

    bool isEmpty() const
    {
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

    Agent() : id(0), name("Asad Jafri"), available(true), numOfTicket(0) {}

    bool isFull() const
    {
        return numOfTicket >= 5;
    }

    bool assignTicket(Ticket *t)
    {
        if (!isFull())
        {
            assignedTickets.push_back(*t);
            numOfTicket++;
            return true;
        }
        else
        {
            cout << "Agent not available (ticket limit reached)." << "\n";
            return false;
        }
    }
    void displayAgentTicketLoad()
    {
        cout << "Agent " << name << " has " << numOfTicket << " assigned tickets:\n";
        displayAllTicket();
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

    bool status() const
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

    Ticket *getTicketById(int id)
    {
        Ticket *curr = head;
        while (curr)
        {
            if (curr->id == id)
            {
                return curr;
            }
            curr = curr->next;
        }
        cout << "Ticket not found: ID " << id << endl;
        return nullptr;
    }

    void listOpenTickets()
    {
        vector<Ticket *> openTickets;
        Ticket *current = head;
        while (current != nullptr)
        {
            if (current->status == "open")
                openTickets.push_back(current);
            current = current->next;
        }
        sort(openTickets.begin(), openTickets.end(), [](Ticket *a, Ticket *b)
             { return a->priority < b->priority || (a->priority == b->priority && a->creationTime < b->creationTime); });
        cout << "List of Open Tickets:\n";
        for (const auto &ticket : openTickets)
        {
            ticket->displayTicket();
        }
    }

    void searchTicket(const string &query)
    {
        int ticketID = -1;
        if (isdigit(query[0]))
        {
            ticketID = stoi(query);
        }
        bool flag;
        if (searchtechnique == "binarysearch")
        {
            flag = binarySearchTicket(ticketID);
        }
        else
        {
            flag = interpolationSearchTicket(ticketID);
        }
        if (!flag)
            cout << "Ticket not found for query: " << query << endl;
        else
        {
            cout << "Ticket Found ." << "\n";
        }
    }

    bool binarySearchTicket(int ticketID)
    {
        vector<Ticket *> tickets;
        Ticket *curr = head;

        while (curr)
        {
            tickets.push_back(curr);
            curr = curr->next;
        }

        sort(tickets.begin(), tickets.end(), [](Ticket *a, Ticket *b)
             { return a->id < b->id; });

        int left = 0, right = tickets.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (tickets[mid]->id == ticketID)
            {
                return true;
            }
            else if (tickets[mid]->id < ticketID)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        cout << "Ticket not found.\n";
        return false;
    }

    bool interpolationSearchTicket(int ticketID)
    {
        vector<Ticket *> tickets;
        Ticket *curr = head;

        while (curr)
        {
            tickets.push_back(curr);
            curr = curr->next;
        }

        sort(tickets.begin(), tickets.end(), [](Ticket *a, Ticket *b)
             { return a->id < b->id; });

        int low = 0, high = tickets.size() - 1;

        while (low <= high && ticketID >= tickets[low]->id && ticketID <= tickets[high]->id)
        {
            int pos = low + ((ticketID - tickets[low]->id) * (high - low)) / (tickets[high]->id - tickets[low]->id);

            if (tickets[pos]->id == ticketID)
            {
                return true;
            }
            else if (tickets[pos]->id < ticketID)
            {
                low = pos + 1;
            }
            else
            {
                high = pos - 1;
            }
        }

        cout << "Ticket not found.\n";
        return false;
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
        int count = getCount();
        if (count <= 5)
        {
            if (defaultsort == "bubblesort")
            {
                bubbleSort();
            }
            else if (defaultsort == "selectionsort")
            {
                selectionSort();
            }
            else if (defaultsort == "insertionsort")
            {
                insertionSort();
            }
        }
        else
        {
            if (advancesort == "quicksort")
            {
                Ticket *end = head;
                while (end->next != nullptr)
                {
                    end = end->next;
                }
                quickSort(head, end);
            }
            else
            {
                mergeSort(&head);
            }
        }
        cout << "Tickets sorted." << endl;
    }

    void insertionSort()
    {
        if (!head || !head->next)
            return;
        Ticket *sorted = nullptr;
        Ticket *current = head;

        while (current)
        {
            Ticket *next = current->next;
            if (!sorted || sorted->priority >= current->priority)
            {
                current->next = sorted;
                sorted = current;
            }
            else
            {
                Ticket *temp = sorted;
                while (temp->next && temp->next->priority < current->priority)
                {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }
        head = sorted;
    }

    int getCount()
    {
        Ticket *t = head;
        int cnt = 0;
        while (t != nullptr)
        {
            t = t->next;
            cnt++;
        }
        return cnt;
    }

    void selectionSort()
    {
        for (Ticket *start = head; start && start->next; start = start->next)
        {
            Ticket *minTicket = start;
            for (Ticket *current = start->next; current; current = current->next)
            {
                if (current->priority < minTicket->priority)
                {
                    minTicket = current;
                }
            }
            if (minTicket != start)
            {
                swap(start->id, minTicket->id);
                swap(start->name, minTicket->name);
                swap(start->priority, minTicket->priority);
                swap(start->description, minTicket->description);
            }
        }
    }

    void splitList(Ticket *source, Ticket **frontRef, Ticket **backRef)
    {
        Ticket *fast = source->next;
        Ticket *slow = source;

        while (fast)
        {
            fast = fast->next;
            if (fast)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *frontRef = source;
        *backRef = slow->next;
        slow->next = nullptr;
    }

    Ticket *sortedMerge(Ticket *a, Ticket *b)
    {
        if (!a)
            return b;
        if (!b)
            return a;

        Ticket *result = nullptr;
        if (a->priority <= b->priority)
        {
            result = a;
            result->next = sortedMerge(a->next, b);
        }
        else
        {
            result = b;
            result->next = sortedMerge(a, b->next);
        }
        return result;
    }

    void mergeSort(Ticket **headRef)
    {
        if (!(*headRef) || !(*headRef)->next)
            return;

        Ticket *head = *headRef;
        Ticket *a;
        Ticket *b;

        splitList(head, &a, &b);
        mergeSort(&a);
        mergeSort(&b);
        *headRef = sortedMerge(a, b);
    }

    void bubbleSort()
    {
        if (head == nullptr || head->next == nullptr)
        {
            return;
        }

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

    void quickSort(Ticket *start, Ticket *end)
    {
        if (start == end || !start || !end)
        {
            return;
        }

        Ticket *pivot = partition(start, end);
        quickSort(start, pivot);
        quickSort(pivot->next, end);
    }

    Ticket *partition(Ticket *start, Ticket *end)
    {
        int pivotValue = start->priority;
        Ticket *lessHead = nullptr, *lessTail = nullptr;
        Ticket *greaterHead = nullptr, *greaterTail = nullptr;

        Ticket *curr = start;
        while (curr != end->next)
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
            else if (curr->priority > pivotValue)
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
        if (greaterTail)
            greaterTail->next = nullptr;

        if (lessHead)
        {
            lessTail->next = start;
            start->next = greaterHead;
            return lessHead;
        }
        start->next = greaterHead;
        return start;
    }
};

class ResolutionLog
{
public:
    Stack resolutionStack;
    Queue pendingQueue;

    ResolutionLog()
    {
        resolutionStack.setSize(10);
        pendingQueue.setSize(20);
    }

    void assignTicket(Ticket *ticket, Agent *agent)
    {
        auto start = chrono::high_resolution_clock::now();

        if (!agent->isFull())
        {
            agent->assignTicket(ticket);
            cout << "Ticket ID " << ticket->id << " assigned to Agent " << agent->name << endl;
        }
        else
        {
            pendingQueue.enqueue(ticket);
            cout << "Ticket ID " << ticket->id << " added to pending queue (agent at capacity)." << endl;
        }

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "Time taken to assign ticket: " << elapsed.count() << " seconds\n";
    }
    void displayTicketResolutionHistory()
    {
        cout << "Ticket Resolution History:\n";
        Stack tempStack = resolutionStack;
        int count = 0;
        while (!tempStack.isEmpty() && count < 10)
        {
            Ticket ticket = tempStack.pop();
            ticket.displayTicket();
            count++;
        }
    }

    void closeTicket(Ticket *ticket, Agent *agent)
    {
        auto start = chrono::high_resolution_clock::now();

        agent->removeTicket(ticket);
        ticket->status = "closed";
        resolutionStack.push(*ticket);

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "Ticket closed and logged in resolution stack in " << elapsed.count() << " seconds\n";
    }

    void displayPendingTickets()
    {
        if (pendingQueue.isEmpty())
        {
            cout << "No pending tickets.\n";
            return;
        }
        int originalFront = pendingQueue.front;
        int originalRear = pendingQueue.rear;

        while (!pendingQueue.isEmpty())
        {
            Ticket *frontTicket = pendingQueue.peekFront();
            cout << "Pending Ticket ID: " << frontTicket->id << "\n";
            pendingQueue.dequeue();
        }

        pendingQueue.front = originalFront;
        pendingQueue.rear = originalRear;
    }

    void displayResolutionLogs() const
    {
        cout << "Most Recent Ticket Resolution Logs (Last 10):\n";
        if (resolutionStack.isEmpty())
        {
            cout << "No logs available.\n";
            return;
        }
        Stack tempStack = resolutionStack;
        int count = 0;
        while (!tempStack.isEmpty() && count < 10)
        {
            Ticket ticket = tempStack.pop();
            ticket.displayTicket();
            count++;
        }
    }

    ~ResolutionLog() {}
};
int main()
{
    cout << "Welcome to OneStop Management System!" << "\n\n";
    cout << "First, you need to tell us your preferred sort and search algorithms. Your data can be processed accordingly." << "\n";
    initializeConfig();

    ResolutionLog t;
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
        cout << "6. Assign Ticket to Agent\n";
        cout << "7. Close Ticket\n";
        cout << "8. View Pending Tickets\n";
        cout << "9. View Recent Resolution Logs\n";
        cout << "11. View List of Open Tickets\n";
        cout << "12. View Agent Ticket Load\n";
        cout << "13. View Ticket Resolution History\n";
        cout << "10. Exit\n";
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
        {
            int id;
            cout << "Enter Ticket ID to assign to agent: ";
            cin >> id;
            Ticket *ticket = manager.getTicketById(id);
            if (ticket)
            {
                t.assignTicket(ticket, &agent);
            }
            break;
        }
        case 7:
        {
            int id;
            cout << "Enter Ticket ID to close: ";
            cin >> id;
            Ticket *ticket = manager.getTicketById(id);
            if (ticket)
            {
                t.closeTicket(ticket, &agent);
            }
            break;
        }

        case 8:
            t.displayPendingTickets();
            break;
        case 9:
            t.displayResolutionLogs();
            break;
        case 10:
            cout << "Exiting program." << endl;
            break;
        case 11:
            manager.listOpenTickets();
            break;
        case 12:
            agent.displayAgentTicketLoad();
            break;
        case 13:
            t.displayTicketResolutionHistory();
            break;

        default:
            cout << "Invalid choice. Please enter a number between 1 and 10.\n";
        }
    } while (choice != 10);

    return 0;
}

#include <bits/stdc++.h>

using namespace std;
class Ticket
{
private:
    int id;
    string name;
    int priority;
    string service;
    int  start_time_min;
    bool status;
    int  end_time_min;
    public:
    Ticket(int id , string name, int priority ,string service , int start , bool status , int end ){
        this -> id = id ;
        this -> name = name; 
        this -> priority = priority;
        this -> service = service ;
        this -> start_time_min = start ;
        this -> end_time_min = end;
        this -> status = status;
    }
    
};

int main()
{
    return 0;
}
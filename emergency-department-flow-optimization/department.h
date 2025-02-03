#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "main.h";

typedef std::string string;
typedef std::vector vector;


class department
{
    public:
        department(int totalPatients, string name, vecto<int> queue);
        department();

        //Functions
        void pushToQueue(int patientID);

    private:
        int _totalPatients; //# of patients in queue

        string _name; //department name
        vector<int> _queue; //Patient queue

};

#endif // DEPARTMENT_H

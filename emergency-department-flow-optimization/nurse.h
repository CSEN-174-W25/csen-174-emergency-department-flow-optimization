#ifndef NURSE_H
#define NURSE_H

#include "main.h";

typedef std::string string;

class nurse
{

    public:
        nurse(int nurseID, string name);
        nurse();

        //Accessors
        int nurseID(){return _nurseID;}
        string name(){return _name;}

        //Mutators


    private:
        int _nurseID();
        string _name;
};

#endif // NURSE_H

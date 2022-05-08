#pragma once
#include "ofMain.h"
class PowerUp{
    private:
    int rank;
    string name;
    public:
    PowerUp(){}
    int getRank(){return this->rank;}
    string getName(){return this->name;}
    void setName(string s){this->name = s;}
    void setRank(int r){this->rank = r;}
    bool compare(PowerUp* t){
        if (this->getRank() > t->getRank()){
            return true;  // return true if target is bigger than t 
        }else{
            return false;
        }
    }
    //
    virtual void activate() = 0; //virtual Method

};
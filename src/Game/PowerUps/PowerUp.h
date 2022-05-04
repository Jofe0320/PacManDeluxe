#pragma once
class PowerUp{
    private:
    int rank;
    public:
    PowerUp(){}
    int getRank(){return this->rank;}
    void setRank(int r){this->rank = r;}
    virtual void activate() = 0; //virtual Method

};
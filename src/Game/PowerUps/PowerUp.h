#pragma once
class PowerUp{
    private:
    int rank;
    public:
    PowerUp(){}
    int getRank(){return this->rank;}
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
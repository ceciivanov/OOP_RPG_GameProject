
#ifndef GAMEPROJECT_RANGE_H
#define GAMEPROJECT_RANGE_H

#include <iostream>
#include <cstdlib>


class Range {

private:
    int min;
    int max;

public:

    Range(int low, int high)
    : min(low), max(high){};

    ~Range() = default;

    void print() const{
        std::cout << min << "-" << max << std::endl;
    }

    int getValue() const{
        return min + ((int)random() % ((max+1) - min));     //return random value within the range
    }

    int getMax() const{
        return max;
    }

    void reduceRange(int reduce){
        min -= reduce;
        max -= reduce;

        if ( min < 0 )
            min = 0;

        if ( max < 0 )
            max = 0;
    }

};


#endif //GAMEPROJECT_RANGE_H
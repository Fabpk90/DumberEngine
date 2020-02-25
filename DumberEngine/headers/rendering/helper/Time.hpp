//
// Created by fab on 24/02/2020.
//

#ifndef DUMBERENGINE_TIME_HPP
#define DUMBERENGINE_TIME_HPP

class Time
{
private:
    static Time instance;

    Time(){}

public:

    Time(const Time &) = delete;

    static Time &getInstance()
    {
        return instance;
    }

    float deltaTime = 0.0f;
};

#endif //DUMBERENGINE_TIME_HPP

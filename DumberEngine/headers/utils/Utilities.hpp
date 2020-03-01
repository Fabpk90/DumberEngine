//
// Created by fab on 27/02/2020.
//

#ifndef DUMBERENGINE_UTILITIES_HPP
#define DUMBERENGINE_UTILITIES_HPP

#include <cstdlib>

#ifndef NAN
#define NAN(x) (x!=x)
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef sign
#define sign(a)            (((a) >= (0)) ? (1) : (-1))
#endif

#define BUFFER_OFFSET(i) (reinterpret_cast<void*>(i))

inline double randf()
{
    double rnd = rand();
    rnd /= RAND_MAX;
    return rnd;
}

template<class T>
inline T round(T val)
{
    T rest;
    modf(val,&rest);
    if (rest > 0.5)
        return ceil(val);
    return floor(val);
}
#endif //DUMBERENGINE_UTILITIES_HPP

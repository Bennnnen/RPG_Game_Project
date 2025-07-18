#ifndef RESOURCES_H
#define RESOURCES_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Resources
{
private:
    double stone_;
    double robber_;
    double iron_;
    double wood_;
    double money_;
public:
    Resources(double stone, double robber, double iron, double wood, double money)
    : stone_(stone), robber_(robber), iron_(iron), wood_(wood), money_(money){}
    virtual ~Resources() = default;
};

#endif


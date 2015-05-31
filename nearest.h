#ifndef NEAREST_H
#define NEAREST_H

#include <cmath>

#include "optionsview.h"

class OptionsView;

class Nearest
{
public:
    Nearest();
    ~Nearest();

    OptionsView* opv;
    void setOpv(OptionsView* ov);
    void coordsNearest(int x, int y, int aa);
};

#endif // NEAREST_H

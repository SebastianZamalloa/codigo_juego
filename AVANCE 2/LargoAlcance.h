#include "personaje.h"
#include "image.h"
#include <iostream>

using namespace std;

class LargoAlcance : public Personajes{
    protected:
        int targetRange;
        
    public:
        void atacar();
};
#include "personaje.h"
#include <iostream>

using namespace std;

class Universal : public Personajes{
    protected: 
        bool toEnemies;
        int coolDown;
    public:
        void atacar();
};
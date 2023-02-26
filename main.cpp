#include <iostream>
#include <vector>
#include "state.h"
#include "prototype.h"

int main()
{
    std::cout << " State pattern:\n";
    StateContext* pState = new StateContext(new NoMoney());
    pState->CoinIn();
    pState->CoinOut();
    for (size_t i = 0; i < 5; i++)
    {
        pState->CoinIn();
        pState->Buy();
        pState->TakeCoffee();
    }

    std::cout << "\n Prototype:\n";
    std::vector<Enemy*> myMonsters;
    myMonsters.push_back(new Monster(12, 20, 50, "MyMonster"));
    for (size_t i = 0; i < 4; i++)
    {
        myMonsters.push_back(myMonsters[0]->clone());
    }
    myMonsters[2]->changeHp(88);
    for (auto it : myMonsters) {
        std::cout << "HP: " << it->getHp() << std::endl;
    }
    return 0;
}

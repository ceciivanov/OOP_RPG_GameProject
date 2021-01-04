#include "Game.h"

Game::Game() {
    std::cout << "Our Game is created!" << std::endl;
}

Game::~Game() {
    delete map;
    delete marketPlace;
    delete squad;
    delete[] monsters;
}

void Game::play() {
    std::cout << "Welcome to our game" << std::endl;
    std::cout << "Please create your Hero Squad  of (1-3) members" << std::endl;

    int n;
    while (true)
    {
        std::cin >> n;

        if ( n > MAX_TEAMMATES )
        {
            std::cout << "Please choose valid number of heroes" << std::endl;
            continue;
        }
        createTeam(n);
        break;
    }

    std::cout << "Your Hero Squad is ready: " << std::endl;
    //print HeroSquad for the player
    squad->print();

    std::cout << "Are you ready to begin..." << std::endl;
    std::cout << "Move your squad by using keys (w, a, s, d) for up, left, down and right" << std::endl;
    std::cout << "You can see map by pressing (m) whenever you want" << std::endl;
    std::cout << "You can quit game by pressing (q) whenever you want" << std::endl;
    std::cout << "If your squad gets in common square and don't get in fight, you can check inventory of your heroes by pressing (i)" << std::endl;
    std::cout << "Whenever you get involved in fight and it's your turn you can display stats of your squad and enemies by pressing (t)" << std::endl;
    std::cout << "You can make normal attack by pressing (o), cast spell by pressing (l) or use potion by pressing (p)" << std::endl;


    Square* start = map->getSquare(0,0);
    squad->move(start);

    bool validButton = true;

    std::cout << "Start moving your squad..." << std::endl;

    while(true)
    {
        char button;
        std::cin >> button;

        unsigned int x, y;
        x = start->getX();
        y = start->getY();

        unsigned int x1, y1;

        switch (button)
        {
            case 'w':
                x1 = x + 1;
                y1 = y;
                break;
            case 's':
                x1 = x - 1;
                y1 = y;
                break;
            case 'a':
                x1 = x;
                y1 = y - 1;
                break;
            case 'd':
                x1 = x;
                y1 = y + 1;
                break;
            case 'q':
                quit();
                break;
            case 'm':
                map->displayMap();
                continue;
            default:
                validButton = false;
                break;
        }

        if ( !validButton )
        {
            std::cout << "Please enter a valid button" << std::endl;
            continue;
        }

        if (map->outOfBounds(x1, y1))
        {
            std::cout << "You are going out of bounds please try again" << std::endl;
            continue;
        }
        else
        {
            start->setSquad(nullptr);
            Square* next = map->getSquare(x1, y1);
            squad->move(next);

            if(next->getType() == nonAccessible)
            {
                std::cout << "The Square you want to enter is no accessible" << std::endl;
                std::cout << "Please, go to another direction" << std::endl;
                continue;
            }
            else if (next->getType() == market)
            {
                std::cout << "You entered a marketPlace do you want to open market? Y/N" << std::endl;
                char answer;
                std::cin >> answer;

                if ( answer == 'y' || answer == 'Y')
                {
                    for(int i=0; i<squad->getSize(); i++)
                    {
                        std::cout << "Do you want to open market for " << squad->getHero(i)->getName() << "? Y/N" << std::endl;

                        std::cin >> answer;

                        if(answer == 'Y' || answer == 'y'){
                            marketPlace->open(squad->getHero(i));
                        }
                        else{
                            continue;
                        }
                    }
                    continue;
                }
                else
                {
                    std::cout << "Bye..." << std::endl;
                    continue;
                }
            }
            else
            {
                std::cout << "You have entered a common square" << std::endl;

                //if(...)
                //attack()

            }
            break;
        }

    }

}

void Game::createTeam(int n) {
    std::cout << "Creating a squad of " << n << " members" << std::endl;
    squad = new HeroSquad(n);

    std::cout << "Please choose name and type of each hero 1:warrior, 2:paladin, 3:sorcerer" << std::endl;

    int i=0;
    while (i < n)
    {
        std::cout << "Create your " << i+1 << " hero" << std::endl;

        std::string name;
        std::cout << "Choose name" << std::endl;
        std::cin >> name;

        int type;
        std::cout << "Choose type" << std::endl;
        std::cin >> type;

        Hero* hero;
        switch(type)
        {
            case warrior:
                hero = new Warrior(name);
                squad->setHero(hero);
                break;
            case paladin:
                hero = new Paladin(name);
                squad->setHero(hero);
                break;
            case sorcerer:
                hero = new Sorcerer(name);
                squad->setHero(hero);
                break;
            default:
                break;
        }
        i++;
    }

}

void Game::fillMarket(const std::vector<Item *> &items, const std::vector<Spell *> &spells) {
    marketPlace = new Market();

    for(Item* i: items){
        marketPlace->addItem(i);
    }
    for(Spell* s: spells){
        marketPlace->addSpell(s);
    }
}

void Game::createMap(int size) {
    map = new Grid(size);
}

void Game::quit() {
    std::cout << "Quit Game... Bye!" << std::endl;
    exit(0);
}

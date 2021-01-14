#include "Game.h"


Game::Game() {

    std::cout << "Welcome to our game!" << std::endl;

    map = new Grid(MAP_SIZE);
    marketPlace = createMarket();
}


Game::~Game() {

    std::cout << "Quit Game... Bye" << std::endl;

    delete map;
    delete marketPlace;
    delete squad;
}


void Game::quit() {

    delete this;
    exit(EXIT_SUCCESS);
}


bool Game::playerMove(Square *currentPos, unsigned int &x1, unsigned int &y1) {

    unsigned int x = currentPos->getX();
    unsigned int y = currentPos->getY();

    std::cout << "Move your heroes" << std::endl;

    char button;
    std::cin >> button;

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
        case 'm':
            map->displayMap();
            break;
        case 'c':
            std::cout << "Your Heroes: " << std::endl;
            squad->print();
            break;
        case 'i':
            squad->checkInventory();
            break;
        case 'q':
            return false;
        default:
            std::cout << "Please enter a valid button" << std::endl;
            break;
    }

    return true;
}


void Game::play() {

    std::cout << "Please create your Hero Squad  of (1-3) heroes" << std::endl;
    createHeroes();

    std::cout << "Your Hero Squad is ready: " << std::endl;
    squad->print();

    std::cout << "Move your heroes by using keys (w, a, s, d) for up, left, down and right" << std::endl;
    std::cout << "You can see map by pressing (m)" << std::endl;
    std::cout << "You can quit game by pressing (q)" << std::endl;
    std::cout << "You can check inventory of your heroes by pressing (i)" << std::endl;
    std::cout << "You can check your heroes stats by pressing (c)\n" << std::endl;

    //heroes start at coordinates 0,0 of map which contains market
    Square* currentPos = map->getSquare(0, 0);
    squad->move(currentPos);

    enterMarket();

    unsigned int x = -1;
    unsigned int y = -1;

    while(true)
    {
        unsigned int tempX = x;
        unsigned int tempY = y;

        if (!playerMove(currentPos, x, y))
            break;

        //check if player is at same coordinates
        if ( (x == -1 && y == -1) || (x == tempX && y == tempY) )
            continue;

        if (map->outOfBounds(x, y))
        {
            std::cout << "You are going out of bounds please try again" << std::endl;
        }
        else
        {
            Square* next = map->getSquare(x, y);

            if (next->getType() == nonAccessible)
            {
                std::cout << "Non-Accessible square, please go to another direction" << std::endl;
                continue;
            }
            else if (next->getType() == market)
            {
                currentPos->setSquad(nullptr);
                squad->move(next);

                enterMarket();
            }
            else
            {
                currentPos->setSquad(nullptr);
                squad->move(next);

                enterCommon();
            }

            currentPos = map->getSquare(x, y);
        }
    }

    //quit game
    quit();
}


Market* Game::createMarket() {

    marketPlace = new Market();

    Item* armor = new Armor("Emblem", 100, 1, 70);
    marketPlace->addItem(armor);
    armor = new Armor("Hat", 150, 4, 130);
    marketPlace->addItem(armor);
    armor = new Armor("Rescue Shield", 200, 8, 200);
    marketPlace->addItem(armor);
    armor = new Armor("Silver Shield", 300, 12, 300);
    marketPlace->addItem(armor);
    armor = new Armor("Gold Shield", 500, 16, 400);
    marketPlace->addItem(armor);

    Item* weapon = new Weapon("axe", 100, 1, 100, true);
    marketPlace->addItem(weapon);
    weapon = new Weapon("sword", 100, 1, 80, false);
    marketPlace->addItem(weapon);
    
    Item* potion = new Potion("Antidote", 100, 1, Health, 55);
    marketPlace->addItem(potion);
    

    Spell* spell = new FireSpell("inferno", 100, 1, 100,Range(100, 300), 50);
    Spell* spell1 = new IceSpell("frost", 100, 1, 100,Range(200, 250), 80);
    Spell* spell2 = new LightingSpell("zeus", 100, 1, 100,Range(100, 200), 5);

    marketPlace->addSpell(spell);
    marketPlace->addSpell(spell1);
    marketPlace->addSpell(spell2);

    return marketPlace;
}


void Game::createHeroes() {

    int n;

    while (true)
    {
        std::cin >> n;

        if ( n > MAX_TEAMMATES )
        {
            std::cout << "Please choose valid number of heroes" << std::endl;
            continue;
        }

        break;
    }

    squad = new HeroSquad(n);

    //random names for heroes
    static std::string names[10] = {"Karontor","Io","Luthic","Merlin","Sixin",
                                    "Ilneval", "Vaprak", "Eadro", "Skerrit", "Jubilex"};

    std::vector<std::string> usedNames;

    for(int i = 0; i < n; i++)
    {
        int HeroType = (int) random() % 3 + 1; //[1, 3]

        Hero *hero = nullptr;

        //check for duplicate names
        std::string name = getUnusedName(usedNames, names);

        switch (HeroType)
        {
            case warrior:
                hero = new Warrior(name);
                break;
            case paladin:
                hero = new Paladin(name);
                break;
            case sorcerer:
                hero = new Sorcerer(name);
                break;
            default:
                break;
        }

        squad->setHero(hero);
    }
}


MonsterSquad *Game::createEnemies() {

    //some random names for the monsters creation
    static std::string names[10] = {"Abbathor","Arvoreen","Ehlonna","Heironeous","Pelor",
                             "Urdlen", "Bahamut", "Orcus", "Vaprak", "Bahgtru"};

    int size = (int)random() % 3 + 1;

    MonsterSquad* enemies = new MonsterSquad(size);

    int averageLevel = 0;

    for(int i = 0; i < squad->getSize(); i++)
    {
        averageLevel += squad->getHero(i)->getLevel();
    }

    averageLevel = averageLevel/squad->getSize();

    std::vector<std::string> usedNames;

    for(int i = 0; i < size; i++)
    {
        int MonsterType = (int) random() % 3 + 1; //[1, 3]

        Monster *monster = nullptr;

        std::string name = getUnusedName(usedNames, names);

        switch (MonsterType)
        {
            case dragon:
                monster = new Dragon(name, averageLevel);
                break;
            case exoskeleton:
                monster = new ExoSkeleton(name, averageLevel);
                break;
            case spirit:
                monster = new Spirit(name, averageLevel);
                break;
            default:
                break;
        }

        enemies->setMonster(monster);
    }

    return enemies;
}


void Game::enterMarket() {

    std::cout << "You have entered a marketPlace do you want to open market? Y/N" << std::endl;

    while (true)
    {
        char answer;
        std::cin >> answer;

        if (answer == 'Y' || answer == 'y')
        {
            int i = 0;

            while ( i < squad->getSize() )
            {
                std::cout << "Do you want to open market for " << squad->getHero(i)->getName() << "? Y/N" << std::endl;

                std::cin >> answer;

                if (answer == 'Y' || answer == 'y')
                {
                    marketPlace->open(squad->getHero(i));
                }
                else if (answer == 'N' || answer == 'n')
                {
                    i++;
                    continue;
                }
                else if (answer == 'Q' || answer == 'q')
                {
                    quit();
                }
                else
                {
                    std::cout << "Invalid input please try again" << std::endl;
                    continue;
                }
                i++;
            }
            return;
        }
        else if (answer == 'N' || answer == 'n')
        {
            break;
        }
        else if (answer == 'Q' || answer == 'q')
        {
            quit();
        }
        else
        {
            std::cout << "Invalid input please try again" << std::endl;
        }
    }
}


void Game::enterCommon() {

    std::cout << "You have entered common square" << std::endl;

    if (!Fight::begin())
    {
        std::cout << "No monsters around..." << std::endl;
        return;
    }

    std::cout << "Fight Begins..." << std::endl;

    squad->setSquadStats();

    MonsterSquad* enemies = createEnemies();

    Fight* fight = new Fight(squad, enemies);

    int round = 1;

    bool stopped = false;

    while (fight->isNotOver())
    {
        std::cout << "Round: " << round << std::endl;

        std::cout << "Your Turn" << std::endl;


        //if player want to quit game within the fight
        if (!fight->playerTurn())
        {
            stopped = true;
            break;
        }

        if (enemies->defeated())
            break;

        std::cout << "Enemies Turn" << std::endl;
        fight->enemiesTurn();

        //reduce active spells on each monster
        enemies->unchargeActiveSpells();

        //regenerate stats of both heroes and enemies
        squad->regeneration();
        enemies->regeneration();

        round++;
    }

    //boolean variable stopped is used in case that player wants to exit game during fight, then stopped is true , delete enemies and fight and call quit()
    if (!stopped)
    {
        if (squad->defeated())
        {
            std::cout << "DEFEATED!" << std::endl;
            defeat();
        }
        else
        {
            std::cout << "VICTORY!" << std::endl;
            victory(enemies->getSize());
        }
        delete enemies;
        delete fight;
    }
    else
    {
        delete enemies;
        delete fight;
        quit();
    }
}


void Game::victory(int monstersDefeated) {

    for (int i = 0; i < squad->getSize(); i++)
    {
        Hero* hero = squad->getHero(i);

        if (hero->dead())
        {
            hero->revive();
        }
    }

    for (int i = 0; i < squad->getSize(); i++)
    {
        Hero* hero = squad->getHero(i);

        int level = hero->getLevel();

        int xp = (level * 2 + 3) * monstersDefeated;
        int money = (level*50) * monstersDefeated;

        std::cout << hero->getName() << " + " << money << " money"  << " + " << xp << " xp " << "    ";

        hero->addExperience(xp);
        hero->earnMoney(money);

    }
}


void Game::defeat() {

    squad->revive();

    for (int i = 0; i < squad->getSize(); i++)
    {
        Hero* hero = squad->getHero(i);
        hero->looseMoney();
    }
}

std::string Game::getUnusedName(std::vector<std::string> &usedNames, std::string *names) {

    while (true)
    {
        std::string name;
        int r = (int)random() % 10;
        bool found = false;

        for (int i = 0; i < usedNames.size(); i++)
        {
            if (names[r] == usedNames[i])
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            usedNames.push_back(names[r]);
            name = names[r];
            return name;
        }
    }
}
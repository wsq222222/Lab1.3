#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Entity {
protected:
    string name;
    int health;
    int attack_power;
    int defense;

public:
    Entity(const string& n, int h, int a, int d)
        : name(n), health(h), attack_power(a), defense(d) {
    }

    virtual void attack(Entity& target) {
        cout << name << " (basic attack) -> " << target.name << endl;
        int damage = attack_power - target.defense;
        if (damage < 0) damage = 0;

        target.health -= damage;
        cout << "  " << target.name << " receives " << damage << " damage.";
        if (target.health <= 0) {
            target.health = 0;
            cout << " " << target.name << " is defeated!";
        }
        cout << " (Remaining HP: " << target.health << ")" << endl;
    }

    virtual void displayInfo() const {
        cout << "Entity: Name: " << name << ", HP: " << health
            << ", Attack: " << attack_power << ", Defense: " << defense << endl;
    }

    virtual void heal(int amount) {
        if (amount <= 0) return;
        health += amount;
        cout << name << " recovers " << amount << " HP. Current HP: " << health << endl;
    }

    int getHealth() const {
        return health;
    }

    string getName() const {
        return name;
    }

    virtual ~Entity() {
    }

    friend class Character;
    friend class Monster;
    friend class Boss;
};

class Character : public Entity {
public:
    Character(const string& n, int h, int a, int d)
        : Entity(n, h, a, d) {
    }

    void attack(Entity& target) override {
        cout << name << " (character attack) -> " << target.name << endl;
        int damage = attack_power - target.defense;
        bool critical_hit = (rand() % 100 < 20);

        if (critical_hit) {
            damage *= 2;
            cout << "  CRITICAL HIT! ";
        }

        if (damage < 0) damage = 0;

        target.health -= damage;
        cout << "  " << target.name << " receives " << damage << " damage.";
        if (target.health <= 0) {
            target.health = 0;
            cout << " " << target.name << " is defeated!";
        }
        cout << " (Remaining HP: " << target.health << ")" << endl;
    }

    void displayInfo() const override {
        cout << "Character: Name: " << name << ", HP: " << health
            << ", Attack: " << attack_power << ", Defense: " << defense << endl;
    }

    void heal(int amount) override {
        if (amount <= 0) return;
        health += amount;
        cout << name << " uses a potion and recovers " << amount << " HP. Current HP: " << health << endl;
    }
};

class Monster : public Entity {
public:
    Monster(const string& n, int h, int a, int d)
        : Entity(n, h, a, d) {
    }

    void attack(Entity& target) override {
        cout << name << " (monster attack) -> " << target.name << endl;
        int damage = attack_power - target.defense;
        bool poison_attack = (rand() % 100 < 30);

        if (poison_attack) {
            damage += 5;
            cout << "  Poison Attack! ";
        }

        if (damage < 0) damage = 0;

        target.health -= damage;
        cout << "  " << target.name << " receives " << damage << " damage.";
        if (target.health <= 0) {
            target.health = 0;
            cout << " " << target.name << " is defeated!";
        }
        cout << " (Remaining HP: " << target.health << ")" << endl;
    }

    void displayInfo() const override {
        cout << "Monster: Name: " << name << ", HP: " << health
            << ", Attack: " << attack_power << ", Defense: " << defense << endl;
    }
};

class Boss : public Monster {
public:
    Boss(const string& n, int h, int a, int d)
        : Monster(n, h, a, d) {
    }

    void attack(Entity& target) override {
        cout << name << " (!! BOSS ATTACK !!) -> " << target.name << endl;
        int damage = attack_power - target.defense;
        bool fire_strike = (rand() % 100 < 40);

        if (fire_strike) {
            damage += 15;
            cout << "  Ignite! ";
        }

        if (damage < 0) damage = 0;

        target.health -= damage;
        cout << "  " << target.name << " receives " << damage << " damage.";
        if (target.health <= 0) {
            target.health = 0;
            cout << " " << target.name << " is defeated!";
        }
        cout << " (Remaining HP: " << target.health << ")" << endl;
    }

    void displayInfo() const override {
        cout << "BOSS: Name: " << name << ", HP: " << health
            << ", Attack: " << attack_power << ", Defense: " << defense << endl;
    }
};


int main() {
    srand(static_cast<unsigned>(time(0)));

    Character hero("Hero Alaric", 120, 25, 12);
    Monster goblin("Stinky Goblin", 50, 15, 5);
    Monster dragon("Ancient Dragon", 200, 30, 20);
    Boss ogreMagi("Ogre Magi", 300, 40, 25);

    vector<Entity*> entities;
    entities.push_back(&hero);
    entities.push_back(&goblin);
    entities.push_back(&dragon);
    entities.push_back(&ogreMagi);

    cout << "--- Entity Information ---" << endl;
    for (const auto& entityPtr : entities) {
        entityPtr->displayInfo();
    }
    cout << "-----------------------------\n" << endl;

    cout << "--- Battle Start! ---" << endl;
    hero.attack(goblin);
    if (goblin.getHealth() > 0) {
        goblin.attack(hero);
    }
    dragon.attack(hero);
    ogreMagi.attack(hero);
    cout << "---------------------\n" << endl;

    cout << "--- Hero decides to heal ---" << endl;
    hero.heal(30);
    cout << "--------------------------------\n" << endl;

    cout << "--- The Boss attacks again! ---" << endl;
    ogreMagi.attack(hero);
    cout << "--------------------------\n" << endl;

    cout << "--- Final State ---" << endl;
    for (const auto& entityPtr : entities) {
        entityPtr->displayInfo();
    }
    cout << "-------------------------\n" << endl;

    return 0;
}
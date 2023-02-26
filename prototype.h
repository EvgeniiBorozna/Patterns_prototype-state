#pragma once
#include <iostream>

class Enemy {
public:
    Enemy() {}
    virtual ~Enemy() {}
    virtual void changeHp(int) = 0;
    virtual void changeAtk(int) = 0;
    virtual void changeDef(int) = 0;
    virtual int getHp() const = 0;
    virtual int getAtk() const = 0;
    virtual int getDef() const = 0;
    virtual Enemy* clone() = 0;
};
class Monster : public Enemy {
private:
    int hp;
    int atk;
    int def;
    std::string type;
public:
    Monster(const Monster& other) {
        hp = other.hp;
        atk = other.atk;
        def = other.def;
        type = other.type;
    }
    Monster(int hp, int atk, int def, const std::string& type) 
        : hp(hp), atk(atk), def(def), type(type) {
        std::cout << "Monster created!\n";
    }

    void changeHp(int change) override {
        hp += change;
    }

    void changeAtk(int change) override {
        atk += change;
    }

    void changeDef(int change) override {
        def += change;
    }

    int getHp() const override {
        return hp;
    }

    int getAtk() const override {
        return atk;
    }

    int getDef() const override {
        return def;
    }
    Enemy* clone() override {
        std::cout << "Monster cloned!\n";
        return new Monster(*this);
    }
};

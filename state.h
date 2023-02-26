#pragma once
#include <iostream>

class StateContext;

int coffeeCount = 3;

class State {
private:
	std::string stateName;
	bool coin = false;
public:
	State(const std::string& stateName) : stateName(stateName) {}
	std::string getStateName() {
		return stateName;
	}
	virtual void CoinIn(StateContext*) = 0;
	virtual void CoinOut(StateContext*) = 0;
	virtual void Buy(StateContext*) = 0;
	virtual void TakeCoffee(StateContext*) = 0;
	void setCoin() { coin = !coin; }
	std::string GetName() {
		return stateName;
	}
	void changeCount(int change) {
		coffeeCount += change;
		if (coffeeCount < 0) coffeeCount = 0;
	}
	int getCount() {
		return coffeeCount;
	}
};

class StateContext {
private:
	State* state;
public:
	StateContext(State* state) : state(state) {}

	void CoinIn() {
		std::cout << state->getStateName() << ": Coin inside " << std::endl;
		state->CoinIn(this);
		state->setCoin();
	}
	void CoinOut() {
		std::cout << state->getStateName() << ": Coin reject " << std::endl;
		state->CoinOut(this);
		state->setCoin();
	}
	void Buy() {
		if (coffeeCount > 0) {
			std::cout << state->getStateName() << ": Buying coffee " << std::endl;
			state->setCoin();
			state->Buy(this);
		}
	}
	void TakeCoffee() {
		if (coffeeCount > 0) {
			std::cout << state->getStateName() << ": Coffee ready " << std::endl;
			state->TakeCoffee(this);
		}
	}
	void SetState(State* s)
	{
		std::cout << "Chaging state from " << state->GetName()
			<< " to " << s->GetName() << "..." << std::endl;
		delete state;
		state = s;
	}
	State* GetState() {
		return state;
	}
	~StateContext() {
		delete state;
	}
};

class NoMoney : public State
{
public:
	NoMoney() : State("No Money") {}
	virtual void CoinIn(StateContext* state);
	virtual void CoinOut(StateContext* state);
	virtual void Buy(StateContext* state);
	virtual void TakeCoffee(StateContext* state);
};
class HaveMoney : public State
{
public:
	HaveMoney() : State("Have Money") {}
	virtual void CoinIn(StateContext* state);
	virtual void CoinOut(StateContext* state);
	virtual void Buy(StateContext* state);
	virtual void TakeCoffee(StateContext* state);
};
class Coffee : public State
{
public:
	Coffee() : State("Coffee") {	}
	virtual void CoinIn(StateContext* state);
	virtual void CoinOut(StateContext* state);
	virtual void Buy(StateContext* state);
	virtual void TakeCoffee(StateContext* state);
};
class NoCoffee : public State
{
public:
	NoCoffee() : State("No more coffee") {}
	virtual void CoinIn(StateContext* state);
	virtual void CoinOut(StateContext* state);
	virtual void Buy(StateContext* state);
	virtual void TakeCoffee(StateContext* state);
};

void NoMoney::CoinIn(StateContext* state) {
	if (getCount() > 0) {
		std::cout << "Get money!" << std::endl;
		state->SetState(new HaveMoney);
	}
}
void NoMoney::CoinOut(StateContext* state) { std::cout << "Nothing happend!\n"; }
void NoMoney::Buy(StateContext* state) { std::cout << "Nothing happend!\n"; }
void NoMoney::TakeCoffee(StateContext* state) { std::cout << "Nothing happend!\n"; }

void HaveMoney::CoinIn(StateContext* state) { std::cout << "Nothing happend!\n"; }
void HaveMoney::CoinOut(StateContext* state) {
	std::cout << "Return money!" << std::endl;
	state->SetState(new NoMoney);
}
void HaveMoney::Buy(StateContext* state) {
	if (getCount() > 0) {
		std::cout << "Buying coffee" << std::endl;
		if (getCount()) changeCount(-1);
		else {
			std::cout << "No more coffee!\n";
		}
		std::cout << "Brewing coffee... Machine has " << getCount() << " left" << std::endl;
		state->SetState(new Coffee);
	}
}
void HaveMoney::TakeCoffee(StateContext* state) { std::cout << "Nothing happend!\n"; }

void Coffee::CoinIn(StateContext* state) { std::cout << "Nothing happend!\n"; }
void Coffee::CoinOut(StateContext* state) { std::cout << "Nothing happend!\n"; }
void Coffee::Buy(StateContext* state) { std::cout << "Nothing happend!\n"; }
void Coffee::TakeCoffee(StateContext* state) {
	if (getCount() > 0) {
		std::cout << "Taking coffee" << std::endl;
		state->SetState(new NoMoney);
	}
}

void NoCoffee::CoinIn(StateContext* state) { std::cout << "No more coffee!\n"; }
void NoCoffee::CoinOut(StateContext* state) { std::cout << "No more coffee!\n"; }
void NoCoffee::Buy(StateContext* state) { std::cout << "No more coffee!\n"; }
void NoCoffee::TakeCoffee(StateContext* state) { std::cout << "No more coffee!\n"; }
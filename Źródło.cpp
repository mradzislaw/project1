#include <iostream>
#include <typeinfo>

#include "lib.h"

/**
* The base State class declares methods that all Concrete State should
* implement and also provides a backreference to the Context object, associated
* with the State. This backreference can be used by States to transition the
* Context to another State.
*/


State::~State() {};


void State::set_context(Context *context) 
{
	this->context_ = context;
}


/**
* The Context defines the interface of interest to clients. It also maintains a
* reference to an instance of a State subclass, which represents the current
* state of the Context.
*/
	
Context::~Context() {
	delete state_;
}

void Context::Request1() {
	this->state_->Handle1();
}
void Context::Request2() {
	this->state_->Handle2();
}

void Context::TransitionTo(State *state) 
{
	std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
	if (this->state_ != nullptr)
		delete this->state_;
	this->state_ = state;
	this->state_->set_context(this);
}

	Context::Context(State *state) : state_(nullptr) {
	this->TransitionTo(state);
}

/**
* Concrete States implement various behaviors, associated with a state of the
* Context.
*/

class ConcreteStateA : public State {
public:
	void Handle1() override;

	void Handle2() override {
		std::cout << "ConcreteStateA handles request2.\n";
	}
};

class ConcreteStateB : public State {
public:
	void Handle1() override {
		std::cout << "ConcreteStateB handles request1.\n";
	}
	void Handle2() override {
		std::cout << "ConcreteStateB handles request2.\n";
		std::cout << "ConcreteStateB wants to change the state of the context.\n";
		this->context_->TransitionTo(new ConcreteStateA);
	}
};

void ConcreteStateA::Handle1() {
	{
		std::cout << "ConcreteStateA handles request1.\n";
		std::cout << "ConcreteStateA wants to change the state of the context.\n";

		this->context_->TransitionTo(new ConcreteStateB);
	}
}

/**
* The client code.
*/
void ClientCode() {
	Context *context = new Context(new ConcreteStateA);
	context->Request1();
	context->Request2();
	delete context;
}

int main() {
	ClientCode();

	cout << "TEST" << endl;

	std::cout << "\n\n\n";
	std::cout << "nowe\n";
	system("pause");
	return 0;
}
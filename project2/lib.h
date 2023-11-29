#pragma once

class State;

class Context
{
private:
	State * state_;
public:
	Context(State *state);
	~Context();
	void TransitionTo(State *state);
	void Request1();
	void Request2();
};

class State {
protected:
	Context * context_;
public:
	virtual ~State();
	void set_context(Context *context);
	virtual void Handle1() = 0;
	virtual void Handle2() = 0;
};
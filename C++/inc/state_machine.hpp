#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "singleton.hpp"

#include <stack> // stack

class State
{
public:
    virtual ~State();

    // template<typename... Args>
    virtual void render(/*Args... args*/) = 0;
};

class StateMachine : public Singleton<StateMachine>
{
    friend class Singleton<StateMachine>;

public:
    StateMachine() = default;
    ~StateMachine() = default;

    State& get_current_state();
    void add_state(State&& a_state);
    void replace_state(State&& a_state);
    void exit_state();

private:
    std::stack<State> m_states;
};

#endif // STATE_MACHINE_HPP
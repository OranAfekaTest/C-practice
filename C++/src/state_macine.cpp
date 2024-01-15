#include "state_machine.hpp"

State& StateMachine::get_current_state()
{
    return m_states.top();
}

void StateMachine::add_state(State&& a_state)
{
    m_states.push(a_state);
}

void StateMachine::replace_state(State&& a_state)
{
    m_states.pop();
    m_states.push(a_state);
}

void StateMachine::exit_state()
{
    m_states.pop();
}
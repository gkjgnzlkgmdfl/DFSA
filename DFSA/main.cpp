#include <iostream>
#include <vector>
#include <string>

using namespace std;

class State
{
public:
    State() {}
    State(bool isTerminal)
    {
        _id = _lastId;
        _isTerminal = isTerminal;
        _lastId++;
    }
    
    State(const State& other)
    {
            this->_id = other._id;
            this->_isTerminal = other._isTerminal;
    }

    ~State() {}
    
    State& operator=(const State& other)
    {
        if (this != &other)
        {
            this->_id = other._id;
            this->_isTerminal = other._isTerminal;
        }
        return *this;
    }

    unsigned int GetID() const
    {
        return _id;
    }

    bool IsTermnal()
    {
        return _isTerminal;
    }

private:
    bool _isTerminal;
    unsigned int _id;
    static unsigned int _lastId;
};
unsigned int State::_lastId = 0;

template<typename T>
class TransitionFunction
{
public:
    TransitionFunction(State from, State to, T trigger)
    {
        _from = from;
        _to = to;
        _trigger = trigger;
    }
    
   TransitionFunction(const TransitionFunction& other)
    {
        if (this != &other) 
        {
            this->_from = other._from;
            this->_to = other._to;
            this->_trigger = other._trigger;
        }
    }
      
    TransitionFunction& operator=(const TransitionFunction<T>& other)
    {
        if (this != &other)
        {
            this->_from = other._from;
            this->_to = other._to;
            this->_trigger = other._trigger;
            
        }
        return *this;
    }

    ~TransitionFunction() {}

    State GetFromState() const
    {
        return _from;
    }

    State GetToState() const
    {
        return _to;
    }

    T GetTrigger() const
    {
        return _trigger;
    }

private:
    State _from;
    State _to;
    T _trigger;
};

template<typename T>
class Automata
{
public:
    Automata(vector<State> states, vector<TransitionFunction<T>> functions, vector<T> alphabet, State initialState)
    {
        _states = states;
        _functions = functions;
        _alphabet = alphabet;
        _initialState = initialState;
        _currentState = initialState;
    }

    bool triggerTransition(T trigger)
    {
        for (auto& function : _functions)
        {
            if (function.GetFromState().GetID() == _currentState.GetID() && function.GetTrigger() == trigger)
            {
                _currentState = function.GetToState();
                return true;
            }
        }
        return false;
    }

    bool Read(vector<T> inputs)
    {
        for (int i = 0; i < inputs.size(); i++)
        {
            if (triggerTransition(inputs[i]) == false )
            {
                return false;
            }
            if (_currentState.IsTermnal())
            {
                return true;
            }
        }
        return false;
    }
private:
    vector<State> _states;
    vector<TransitionFunction<T>> _functions;
    vector<T> _alphabet;
    State _initialState;
    State _currentState;
};

int main()
{
    
    return 0;
}
#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <cstddef>
#include <map>
#include <set>

#include "State.h"
#include "Transition.h"

/*
                     _                                 _
     /\             | |                               | |
    /  \     _   _  | |_    ___    _ __ ___     __ _  | |_    ___    _ __
   / /\ \   | | | | | __|  / _ \  | '_ ` _ \   / _` | | __|  / _ \  | '_ \
  / ____ \  | |_| | | |_  | (_) | | | | | | | | (_| | | |_  | (_) | | | | |
 /_/    \_\  \__,_|  \__|  \___/  |_| |_| |_|  \__,_|  \__|  \___/  |_| |_|


*/

namespace fa {

    class Automaton {
    private:
        std::set<char> alphabet;
        std::map<int, State> states;
        std::set<Transition> transitions;
    public:
        //Constructor
        Automaton();

        //States
        /**
         * Add the number given state to the automaton
         * @param state
         */
        void addState(int state);

        /**
         * Remove the number given state to the automaton
         * @param state
         */
        void removeState(int state);

        /**
         * Test if we have a state or not into the automaton
         * @param state
         * @return true if we had the state false otherwise
         */
        bool hasState(int state) const;

        /**
         *
         * @return the number of states in the automaton
         */
        std::size_t countStates() const;

        /**
         * Make a state Initial
         * @param state
         */
        void setStateInitial(int state);

        /**
         * Test if a state is Initial
         * @param state
         * @return true if yes false otherwise
         */
        bool isStateInitial(int state) const;

        /**
         * Make a state Final
         * @param state
         */
        void setStateFinal(int state);

        /**
         * Test if a state is Final
         * @param state
         * @return true if yes false otherwise
         */
        bool isStateFinal(int state);

        //Transitions
        /**
         * Add the given transition (if possible) into the automaton
         * @param from
         * @param c
         * @param to
         */
        void addTransition(int from, char c, int to);

        /**
         * Remove the given transition (if possible) from the automaton
         * @param from
         * @param c
         * @param to
         */
        void removeTransition(int from, char c, int to);

        /**
         * Test if you have the given transition
         * @param from
         * @param c
         * @param to
         * @return true if yes false otherwise
         */
        bool hasTransition(int from, char c, int to) const;

        /**
         *
         * @return the number of transitions into the automaton
         */
        std::size_t countTransitions() const;

        //Alphabet
        /**
         *
         * @return the number of letters into the alphabet
         */
        std::size_t getAlphabetSize() const;

        //Divers
        /**
         *
         * @param os
         */
        void prettyPrint(std::ostream &os) const;

        //Automate
        /**
         *
         * @return true if yes false otherwise
         */
        bool isDeterministic() const;

        /**
         *
         * @return true if yes false otherwise
         */
        bool isComplete() const;

        /**
         * Make an automaton complete
         */
        void makeComplete();

        /**
         *
         * @return
         */
        bool isLanguageEmpty() const;

        /**
         *
         */
        void removeNonAccessibleStates();
        /**
         *
         */
        void removeNonCoAccessibleStates();
    };

}; // namespace fa

#endif // AUTOMATON_H

#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <cstddef>
#include <iostream>
#include <map>
#include <set>

namespace fa {
/*
  ____    _             _
 / ___|  | |_    __ _  | |_    ___
 \___ \  | __|  / _` | | __|  / _ \
  ___) | | |_  | (_| | | |_  |  __/
 |____/   \__|  \__,_|  \__|  \___|

*/
    class State {
    private:
        int number;
        bool IsInit = false;
        bool IsFinal = false;

    public:

        //Constructor
        State();
        State(int num);

        bool isIsInit() const;

        void setIsInit(bool IsInit);

        bool isIsFinal() const;

        void setIsFinal(bool IsFinal);

        int getNumber() const;

    };
/*
  _____                                _   _     _
 |_   _|  _ __    __ _   _ __    ___  (_) | |_  (_)   ___    _ __
   | |   | '__|  / _` | | '_ \  / __| | | | __| | |  / _ \  | '_ \
   | |   | |    | (_| | | | | | \__ \ | | | |_  | | | (_) | | | | |
   |_|   |_|     \__,_| |_| |_| |___/ |_|  \__| |_|  \___/  |_| |_|

 */
    class Transition {
    private:
        int begin_state;
        int end_state;
        char letter;
    public:
        //Constructor
        Transition();
        Transition(int a, char c, int b);

        int getBegin_state() const;

        void setBegin_state(int begin_state);

        int getEnd_state() const;

        void setEnd_state(int end_state);

        char getLetter() const;

        void setLetter(char letter);

        bool operator< (const Transition &other) const{
            return std::tie(begin_state, letter, end_state) < std::tie(other.begin_state, other.letter, other.end_state);
        }
    };
/*
                     _                                 _
     /\             | |                               | |
    /  \     _   _  | |_    ___    _ __ ___     __ _  | |_    ___    _ __
   / /\ \   | | | | | __|  / _ \  | '_ ` _ \   / _` | | __|  / _ \  | '_ \
  / ____ \  | |_| | | |_  | (_) | | | | | | | | (_| | | |_  | (_) | | | | |
 /_/    \_\  \__,_|  \__|  \___/  |_| |_| |_|  \__,_|  \__|  \___/  |_| |_|


*/
    class Automaton {
    private:
        std::set<char> alphabet;
        std::map<int, State> states;
        std::set<Transition> transitions;
    public:
        //Constructor
        Automaton();
        //Other
        int checkAutomaton() const {
            if (isComplete()) {
                std::cout << "L'automate est complet !\n";
            } else {
                std::cout << "L'automate n'est pas complet !\n";
            }
            if (isDeterministic()) {
                std::cout << "L'automate est déterministe !\n";
            } else {
                std::cout << "L'automate n'est pas déterministe !\n";
            }
            if (isLanguageEmpty()) {
                std::cout << "Le langage reconnu est vide !\n";
            } else {
                std::cout << "Le langage reconnu n'est pas vide !\n";
            }
            return 0;
        }
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
        bool isStateFinal(int state) const;

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
        /**
         *
         */
        static Automaton createProduct(const Automaton& lhs, const Automaton& rhs);
    };

}; // namespace fa

#endif // AUTOMATON_H

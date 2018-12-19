#include "Automaton.h"

#include <cassert>
#include <iostream>
#include <algorithm>

/*
                     _                                 _
     /\             | |                               | |
    /  \     _   _  | |_    ___    _ __ ___     __ _  | |_    ___    _ __
   / /\ \   | | | | | __|  / _ \  | '_ ` _ \   / _` | | __|  / _ \  | '_ \
  / ____ \  | |_| | | |_  | (_) | | | | | | | | (_| | | |_  | (_) | | | | |
 /_/    \_\  \__,_|  \__|  \___/  |_| |_| |_|  \__,_|  \__|  \___/  |_| |_|


*/

namespace fa {

    void fa::Automaton::addState(int state) {
        if (hasState(state)) return;
        states.insert(std::pair<int, State>(state, State(state)));
    };

    void fa::Automaton::removeState(int state) {
        states.erase(state);
        std::set<Transition>::iterator tr;
        for (tr = transitions.begin(); tr != transitions.end(); ++tr) {
            if ((tr->getBegin_state() == state) || (tr->getEnd_state() == state)) {
                removeTransition(tr->getBegin_state(),tr->getLetter(),tr->getEnd_state());
            }
        }
    };

    bool fa::Automaton::hasState(int state) const {
        return (states.find(state) != states.end());
    };

    std::size_t fa::Automaton::countStates() const {
        return states.size();
    };

    void fa::Automaton::setStateInitial(int state) {
        states[state].setIsInit(true);
    };
    bool fa::Automaton::isStateInitial(int state) const {
        return states.at(state).isIsInit();
    };

    void fa::Automaton::setStateFinal(int state) {
        states[state].setIsFinal(true);
    };

    bool fa::Automaton::isStateFinal(int state) {
        return states.at(state).isIsFinal();
    };

    void fa::Automaton::addTransition(int from, char c, int to) {
        transitions.insert(fa::Transition(from, c, to));
        alphabet.insert(c);
    };

    void Automaton::removeTransition(int from, char c, int to) {
        transitions.erase(fa::Transition(from,c,to));
    };

    bool Automaton::hasTransition(int from, char c, int to) const {
        return (transitions.find(fa::Transition(from,c,to)) != transitions.end());
    };

    std::size_t Automaton::countTransitions() const {
        return transitions.size();
    };

    std::size_t Automaton::getAlphabetSize() const {
        return alphabet.size();
    };

    void Automaton::prettyPrint(std::ostream &os) const {
        //Initials states
        std::cout<<"Initial States : "<<std::endl;
        for (const auto& state : states)
        {
            if (state.second.isIsInit()) {
                std::cout << state.first << ' ';
            }
        }

        std::cout << std::endl;

        std::cout<<"Final States : "<<std::endl;
        for (const auto& state : states) {
            if (state.second.isIsFinal()) {
                std::cout << state.first << ' ';
            }
        }

        std::cout << std::endl;
        std::cout << "Nombre d'états : " << countStates() << std::endl;
        //Transitions
        std::cout<<"Transitions : "<<std::endl;
        int previousState=999999;

        char previousChar=0;
        std::cout << "Nombre de transitions : " << countTransitions() << std::endl;
        for (Transition const& tr : transitions) {
            if (tr.getBegin_state() != previousState) {
                previousState = tr.getBegin_state();
                previousChar=0;
                std::cout << "Pour l'état " << previousState << " :" << std::endl;
            }
            if (tr.getBegin_state() == previousState) {
                if (tr.getLetter() != previousChar) {
                    previousChar = tr.getLetter();
                    std::cout << "\tPour la lettre " << previousChar << " :" << "\t";
                }
                if (tr.getLetter() == previousChar) {
                    std::cout << tr.getEnd_state() << "\t";
                }
                std::cout << std::endl;
            }
        }
    };

    bool Automaton::isDeterministic() const {
        bool flag = true;
        char previousChar = 0;
        int previousState = 0;
        int nextState = 0;
        for (Transition const& tr : transitions) {
            if (flag) {
                previousChar = tr.getLetter();
                previousState = tr.getBegin_state();
                nextState = tr.getEnd_state();
                flag = false;
            }
            if (previousChar == tr.getLetter() &&
                previousState == tr.getBegin_state() &&
                nextState != tr.getEnd_state()) {
                return false;
            }
            previousChar = tr.getLetter();
            previousState = tr.getBegin_state();
            nextState = tr.getEnd_state();
        }
        return true;
    }

    bool Automaton::isComplete() const {
        for (auto st : states) {
            std::set<char> alpha = alphabet;
            for (auto tr : transitions) {
                if (tr.getBegin_state() == st.second.getNumber()) {
                    alpha.erase(tr.getLetter());
                }
            }
            if (!alpha.empty()) {
                return false;
            }
        }
        return true;
    }

    void Automaton::makeComplete() {
        if (not (isComplete())) {
            int trashState=0;
            while (hasState(trashState)) {
                --trashState;
            }
            addState(trashState);
            for (auto st : states) {
                std::set<char> alpha = alphabet;
                for (auto tr : transitions) {
                    if (tr.getBegin_state() == st.second.getNumber()) {
                        alpha.erase(tr.getLetter());
                    }
                }
                for (auto remainingLetters : alpha) {
                    this->addTransition(st.second.getNumber(),remainingLetters,trashState);
                }
            }
        }
    };

    bool Automaton::isLanguageEmpty() const{
        std::set<int> initial, final;

        for (auto st : states) {
            if (st.second.isIsInit()) {
                initial.insert(st.second.getNumber());
            }
            if (st.second.isIsFinal()) {
                final.insert(st.second.getNumber());
            }
        }
        std::set<int> theWayFromInitial = initial;
        for (auto alpha : alphabet) {
            for (auto fromSt : theWayFromInitial) {
                for (auto toSt : states) {
                    if (hasTransition(fromSt,alpha,toSt.second.getNumber())) {
                        theWayFromInitial.insert(toSt.second.getNumber());
                        if ((initial.find(fromSt) != initial.end()) && (final.find(toSt.second.getNumber()) != final.end())) {
                            return false;
                        }
                    }
                }
            }
        }
        for (auto finalSate : final) {
            if (theWayFromInitial.find(finalSate) != theWayFromInitial.end()) {
                return false;
            }
        }
        return true;
    }

    void Automaton::removeNonAccessibleStates() {
        std::set<int> initial, final;

        for (auto st : states) {
            if (st.second.isIsInit()) {
                initial.insert(st.second.getNumber());
            }
            if (st.second.isIsFinal()) {
                final.insert(st.second.getNumber());
            }
        }
        std::set<int> theWayFromInitial = initial;
        for (auto alpha : alphabet) {
            for (auto fromSt : theWayFromInitial) {
                for (auto toSt : states) {
                    if (hasTransition(fromSt,alpha,toSt.second.getNumber())) {
                        theWayFromInitial.insert(toSt.second.getNumber());
                    }
                }
            }
        }
        for (auto nonAccessibleState : states) {
            if (theWayFromInitial.find(nonAccessibleState.second.getNumber()) == theWayFromInitial.end()) {
                removeState(nonAccessibleState.second.getNumber());
            }
        }
    }

    void Automaton::removeNonCoAccessibleStates() {
        std::set<int> finalOrClose;

        for (auto st : states) {
            if (st.second.isIsFinal()) {
                finalOrClose.insert(st.second.getNumber());
            }
        }

        u_long numberOfStateCoAccessible = finalOrClose.size();
        // PAS OPTIMISEE
        for (auto fromSt : states) {
            for (auto toSt : finalOrClose) {
                for (auto alpha : alphabet) {
                    if (hasTransition(fromSt.second.getNumber(),alpha,toSt)) {
                        finalOrClose.insert(fromSt.second.getNumber());
                    }
                }
            }
        }
        while (numberOfStateCoAccessible != finalOrClose.size()) {
            numberOfStateCoAccessible = finalOrClose.size();

            for (auto fromSt : states) {
                for (auto toSt : finalOrClose) {
                    for (auto alpha : alphabet) {
                        if (hasTransition(fromSt.second.getNumber(),alpha,toSt)) {
                            finalOrClose.insert(fromSt.second.getNumber());
                        }
                    }
                }
            }
        }

        for (auto stateToDelete : states) {
            if (finalOrClose.find(stateToDelete.second.getNumber()) == finalOrClose.end()) {
                removeState(stateToDelete.first);
            }
        }
    };

    Automaton::Automaton() = default;;
};

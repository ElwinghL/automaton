#include "Automaton.h"

#include <cassert>
#include <iostream>
#include <algorithm>

namespace fa {
/*
  ____    _             _
 / ___|  | |_    __ _  | |_    ___
 \___ \  | __|  / _` | | __|  / _ \
  ___) | | |_  | (_| | | |_  |  __/
 |____/   \__|  \__,_|  \__|  \___|

*/
    fa::State::State() = default;;

    fa::State::State(int num) {
        number = num;
    };

    int fa::State::getNumber() const {
        return number;
    };

    bool State::isIsInit() const {
        return IsInit;
    }

    void State::setIsInit(bool IsInit) {
        State::IsInit = IsInit;
    }

    bool State::isIsFinal() const {
        return IsFinal;
    }

    void State::setIsFinal(bool IsFinal) {
        State::IsFinal = IsFinal;
    }
/*
  _____                                _   _     _
 |_   _|  _ __    __ _   _ __    ___  (_) | |_  (_)   ___    _ __
   | |   | '__|  / _` | | '_ \  / __| | | | __| | |  / _ \  | '_ \
   | |   | |    | (_| | | | | | \__ \ | | | |_  | | | (_) | | | | |
   |_|   |_|     \__,_| |_| |_| |___/ |_|  \__| |_|  \___/  |_| |_|

 */
    fa::Transition::Transition() = default;;

    fa::Transition::Transition(int a, char c, int b) {
        begin_state = a;
        end_state = b;
        letter = c;
    }

    int Transition::getBegin_state() const {
        return begin_state;
    }

    void Transition::setBegin_state(int begin_state) {
        Transition::begin_state = begin_state;
    }

    int Transition::getEnd_state() const {
        return end_state;
    }

    void Transition::setEnd_state(int end_state) {
        Transition::end_state = end_state;
    }

    char Transition::getLetter() const {
        return letter;
    }

    void Transition::setLetter(char letter) {
        Transition::letter = letter;
    };


/*
                     _                                 _
     /\             | |                               | |
    /  \     _   _  | |_    ___    _ __ ___     __ _  | |_    ___    _ __
   / /\ \   | | | | | __|  / _ \  | '_ ` _ \   / _` | | __|  / _ \  | '_ \
  / ____ \  | |_| | | |_  | (_) | | | | | | | | (_| | | |_  | (_) | | | | |
 /_/    \_\  \__,_|  \__|  \___/  |_| |_| |_|  \__,_|  \__|  \___/  |_| |_|


*/
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

    bool fa::Automaton::isStateFinal(int state) const {
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
        os << "Initial States : "<<std::endl;
        for (const auto& state : states)
        {
            if (state.second.isIsInit()) {
                std::cout << state.first << ' ';
            }
        }

        os << std::endl;

        os <<"Final States : "<<std::endl;
        for (const auto& state : states) {
            if (state.second.isIsFinal()) {
                std::cout << state.first << ' ';
            }
        }

        os << std::endl;
        os << "Nombre d'états : " << countStates() << std::endl;
        //Transitions
        os <<"Transitions : "<<std::endl;
        int previousState=999999;

        char previousChar=0;
        os << "Nombre de transitions : " << countTransitions() << std::endl;
        for (Transition const& tr : transitions) {
            if (tr.getBegin_state() != previousState) {
                previousState = tr.getBegin_state();
                previousChar=0;
                os << "Pour l'état " << previousState << " :" << std::endl;
            }
            if (tr.getBegin_state() == previousState) {
                if (tr.getLetter() != previousChar) {
                    previousChar = tr.getLetter();
                    os << "\tPour la lettre " << previousChar << " :" << "\t";
                }
                if (tr.getLetter() == previousChar) {
                    os << tr.getEnd_state() << "\t";
                }
                os << std::endl;
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
    }

    Automaton Automaton::createProduct(const Automaton &lhs, const Automaton &rhs) {
        Automaton ret =  Automaton();
        std::map<std::pair<int,int>,int> workingOn;

        std::set<int> lhsInit;
        std::set<int> rhsInit;
        std::set<char> alphabetFromBoth;

        for (auto alpha1 : lhs.alphabet) {
            alphabetFromBoth.insert(alpha1);
        }
        for (auto alpha2 : rhs.alphabet) {
            alphabetFromBoth.insert(alpha2);
        }

        for (auto lhsSt : lhs.states) {
            if (lhs.isStateInitial(lhsSt.first)) {
                lhsInit.insert(lhsSt.first);
            }
        }
        for (auto rhsSt : rhs.states) {
            if (rhs.isStateInitial(rhsSt.first)) {
                rhsInit.insert(rhsSt.first);
            }
        }
        int currentNumber = 0;
        for (auto init1 : lhsInit) {
            for (auto init2 : rhsInit) {
                ret.addState(currentNumber);
                ret.setStateInitial(currentNumber);
                std::cout << "Merged from left automata " << init1 << " and from right automata " << init2 << " into " << currentNumber <<"\n";
                workingOn.insert(std::make_pair(std::pair<int,int>(init1,init2),currentNumber));
                if (lhs.isStateFinal(init1) && rhs.isStateFinal(init2)) {
                    ret.setStateFinal(currentNumber);
                }
                ++currentNumber;
            }
        }

        while (!workingOn.empty()) {
            std::map<std::pair<int,int>,int> copy = workingOn;
            for (auto pair : workingOn) {
                int p = pair.first.first;
                int q = pair.first.second;
                int thatState = pair.second;
                workingOn.erase(std::pair<int,int>(p,q));
                if ((lhs.isStateFinal(p)) && (rhs.isStateFinal(q))) {
                    ret.setStateFinal(thatState);
                }

                for (auto lhsSt : lhs.states) {
                    int pPrime = lhsSt.first;
                    for (auto rhsSt : rhs.states) {
                        int qPrime = rhsSt.first;
                        for (auto alpha : alphabetFromBoth) {
                            if (lhs.hasTransition(p,alpha,pPrime)) {
                                if (rhs.hasTransition(q,alpha,qPrime)) {

                                    if (copy.find(std::pair<int,int>(pPrime,qPrime)) == copy.end()) {
                                        ret.addState(currentNumber);
                                        workingOn.insert(std::make_pair(std::pair<int,int>(pPrime,qPrime),currentNumber));
                                        copy.insert(std::make_pair(std::pair<int,int>(pPrime,qPrime),currentNumber));
                                        std::cout << "Merged from left automata " << pPrime << " and from right automata " << qPrime << " into " << currentNumber <<"\n";
                                        ++currentNumber;
                                    }
                                    auto toThatState = copy.find(std::pair<int,int>(pPrime,qPrime));
                                    ret.addTransition(thatState,alpha,toThatState->second);
                                    std::cout << "Added this transitions (" << p <<","<< q <<") " << alpha << " (" << pPrime <<","<< qPrime <<")\n";
                                }
                            }
                        }
                    }
                }
            }
            std::cout << "Copy.size = " << copy.size() << "\n";
            std::cout << "workingOn.size = " << workingOn.size() << "\n";
        }

        return ret;
    }


    Automaton::Automaton() = default;;
};

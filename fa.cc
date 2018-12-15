#include <iostream>
#include "Automaton.h"

int main() {
    fa::Automaton automate,automate2;

    automate.addState(0);
    automate.addState(1);
    automate.addState(2);
    automate.setStateInitial(0);
    automate.setStateFinal(1);
    automate.addTransition(0, 'a', 1);
    automate.addTransition(0, 'b', 0);
    automate.addTransition(1, 'b', 0);
    automate.addTransition(2, 'c', 0);

    automate2.addState(0);
    automate2.addState(1);
    automate2.addState(2);
    automate2.addState(3);
    automate2.setStateInitial(0);
    automate2.setStateFinal(3);
    automate2.addTransition(0, 'a', 1);
    automate2.addTransition(0, 'b', 0);
    automate2.addTransition(1, 'b', 0);
    automate2.addTransition(2, 'c', 0);
    automate2.addTransition(0,'c',2);
    automate2.addTransition(2,'a',3);
    automate2.addTransition(3,'a',3);



    automate2.prettyPrint(std::cout);
    automate2.removeNonCoAccessibleStates();
    automate2.prettyPrint(std::cout);

    return 0;
}

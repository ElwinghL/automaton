#include <iostream>
#include "Automaton.h"

int main() {
    fa::Automaton automate;

    /**
     * La création d'un automate se fait seule, comme vu plus haut, il suffit ensuite de lui ajouter des états et des transitions  comme suit :
     *
     * Réalisation de l'automate suivant : http://leboeuf.iiens.net/automate.png
     *
     * avec p = 0 ; q = 1 et r =2.
     */

    for (int i = 0; i < 3; ++i) {
        automate.addState(i);
    }
    // Transition de p
    automate.addTransition(0,'a',1);
    // Transitions de q
    automate.addTransition(1,'a',0);
    automate.addTransition(1,'b',2);
    // Transition de r
    automate.addTransition(2,'b',2);
    // Définitions des étas finaux et initiaux
    automate.setStateInitial(0);
    automate.setStateFinal(2);
    // Affichage de l'automate pour vérifier nos données
    automate.prettyPrint(std::cout);
    std::cout << "========================================\n\n\n========================================\n";
    /**
     * Par la suite on peut s'enquérir de l'automate ainsi conçu pour voir s'il est détérministe,
     * complet, si le langage reconnu est vide...
     */

    automate.checkAutomaton(); // Affiche si l'automate est complet, déterministe ou si son langage est vide
    std::cout << "========================================\n\n\n========================================\n";

    /**
     * On peut compléter un automate, supprimer les états non accessibles, non co-accessibles...
     * Comme suit (la copie est optionelle, je veut juste conserver mon automate)
     */

    fa::Automaton automateCopied = automate;

    automateCopied.makeComplete();
    automateCopied.checkAutomaton();
    automateCopied.prettyPrint(std::cout);
    std::cout << "========================================\n\n\n========================================\n";
    //Suppression des états non accessibles (ajout d'un état préalable)
    automateCopied.addState(89);
    automateCopied.addTransition(89,'a',89);
    automateCopied.prettyPrint(std::cout);
    automateCopied.removeNonAccessibleStates();
    automateCopied.prettyPrint(std::cout);
    std::cout << "========================================\n\n\n========================================\n";
    //Suppression des états non co-accessibles (état poubelle du makeComplete)
    automateCopied.removeNonCoAccessibleStates();
    automateCopied.prettyPrint(std::cout);
    std::cout << "========================================\n\n\n========================================\n";

    /**
     * La suppression des états ou des transitions se fait à l'aide des fonctions suivantes
     * (ainsi que le contrôle d'existance d'un état ou d'une transition)
     */
    if(automateCopied.isStateInitial(0)) {
        std::cout << "Oui.\n";
    }
    if(automateCopied.isStateFinal(2)) {
        std::cout << "Aussi.\n";
    }
    if(automateCopied.hasTransition(1,'a',0)) {
        automateCopied.removeTransition(1,'a',0);
    }
    // Marche aussi sans la vérification
    automateCopied.removeTransition(2,'a',2); //N'existe pas.

    automateCopied.prettyPrint(std::cout);
    std::cout << "========================================\n\n\n========================================\n";

    /**
     * Faire le produit de deux automates pour vérifier l'intersection
     * Réalisation de cet automate : http://leboeuf.iiens.net/automate2.png
     * Et du produit qui doit donner : http://leboeuf.iiens.net/automateProduct.png
     *
     * Pour l'automate2 :
     * s = 0; t = 1; u = 2;
     *
     * Les correspondances du produit sont affichés dans le flux courant
     */

    fa::Automaton automate2;

    for (int j = 0; j < 3; ++j) {
        automate2.addState(j);
    }
    automate2.setStateInitial(0);
    automate2.setStateInitial(1);
    automate2.setStateFinal(2);
    automate2.addTransition(0,'a',1);
    automate2.addTransition(1,'a',2);
    automate2.addTransition(1,'b',2);
    automate2.addTransition(2,'b',1);

    fa::Automaton automateProduct = fa::Automaton::createProduct(automate,automate2);

    automateProduct.prettyPrint(std::cout);




    return 0;
}


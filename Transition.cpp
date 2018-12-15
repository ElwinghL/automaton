//
// Created by e1w1ngh on 17/10/18.
//

#include "Transition.h"
#include "State.h"

/*
  _______                                _   _     _
 |__   __|                              (_) | |   (_)
    | |     _ __    __ _   _ __    ___   _  | |_   _    ___    _ __    ___
    | |    | '__|  / _` | | '_ \  / __| | | | __| | |  / _ \  | '_ \  / __|
    | |    | |    | (_| | | | | | \__ \ | | | |_  | | | (_) | | | | | \__ \
    |_|    |_|     \__,_| |_| |_| |___/ |_|  \__| |_|  \___/  |_| |_| |___/


*/

namespace fa {

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
};
//
// Created by e1w1ngh on 17/10/18.
//

#include "State.h"

/*
   _____   _             _
  / ____| | |           | |
 | (___   | |_    __ _  | |_    ___   ___
  \___ \  | __|  / _` | | __|  / _ \ / __|
  ____) | | |_  | (_| | | |_  |  __/ \__ \
 |_____/   \__|  \__,_|  \__|  \___| |___/


*/

namespace fa {

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

};
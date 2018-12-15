//
// Created by e1w1ngh on 17/10/18.
//

#ifndef FA_TRANSITION_H
#define FA_TRANSITION_H

#include <tuple>
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
};

#endif //FA_TRANSITION_H

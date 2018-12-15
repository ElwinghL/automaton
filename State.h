//
// Created by e1w1ngh on 17/10/18.
//

#ifndef FA_STATE_H
#define FA_STATE_H

/*
   _____   _             _
  / ____| | |           | |
 | (___   | |_    __ _  | |_    ___   ___
  \___ \  | __|  / _` | | __|  / _ \ / __|
  ____) | | |_  | (_| | | |_  |  __/ \__ \
 |_____/   \__|  \__,_|  \__|  \___| |___/


*/

namespace fa {

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

};

#endif //FA_STATE_H

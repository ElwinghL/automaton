#include <iostream>
#include <iomanip>

#include "gtest/gtest.h"

#include "Automaton.h"

TEST(AutomatonTest, Empty) {
    fa::Automaton fa;

    EXPECT_EQ(fa.countStates(), 0u);
    EXPECT_EQ(fa.countTransitions(), 0u);
}

TEST(AutomatonTest,isDeterministic) {
    fa::Automaton fa;

    for (int i = 0; i < 3; ++i) {
        fa.addState(i);
    }
    fa.addTransition(0,'a',1);
    fa.addTransition(1,'a',0);
    fa.addTransition(1,'b',2);
    fa.addTransition(2,'b',2);
    fa.setStateInitial(0);
    fa.setStateFinal(2);

    EXPECT_TRUE(fa.isDeterministic());
}

TEST(AutomatonTest,Complete) {
    fa::Automaton fa;

    for (int i = 0; i < 3; ++i) {
        fa.addState(i);
    }
    fa.addTransition(0,'a',1);
    fa.addTransition(1,'a',0);
    fa.addTransition(1,'b',2);
    fa.addTransition(2,'b',2);
    fa.setStateInitial(0);
    fa.setStateFinal(2);

    EXPECT_FALSE(fa.isComplete());
    fa.makeComplete();
    EXPECT_TRUE(fa.isComplete());
}

TEST(AutomatonTest,Count) {
    fa::Automaton fa;

    for (int i = 0; i < 3; ++i) {
        fa.addState(i);
    }
    fa.addTransition(0,'a',1);
    fa.addTransition(1,'a',0);
    fa.addTransition(1,'b',2);
    fa.addTransition(2,'b',2);
    fa.setStateInitial(0);
    fa.setStateFinal(2);

    EXPECT_EQ(fa.countStates(),3);
    EXPECT_EQ(fa.countTransitions(),4);
    EXPECT_EQ(fa.getAlphabetSize(),2);
}

TEST(StatesTest,addState) {
    fa::Automaton fa;
    fa.addState(42);
    EXPECT_TRUE(fa.hasState(42));
}

TEST(StatesTest,initialAndFinal) {
    fa::Automaton fa;

    for (int i = 0; i < 3; ++i) {
        fa.addState(i);
    }
    fa.setStateInitial(0);
    fa.setStateFinal(2);

    EXPECT_TRUE(fa.isStateFinal(2));
    EXPECT_TRUE(fa.isStateInitial(0));

    EXPECT_FALSE(fa.isStateInitial(2));
    EXPECT_FALSE(fa.isStateFinal(0));
}

TEST(StatesTest,removeState) {
    fa::Automaton fa;
    fa.addState(42);
    EXPECT_TRUE(fa.hasState(42));
    fa.removeState(42);
    EXPECT_FALSE(fa.hasState(42));
}

TEST(TransitionsTest,addTransition) {
    fa::Automaton fa;

    for (int i = 0; i < 3; ++i) {
        fa.addState(i);
    }
    fa.addTransition(0,'a',1);
    fa.addTransition(1,'a',0);
    fa.addTransition(1,'b',2);
    fa.addTransition(2,'b',2);

    EXPECT_TRUE(fa.hasTransition(0,'a',1));
    EXPECT_TRUE(fa.hasTransition(1,'a',0));
    EXPECT_TRUE(fa.hasTransition(1,'b',2));
    EXPECT_TRUE(fa.hasTransition(2,'b',2));

}

TEST(TransitionsTest,removeTransition) {
    fa::Automaton fa;

    for (int i = 0; i < 3; ++i) {
        fa.addState(i);
    }
    fa.addTransition(0,'a',1);
    fa.addTransition(1,'a',0);
    fa.addTransition(1,'b',2);
    fa.addTransition(2,'b',2);

    fa.removeTransition(2,'b',2);

    EXPECT_TRUE(fa.hasTransition(0,'a',1));
    EXPECT_TRUE(fa.hasTransition(1,'a',0));
    EXPECT_TRUE(fa.hasTransition(1,'b',2));
    EXPECT_FALSE(fa.hasTransition(2,'b',2));
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

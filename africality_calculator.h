// Created by Taka 03/15/2018
// Inside africality_calculator.h
#ifndef AFRICALITY_CALCULATOR_H
#define AFRICALITY_CALCULATOR_H

// Overall Probabilities of 3 types of cards
const int P_BASE = 100;
const int P_R = 89;
const int P_SR = 10;
const int P_SSR = 1;

// Numbers of cards in diamond pool
// 假设四大天王四小天王不存在QAQ
const int NUM_R = 8 * 4 - 2 - 1;
const int NUM_SR = (3 + 3) * 4 - 1;
const int NUM_SSR = (2 + 1) * 4 - 1;

const int NUM_DRAW = 100000;

class Draw {
    int num;
    int SSRNum;
    int SRNum;
    int RNum;
    int newNum;
    int newGoodNum;
    std::vector<int> vecR;
    std::vector<int> vecSR;
    std::vector<int> vecSSR;

    void countNewNum();

public:
    Draw (int inNum);
    int getNewNum() { return newNum; }
    int getNewGoodNum() { return newGoodNum; }
    int getGoodNum() { return SSRNum + SRNum; }
    
};
void printFirstSSRDis();
void printDistribution(std::map<int, int> & disMap);

#endif /* AFRICALITY_CALCULATOR_H */

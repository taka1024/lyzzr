// Created by Taka 03/15/2018

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <map>
#include "africality_calculator.h"

void printFirstSSRDis() {
    std::cout << "第一次抽到SSR为第几发？" << std::endl;
    double moreAfricanProb = 1;
    if (IS_VERBOSE) {
        for (int i = 0; i < 350; i += 10) {
            std::cout << "第" << i << "抽抽到SSR，比" << (int)(moreAfricanProb * 100) << "\%的人更欧" << std::endl;
            moreAfricanProb *= 0.90438;
        }
    }
    else {
        int currentPercent = 100;
        for (int i = 0; i < 350; ++i) {
            if ((int)(moreAfricanProb * 100) / 20 == currentPercent / 20 - 1) {
                std::cout << "第" << i << "抽抽到SSR，欧气打败" << currentPercent / 20 * 20 << "\%的制作人" << std::endl;
            }
            currentPercent = (int)(moreAfricanProb * 100);
            moreAfricanProb *= 0.99;

        }
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "-----------------------" << std::endl;
    printFirstSSRDis();
    std::cout << "-----------------------" << std::endl;
    for (int num = 80; num < 360; num += 20) {
        std::map<int, int> newNumDis;
        std::map<int, int> newGoodNumDis;
        std::map<int, int> goodNumDis;
        // std::map<int, int> firstSSRDis;

        for (int i = 0; i < NUM_DRAW; ++i) {
            Draw myDraw(num);
            int myNewNum = myDraw.getNewNum();
            int myNewGoodNum = myDraw.getNewGoodNum();
            int myGoodNum = myDraw.getGoodNum();
            // int myFirstSSR = myDraw.getFirstSSR();

            if (newGoodNumDis.find(myNewGoodNum) == newGoodNumDis.end())
                newGoodNumDis[myNewGoodNum] = 1;
            else
                newGoodNumDis[myNewGoodNum]++;

            if (newNumDis.find(myNewNum) == newNumDis.end())
                newNumDis[myNewNum] = 1;
            else
                newNumDis[myNewNum]++;

            if (goodNumDis.find(myGoodNum) == goodNumDis.end())
                goodNumDis[myGoodNum] = 1;
            else
                goodNumDis[myGoodNum]++;

            // if (firstSSRDis.find(myFirstSSR) == firstSSRDis.end())
            //     firstSSRDis[myFirstSSR] = 1;
            // else
            //     firstSSRDis[myFirstSSR]++;

        }
        std::cout << "-----------------------" << std::endl;
        std::cout << "抽花数量：" << num << std::endl;
        std::cout << "new卡数量总和（R+SR+SSR)"<< std::endl;
        printDistribution(newNumDis);
        std::cout << std::endl;
        std::cout << "稀有超稀有new卡数量总和（SR+SSR)"<< std::endl;
        printDistribution(newGoodNumDis);
        std::cout << std::endl;
        std::cout << "稀有超稀有卡数量总和（SR+SSR)"<< std::endl;
        printDistribution(goodNumDis);
        std::cout << std::endl;
        std::cout << "-----------------------" << std::endl;
        // printDistribution(firstSSRDis);
    }
    return 0;

}



Draw::Draw (int inNum) : SSRNum(0), SRNum(0), RNum(0), 
                vecR(NUM_R, 0), vecSR(NUM_SR, 0), vecSSR(NUM_SSR, 0) {
    num = inNum;
    for (int i = 0; i < num; ++i) {
        int randType =  rand() % P_BASE;
        if (randType < P_SSR) {
            int randCard = rand() % NUM_SSR;
            vecSSR[randCard]++;
            SSRNum++;
        }
        else if (randType < (P_SSR + P_SR)) {
            int randCard = rand() % NUM_SR;
            vecSR[randCard]++;
            SRNum++;
        }
        else {
            int randCard = rand() % NUM_R;
            vecR[randCard]++;
            RNum++;
        }

    }
    countNewNum();
}

void Draw::countNewNum() {
    newNum = 0;
    newGoodNum = 0;
    for (int i = 0; i < vecSSR.size(); ++i) {
        if (vecSSR[i]) {
            newNum++;
            newGoodNum++;
        }
    }
    for (int i = 0; i < vecSR.size(); ++i) {
        if (vecSR[i]) {
            newNum++;
            newGoodNum++;
        }
    }
    for (int i = 0; i < vecR.size(); ++i) {
        if (vecR[i])
            newNum++;
    }
}


void printDistribution(std::map<int, int> & disMap) {
    int moreAfricanNum = 0;
    int moreEuropeanNum = NUM_DRAW;
    if (IS_VERBOSE) {
        for (auto it = disMap.begin(); it != disMap.end(); ++it) {
            moreEuropeanNum -= it->second;
            int moreAfricanPercent = (double)moreAfricanNum /  (double)NUM_DRAW * 100;
            int moreEuropeanPercent = (double)moreEuropeanNum / (double)NUM_DRAW * 100;
            if (moreAfricanPercent > 1 &&  moreEuropeanPercent > 1) {
                 std::cout << it->first << ": 比" << moreAfricanPercent
                      << "\%的人更欧，比" << moreEuropeanPercent << "\%的人更非" << std::endl;
            }
            moreAfricanNum += it->second;
        }
    }
    else {
        int currentPercent = 0;
        for (auto it = disMap.begin(); it != disMap.end(); ++it) {
            moreEuropeanNum -= it->second;
            int moreAfricanPercent = (double)moreAfricanNum /  (double)NUM_DRAW * 100;
            int moreEuropeanPercent = (double)moreEuropeanNum / (double)NUM_DRAW * 100;
            int myPercent = (moreAfricanPercent + 100 - moreEuropeanPercent) / 2;
            if (myPercent / 20  == currentPercent / 20 + 1) {
                 std::cout << it->first << ": 欧气打败了" << myPercent / 20 * 20 << "\%的制作人" << std::endl;
                 
            }
            currentPercent = myPercent;
            moreAfricanNum += it->second;
        }
    }
}



















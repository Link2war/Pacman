#include "../include/scoreManager.h"


ScoreManager::ScoreManager() : 
    score(0) 
{
    
}

void ScoreManager::reset() {
    score = 0;
}

void ScoreManager::addGum() {
    score += 10;
}

void ScoreManager::addBigGum() {
    score += 50;
}

void ScoreManager::addCherry() {
    score += 100;
}

int ScoreManager::getScore() const {
    return score;
}
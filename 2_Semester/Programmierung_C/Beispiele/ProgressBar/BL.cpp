//
// Created by Korbinian on 30.04.2024.
//

#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <cmath>

class ProgressBar {
private:
    int maxStep;
    int currStep;

public:
    void setMaxStep(int anz);
    void setCurrStep(int anz);
    void display();
};


int main(){
    ProgressBar b;
    b.setMaxStep(100);

    for(int i= 0; i< 1000; ++i){
        b.setCurrStep(i);
        b.display();
        sleep(1);
    }
    return 1;
}

void ProgressBar::setCurrStep(int anz) {
    this ->currStep = anz;
}

void ProgressBar::setMaxStep(int anz) {
    this ->maxStep = anz;
}

void ProgressBar::display(){
    double currPercentage = (static_cast<double> (this->currStep) / static_cast<double>(this->maxStep));
    std::cout << std::setw(5)<<(currPercentage*100)<<"% ";
    for(int i = 0; i< floor(currPercentage * 15); ++i){
        std::cout << "|";
    }
    std::cout <<"\r";
}
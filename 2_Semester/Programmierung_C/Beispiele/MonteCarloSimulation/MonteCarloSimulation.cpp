#include<iostream>
#include<random>

int main(){
    int inside=0;;
    float coordX;
    float coordY;

    std::string anzSteps;
    std::cout << "num of steps: ";
    std::cin >> anzSteps;

    static std::mt19937 twister(123);
    std::uniform_real_distribution<float> dis(0.0, 1.0);

    for(int i= 1; i<=stoi(anzSteps); ++i){
        coordX = pow(dis(twister), 2);
        coordY = pow(dis(twister), 2);
        if(coordX + coordY <= 1){
            ++inside;
        }
        std::cout << i << ":" << stoi(anzSteps)<<"| inside: " << inside <<" outside: " << i-inside << " | pi = " <<(static_cast<double> (inside) / static_cast<double>(i))*4 <<"\r";
    }
    return 1;
}
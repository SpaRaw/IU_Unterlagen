#include<iostream>
#include<fstream>
#include<iomanip>
int main(){
    std::ofstream file;
    file.open("test.txt");

    file << "Ein mal eins: " << std::endl;
    for (int i = 1; i <=10; i++){
        for(int j = 1; j <=10; j++){
            file << std::setw(3) <<i*j<< " ";
        }
        file << std::endl;
    }

    file << "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet."<<std::endl;
    file.close();
    return 1;
}
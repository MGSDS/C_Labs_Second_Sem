#include <iostream>
#include "Cube.h"
#include "GeneticAlgorithm.h"
#include <ctime>
#include <fstream>

int main() {
    std::cout << "Welcome to cube simulator!\n";
    std::string cmd;
    std::string path;
    RubiksCube::Cube cube;
    while (true){
        std::cin >> cmd;
        if(cmd == "save"){
             std::getline(std::cin, path);
            path = path.substr(1);
            try {
                std::ofstream file(path, std::ios_base::out);
                cube.fileWrite(file);
                file.close();
            } catch(std::exception& e){
                std::cerr << e.what() << '\n';
            }
        } else if (cmd == "load") {
            std::getline(std::cin, path);
            path = path.substr(1);
            try {
                std::ifstream file(path, std::ios_base::in);
                cube.fileRead(file);
                file.close();
            } catch (std::exception &e) {
                std::cerr << e.what() << '\n';
            }
        } else if (cmd == "print") {
            std::cout << cube;
        } else if (cmd == "rotate") {
            std::getline(std::cin, cmd);
            cube.Execute(RubiksCube::str2cmd(cmd));
        } else if (cmd == "scramble") {
            size_t sz;
            std::cin >> sz;
            auto scramble = RubiksCube::Random::GenerateScramble(sz);
            std::cout << RubiksCube::cmd2str(scramble);
            cube.Scramble(scramble);
        } else if (cmd == "solve"){
            try {
                GeneticAlgorithm alg(cube);
                alg.Solve(5, true);
                cube.clear();
            } catch(std::exception& e) {
                std::cerr << e.what() << '\n';
            }
        } else if (cmd == "clear") {
            cube.clear();
         } else if (cmd == "exit") {
            return 0;
        } else {
            std::cerr << "invalid command\n";
        }
    }
}


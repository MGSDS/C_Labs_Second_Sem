//
// Created by Bill Williams on 19.05.2021.
//

#ifndef CUBE_GENETICALGORITHM_H
#define CUBE_GENETICALGORITHM_H

#include "Cube.h"

class GeneticAlgorithm {
    size_t populationSz;
    size_t maxGenerations;
    size_t elitismNum;
    RubiksCube::Cube cube;

    const std::vector<std::string> _premutations = {
            "F' L' B' R' U' R U' B L F R U R' U",
            "F R B L U L' U B' R' F' L' U' L U'",
            "U2 B U2 B' R2 F R' F' U2 F' U2 F R'",
            "U2 R U2 R' F2 L F' L' U2 L' U2 L F'",
            "U' B2 D2 L' F2 D2 B2 R' U'",
            "U B2 D2 R F2 D2 B2 L U",
            "D' R' D R2 U' R B2 L U' L' B2 U R2",
            "D L D' L2 U L' B2 R' U R B2 U' L2",
            "R' U L' U2 R U' L R' U L' U2 R U' L U'",
            "L U' R U2 L' U R' L U' R U2 L' U R' U",
            "F' U B U' F U B' U'",
            "F U' B' U F' U' B U",
            "L' U2 L R' F2 R",
            "R' U2 R L' B2 L",
            "M2 U M2 U2 M2 U M2"
    };

    const std::vector<std::string> _rotations = {"x", "x'", "x2", "y", "y'", "y2"};
    const std::vector<std::string> _orientations = {"z", "z'", "z2"};

    std::vector<std::pair<RubiksCube::Cube, int>> population;
public:
    explicit GeneticAlgorithm( const std::vector<RubiksCube::command> &scramble, size_t populationSz = 1000,
                      size_t maxGenerations = 200, size_t elitismNum = 130);
    explicit GeneticAlgorithm( const RubiksCube::Cube& cube, size_t populationSz = 1000,
                      size_t maxGenerations = 200, size_t elitismNum = 130);

    std::vector<RubiksCube::command> Solve(size_t resetCount = 5, bool verbous = false, std::ostream &out = std::cout);
    std::vector<RubiksCube::command> OneResetSolve(bool verbous = false, std::ostream &out = std::cout);
    void clearPopulation();

private:
    int CalculateFitness(size_t pos);
};


#endif //CUBE_GENETICALGORITHM_H

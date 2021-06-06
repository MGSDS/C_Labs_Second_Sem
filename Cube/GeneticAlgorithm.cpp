//
// Created by Bill Williams on 19.05.2021.
//

#include <iostream>
#include "GeneticAlgorithm.h"

int GeneticAlgorithm::CalculateFitness(size_t pos) {
    int &fit = population.at(pos).second;
    RubiksCube::Cube &cube = population.at(pos).first;

    fit = cube.MaxStatus() * 100;
    if (population.at(pos).second == 700)
        return 9999;
    for (auto &side : cube.GetCube()) {
        for (auto &plate : side) {
            if (plate == side.at(4))
                fit++;
        }
    }
    return fit;
}

std::vector<RubiksCube::command> GeneticAlgorithm::OneResetSolve(bool verbous, std::ostream &out) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist;
        clearPopulation();
        for (int i = 0; i < maxGenerations; ++i) {
            for (int i = elitismNum; i < populationSz; i++) {
                if (CalculateFitness(i) == 9999) {
                    if (verbous)
                        out << "Solution sound in " << population[i].first.GetHistory().size() << " moves: " <<
                            RubiksCube::cmd2str(population[i].first.GetHistory());
                    return population.at(i).first.GetHistory();
                }
            }
            std::sort(population.begin(), population.end(),
                      [](const auto &lhs, const auto &rhs) { return lhs.second > rhs.second; });
            if (i % 10 == 0 && verbous)
                out << "generation: " << i << " Best fitness: " << population.at(0).second << '\n';
            for (int j = elitismNum; j < populationSz; ++j) {
                dist = std::uniform_int_distribution<>(0, elitismNum - 1);
                population.at(j) = population.at(dist(gen));
                dist = std::uniform_int_distribution<>(0, 5);
                switch (dist(gen)) {
                    case 0:
                        dist = std::uniform_int_distribution<>(0, _premutations.size() - 1);
                        population.at(j).first.Execute(RubiksCube::str2cmd(_premutations.at(dist(gen))));
                        break;
                    case 1:
                        dist = std::uniform_int_distribution<>(0, _premutations.size() - 1);
                        population.at(j).first.Execute(RubiksCube::str2cmd(_premutations.at(dist(gen))));
                        population.at(j).first.Execute(RubiksCube::str2cmd(_premutations.at(dist(gen))));
                        break;
                    case 2:
                        dist = std::uniform_int_distribution<>(0, _rotations.size() - 1);
                        population.at(j).first.Execute(RubiksCube::str2cmd(_rotations.at(dist(gen))));
                        dist = std::uniform_int_distribution<>(0, _premutations.size() - 1);
                        population.at(j).first.Execute(RubiksCube::str2cmd(_premutations.at(dist(gen))));
                        break;
                    case 3:
                        dist = std::uniform_int_distribution<>(0, _orientations.size() - 1);
                        population.at(j).first.Execute(RubiksCube::str2cmd(_orientations.at(dist(gen))));
                        dist = std::uniform_int_distribution<>(0, _premutations.size() - 1);
                        population.at(j).first.Execute(RubiksCube::str2cmd(_premutations.at(dist(gen))));
                        break;
                    case 4:
                        dist = std::uniform_int_distribution<>(0, _rotations.size() - 1);
                        population.at(j).first.Execute(RubiksCube::str2cmd(_rotations.at(dist(gen))));
                        dist = std::uniform_int_distribution<>(0, _orientations.size() - 1);
                        population.at(j).first.Execute(RubiksCube::str2cmd(_orientations.at(dist(gen))));
                        dist = std::uniform_int_distribution<>(0, _premutations.size() - 1);
                        population.at(j).first.Execute(RubiksCube::str2cmd(_premutations.at(dist(gen))));
                        break;
                    case 5:
                        dist = std::uniform_int_distribution<>(0, _orientations.size() - 1);
                        population.at(j).first.Execute(RubiksCube::str2cmd(_orientations.at(dist(gen))));
                        dist = std::uniform_int_distribution<>(0, _rotations.size() - 1);
                        population.at(j).first.Execute(RubiksCube::str2cmd(_rotations.at(dist(gen))));
                        dist = std::uniform_int_distribution<>(0, _premutations.size() - 1);
                        population.at(j).first.Execute(RubiksCube::str2cmd(_premutations.at(dist(gen))));
                        break;
                }
            }
        }
        if (verbous) out << "No solution found((\n";
        return std::vector<RubiksCube::command>();
    }

std::vector<RubiksCube::command> GeneticAlgorithm::Solve(size_t resetCount,bool verbous, std::ostream &out) {
    std::vector<RubiksCube::command> res;
    for (int i = 0; i < resetCount; ++i) {
        res = OneResetSolve(verbous, out);
        if(!res.empty())
            return res;
    }
    return res;
}

GeneticAlgorithm::GeneticAlgorithm(const RubiksCube::Cube &cube, size_t populationSz, size_t maxGenerations,
                                   size_t elitismNum) : populationSz(populationSz),
        maxGenerations(maxGenerations), elitismNum(elitismNum){
    this->cube = cube;
    this->cube.clearHistory();

}

GeneticAlgorithm::GeneticAlgorithm(const std::vector<RubiksCube::command> &scramble, size_t populationSz,
                                   size_t maxGenerations, size_t elitismNum)  : populationSz(populationSz),
                                   maxGenerations(maxGenerations), elitismNum(elitismNum) {
    cube.Scramble(scramble);
    cube.clearHistory();
}

void GeneticAlgorithm::clearPopulation() {
    population.resize(populationSz);
    population.at(0).first = cube;
    for (auto p = population.begin() + 1; p != population.end(); ++p) {
        (*p).first = population.at(0).first;
        for (int i = 0; i < 4; ++i) {
            (*p).first.Execute(RubiksCube::Random::GenerateRandomTurn());
        }
    }
}

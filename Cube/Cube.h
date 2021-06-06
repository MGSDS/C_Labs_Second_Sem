//
// Created by Bill Williams on 13.05.2021.
//

#ifndef CUBE_CUBE_H
#define CUBE_CUBE_H

#include <vector>
#include <queue>
#include <random>
#include <string>
#include <unordered_set>
#include <fstream>

namespace RubiksCube {

    enum turn {
        F = 0, L = 1, R = 2, B = 3, U = 4, D = 5, M = 6, E = 7, S = 8, x = 9, y = 10, z = 11
    };

    enum color {
        Green = 0, White = 4, Red = 2, Orange = 1, Blue = 3, Yellow = 5
    };
    enum side {
        Front = 0, Left = 1, Right = 2, Back = 3, Up = 4, Down = 5
    };

    struct command {
        turn side;
        bool opposite = false;
        unsigned int count = 1;
    };

    std::string cmd2str(const std::vector<command> &cmd);

    std::vector<command> str2cmd(std::string);

    class Random {
    public:
        static command GenerateRandomTurn();

        static std::vector<command> GenerateScramble(size_t sz = 10);

    };

    class Cube {
        std::vector<command> _scramble;
        bool _valid;
        std::vector<std::vector<color>> _cube;
        std::vector<command> _cmd;
        const std::vector<std::vector<std::vector<int>>> _turnIndexes = {
                {{6, 7, 8},                   {0, 3, 6},                   {2, 1, 0},                   {8, 5, 2}},
                {{0, 3, 6},                   {0, 3, 6},                   {0, 3, 6},                   {8, 5, 2}},
                {{8, 5, 2},                   {0, 3, 6},                   {8, 5, 2},                   {8, 5, 2}},
                {{2, 1, 0},                   {0, 3, 6},                   {6, 7, 8},                   {8, 5, 2}},
                {{2, 1, 0},                   {2, 1, 0},                   {2, 1, 0},                   {2, 1, 0}},
                {{6, 7, 8},                   {6, 7, 8},                   {6, 7, 8},                   {6, 7, 8}},
                {{7, 4, 1},                   {7, 4, 1},                   {7, 4, 1},                   {1, 4, 7}},
                {{3, 4, 5},                   {3, 4, 5},                   {3, 4, 5},                   {3, 4, 5}},
                {{3, 4, 5},                   {1, 4, 7},                   {5, 4, 3},                   {7, 4, 1}},
                {{0, 1, 2, 3, 4, 5, 6, 7, 8}, {8, 7, 6, 5, 4, 3, 2, 1, 0}, {0, 1, 2, 3, 4, 5, 6, 7, 8}, {0, 1, 2, 3, 4, 5, 6, 7, 8}},
                {{0, 1, 2, 3, 4, 5, 6, 7, 8}, {0, 1, 2, 3, 4, 5, 6, 7, 8}, {0, 1, 2, 3, 4, 5, 6, 7, 8}, {0, 1, 2, 3, 4, 5, 6, 7, 8}},
                {{0, 1, 2, 3, 4, 5, 6, 7, 8}, {2, 5, 8, 1, 4, 7, 0, 3, 6}, {8, 7, 6, 5, 4, 3, 2, 1, 0}, {6, 3, 0, 7, 4, 1, 8, 5, 2}}
        };

        const std::vector<std::vector<std::vector<int>>> _rotationIndexes = {
                {{0, 1, 2, 3, 4, 5, 6, 7, 8}, {2, 5, 8, 1, 4, 7, 0, 3, 6}, {8, 7, 6, 5, 4, 3, 2, 1, 0}, {6, 3, 0, 7, 4, 1, 8, 5, 2}},
                {{2, 5, 8, 1, 4, 7, 0, 3, 6}, {2, 5, 8, 1, 4, 7, 0, 3, 6}, {2, 5, 8, 1, 4, 7, 0, 3, 6}, {6, 3, 0, 7, 4, 1, 8, 5, 2}},
                {{6, 3, 0, 7, 4, 1, 8, 5, 2}, {2, 5, 8, 1, 4, 7, 0, 3, 6}, {6, 3, 0, 7, 4, 1, 8, 5, 2}, {6, 3, 0, 7, 4, 1, 8, 5, 2}},
                {{8, 7, 6, 5, 4, 3, 2, 1, 0}, {2, 5, 8, 1, 4, 7, 0, 3, 6}, {0, 1, 2, 3, 4, 5, 6, 7, 8}, {6, 3, 0, 7, 4, 1, 8, 5, 2}},
                {{8, 7, 6, 5, 4, 3, 2, 1, 0}, {8, 7, 6, 5, 4, 3, 2, 1, 0}, {8, 7, 6, 5, 4, 3, 2, 1, 0}, {8, 7, 6, 5, 4, 3, 2, 1, 0}},
                {{0, 1, 2, 3, 4, 5, 6, 7, 8}, {0, 1, 2, 3, 4, 5, 6, 7, 8}, {0, 1, 2, 3, 4, 5, 6, 7, 8}, {0, 1, 2, 3, 4, 5, 6, 7, 8}}
        };

        const std::vector<side> _oppositeSides = {
                Back, Right, Left, Front, Down, Up
        };

        const std::vector<color> _oppositeCenters ={
                Blue, Red, Orange, Green, Yellow, White
        };


        const std::vector<std::vector<side>> _adjacentSides = {
                {Up,    Right, Down,  Left},
                {Up,    Front, Down,  Back},
                {Up,    Back,  Down,  Front},
                {Up,    Left,  Down,  Right},
                {Back,  Right, Front, Left},
                {Front, Right, Back,  Left},
                {Up,    Front, Down,  Back},
                {Front, Right, Back,  Left},
                {Up,    Right, Down,  Left},
                {Up,    Back,  Down,  Front},
                {Front, Left,  Back,  Right},
                {Up,    Right, Down,  Left}
        };

        const std::vector<std::unordered_set<color>> _cornerBlocks = {
                {White, Orange, Green},
                {White, Green, Red},
                {Red, Yellow, Green},
                {Yellow, Orange, Green},
                {White, Orange, Blue},
                {Red, White, Blue},
                {Yellow, Red, Blue},
                {Orange, Yellow, Blue}
        };

        const std::vector<std::unordered_set<color>> _sideBlocks = {
                {Green, White}, {Green, Red}, {Green, Yellow}, {Green, Orange},
                {White, Orange}, {White, Red}, {Yellow, Red}, {Yellow, Orange},
                {Blue, White}, {Blue, Red}, {Blue, Yellow}, {Blue, Orange},
        };
        const std::vector<std::vector<int>> _sideBlocksIndexes = {
                {1, 7}, {5, 3}, {7, 1}, {3, 5},
                {3, 1}, {5, 1}, {5, 7}, {3, 7},
                {1, 1}, {5, 3}, {7, 7}, {3, 5}
        };

        const std::vector<std::vector<side>> _sideBlocksSides = {
                {Front, Up}, {Front, Right}, {Front, Down}, {Front, Left},
                {Up, Left}, {Up, Right}, {Down, Right}, {Down, Left},
                {Up, Back}, {Right, Back}, {Down, Back}, {Left, Back}
        };

        const std::vector<std::vector<int>> _cornerBlocksIndexes = {
                {0, 6, 2}, {2, 8, 0}, {8, 6, 2}, {6, 0, 8},
                {2, 0, 0}, {0, 2, 2}, {6, 8, 8}, {8, 6, 6}
        };

        const std::vector<std::vector<side>> _cornerBlocksSides = {
                {Front, Up, Left}, {Front, Up, Right}, {Front, Right, Down}, {Front, Down, Left},
                {Back, Up, Left}, {Back, Up, Right}, {Back, Down, Right}, {Back, Down, Left}

        };


    public:
        Cube();

        Cube &operator=(const Cube &rhs);

        void Execute(command cmd);
        void Execute(const std::vector<command> &cmd);
        void Scramble(const std::vector<command> &cmd);

        void Turn(turn t);

        int Status(side s) const;
        int MaxStatus() const;

        bool WhiteCross(side s) const;
        bool WhiteCorners(side s) const;
        bool MiddleEdges(side s) const;
        bool YellowCross(side s) const;
        bool PlaceYellowCorners(side s) const;
        bool YellowCorners(side s) const;
        bool YellowEdges(side s) const;

        bool validate();

        [[nodiscard]] std::vector<std::vector<color>> GetCube() const;
        [[nodiscard]] std::vector<command> GetHistory() const;

        bool fileRead(std::ifstream& f);
        void fileWrite(std::ofstream& f);

        friend std::ostream &operator<<(std::ostream &output, const RubiksCube::Cube &c);

        void clearHistory();

        void clear();


    private:
        void _TurnCW(side s);
        void _TurnCCW(side s);


    };
}
#endif //CUBE_CUBE_H
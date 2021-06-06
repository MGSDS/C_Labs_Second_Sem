#include "Cube.h"
#include <iostream>
#include <sstream>

RubiksCube::Cube::Cube() : _valid(true){
    _cube.resize(6);
    for(int i = 0; i < 6; ++i){
        _cube.at(i).resize(9);
        for(int j = 0; j < 9; ++j){
            _cube.at(i).at(j) = static_cast<color>(i);
        }
    }
}

void RubiksCube::Cube::Turn(turn s) {
    std::queue<color> q;
    if(s <= 5){
        _TurnCW(static_cast<side>(s));
    }
    else if(s >= 9 && s <= 11){
        switch(s){
            case x:
                _TurnCW(Right);
                _TurnCCW(_oppositeSides.at(Right));
                break;
            case y:
                _TurnCW(Up);
                _TurnCCW(_oppositeSides.at(Up));
                break;
            case z:
                _TurnCW(Front);
                _TurnCCW(_oppositeSides.at(Front));
                break;
        }
    }
    for (int i = 0; i < 4; ++i){
        for(int j = 0; j < _turnIndexes.at(s).at(i).size(); ++j){
            q.push(_cube.at(_adjacentSides.at(s).at(i)).at(_turnIndexes.at(s).at(i).at(j)));
        }
    }
    for (int i = 1; i < 4; ++i){
        for(int j = 0; j < _turnIndexes.at(s).at(i).size(); ++j){
            _cube.at(_adjacentSides.at(s).at(i)).at(_turnIndexes.at(s).at(i).at(j)) = q.front();
            q.pop();
        }
    }
    for(int j = 0; j < _turnIndexes.at(s).at(0).size(); ++j){
        _cube.at(_adjacentSides.at(s).at(0)).at(_turnIndexes.at(s).at(0).at(j)) = q.front();
        q.pop();
    }
}

void RubiksCube::Cube::_TurnCW(side s) {
    std::queue<color> q;
    q.push(_cube.at(s).at(0));
    q.push(_cube.at(s).at(1));
    q.push(_cube.at(s).at(2));
    q.push(_cube.at(s).at(5));
    q.push(_cube.at(s).at(8));
    q.push(_cube.at(s).at(7));
    q.push(_cube.at(s).at(6));
    q.push(_cube.at(s).at(3));
    _cube.at(s).at(2) = q.front();
    q.pop();
    _cube.at(s).at(5) = q.front();
    q.pop();
    _cube.at(s).at(8) = q.front();
    q.pop();
    _cube.at(s).at(7) = q.front();
    q.pop();
    _cube.at(s).at(6) = q.front();
    q.pop();
    _cube.at(s).at(3) = q.front();
    q.pop();
    _cube.at(s).at(0) = q.front();
    q.pop();
    _cube.at(s).at(1) = q.front();
    q.pop();

}

void RubiksCube::Cube::Execute(RubiksCube::command cmd) {
    _cmd.push_back(cmd);
    if (cmd.opposite) {
        cmd.count *= 3;
    }
    cmd.count %= 4;
    for (int i = 0; i < cmd.count; ++i) {
        Turn(cmd.side);
    }
}

void RubiksCube::Cube::Execute(const std::vector<command> &cmd) {
    for (auto& c : cmd) {
        Execute(c);
    }
}

void RubiksCube::Cube::_TurnCCW(RubiksCube::side s) {
    std::queue<color> q;
    q.push(_cube.at(s).at(2));
    q.push(_cube.at(s).at(1));
    q.push(_cube.at(s).at(0));
    q.push(_cube.at(s).at(3));
    q.push(_cube.at(s).at(6));
    q.push(_cube.at(s).at(7));
    q.push(_cube.at(s).at(8));
    q.push(_cube.at(s).at(5));
    _cube.at(s).at(0) = q.front();
    q.pop();
    _cube.at(s).at(3) = q.front();
    q.pop();
    _cube.at(s).at(6) = q.front();
    q.pop();
    _cube.at(s).at(7) = q.front();
    q.pop();
    _cube.at(s).at(8) = q.front();
    q.pop();
    _cube.at(s).at(5) = q.front();
    q.pop();
    _cube.at(s).at(2) = q.front();
    q.pop();
    _cube.at(s).at(1) = q.front();
    q.pop();
}

std::vector<std::vector<RubiksCube::color>> RubiksCube::Cube::GetCube() const {
    return _cube;
}

void RubiksCube::Cube::clear() {
    _scramble.clear();
    _cmd.clear();
    _cube.resize(6);
    for(int i = 0; i < 6; ++i){
        _cube.at(i).resize(9);
        for(int j = 0; j < 9; ++j){
            _cube.at(i).at(j) = static_cast<color>(i);
        }
    }
}

void RubiksCube::Cube::Scramble(const std::vector<command> &cmd) {
    clear();
    _scramble = cmd;
    for (auto& c : cmd) {
        int count;
        count = c.count;
        if (c.opposite) {
            count *= 3;
        }
        count %= 4;
        for (int i = 0; i < count; ++i) {
            Turn(c.side);
        }
    }
}

std::vector<RubiksCube::command> RubiksCube::Cube::GetHistory() const {
    return _cmd;
}

RubiksCube::Cube& RubiksCube::Cube::operator=(const Cube& rhs) {
    if(!rhs._valid)
        throw std::invalid_argument("Assignment of invalid cube");
    _cube = rhs._cube;
    _valid = true;
    _cube = rhs._cube;
    _scramble = rhs._scramble;
    _cmd = rhs._cmd;
    return *this;
}

bool RubiksCube::Cube::WhiteCross(RubiksCube::side s) const{
    color sideColor = _cube[s][4];
    if(_cube[s][1] != sideColor || _cube[s][7] != sideColor || _cube[s][3] != sideColor || _cube[s][5] != sideColor)
        return false;
    for (int i = 0; i < _adjacentSides[s].size(); ++i) {
        side adjacentSide = _adjacentSides[s][i];
        sideColor = _cube[adjacentSide][4];
        if(_cube[adjacentSide][_rotationIndexes[s][i][7]] != sideColor)
            return false;
    }
    return true;
}

bool RubiksCube::Cube::WhiteCorners(RubiksCube::side s) const{
    color sideColor = _cube[s][4];
    if(_cube[s][0] != sideColor || _cube[s][2] != sideColor || _cube[s][8] != sideColor || _cube[s][6] != sideColor)
        return false;
    for (int i = 0; i < _adjacentSides[s].size(); ++i){
        side adjacentSide = _adjacentSides[s][i];
        sideColor = _cube[adjacentSide][4];
        if(_cube[adjacentSide][_rotationIndexes[s][i][6]] != sideColor || _cube[adjacentSide][_rotationIndexes[s][i][8]] != sideColor)
            return false;
    }
    return true;
}

bool RubiksCube::Cube::PlaceYellowCorners(RubiksCube::side s) const{
    color sideColor = _cube[_oppositeSides[s]][4];
    if(_cube[_oppositeSides[s]][0] != sideColor ||_cube[_oppositeSides[s]][2] != sideColor ||
       _cube[_oppositeSides[s]][8] != sideColor || _cube[_oppositeSides[s]][6] != sideColor)
        return false;
    return true;
}

bool RubiksCube::Cube::YellowCorners(RubiksCube::side s) const{
    color sideColor;
    for (int i = 0; i < _adjacentSides[s].size(); ++i) {
        side adjacentSide = _adjacentSides[s][i];
        sideColor = _cube[adjacentSide][4];
        if(_cube[adjacentSide][_rotationIndexes[s][i][0]] != sideColor || _cube[adjacentSide][_rotationIndexes[s][i][2]] != sideColor)
            return false;
    }
    return true;
}

bool RubiksCube::Cube::YellowEdges(RubiksCube::side s) const{
    color sideColor;
    for (int i = 0; i < _adjacentSides[s].size(); ++i) {
        side adjacentSide = _adjacentSides[s][i];
        sideColor = _cube[adjacentSide][4];
        if(_cube[adjacentSide][_rotationIndexes[s][i][1]] != sideColor)
            return false;
    }
    return true;
}

bool RubiksCube::Cube::MiddleEdges(RubiksCube::side s) const{
    color sideColor;
    for (int i = 0; i < _adjacentSides[s].size(); ++i) {
        side adjacentSide = _adjacentSides[s][i];
        sideColor = _cube[adjacentSide][4];
        if(_cube[adjacentSide][_rotationIndexes[s][i][3]] != sideColor || _cube[adjacentSide][_rotationIndexes[s][i][5]] != sideColor)
            return false;
    }
    return true;
}

bool RubiksCube::Cube::YellowCross(RubiksCube::side s) const{
    color sideColor = _cube[_oppositeSides[s]][4];
    if(_cube[_oppositeSides[s]][1] != sideColor ||_cube[_oppositeSides[s]][7] != sideColor ||
       _cube[_oppositeSides[s]][3] != sideColor || _cube[_oppositeSides[s]][5] != sideColor)
        return false;
    return true;
}

int RubiksCube::Cube::Status(RubiksCube::side s) const{
    int st = 0;
    if(WhiteCross(s)) st++;
    else return st;
    if(WhiteCorners(s)) st++;
    else return st;
    if(MiddleEdges(s)) st++;
    else return st;
    if(YellowCross(s)) st++;
    else return st;
    if(PlaceYellowCorners(s)) st++;
    else return st;
    if(YellowCorners(s)) st++;
    else return st;
    if(YellowEdges(s)) st++;
    return st;
}

int RubiksCube::Cube::MaxStatus() const{
    int res = 0;
    for (int s = 0; s < 6; s++){
        res = std::max(res,
        Status(static_cast<side>(s)));
        if(res == 7)
            return res;
    }
    return res;
}

bool RubiksCube::Cube::validate() {

    if(_valid)
        return true;

    std::vector<size_t> colors(6);

    for (int i = 0; i < _cornerBlocksIndexes.size(); ++i) {
        std::unordered_set<color> tmp;
        for (int j = 0; j < _cornerBlocksIndexes.at(i).size(); ++j) {
            color clr = _cube.at(_cornerBlocksSides.at(i).at(j)).at(_cornerBlocksIndexes.at(i).at(j));
            tmp.insert(clr);
            colors.at(clr)++;
        }
        if (std::find(_cornerBlocks.begin(), _cornerBlocks.end(), tmp) == _cornerBlocks.end()){
            return false;
        }
    }

    for (int i = 0; i < _sideBlocksIndexes.size(); ++i) {
        std::unordered_set<color> tmp;
        for (int j = 0; j < _sideBlocksIndexes.at(i).size(); ++j) {
            color clr = _cube.at(_sideBlocksSides.at(i).at(j)).at(_sideBlocksIndexes.at(i).at(j));
            tmp.insert(clr);
            colors.at(clr)++;
        }
        if (std::find(_sideBlocks.begin(), _sideBlocks.end(), tmp) == _sideBlocks.end()){
            return false;
        }
    }

    for (int i = 0; i < _cube.size(); ++i) {
        if(_oppositeSides.at(_cube.at(i).at(4)) != _cube.at(_oppositeSides.at(i)).at(4)){
            return false;
        }
    }

    if(std::find_if_not(colors.begin(), colors.end(), [](int e){return e == 8;}) != colors.end())
        return false;
    _valid = true;
    return true;
}



std::ostream &RubiksCube::operator<<(std::ostream &output, const RubiksCube::Cube &c) {
    for (int i = 0; i < 3; ++i){
        output <<"       ";
        for (int j = 0; j < 3; ++j){
            output << c._cube.at(RubiksCube::side::Up).at(i*3 + j) << ' ';
        }
        output << '\n';
    }

    int tmpSides[] = {1, 0, 2, 3};
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 4; ++j){
            for (int k = 0; k < 3; ++k) {
                output << c._cube.at(tmpSides[j]).at(i * 3 + k) << ' ';
            }
            output << ' ';
        }
        output << '\n';
    }
    for (int i = 0; i < 3; ++i){
        output <<"       ";
        for (int j = 0; j < 3; ++j){
            output << c._cube.at(RubiksCube::side::Down).at(i*3 + j) << ' ';
        }
        output << '\n';
    }
    output << '\n';
    return output;
}

void RubiksCube::Cube::fileWrite(std::ofstream& f) {
    if(!f)
        throw std::invalid_argument("File can not be opened");
    for (const auto & i : _cube) {
        for (auto j : i) f << static_cast<int>(j) << ' ';
    }
}

bool RubiksCube::Cube::fileRead(std::ifstream &f) {
    if(!f)
        throw std::invalid_argument("File can not be opened");
    _valid = false;
    for(auto& i : _cube){
        for (auto& j : i) {
            int t;
            f >> t;
            if(!(t < 6 && t >= 0)){
                throw std::invalid_argument("invalid color");
            }
            j = static_cast<RubiksCube::color>(t);
        }
    }
    return validate();
}

void RubiksCube::Cube::clearHistory() {
    _scramble.clear();
    _cmd.clear();
}


RubiksCube::command RubiksCube::Random::GenerateRandomTurn() {
    command cmd;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 11);
    cmd.side = static_cast<turn>(dist(gen));
    dist = std::uniform_int_distribution<>(0, 1);
    cmd.opposite = dist(gen);
    if(!cmd.opposite) {
        dist = std::uniform_int_distribution<>(1, 2);
        cmd.count = dist(gen);
    }
    return cmd;
}

std::vector<RubiksCube::command> RubiksCube::Random::GenerateScramble(size_t sz) {
    std::vector<command> vec(sz);
    for (auto& cmd : vec) {
        cmd = GenerateRandomTurn();
    }
    return vec;
}

std::string RubiksCube::cmd2str(const std::vector<command> &cmd) {
    std::string str;
    for (auto& c : cmd) {
        switch (c.side) {
            case F:
                str+='F';
                break;
            case L:
                str+='L';
                break;
            case R:
                str+='R';
                break;
            case B:
                str+='B';
                break;
            case U:
                str+='U';
                break;
            case D:
                str+='D';
                break;
            case M:
                str+='M';
                break;
            case E:
                str+='E';
                break;
            case S:
                str+='S';
                break;
            case x:
                str+='x';
                break;
            case y:
                str+='y';
                break;
            case z:
                str+='z';
                break;
        }
        if (c.count != 1)
            str += std::to_string(c.count);
        if(c.opposite)
            str+='\'';
        str += ' ';
    }
    return str;
}

std::vector<RubiksCube::command> RubiksCube::str2cmd(std::string str) {
    std::vector<command> cmd;
    std::istringstream iss(str);
    std::vector<std::string> vec;
    copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
                 back_inserter(vec));
    cmd.reserve(vec.size());
    for (auto& s : vec) {
        if(s.empty() || s.size() > 2){
            throw std::invalid_argument("Invalid command");
        }
        cmd.emplace_back();
        switch (s[0]) {
            case 'F':
                cmd.back().side = static_cast<turn>(0);
                break;
            case 'L':
                cmd.back().side = static_cast<turn>(1);
                break;
            case 'R':
                cmd.back().side = static_cast<turn>(2);
                break;
            case 'B':
                cmd.back().side = static_cast<turn>(3);
                break;
            case 'U':
                cmd.back().side = static_cast<turn>(4);
                break;
            case 'D':
                cmd.back().side = static_cast<turn>(5);
                break;
            case 'M':
                cmd.back().side = static_cast<turn>(6);
                break;
            case 'E':
                cmd.back().side = static_cast<turn>(7);
                break;
            case 'S':
                cmd.back().side = static_cast<turn>(8);
                break;
            case 'x':
                cmd.back().side = static_cast<turn>(9);
                break;
            case 'y':
                cmd.back().side = static_cast<turn>(10);
                break;
            case 'z':
                cmd.back().side = static_cast<turn>(11);
                break;
            default:
                std::cout << s;
                throw std::invalid_argument("Invalid command");
        }
        if(s.size() == 2){
            switch (s[1]) {
                case '2':
                    cmd.back().count = 2;
                    break;
                case '\'':
                    cmd.back().opposite = true;
                    break;
                default:
                    std::cout << s[1];
                    throw std::invalid_argument("Invalid command");
            }
        }
    }
    return cmd;
}

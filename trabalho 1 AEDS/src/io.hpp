#ifndef IO_HPP
#define IO_HPP
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

using Matriz = std::vector<std::vector<int>>;

struct Arquivo {
    int N, M;         
    int fogoLinha, fogoCol; 
    Matriz forest;      
};

class IO {
public:

    static void logError(const std::string &filename, const std::string &errorMessage);
    static Arquivo readInput(const std::string &filename);
    static void initOutput(const std::string &filename);
    static void writeOutput(const std::string &filename,
                            const Matriz &forest,
                            int iteration);
};
#endif 
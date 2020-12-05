#ifndef OFCT_TEAM_GENERATOR_INPUT_H
#define OFCT_TEAM_GENERATOR_INPUT_H

#include <cinttypes>
#include <fstream>
#include <iostream>
#include <type_traits>
#include <vector>

#include "user.h"

namespace OFCT {

    enum class input_method {
        TEST,
        FILE,
    };

    constexpr auto input_method_test = input_method::TEST;
    constexpr auto input_method_file = input_method::FILE;

    template<input_method method, typename... Args>
    void user_input(Args&&... args);

    template<>
    void user_input<input_method_test>(uint32_t &M, uint32_t &N, std::vector<user> &users) {
        std::cout << "This is a demo of the program." << std::endl;

        M = 3;
        N = 4;

        users.reserve(M * N);
        for(int i = 0; i < M; i++) {
            for(int j = 0; j < N; j++) {
                users.emplace_back((char)(i + 'a') + std::to_string(j), 10000 * i + rand() % 10000);
            }
        }
    }

    template<>
    void user_input<input_method_file>(uint32_t &M, uint32_t &N, std::vector<user> &users, std::ifstream &file) {
        // Input as Comma Separated Values

        std::string line;

        // M,N
        std::getline(file, line);

        for(size_t i = 0; i < line.length(); i++) {
            if(line[i] == ',') {
                M = std::stoul(line.substr(0, i));
                N = std::stoul(line.substr(i+1));
                break;
            }
        }

        // `username`,`number`
        while(std::getline(file, line)) {
            size_t const l = line.length();
            for(size_t i = 0; i < l; i++) {
                if(line[i] == ',') {
                    users.emplace_back(line.substr(0, i), std::stoul(line.substr(i+1)));
                    break;
                }
            }
        }

        std::sort(users.begin(), users.end());
    }
}

#endif
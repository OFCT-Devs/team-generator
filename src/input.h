#ifndef OFCT_TEAM_GENERATOR_INPUT_H
#define OFCT_TEAM_GENERATOR_INPUT_H

#include <cinttypes>
#include <fstream>
#include <iostream>
#include <vector>

#include "user.h"

namespace OFCT {

    enum class input_method {
        TEST,
        FILE,
    };

    constexpr auto input_method_none = input_method::TEST;
    constexpr auto input_method_file = input_method::FILE;

    template<input_method method, typename... Args>
    std::vector<user> user_input(Args... args);

    template<>
    std::vector<user> user_input<input_method_none>(uint32_t M, uint32_t N) {
        std::cout << "This is a demo of the program." << std::endl;

        std::vector<user> users;
        users.reserve(M * N);
        for(int i = 0; i < M; i++) {
            for(int j = 0; j < N; j++) {
                users.emplace_back((char)(i + 'a') + std::to_string(j), 10000 * i + rand() % 10000);
            }
        }
        return users;
    }

    template<>
    std::vector<user> user_input<input_method_file>(std::fstream &file) {
        // TODO
    }
}

#endif
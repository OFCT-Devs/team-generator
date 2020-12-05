#include "ortools/linear_solver/linear_solver.h"

#include <memory>
#include <vector>

#include "core.h"
#include "user.h"
#include "input.h"

int main(int argc, char* argv[]) {
    using namespace OFCT;
    std::vector<user> users;
    /// M denotes the number of people in each team, or the number of seeds.
    /// N denotes the number of teams, or the number of people in each seed.
    uint32_t M, N;
    OFCT::input_method input_method;

    if(argc > 1 && argv[1] != nullptr && ::strcmp(argv[1], "--file") == 0) {
        input_method = input_method_file;
        std::ifstream file(argv[2]);
        if(!file) {
            std::cerr << "Failed loading file " << argv[2] << std::endl;
            return 1;
        }
        user_input<input_method_file>(M, N, users, file);
        file.close();
    }
    else {
        input_method = input_method_test;
        user_input<input_method_test>(M, N, users);
    }

    auto res = OFCT::Program(users, M, N);

    std::vector<std::vector<user>> team(N);
    for(int i = 0; i < N; i++) {
        team[i] = std::vector<user>();
    }

    assert(res.size() == M * N);
    for(int i = 0; i < M * N; i++) {
        assert(res[i].size() == N);
        for(int j = 0; j < N; j++) {
            if(res[i][j] == 1) {
                team[j].emplace_back(users[i]);
                break;
            }
        }
    }

    std::cout << "RESULT:\n\n";
    for(int i = 0; i < N; i++) {
        std::cout << "team " << i + 1 << '\t';
        uint32_t sum = 0;
        for(int j = 0; j < M; j++) {
            std::cout << team[i][j] << ' ';
            sum += team[i][j].get_mmr();
        }
        std::cout << "\tsum = " << sum << std::endl;
    }

    /// | team 1 |         | team 2 |         | team 3 |         |
    /// | name 1 |  mmr 1  | name 2 |  mmr 2  | name 3 |  mmr 3  |
    /// | name 4 |  mmr 4  | name 5 |  mmr 5  | name 6 |  mmr 6  |
    /// ...
    /// |        |  sum 1  |        |  sum 2  |        |  sum 3  |

    switch(input_method) {
        case input_method_file: {
            std::ofstream of("out.csv");

            for(int i = 0; i < N; i++) {
                of << "team " << i + 1 << ",,";
            }
            of << '\n';
            
            for(int j = 0; j < M; j++) {
                for(int i = 0; i < N; i++) {
                    of << team[i][j];
                }
                of << '\n';
            }

            for(int i = 0; i < N; i++) {
                uint32_t sum = 0;
                for(int j = 0; j < M; j++) {
                    sum += team[i][j].get_mmr();
                }
                of << ',' << sum << ',';
            }

            of.close();
        } break;

        default:
        break;
    }

    return EXIT_SUCCESS;
}
#include "ortools/linear_solver/linear_solver.h"

#include <memory>
#include <vector>

#include "user.h"
#include "input.h"

namespace operations_research {
    auto const infinity = MPSolver::infinity();
    using namespace OFCT;
    std::vector<std::vector<uint32_t>> Program(std::vector<user> const &users /* sorted < */,
      uint32_t M /* Number of people in each team OR Number of seeds */,
      uint32_t N /* Number of teams OR Number of people in each seed */) {
        MPSolver solver("OFCT_mip_team_generator", MPSolver::SCIP_MIXED_INTEGER_PROGRAMMING);

        auto const upper = solver.MakeIntVar(0.0, infinity, "upper");
        auto const lower = solver.MakeIntVar(0.0, infinity, "lower");

        auto uservar_matrix = std::make_unique<std::unique_ptr<MPVariable*[]>[]>(N);
        for(uint32_t i = 0; i < N; i++) {
            uservar_matrix[i] = std::make_unique<MPVariable*[]>(M * N);
            for(uint32_t j = 0; j < M * N; j++) {
                uservar_matrix[i][j] = solver.MakeIntVar(0.0, 1.0, "x[" + std::to_string(i) + "," + std::to_string(j) + "]");
            }
        }

        LOG(INFO) << "Number of variables = " << solver.NumVariables();

        std::vector<MPConstraint*> constraints;
        for(uint32_t i = 0; i < M * N; i++) {
            constraints.emplace_back(
                solver.MakeRowConstraint(1.0, 1.0, "each_user_only_in_single_team_" + std::to_string(i))
            );
            for(uint32_t j = 0; j < N; j++) {
                constraints.back()->SetCoefficient(uservar_matrix[j][i], 1);
            }
        }

        for(uint32_t i = 0; i < M; i++) { // for each seed
            for(uint32_t j = 1; j < N; j++) { // for each user in seed 
                01234567; // j + i * N
                // constraints[offset + ]
                for(uint32_t k = 0; k < j; k++) { // for corresponding user
                    for(uint32_t l = 0; l < N; l++) { // for each team
                        constraints.emplace_back(
                            solver.MakeRowConstraint(0.0, 1.0,
                                "each_team_contains_exactly_one_user_in_seed_" + std::to_string(i * N * (N - 1) / 2 + j * (j - 1) / 2 + k))
                        );
                        constraints.back()->SetCoefficient(uservar_matrix[l][i * N + j], 1);
                        constraints.back()->SetCoefficient(uservar_matrix[l][i * N + k], 1);
                    }
                }
            }
        }

        for(uint32_t i = 0; i < N; i++) {
            constraints.emplace_back(
                solver.MakeRowConstraint(0.0, infinity,
                    "value_of_team_not_smaller_than_lower_" + std::to_string(i))
            );
            for(uint32_t j = 0; j < M * N; j++) {
                constraints.back()->SetCoefficient(uservar_matrix[i][j], users[j].get_mmr());
            }
            constraints.back()->SetCoefficient(lower, -1);
        }

        for(uint32_t i = 0; i < N; i++) {
            constraints.emplace_back(
                solver.MakeRowConstraint(0.0, infinity,
                    "value_of_team_not_bigger_than_higher_" + std::to_string(i))
            );
            for(uint32_t j = 0; j < M * N; j++) {
                constraints.back()->SetCoefficient(uservar_matrix[i][j], -1.0 * users[j].get_mmr());
            }
            constraints.back()->SetCoefficient(upper, 1);
        }

        auto const objective = solver.MutableObjective();
        objective->SetCoefficient(upper, 1);
        objective->SetCoefficient(lower, -1);
        objective->SetMinimization();

        solver.Solve();

        std::vector<std::vector<uint32_t>> res;

        LOG(INFO) << "Solution:" << std::endl;
        LOG(INFO) << "Objective value = " << objective->Value();
        LOG(INFO) << "upper = " << upper->solution_value();
        LOG(INFO) << "lower = " << lower->solution_value();

        LOG(INFO) << "Matrix:" << std::endl;
        for(uint32_t i = 0; i < M * N; i++) {
            res.emplace_back();
            for(uint32_t j = 0; j < N; j++) {
                auto const sol_val = uservar_matrix[j][i]->solution_value();
                std::cout << sol_val << ' ';
                res.back().emplace_back(sol_val);
            }
            std::cout << std::endl;
        }

        return res;
    }
}

constexpr uint32_t M = 5;
constexpr uint32_t N = 5;

int main() {
    using namespace OFCT;
    std::vector<user> users(std::move(user_input<input_method_none>(M, N)));
    auto res = operations_research::Program(users, M, N);

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

  return EXIT_SUCCESS;
}
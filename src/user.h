#ifndef OFCT_TEAM_GENERATOR_USER_H
#define OFCT_TEAM_GENERATOR_USER_H

#include <cinttypes>
#include <compare>
#include <ostream>
namespace OFCT {
    class user {
    public:
        user() {}
        explicit user(std::string username, uint32_t mmr);
        user(user const&) = default;
        user(user&&) = default;
        user &operator=(user const&) = default;
        user &operator=(user&&) = default;
        ~user() = default;

        auto operator<=>(user const&) const = default;
        uint32_t get_mmr() const noexcept;
        friend std::ostream &operator<<(std::ostream &os, user const &user);

    private:
        uint32_t mmr;
        std::string username;
    };

    user::user(std::string username, uint32_t mmr) : username(username), mmr(mmr) {}

    uint32_t user::get_mmr() const noexcept {
        return mmr;
    }

    std::ostream &operator<<(std::ostream &os, user const &user) {
        os << user.username << ":\t" << user.mmr << '\t';
        return os;
    }
}

#endif
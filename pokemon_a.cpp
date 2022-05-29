#include <map>
#include <ranges>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "pokemon.hpp"

auto entwicklungen = get_entwicklung();
auto pokemon = get_pokemon();

template <std::ranges::input_range R> 
class view_entwickle : public std::ranges::view_base  {
private:
    struct data_members_t {
        R r;
    };
    std::shared_ptr<data_members_t> data_members;

    struct iterator_type : std::ranges::iterator_t<R> {

        using base = std::ranges::iterator_t<R>;

        iterator_type() = default;
        iterator_type(base const & b) : base{b} {}

        iterator_type operator++(int) {
            return static_cast<base&>(*this)++;
        }

        iterator_type& operator++() {
            auto orig = ++static_cast<base&>(*this);
            return (*this);
        }

        Pokemon operator*() const {
            auto original = *static_cast<base>(*this);
            auto entwicklung_id = entwicklungen[original.id].pokemon_id;
            auto it = std::ranges::find(pokemon, entwicklung_id, &Pokemon::id);
            if (it == pokemon.end()) {
                return Pokemon{};
            }
            return *it;
        }
    };
public:
    using iterator          = iterator_type;
    using const_iterator    = iterator_type;
    view_entwickle() = default;
    view_entwickle(view_entwickle const & rhs) = default;
    view_entwickle(view_entwickle && rhs) = default;
    view_entwickle & operator=(view_entwickle const & rhs) = default;
    view_entwickle & operator=(view_entwickle && rhs) = default;
    ~view_entwickle() = default;
    view_entwickle(R && r) : data_members{new data_members_t{std::forward<R>(r)}} {}

    iterator begin() const {
        return std::begin(data_members->r);
    }
    
    iterator end() const {
        return std::end(data_members->r);
    }

};

template <typename R>
view_entwickle(R &&) -> view_entwickle<R>;

struct entwickle_view_fn
{
    template <typename R>
    auto operator()(R && r) const {
        return view_entwickle{std::forward<R>(r)};
    }
    
    template <typename R>
    friend auto operator|(R && r, entwickle_view_fn const &) {
        return view_entwickle{std::forward<R>(r)};
    }
};

namespace view {
    entwickle_view_fn entwickle;
}

int main() {
    auto pokemon = get_pokemon();

    auto view = pokemon | view::entwickle | std::views::filter([](const auto& p){return p.id != 0; });

    for (const auto& p : view) {
        std::cout << p << std::endl;
    }

    return 0;
}
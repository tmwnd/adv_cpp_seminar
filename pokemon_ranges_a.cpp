#include <ranges>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

#include "pokemon.hpp"

int main() {
    auto pokemon = get_pokemon();

    std::vector<Pokemon> starter;

    auto filter_starter = [] (const Pokemon& p) {return p.id <= 9;};
    auto type_value = [] (const Pokemon& p) {return p.primaer_typ * 100 + p.sekundaer_typ;};
    auto sort_type = [&type_value] (const Pokemon& p1, const Pokemon& p2) {return type_value(p1) < type_value(p2);};
    auto find_best = [] (const Pokemon& p) {return p.id == 4;};

    std::ranges::copy_if(pokemon, std::back_inserter(starter), filter_starter);

    std::ranges::sort(starter, sort_type);
    
    auto it_best = std::ranges::find_if(starter, find_best);
    
    const auto [min, max] = std::ranges::minmax_element(starter, {}, &Pokemon::id);

    std::cout << "bester starter:" << std::endl;
    std::cout << *it_best << std::endl << std::endl;

    std::cout << "min/max starter:" << std::endl;
    for (const auto& it : {min, max})
        std::cout << *it << std::endl;
    std::cout << std::endl;

    std::cout << "starter:" << std::endl;
    for (auto it = starter.begin(); it != starter.end(); ++it)
        std::cout << *it << std::endl;
    std::cout << std::endl;

    return 0;
}
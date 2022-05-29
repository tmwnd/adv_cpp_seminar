#include <algorithm>
#include <iostream>
#include <map>
#include <ranges>
#include <vector>

#include "pokemon.hpp"

// Author: Felix Racz

int main() {
    auto pokemon = get_pokemon();
    auto entwicklungen = get_entwicklung();

    auto feuer = pokemon | std::views::filter([](const Pokemon& p) {
                     return p.primaer_typ == Typ::Feuer;
                 });

    auto levels = feuer |
                  std::views::transform([&entwicklungen](const Pokemon& p) {
                      return entwicklungen[p.id].level;
                  }) |
                  std::views::filter([](const int& l) { return l > 0; });

    size_t size{0};
    int level{0};
    for (int l : levels) {
        level += l;
        size++;
    }
    std::cout << "Durchschnittliches Entwicklungslevel: "
              << (double)level / size << std::endl;
}
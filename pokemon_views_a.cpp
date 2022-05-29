#include <algorithm>
#include <iostream>
#include <map>
#include <ranges>
#include <vector>

#include "pokemon.hpp"

// Author: Felix Racz

/*
    Wir haben einen Vector von Pokémon.
    
    Wir wollen wissen was das durchschnittliche Entwicklungslevel aller Pokémon mit Primärtyp Feuer.
    Dafür gehen Sie wie folgt vor:

    Aufgaben:
        a) Erstellen Sie zuerst eine View die alle Pokémon mit Primärtyp Feuer enthält.
        b) Transformieren Sie die View sodass Sie zu jedem Pokémon das Entwicklungslevel erhalten.
        c) Filtern sie nun alle Pokémon die sich nicht entwickeln (diese haben das Entwicklungslevel 0). (Sie können auch Schritt 2 und 3 tauschen)
        d) Addieren Sie nun alle Entwicklungslevel und dividieren durch die Anzahl der Pokémon.
           (Das zusammenaddieren geht leider noch nicht mit ranges, da ranges für die Algorithmen in <numeric> vermutlich erst mit c++23 kommt.
           Wir können das aber anstattdessen mit einer For-Schleife machen.)

    Hinweise:
        i) eine .size() Methode gibt es nicht, da durch das Filtern die Anzahl der Elemente verloren geht.
           Unsere View ist also keine sized_range mehr, da die Größe nicht mehr in konstanter Zeit berechenbar ist.
           Sie müssen die Länge des Views also auch selber berechnen.
*/

int main() {
    auto pokemon = get_pokemon();
    auto entwicklungen = get_entwicklung();

    //1)
    auto feuer = pokemon | std::views::filter([](const Pokemon& p) { return p.primaer_typ == Typ::Feuer; });

    //2)
    auto levels = feuer | std::views::transform([&entwicklungen](const Pokemon& p) { return entwicklungen[p.id].level; }) | std::views::filter([](const int& l) { return l > 0; });

    //3)
    size_t size{0};
    int level{0};
    for (int l : levels) {
        level += l;
        size++;
    }
    std::cout << "Durchschnittliches Entwicklungslevel: " << (double) level / size << std::endl;
}
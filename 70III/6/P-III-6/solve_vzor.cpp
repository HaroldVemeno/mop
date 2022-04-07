#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    map<int, int> q;

    for (int i = 0; i < k; i++) {
        int s, o, d;
        cin >> s >> o >> d;

        // Konvertujeme časy
        int t1 = o - s + 1;
        int t2 = d - s + 1;

        // Ořežeme intervaly na platný rozsah
        t1 = max(t1, 1);
        t2 = min(t2, m);

        // Zbylo po ořezání něco?
        if (t1 <= t2) {
            // Pokud klíč x není v q, je q[x] == 0. Přičtení jedničky pak v takovém
            // případě nastaví q[x] = 1.
            q[t1] += 1;
            q[t2 + 1] -= 1;
        }
    }

    int vysledek = 0;
    int ted = 0;

    // Projdi vzestupně všechny dvojice e == (klíč, hodnota) v q
    for (auto& e : q) {
        ted += e.second;

        vysledek = max(vysledek, ted);
    }

    cout << vysledek << endl;
}

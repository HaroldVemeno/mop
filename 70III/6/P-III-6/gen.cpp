// Autor generatoru: Václav Volhejn

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// rand() nepouzivame, napr. protoze neni definovane, jak velka cisla muze
// vracet
#define rand(x) ("Misto rand() prosim pouzivej funkce rand* definovane zde", +)
#define ll long long
using namespace std;

#define rep(i, a, n) for (int i = a; i < (int)(n); i++)

// Generator nahodnych cisel
std::mt19937_64 rng;

ll randRange(ll from, ll to) {
    // Vrati nahodny long long v intervalu [from, to] (tj. vcetne `to`).
    std::uniform_int_distribution<ll> dist(from, to);
    return dist(rng);
}

double randDouble(double from, double to) {
    // Vrati nahodny double v intervalu [from, to), (tj. bez `to`).
    std::uniform_real_distribution<double> dist(from, to);
    return dist(rng);
}

ll randAlmost(ll to, double min_part = 0.9) {
    // Vrati nahodny long long ktery je v nejakem smyslu "skoro tak velky" jako
    // `to`, konkretne vrati cislo v intervalu [floor(value*min_part), value].
    // Uzitecne napr. pro generovani velikosti problemu
    assert(to >= 1);
    return randRange(min_part * to, to);
}

bool randBool(double p = 0.5) {
    // Vrati true s pravdepodobnosti p a false s pravdepodobnosti 1-p
    return randDouble(0, 1) <= p;
}

vector<ll> randDifferentNumbers(ll from, ll to, int k) {
    // Vrati k ruznych nahodnych cisel z intervalu [from, to]
    // Implementace podle:
    // https://www.gormanalysis.com/blog/random-numbers-in-cpp/

    unordered_set<ll> samples;
    ll n = to - from + 1;
    assert(n >= k);

    for (ll r = n - k; r < n; ++r) {
        ll v = uniform_int_distribution<ll>(from, from + r)(rng);
        if (!samples.insert(v).second)
            samples.insert(from + r);
    }

    vector<ll> result(samples.begin(), samples.end());
    shuffle(result.begin(), result.end(), rng);

    return result;
}

// ---------------------------------------------------------------------------
// TODO: upravit tuto ukazku pro svou ulohu

const int DIFFS = 4;
// Pro konstanty, ktere se lisi mezi obtiznostmi, muzeme pouzit takovyto format;
// MAX_N[diff] rika, jake je maximalni N pro danou obtiznost (0 nebo 1)
const int MAX_N[DIFFS] = {10, int(1e5), int(1e5), int(1e5)};
const int MAX_M[DIFFS] = {10, int(1e5), int(1e5), int(1e9)};
const int MAX_K[DIFFS] = {10, 10, int(1e5), int(1e5)};

using Interval = pair<ll, ll>;

struct Problem {
    // Reprezentuje jeden problem (test).
    unordered_map<int, vector<Interval>> a;
    int n;
    ll m;

    Problem() {}

    Problem(int n, int m) : n(n), m(m) {}

    void add(int s, ll o, ll d) { a[s].push_back({o, d}); }

    void check(int diff) {
        // zkontroluje, jestli problem odpovida limitum stanovenym v zadani
        assert(1 <= n && n <= MAX_N[diff]);
        assert(1 <= m && m <= MAX_M[diff]);
        int k = 0;

        for (auto &e : a) {
            k += e.second.size();

            int stall = e.first;
            assert(1 <= stall && stall <= n);
            sort(e.second.begin(), e.second.end());

            // neprekryvajici se intervaly
            int to = -1;
            for (auto interval : e.second) {
                assert(interval.first > to);
                to = interval.second;

                assert(1 <= interval.first && interval.first <= n + m);
                assert(1 <= interval.second && interval.second <= n + m);
                assert(interval.first <= interval.second);
            }
        }

        assert(1 <= k);
        assert(k <= MAX_K[diff]);
    }

    void print(ostream &out) {
        // Vypise problem tak, jak to specifikuje sekce "Tvar vstupu"
        int k = 0;
        for (auto &e : a) {
            k += e.second.size();
        }

        out << n << " " << m << " " << k << endl;

        for (auto &e : a) {
            for (auto interval : e.second) {
                out << e.first << " " << interval.first << " " << interval.second << endl;
            }
        }
    }
};

Problem genRandom(int n, int m, int k) {
    Problem p(n, m);

    unordered_map<ll, int> counts;
    rep(i, 0, k) { counts[randRange(1, n)]++; }

    for (auto &e : counts) {
        int s = e.first;
        int cnt = e.second;
        // zacatky a konce intervalu
        vector<ll> times = randDifferentNumbers(1, n + m, 2 * cnt);
        sort(times.begin(), times.end());

        for (int i = 0; i < 2 * cnt; i += 2) {
            ll t1 = times[i];
            ll t2 = times[i + 1];
            p.add(s, t1, t2 - 1);
        }
    }

    return p;
}

Problem genOutOfRange() {
    // Priklad, kde by bylo optimalni vejit v case mimo interval [1, m]
    // (coz ale nejde)
    Problem p(5, 10);
    p.add(4, 4, 5);
    p.add(2, 6, 10);
    p.add(4, 1, 2);
    p.add(5, 2, 2);

    return p;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "pouziti: ./gen slozka_pro_vygenerovane_vstupy" << endl;
        exit(1);
    }
    string dir(argv[1]);

    rng.seed(125);

    rep(diff, 0, DIFFS) {
        vector<Problem> problems;
        rep(i, 0, 3) {
            problems.push_back(genRandom(randAlmost(MAX_N[diff]), randAlmost(MAX_M[diff]),
                                         randAlmost(MAX_K[diff])));
        }
        problems.push_back(genRandom(MAX_N[diff], MAX_M[diff], MAX_K[diff]));
        problems.push_back(genRandom(MAX_N[diff], MAX_M[diff], 1));
        problems.push_back(genRandom(MAX_N[diff], 1, MAX_K[diff]));
        problems.push_back(genRandom(1, MAX_M[diff], min(MAX_K[diff], MAX_M[diff] / 10)));
        problems.push_back(genRandom(1, 1, 1));

        problems.push_back(genOutOfRange());

        rep(i, 0, problems.size()) {
            Problem &p = problems[i];
            p.check(diff);

            stringstream filename;
            filename << dir << "/" << setw(2) << setfill('0') << (diff + 1) << "_"
                     << setw(2) << setfill('0') << (i + 1) << ".in";

            ofstream file;
            file.open(filename.str());
            p.print(file);
            file.close();
        }
    }
}

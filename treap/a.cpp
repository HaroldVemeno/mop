#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

#define D(x) cerr << #x << ": " << (x) << '\n';
#define all(x) begin(x), end(x)
using ll = long long;

template<typename T>
ostream& operator <<(ostream& o, const vector<T>& v) {
    bool first = true; o << '['; for(auto& a : v) { if(first) { o << a; first = false; } else { o << ", " << a; } } o << ']'; return o;
}

struct Treap {
    Treap* l = nullptr;
    Treap* r = nullptr;
    int v;
    int p;
    Treap(int v): v{v}, p{rand()} {}
    Treap(int v, int p): v{v}, p{p} {}

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

#define RST "\e[0m"

    void print(ostream& o, string bef = string{}, int pos = 0) const {
        if(l == nullptr) {
            o << bef;
            if(pos == -1) o << "  ";
            if(pos == 1)  o << "| ";
            o << ",-o\n";
        } else {
            if(pos == -1) l->print(o, bef + "  ", -1);
            if(pos == 1)  l->print(o, bef + "| ", -1);
            if(pos == 0)  l->print(o, bef, -1);
        }
        o << bef;
        if(pos == -1) o << ",-";
        if(pos == 1)  o << "`-";
        o << "(v: " << v << ", p: " << p << ")\n";
        if(r == nullptr) {
            o << bef;
            if(pos == -1) o << "| ";
            if(pos == 1)  o << "  ";
            o << "`-o\n";
        } else {
            if(pos == -1) r->print(o, bef + "| ", 1);
            if(pos == 1)  r->print(o, bef + "  ", 1);
            if(pos == 0)  r->print(o, bef, 1);
        }

    }

    friend ostream& operator<< (ostream& o, const Treap& a) {
        a.print(o);
        return o;
    }
};

Treap* merge(Treap* l, Treap* r) {
    if(l == nullptr) return r;
    if(r == nullptr) return l;
    if(l->p > r->p) {
        Treap* root = l;
        root->r = merge(root->r, r);
        return root;
    } else {
        Treap* root = r;
        root->l = merge(root->l, l);
        return root;
    }
}

pair<Treap*, Treap* > split(Treap* p, int s) {
    if(!p) return {nullptr, nullptr};
    if(s < p->v) {
        if(p->l == nullptr) return {nullptr, p};
        auto[l, r] = split(p->l, s);
        p->l = r;
        return {l, p};
    } else {
        if(p->r == nullptr) return {p, nullptr};
        auto[l, r] = split(p->r, s);
        p->r = l;
        return {p, r};
    }
        // === >>= <<= <=< www  === <> <!-- *** ||
}

Treap* insert(Treap* rt, int v, int p = rand()) {
    if(rt == nullptr) return new Treap{v, p};
    if(v == rt->v) return rt;
    if(p < rt->p) {
        if(v < rt->v) {
            rt->l = insert(rt->l, v, p);
        } else {
            rt->r = insert(rt->r, v, p);
        }
    } else {
        auto[l, r] = split(rt, v);
        rt = new Treap{v, p};
        rt->l = l;
        rt->r = r;
    }
    return rt;
}

Treap* find(Treap* a, int v) {
    if(a == nullptr) return a;
    if(v < a->v) {
        return find(a->l, v);
    } else if (a->v < v) {
        return find(a->r, v);
    } else {
        return a;
    }
}

Treap* remove(Treap* a, int v) {
    if(a == nullptr) return a;
    if(v < a->v) {
        a->l = remove(a->l, v);
        return a;
    } else if (a->v < v) {
        a->r = remove(a->r, v);
        return a;
    } else {
        Treap* m = merge(a->l, a->r);
        delete a;
        return m;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    srand(7539000);

    Treap* a = nullptr;
    a = insert(a, 10);
    cout << *a << '\n';
    a = insert(a, 77);
    cout << *a << '\n';
    a = insert(a, 22);
    cout << *a << '\n';
    a = insert(a, 5);
    cout << *a << '\n';
    a = insert(a, 35);
    cout << *a << '\n';
    a = insert(a, 11);
    cout << *a << '\n';
    a = insert(a, 9);
    cout << *a << '\n';

    for(int i = 0; i < 100; ++i) {
        int n = rand() % 128;
        a = insert(a, n);
    }

    cout << *a << '\n' << flush;

    Treap* f = find(a, 99);

    cout << *f << '\n' << flush;

    a = remove(a, 99);

    for(int i = 0; i < 100; ++i) {
        a = remove(a, i*3);
    }

    cout << *a << '\n';

}

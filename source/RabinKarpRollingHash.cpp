#include <iostream>
#include <deque>

using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

class rolling_hash {

   private:
    const ll HASH = 'z' - ('a' - 1) + 1;

    ll value = 0;
    deque<char> dq;

    ll pow_mod(ll a, ll p) {
        if (p == 0) {
            return 1;
        }

        ll tmp = pow_mod(a, p / 2);
        ll res = (tmp * tmp) % MOD;

        if (p % 2) {
            res *= a;
        }

        return res % MOD;
    }

   public:
    void push_back(char c) {
        c -= 'a' - 1;
        value = (value * HASH + c) % MOD;
        dq.push_back(c);
    }

    void pop_front() {
        ll a = dq.front() * pow_mod(HASH, dq.size() - 1);
        value = ((value - a) % MOD + MOD) % MOD;
        dq.pop_front();
    }

    ll get() {
        return value;
    }
};

int main_test() {
    ios::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    string a, b;
    int kmer_size = 3;
    // cin >> a >> b;
    a = "aaabbcccababacbbaaa";
    b = "abc";
    rolling_hash hash_a, hash_b;

    for (int i = 0; i < kmer_size; i++) {
        hash_a.push_back(a[i]);
    }
    cout << a[2] << a[1] << a[0] << " : " << hash_a.get() << endl;
    
    for (ll i=kmer_size; i < a.size()-kmer_size; i++) {
        hash_a.pop_front();
        hash_a.push_back(a[i]);
        cout << a[i-2] << a[i-1] << a[i] << " : " << hash_a.get() << endl;
    }
}

//https://gist.github.com/NamPE286/a436341492dc68364efb37cf873c469a
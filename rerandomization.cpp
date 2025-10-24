#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll mod(const ll &a, const ll &m)
{
    ll res = a % m;
    if (res < 0)
        res += m;
    return res;
}
// modular exponentiation
ll modExp(ll base, ll exp, ll p)
{
    ll res = 1;
    base %= p;
    while (exp > 0)
    {
        if (exp & 1)
            res = (res * base) % p;
        base = (base * base) % p;
        exp = exp / 2;
    }
    return res;
}

// modular inverse using Fermat’s theorem
ll modInv(ll a, ll p)
{
    a = mod(a, p); // Ensure a is positive
    for (ll i = 1; i < p; i++)
    {
        if ((a * i) % p == 1)
            return i;
    }
    return -1; // no inverse exists
}

// === Rerandomization function ===
// Given ciphertext (c1, c2), returns a rerandomized version (c1', c2')
pair<ll, ll> rerandomize(ll c1, ll c2, ll g, ll h, ll p, ll r)
{
    ll c1_new = (c1 * modExp(g, r, p)) % p;
    ll c2_new = (c2 * modExp(h, r, p)) % p;
    return {c1_new, c2_new};
}
bool is_generator(ll g, ll p)
{
    set<ll> powers; // To store all distinct powers of g mod p
    for (ll i = 1; i < p; i++)
    {
        powers.insert(modExp(g, i, p)); // Compute g^i mod p
    }
    return powers.size() == p - 1; // If we get all numbers from 1 to p-1
}

// Function to find the smallest generator
ll find_generator(ll p)
{
    for (ll g = 2; g < p; g++) // Start with g = 2
    {
        if (is_generator(g, p))
        {
            return g; // Found a generator
        }
    }
    return -1; // If no generator found (which should not happen for prime p)
}

int main()
{
    ll p = 61; // a small prime for demonstration
    ll g = find_generator(p);
    if (g == -1)
    {
        cout << "No generator found for p" << endl;
        return 0;
    }
    ll a = 127;
    ll h = modExp(g, a, p);

    ll ms1 = 123;
    ll ms2 = 67;
    ll k1 = 53;
    ll k2 = 77;

    cout << "Parameters: p=" << p << " g=" << g << " a(private)=" << a << " h(public)=" << h << "\n\n";
    cout << "Messages: ms1=" << ms1 << ", ms2=" << ms2 << "\n\n";

    // Encrypt two messages
    ll c11 = modExp(g, k1, p);
    ll c21 = (ms1 * modExp(h, k1, p)) % p;
    ll c12 = modExp(g, k2, p);
    ll c22 = (ms2 * modExp(h, k2, p)) % p;

    // Product ciphertext (homomorphic property)
    ll c1 = (c11 * c12) % p;
    ll c2 = (c21 * c22) % p;
    cout << "Product ciphertext: (c1, c2) = (" << c1 << ", " << c2 << ")\n\n";

    // Decrypt product
    ll s = modExp(c1, a, p);
    ll s_inv = modInv(s, p);
    ll dec = (c2 * s_inv) % p;

    ll expected = (ms1 * ms2) % p;
    cout << "Decrypted product message: " << dec << endl;
    cout << "Expected (ms1 * ms2 mod p): " << expected << endl;
    cout << ((dec == expected) ? "Product decryption successful!\n" : "Mismatch!\n");

    // === Demonstrate re-randomization ===
    ll r = 111; // new random number
    // obtain rerandomized ciphertext
    auto pr = rerandomize(c1, c2, g, h, p, r);
    ll c1_new = pr.first;
    ll c2_new = pr.second;

    cout << "\nRerandomized ciphertext: \n";
    cout << "c1' = " << c1_new << "\n";
    cout << "c2' = " << c2_new << "\n";

    // Decrypt rerandomized ciphertext
    ll s2 = modExp(c1_new, a, p);
    ll s2_inv = modInv(s2, p);
    ll dec2 = (c2_new * s2_inv) % p;

    cout << "Decrypted rerandomized message: " << dec2 << "\n";
    cout << ((dec2 == expected) ? "Rerandomization successful (message unchanged).\n"
                                : "Something went wrong in rerandomization!\n");

    return 0;
}
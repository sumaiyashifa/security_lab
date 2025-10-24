#include <bits/stdc++.h>
using namespace std;

#define ll long long

// Safe modular function (handles negatives)
ll mod(const ll &a, const ll &m)
{
    ll res = a % m;
    if (res < 0)
        res += m;
    return res;
}

// Fast modular exponentiation (base^exp mod n)
ll powMod(ll base, ll exp, ll n)
{
    ll res = 1;
    base = mod(base, n); // Using the mod function to ensure base is positive

    while (exp > 0)
    {
        if (exp % 2 == 1)
            res = mod(res * base, n); // Using mod for the result

        exp >>= 1;
        base = mod(base * base, n); // Using mod for base
    }
    return res;
}

// Modular inverse using brute force (only for small numbers)
ll modInverse(ll a, ll p)
{
    a = mod(a, p); // Ensure a is positive
    for (ll i = 1; i < p; i++)
    {
        if ((a * i) % p == 1)
            return i;
    }
    return -1; // no inverse exists
}
bool is_generator(ll g, ll p)
{
    set<ll> powers; // To store all distinct powers of g mod p
    for (ll i = 1; i < p; i++)
    {
        powers.insert(powMod(g, i, p)); // Compute g^i mod p
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
pair<ll, ll> rerandomize(ll c1, ll c2, ll g, ll h, ll p, ll r)
{
    ll c1_new = (c1 * powMod(g, r, p)) % p;
    ll c2_new = (c2 * powMod(h, r, p)) % p;
    return {c1_new, c2_new};
}
int main()
{
    // --- Example with smaller primes ---
    ll p = 61; // large prime
    ll g = find_generator(p);
    if (g == -1)
    {
        cout << "No generator found for p" << endl;
        return 0;
    }

    cout << "Generated g = " << g << "\n";
    ll a = 123;
    ll r1 = 456;
    ll r2 = 789;
    ll beta = powMod(g, a, p); // beta = g^a mod p
    cout << "Beta: " << beta << endl;

    // Calculate C11 = g^r1 mod p
    ll c11 = powMod(g, r1, p);
    cout << "C11: " << c11 << endl;

    // Calculate C12 = g^r2 mod p
    ll c12 = powMod(g, r2, p);
    cout << "C12: " << c12 << endl;

    // Messages
    ll m1 = 3140564;
    ll c21 = mod(m1 * powMod(beta, r1, p), p); // C21 = m1 * beta^r1 mod p
    cout << "C21: " << c21 << endl;

    ll m2 = 1034675;
    ll c22 = mod(m2 * powMod(beta, r2, p), p); // C22 = m2 * beta^r2 mod p
    cout << "C22: " << c22 << endl;

    // C1 = g^(r1 + r2) mod p
    ll c1 = powMod(g, r1 + r2, p);
    cout << "C1: " << c1 << endl;

    // C2 = m1 * m2 * beta^(r1 + r2) mod p
    ll c2 = mod(m1 * m2 * powMod(beta, r1 + r2, p), p);
    cout << "C2: " << c2 << endl;

    // Inverse of C1
    ll res3 = 1;
    for (ll i = 0; i < a; i++)
    {
        res3 = mod(res3 * c1, p);
    }

    ll c1inv = modInverse(res3, p); // Inverse of C1
    cout << "C1 Inv: " << c1inv << endl;

    ll dec = mod(c2 * c1inv, p);
    cout << "Decrypted: " << dec << endl;
    ll m3 = m1 * m2;
    cout << "Original Msg: " << mod(m3, p) << endl;
    ll r = 111; // new random number
    // obtain rerandomized ciphertext
    auto pr = rerandomize(c1, c2, g, beta, p, r);
    ll c1_new = pr.first;
    ll c2_new = pr.second;

    cout << "\nRerandomized ciphertext: \n";
    cout << "c1' = " << c1_new << "\n";
    cout << "c2' = " << c2_new << "\n";

    // Decrypt rerandomized ciphertext
    ll s2 = powMod(c1_new, a, p);
    ll s2_inv = modInverse(s2, p);
    ll dec2 = (c2_new * s2_inv) % p;

    cout << "Decrypted rerandomized message: " << dec2 << "\n";
    cout << ((dec2 == mod(m3, p)) ? "Rerandomization successful (message unchanged).\n"
                                  : "Something went wrong in rerandomization!\n");

    return 0;
}

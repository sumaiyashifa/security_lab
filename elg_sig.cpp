#include <bits/stdc++.h>
using namespace std;

#define ll long long
// Modular inverse using brute force (only for small numbers)
ll modinv(ll a, ll p)
{
    a = a % p;
    for (ll i = 1; i < p; i++)
    {
        if ((a * i) % p == 1)
            return i;
    }
    return 0;
}
// Safe modular function (handles negatives)
ll mod(const ll &a, const ll &m)
{
    ll res = a % m;
    if (res < 0)
        res += m;
    return res;
}

// Fast modular exponentiation
ll power(ll base, ll exp, ll n)
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

// Check if g is a generator (primitive root modulo p)
bool is_generator(ll g, ll p)
{
    set<ll> powers; // To store all distinct powers of g mod p
    for (ll i = 1; i < p; i++)
    {
        powers.insert(power(g, i, p)); // Compute g^i mod p
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
    // --- Example with smaller primes ---
    ll p = 61; // A small prime number for debugging purposes

    // Generate g (generator for p)
    ll g = find_generator(p);
    if (g == -1)
    {
        cout << "No generator found for p" << endl;
        return 0;
    }

    cout << "Generated g = " << g << "\n";

    // Private key
    ll a = 5;              // Example private key
    ll y = power(g, a, p); // public key

    cout << "Public parameters:\n";
    cout << "p = " << p << ", g = " << g << ", y = " << y << "\n";
    cout << "Private key a = " << a << "\n";

    // Message
    ll m = 1345;

    // Choose k (coprime with p-1)
    ll k = 123;                  // choose small number for example
    while (__gcd(k, p - 1) != 1) // Use C++ standard library's gcd function
        k++;

    // --- Signature generation ---
    ll r = power(g, k, p);
    ll k_inv = modinv(k, p - 1);

    ll temp = mod(m - a * r, p - 1);
    ll s = mod(temp * k_inv, p - 1);

    cout << "\nMessage m = " << m << "\n";
    cout << "Random k = " << k << " (coprime with p-1)\n";
    cout << "Signature (r, s) = (" << r << ", " << s << ")\n";

    // --- Verification ---
    ll v1 = power(g, m, p);
    ll v2 = (power(y, r, p) * power(r, s, p)) % p;

    cout << "\nVerification:\n";
    cout << "v1 = g^m mod p = " << v1 << "\n";
    cout << "v2 = y^r * r^s mod p = " << v2 << "\n";

    if (v1 == v2)
        cout << "Signature is VALID\n";
    else
        cout << "Signature is INVALID\n";

    return 0;
}

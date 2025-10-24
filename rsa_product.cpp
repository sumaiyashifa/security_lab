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

// Function to calculate the GCD of two numbers
ll gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to calculate the modular inverse (using brute force)
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

// Fast modular exponentiation (base^exp mod n)
ll powMod(ll base, ll exp, ll n)
{
    ll res = 1;
    base = mod(base, n); // Using the mod function to ensure base is positive

    while (exp > 0)
    {
        if (exp & 1)
            res = mod(res * base, n); // Using mod for the result

        exp >>= 1;
        base = mod(base * base, n); // Using mod for base
    }
    return res;
}

int main()
{
    ll p, q;
    cout << "Enter prime p: ";
    cin >> p;
    cout << "Enter prime q: ";
    cin >> q;

    ll n = p * q;               // Calculate n = p * q
    ll phi = (p - 1) * (q - 1); // Euler's Totient function

    ll e = 65537; // Start with a commonly used public exponent
    while (e < phi)
    {
        if (gcd(e, phi) == 1)
            break;
        e++;
    }

    cout << "Public key (e): " << e << endl;
    cout << "Phi(n): " << phi << endl;

    ll d = modInverse(e, phi); // Calculate private key d
    cout << "Private key (d): " << d << endl;

    // Input two messages
    ll m1, m2;
    cout << "Enter message 1: ";
    cin >> m1;
    cout << "Enter message 2: ";
    cin >> m2;

    cout << "Product of plaintexts: " << mod(m1 * m2, n) << endl;

    // Encrypt the messages
    ll c1 = powMod(m1, e, n); // Encrypt message 1
    ll c2 = powMod(m2, e, n); // Encrypt message 2
    cout << "Cipher 1: " << c1 << endl;
    cout << "Cipher 2: " << c2 << endl;

    // Homomorphic encryption (multiplying ciphertexts)
    ll c = mod(c1 * c2, n);
    cout << "C1 * C2 (mod n): " << c << endl;

    // Decrypt the product of the ciphertexts
    ll decrypted = powMod(c, d, n);
    cout << "Decrypted (m1 * m2 mod n): " << decrypted << endl;

    // Check if the homomorphic property holds
    if (decrypted == mod(m1 * m2, n))
        cout << "Valid (Homomorphic property holds)" << endl;
    else
        cout << "Invalid" << endl;

    return 0;
}

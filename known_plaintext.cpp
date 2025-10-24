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

// Fast modular exponentiation (a^exp mod n)
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

// Modular inverse using brute force (only for small numbers)
ll modInv(ll a, ll p)
{
    a = mod(a, p);
    for (ll i = 1; i < p; i++)
    {
        if ((a * i) % p == 1)
            return i;
    }
    return -1; // no inverse exists
}

int main()
{
    ll p = 19, q = 23; // Choose small primes for simplicity
    ll n = p * q;

    ll phi = (p - 1) * (q - 1); // Euler's totient function

    // Start with a large value for e (typically 65537)
    ll e = 65537;
    while (e < phi)
    {
        if (gcd(e, phi) == 1)
            break;
        e++;
    }
    cout << "Public key (e): " << e << endl;

    // Calculate the private key d
    ll d = modInv(e, phi);
    cout << "Private key (d): " << d << endl;

    // Find multiple private keys (d values) using the formula e * d ≡ 1 mod φ(n)
    ll cnt = 0;
    ll dd[5];
    for (ll i = 0; i < phi; i++)
    {
        if ((1 + i * phi) % e == 0)
        {
            dd[cnt] = (1 + i * phi) / e;
            cnt++;
            if (cnt > 4)
                break;
        }
    }
    for (auto it : dd)
        cout << it << " ";
    cout << endl;

    // Encrypt a message
    ll ms = 12;
    ll c1 = powMod(ms, e, n);
    cout << "Ciphertext: " << c1 << endl;

    // Decrypt the ciphertext
    ll dec = powMod(c1, d, n);
    cout << "Decrypted using d: " << dec << endl;

    // Try brute-forcing to find d (decryption exponent)
    for (ll i = 2; i < n; i++)
    {
        if (ms == powMod(c1, i, n))
        {
            cout << "Decrypted: " << ms << endl;
            cout << "Iteration is: " << i << endl;
            break;
        }
    }

    return 0;
}

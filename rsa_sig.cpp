#include <bits/stdc++.h>
using namespace std;

#define ll long long

// Function to calculate the GCD of two numbers
ll gcd(ll a, ll b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}
ll modInv(ll a, ll p)
{
    a = a % p;
    for (ll i = 1; i < p; i++)
    {
        if ((a * i) % p == 1)
            return i;
    }
    return -1; // no inverse exists
}
// Function to calculate power modulo n (m^e mod n)
ll power(ll a, ll p, ll mod)
{
    ll res = 1;
    a = a % mod;
    for (ll i = 0; i < p; i++)
    {
        res = (res * a) % mod;
    }
    return res;
}

int main()
{
    // Small primes for demonstration purposes
    ll p, q;
    cin >> p >> q;

    // Calculate n and phi(n)
    ll n = p * q;
    ll phi = (p - 1) * (q - 1);

    // Choose e such that gcd(e, phi) = 1
    ll new_e = 1000000;
    ll e = 65537; // start with a bit larger value
    while (e < phi)
    {
        if (gcd(e, phi) == 1)
            break;
        e++;
    }
    cout << "Public key (e): " << e << endl;

    // Find private key d (modular inverse of e mod phi)
    ll d = modInv(e, phi);
    cout << "Private key (d): " << d << endl;

    // Message to be signed
    ll m = 20;
    cout << "Message (m): " << m << endl;

    // RSA Digital Signature: se = m^d mod n
    ll se = power(m, d, n);
    cout << "Signature (se = m^d mod n): " << se << "\n";

    // Verification: M = se^e mod n; valid if M == m
    ll M = power(se, e, n);
    cout << "Verified message (M = se^e mod n): " << M << "\n";

    if (M == m)
    {
        cout << "Signature VALID \n";
    }
    else
    {
        cout << "Signature INVALID \n";
    }

    return 0;
}

#include <bits/stdc++.h>
#include <gmpxx.h>
using namespace std;

// Safe modular function (handles negatives)
mpz_class mod(const mpz_class &a, const mpz_class &m)
{
    mpz_class res = a % m;
    if (res < 0)
        res += m;
    return res;
}

// Fast modular exponentiation
mpz_class power(const mpz_class &a, const mpz_class &p, const mpz_class &modn)
{
    mpz_class res = 1;
    mpz_class base = a % modn;
    mpz_class exp = p;

    while (exp > 0)
    {
        if (exp % 2 == 1)
            res = (res * base) % modn;
        exp /= 2;
        base = (base * base) % modn;
    }
    return res;
}

// Modular inverse using GMP
mpz_class modinv(mpz_class a, mpz_class p)
{
    a = a % p;
    for (mpz_class i = 1; i < p; i++)
    {
        if ((a * i) % p == 1)
            return i;
    }
    return 0;
}

int main()
{
    // --- Big prime example ---
    mpz_class p("15588119"); // large prime
    mpz_class g = 2;         // generator

    // Private key
    mpz_class a = 123;
    mpz_class y = power(g, a, p); // public key

    cout << "Public parameters:\n";
    cout << "p = " << p << ", g = " << g << ", y = " << y << "\n";
    cout << "Private key a = " << a << "\n";

    // Message
    mpz_class m("3140564");

    // Choose k (coprime with p-1)
    mpz_class k = 456; // choose small number for example
    while (gcd(k, p - 1) != 1)
        k++;

    // --- Signature generation ---
    mpz_class r = power(g, k, p);
    mpz_class k_inv = modinv(k, p - 1);

    mpz_class temp = mod(m - a * r, p - 1);
    mpz_class s = mod(temp * k_inv, p - 1);

    cout << "\nMessage m = " << m << "\n";
    cout << "Random k = " << k << " (coprime with p-1)\n";
    cout << "Signature (r, s) = (" << r << ", " << s << ")\n";

    // --- Verification ---
    mpz_class v1 = power(g, m, p);
    mpz_class v2 = (power(y, r, p) * power(r, s, p)) % p;

    cout << "\nVerification:\n";
    cout << "v1 = g^m mod p = " << v1 << "\n";
    cout << "v2 = y^r * r^s mod p = " << v2 << "\n";

    if (v1 == v2)
        cout << "Signature is VALID\n";
    else
        cout << "Signature is INVALID\n";

    return 0;
}

// pacman -S mingw-w64-x86_64-gmp
// pacman -S mingw-w64-x86_64-gcc
// /c/Users/Asus/Desktop/security
// $ g++ sig.cpp -o sig -lgmpxx -lgmp
// ./sig
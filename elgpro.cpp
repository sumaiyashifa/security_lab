#include <bits/stdc++.h>
#include <gmpxx.h>

using namespace std;

mpz_class power(mpz_class b, mpz_class p, mpz_class mod)
{
    mpz_class res = 1;
    b = b % mod;
    while (p > 0)
    {
        if (p % 2 == 1)
        {
            res = (res * b) % mod;
        }
        p /= 2;
        b = (b * b) % mod;
    }
    return res;
}

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
    mpz_class p("15588119");
    mpz_class g = 2;

    mpz_class a = 123;
    mpz_class r1 = 456;
    mpz_class r2 = 789;
    mpz_class beta = power(g, a, p);
    cout << "Beta: " << beta << endl;

    mpz_class c11 = power(g, r1, p);
    cout << "C11: " << c11 << endl;

    mpz_class c12 = power(g, r2, p);
    cout << "C12: " << c12 << endl;

    mpz_class m1("3140564");
    mpz_class c21 = m1 * power(beta, r1, p);
    cout << "C21: " << c21 << endl;

    mpz_class m2("1034675");
    mpz_class c22 = m2 * power(beta, r2, p);
    cout << "C22: " << c22 << endl;

    // mpz_class res1 = 1;
    // for(mpz_class i = 0; i<a; i++){
    //     res1 *= c11;
    //     res1 %= p;
    // }

    // mpz_class c11inv = modinv(res1, p);
    // cout<<"C11 Inv: "<<c11inv<<endl;

    // mpz_class res2 = 1;
    // for(mpz_class i = 0; i<a; i++){
    //     res2 *= c12;
    //     res2 %= p;
    // }

    // mpz_class c12inv = modinv(res2, p);
    // cout<<"C21 Inv: "<<c12inv<<endl;

    mpz_class c1 = power(g, r1 + r2, p);
    cout << "C1: " << c1 << endl;

    mpz_class c2 = m1 * m2 * power(beta, r1 + r2, p);
    cout << "C2: " << c2 << endl;

    mpz_class res3 = 1;
    for (mpz_class i = 0; i < a; i++)
    {
        res3 *= c1;
        res3 %= p;
    }

    mpz_class c1inv = modinv(res3, p);
    cout << "C1 Inv: " << c1inv << endl;
    mpz_class msg = (m1 * m2) % p;
    cout << "Original Msg: " << msg << endl;
    // mpz_class dec1 = (c21*c11inv) % p;
    // cout<<"Decrypted Msg1: "<<dec1<<endl;

    // mpz_class dec2 = (c22*c12inv) % p;
    // cout<<"Decrypted Msg2: "<<dec2<<endl;

    mpz_class dec = (c2 * c1inv) % p;
    cout << "Decrypted: " << dec << endl;

    // if ((dec = dec1 * dec2) % p)
    // {
    //     cout << "Product Cipher Decryption Valid" << endl;
    // }
    // else
    // {
    //     cout << "Product Cipher Decryption invalid" << endl;
    // }
}
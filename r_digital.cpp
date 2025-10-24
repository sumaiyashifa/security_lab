#include<bits/stdc++.h>
#include<gmpxx.h>

using namespace std;

mpz_class gcd(mpz_class& a, mpz_class& b){
    if(b==0){
        return a;
    }
    else{
        return gcd(b, a%b);
    }
}
    
mpz_class power(mpz_class& a, mpz_class& p, mpz_class& mod){
    mpz_class res= 1;
    for(mpz_class i = 0; i<p; i++){
        res = res*a;
        res = res%mod;
    }
    return res;
}

int main() {
    //mpz_class p("12557914224249883241");
    //mpz_class q("9442376104487385859");
    mpz_class p("58657");
    mpz_class q("229");
    mpz_class n = p*q;
    mpz_class phi = (p-1)*(q-1);

    //mpz_class new_e = 10000000;
    //mpz_class e = 10000000;
    mpz_class new_e = 1000000;
    mpz_class e = 1000000;
    //cout<<new_e<<endl;
    while(new_e < phi){
        mpz_class cal_gcd = gcd(new_e, phi);
        if(cal_gcd==1){
            e = new_e;
            break;
        }
        else{
            new_e = new_e + 1;
        }
    }
    cout<<"E: "<<e<<endl;

    mpz_class k = 1;
    mpz_class d = 1;
    while(k < 1000000){
        mpz_class j = (phi*k) + 1;
        if(j%e==0){
            d = j/e;
            break;
        }
        k = k + 1;
    }
    cout<<"D: "<<d<<endl;


    mpz_class m= 20;
          cout<<"MSG 1: "<<m<<endl;


    // ===== RSA Digital Signature: se = m^d mod n =====
    mpz_class se = power(m, d, n);
    cout << "Signature (se = m^d mod n): " << se << "\n";

    // ===== Verification: M = se^e mod n; valid if M == m =====
    mpz_class M = power(se, e, n);
    cout << "Verified message (M = se^e mod n): " << M << "\n";

    if (M == m) {
        cout << "Signature VALID ✅\n";
    } else {
        cout << "Signature INVALID ❌\n";
    }

    return 0;
}

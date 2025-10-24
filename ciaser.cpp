#include <bits/stdc++.h>

using namespace std;

string encrypt(string s, int key)
{
    string e = s;
    for (int i = 0; i < e.length(); i++)
    {
        if (e[i] >= 'a' && e[i] <= 'z')
        {
            int x = e[i];
            x = x - 97;
            x = (x + key) % 26; // safe modulo
            if (x < 0)
                x += 26;
            x = x + 97;
            e[i] = x;
        }
        else if (e[i] >= 'A' && e[i] <= 'Z')
        {
            int x = e[i];
            x = x - 65;
            x = (x + key) % 26; // safe modulo
            if (x < 0)
                x += 26;
            x = x + 65;
            e[i] = x;
        }
        else if (e[i] >= '0' && e[i] <= '9')
        {
            int x = e[i];
            x = x - 48;
            x = (x + key) % 10; // safe modulo
            if (x < 0)
                x += 10;
            x = x + 48;
            e[i] = x;
        }
        else
        {
            continue;
        }
    }
    return e;
}

string chng_encrypt(string s, int key)
{
    string e = s;
    for (int i = 0; i < e.length(); i++)
    {
        if (e[i] >= 'a' && e[i] <= 'z')
        {
            int x = e[i];
            x = x - 97;
            x = (x + key) % 26; // safe modulo
            if (x < 0)
                x += 26;
            x = x + 65;
            e[i] = x;
        }
        else if (e[i] >= 'A' && e[i] <= 'Z')
        {
            int x = e[i];
            x = x - 65;
            x = (x + key) % 26; // safe modulo
            if (x < 0)
                x += 26;
            x = x + 97;
            e[i] = x;
        }
        else if (e[i] >= '0' && e[i] <= '9')
        {
            int x = e[i];
            x = x - 48;
            x = (x + key) % 10; // safe modulo
            if (x < 0)
                x += 10;
            x = x + 48;
            e[i] = x;
        }
        else
        {
            continue;
        }
    }
    return e;
}

string decrypt(string s, int key)
{
    string e = s;
    for (int i = 0; i < e.length(); i++)
    {
        if (e[i] >= 'a' && e[i] <= 'z')
        {
            int x = e[i];
            x = x - 97;
            x = (x - key) % 26;
            if (x < 0)
                x += 26;
            x = x + 97;
            e[i] = x;
        }
        else if (e[i] >= 'A' && e[i] <= 'Z')
        {
            int x = e[i];
            x = x - 65;
            x = (x - key) % 26;
            if (x < 0)
                x += 26;
            x = x + 65;
            e[i] = x;
        }
        else if (e[i] >= '0' && e[i] <= '9')
        {
            int x = e[i];
            x = x - 48;
            x = (x - key) % 10;
            if (x < 0)
                x += 10;
            x = x + 48;
            e[i] = x;
        }
        else
        {
            continue;
        }
    }
    return e;
}

int main()
{
    int key;
    cin >> key;
    string input = "Naimur Rahman 1234";
    cout << "original text: " << input << endl;
    string cip = encrypt(input, key);
    cout << "Cipher text: " << cip << endl;
    string chng_cip = chng_encrypt(input, key);
    cout << "Changed Cipher text: " << chng_cip << endl;
    string org = decrypt(cip, key);
    cout << "Decrypt text: " << org << endl;
    if (org == input)
    {
        cout << "Strings Matched" << endl;
    }
    else
    {
        cout << "Wrong Decryption" << endl;
    }
    return 0;
}

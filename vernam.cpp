#include <bits/stdc++.h>
using namespace std;

string vernamEncrypt(string text, string key)
{
    string result = "";
    if (key.length() != text.length())
    {
        cout << "Error: Key must be the same length as text!" << endl;
        return "";
    }

    for (size_t i = 0; i < text.length(); i++)
    {
        if (isupper(text[i]) && isupper(key[i]))
        {
            // A=0 ... Z=25, add and wrap around using modulo 26
            char enc = ((text[i] - 'A') ^ (key[i] - 'A')) + 'A';
            result += enc;
        }
        else if (islower(text[i]) && islower(key[i]))
        {
            char enc = ((text[i] - 'a') ^ (key[i] - 'a')) + 'a';
            result += enc;
        }
        else
        {
            // If characters aren't letters, just keep them same
            result += text[i];
        }
    }

    return result;
}

string vernamDecrypt(string cipher, string key)
{
    string result = "";
    if (key.length() != cipher.length())
    {
        cout << "Error: Key must be the same length as text!" << endl;
        return "";
    }

    for (size_t i = 0; i < cipher.length(); i++)
    {
        if (isupper(cipher[i]) && isupper(key[i]))
        {
            char dec = ((cipher[i] - 'A') ^ (key[i] - 'A')) + 'A';
            result += dec;
        }
        else if (islower(cipher[i]) && islower(key[i]))
        {
            char dec = ((cipher[i] - 'a') ^ (key[i] - 'a')) + 'a';
            result += dec;
        }
        else
        {
            result += cipher[i];
        }
    }

    return result;
}

int main()
{
    string text, key;

    cout << "Enter text (A,Z only): ";
    getline(cin, text);
    cout << "Enter key  (same length): ";
    getline(cin, key);

    string encrypted = vernamEncrypt(text, key);
    cout << "\nEncrypted Text: " << encrypted << endl;

    string decrypted = vernamDecrypt(encrypted, key);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}

// #include <bits/stdc++.h>
// using namespace std;

// // Function to encrypt/decrypt using Vernam Cipher (XOR encryption)
// string vernam_cipher(string text, string key)
// {
//     string result = "";

//     // Ensure the key is as long as the text, otherwise pad it
//     if (text.length() != key.length())
//     {
//         cout << "Error: Key must be the same length as the text." << endl;
//         return "";
//     }

//     // XOR each character of the text with the key
//     for (int i = 0; i < text.length(); i++)
//     {
//         // XOR each character and convert back to a character
//         result += text[i] ^ key[i];
//     }

//     return result;
// }

// int main()
// {
//     string text, key;

//     // Input message (plaintext or ciphertext) and key
//     cout << "Enter the text (plaintext or ciphertext): ";
//     getline(cin, text);
//     cout << "Enter the key (same length as text): ";
//     getline(cin, key);

//     // Make sure key is as long as the text
//     if (key.length() != text.length())
//     {
//         cout << "Error: The key length must be the same as the text length." << endl;
//         return 0;
//     }

//     // Encrypt or Decrypt the text using the Vernam cipher
//     string result = vernam_cipher(text, key);

//     // Output the result
//     cout << "Result (Encrypted/Decrypted): " << result << endl;

//     return 0;
// }

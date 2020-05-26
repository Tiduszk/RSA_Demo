#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

void getPublicKey(int *n, int *e)
{
    string file;
    string str_n;
    string str_e;
    bool mod = false;

    ifstream publicKeyFile;
    publicKeyFile.open("Public Key.txt");
    if(!publicKeyFile)
    {
        cout << "Unable to find 'Public Key.txt' file." << endl << "Please make sure it is in the same directory as this program." << endl;
        exit(1);
    }

    file.assign((istreambuf_iterator<char>(publicKeyFile)), (istreambuf_iterator<char>()));
    publicKeyFile.close();

    for(int i = 0; i < file.length(); i++)
    {
        if(file[i] != '(' && file[i] != ',' && !mod)
        {
            str_n += file[i];
        }
        else if(file[i] == ',')
        {
            mod = true;
            i += 2;
        }

        if(mod && file[i] != ')')
        {
            str_e += file[i];
        }
    }

    *n = stoi(str_n);
    *e = stoi(str_e);

    return;
}

void writeCiphertext(int c)
{
    ofstream ciphertextFile ("Ciphertext.txt");
    ciphertextFile.clear();
    ciphertextFile << c << endl;
    ciphertextFile.close();

    cout << "Encryption Successful." << endl << "Ciphertext written to 'Ciphertext.txt'" << endl;
}

int main(void)
{
    int n = 0;
    int e = 0;
    int m = 65;
    int c = 0;

    getPublicKey(&n, &e);

    c = (int)pow(m, e) % n;

    writeCiphertext(c);

    return 0;
}

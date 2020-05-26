#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

void getPrivateKey(int *n, int *d)
{
    string file;
    string str_n;
    string str_d;
    bool mod = false;

    ifstream privateKeyFile;
    privateKeyFile.open("Private Key.txt");
    if(!privateKeyFile)
    {
        cout << "Unable to find 'Private Key.txt' file." << endl << "Please make sure it is in the same directory as this program." << endl;
        exit(1);
    }

    file.assign((istreambuf_iterator<char>(privateKeyFile)), (istreambuf_iterator<char>()));
    privateKeyFile.close();

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
            str_d += file[i];
        }
    }

    *n = stoi(str_n);
    *d = stoi(str_d);

    return;
}

void writePlaintext(int m)
{
    ofstream plaintextFile ("Plaintext.txt");
    plaintextFile.clear();
    plaintextFile << m << endl;
    plaintextFile.close();

    cout << "Decryption Successful." << endl << "Plaintext written to 'Plaintext.txt'" << endl;
}

int main(void)
{
    int n = 0;
    int d = 0;
    int m = 0;
    int c = 13;

    getPrivateKey(&n, &d);

    m = (int)pow(c, d) % n;

    cout << m << endl;

    writePlaintext(m);

    return 0;
}

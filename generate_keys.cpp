#include <iostream>
#include <fstream>
#include <cmath>
#include "BigIntegerLibrary.hh"

using namespace std;

bool isPrime(int num)
{
    bool prime = true;
    int root = sqrt(num) + 1;

    if(num <= 1)
    {
        prime = false;
    }
    else
    {
        for(int i = 2; i <= root; i++)
        {
            if(num % i == 0)
            {
                prime = false;
                break;
            }
        }
    }

    return(prime);
}

void getPrimes(int *p, int *q)
{
    bool prime = false;

    while(!prime)
    {
        cout << "Enter a prime number: " << endl;
        cin >> *p;

        prime = isPrime(*p);

        if(!prime)
        {
            cout << "That number is not prime." << endl;
        }
    }

    prime = false;

    while(!prime)
    {
        cout << "Enter another prime number: " << endl;
        cin >> *q;

        prime = isPrime(*q);

        if(!prime)
        {
            cout << "That number is not prime." << endl;
        }
    }

    return;
}

int gcd(int x, int y)
{
    int r = 0;

    do
    {
        r = x % y;
        x = y;
        if(r != 0)
        {
            y = r;
        }
    }
    while(r != 0);

    return(y);
}

int lcm(int x, int y)
{
    int result = 0;

    result = abs(x * y) / gcd(x, y);

    return(result);
}

bool isCoprime(int e, int totient)
{
    bool coprime = false;

    if(e > 1 && e < totient && gcd(e, totient) == 1)
    {
        coprime = true;
    }

    return(coprime);
}

int getE(int totient)
{
    int e = 0;
    bool coprime = false;

    while(!coprime)
    {
        cout << "Enter a value for e such that 1 < e < " << totient << ", and e and " << totient << " are coprime (65537 is recommended if " << totient << " > 65537): " << endl;
        cin >> e;

        coprime = isCoprime(e, totient);

        if(!coprime)
        {
            cout << "That number is not coprime with " << totient << "." << endl;
        }
    }

    return(e);
}

//Old and slow method to calculate d
/*int getD(int e, int phi)
{
    int d = 0;

    while(((e * d) - 1) % phi != 0)
    {
        d++;
    }

    return(d);
}*/

int modInv(int e, int totient)
{
    int s = 0;
    int old_s = 1;
    int t = 1;
    int old_t = 0;
    int r = totient;
    int old_r = e;
    int quotient = 0;
    int temp = 0;

    while(r != 0)
    {
        quotient = old_r / r;

        temp = r;
        r = old_r - quotient * temp;
        old_r = temp;

        temp = s;
        s = old_s - quotient * temp;
        old_s = temp;

        temp = t;
        t = old_t - quotient * temp;
        old_t = temp;
    }

    //cout << endl << s << endl << old_s << endl << t << endl << old_t << endl << r << endl << old_r << endl << quotient << endl << temp << endl;

    return(old_s);
}

int getD(int e, int totient)
{
    int d = 0;

    d = totient - abs(modInv(e, totient));

    return(d);
}

int getKey(int p, int q, int *e)
{
    int phi = 0;
    int lambda = 0;
    int d = 0;
    int d1 = 0;
    int d2 = 0;

    phi = ((p - 1) * (q - 1));
    *e = getE(phi);
    d1 = getD(*e, phi);

    lambda = lcm((p - 1), (q - 1));
    d2 = getD(*e, lambda);

    if((d1 * *e) % phi == 1)
    {
        d = d1;

        if((d2 * *e) % lambda == 1)
        {
            if(d1 > d2)
            {
                d = d2;
            }
        }
    }
    else if((d2 * *e) % lambda == 1)
    {
        d = d2;
    }
    else
    {
        d = -1;
    }

    return d;
}

void writeKeys(int n, int e, int d)
{
    ofstream publicKeyFile ("Public Key.txt");
    publicKeyFile.clear();
    publicKeyFile << "(" << n << ", " << e << ")" << endl;
    publicKeyFile.close();

    ofstream privateKeyFile ("Private Key.txt");
    privateKeyFile.clear();
    privateKeyFile << "(" << n << ", " << d << ")" << endl;
    privateKeyFile.close();

    cout << "Key pairs written successfully." << endl;

    return;
}

int main(void)
{
    int p; //Prime 1
    int q; //Prime 2
    int n; //Modulus
    int e; //Public Exponent
    int d; //Private Exponent

    getPrimes(&p, &q);

    n = p * q;

    d = getKey(p, q, &e);

    //cout << "d: " << d << endl;

    writeKeys(n, e, d);

    return 0;
}

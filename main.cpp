#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream lastNumber("last-num");
    if (!lastNumber) {
        cout << "Error: Failed to open file 'last-num'" << endl;
        return 1;
    }
    long long lastNum;
    lastNumber >> lastNum;
    lastNumber.close();
    ifstream primeList("prime-list");
    if (!primeList) {
        cout << "Error: Failed to open file 'prime-list'" << endl;
        return 1;
    }
    vector<long long> primes;
    long long prime;
    while (primeList >> prime) {
        primes.push_back(prime);
    }
    primeList.close();
    cout << "How many primes would you like to calculate? " << endl;
    long long numberOfCalcs;
    cin >> numberOfCalcs;
    if (numberOfCalcs == -123) numberOfCalcs = 1000000000000;// secret code to calculate up to 1 trillion
    if (numberOfCalcs < 1) {
        cout << "Error: Invalid number of calculations" << endl;
        return 1;
    }
    if (numberOfCalcs > 1000000000000) {
        cout << "Error: Number of calculations is up to 1 trillion" << endl;
        return 1;
    }
    for (long long i = 0; i < numberOfCalcs; i++) {
        if (i % 100000 == 0) {
            cout << "Calculating prime " << i+1 << " of " << numberOfCalcs << endl;
        }
        lastNum++;
        bool isPrime = true;
        int sqrtLastNum = sqrt(lastNum);
        for (long long j = 0; j < primes.size() && primes[j] <= sqrtLastNum; j++) {
            if (lastNum % primes[j] == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            primes.push_back(lastNum);
        }
    }
    ofstream newLastNumber("last-num");
    if (!newLastNumber) {
        cout << "Error: Failed to open file 'last-num'" << endl;
        return 1;
    }
    newLastNumber << lastNum;
    newLastNumber.close();
    ofstream newPrimeList("prime-list");
    if (!newPrimeList) {
        cout << "Error: Failed to open file 'prime-list'" << endl;
        return 1;
    }
    string primeListOutput = "";
    for (long long i = 0; i < primes.size(); i++) {
        primeListOutput += to_string(primes[i]) + "\n";
    }
    newPrimeList << primeListOutput;
    newPrimeList.close();
}

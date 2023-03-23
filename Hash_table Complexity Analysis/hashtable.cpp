#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;



class HashTable {
private:
    vector<int>* table;
    int total_elements;


    // Hash function to calculate hash for a value:
    int getHash(int key) {
        return key % total_elements;
    }

public:
    // Constructor to create a hash table with 'n' indices:
    HashTable(int n) {
        total_elements = n;
        table = new  vector<int>[total_elements];
        
    }

    // Insert data in the hash table:
    void insertElement(int key, int r[]) {
        table[getHash(cal(key,r))].push_back(key);
    }

    

    void printAll() {
        // Traverse each index:
        for (int i = 0; i < total_elements; i++) {
            cout << "Index " << i << ": ";
            // Traverse the list at current index:
            for (int j : table[i])
                cout << j << " => ";

            cout << endl;
        }
    }
    int search(int key, int r[]) {
        int x = getHash(cal(key,r));

        vector<int>::iterator i;
        for (i = table[x].begin(); i != table[x].end(); i++) {
            // Check if the iterator points to the required item:
            if (*i == key)
                break;
        }

        // If the item was found in the list, then delete it:
        if (i != table[x].end())
        {
            return -1;
        }
        else {
            return -2;
        }
            
    }
    int cal(int a, int r[]) {
        int b = 0;
        int sum = 0;

        for (int i = 0; i < 4; i++) {
            b = a % 256;
            sum = sum + b * r[i];
            a = a / 256;
            b = 0;
        }
        return sum;
    }
};
bool isprime(int n) {
    bool isPrime = true;
    if (n == 0 || n == 1) {
        isPrime = false;
    }
    else {
        for (int i = 2; i <= n / 2; ++i) {
            if (n % i == 0) {
                isPrime = false;
                break;
            }
        }
    }
    return isPrime;
}

int find_M(int size) {
    int i = 0;
    while (true) {
        if (isprime(size + i)) {
            return size + i;
        }
        i = i + 1;
    }
}




int main() {

    // Create a hash table with 3 indices:
    random_device rd;
    default_random_engine gen = std::default_random_engine(rd());
    uniform_int_distribution<int> dis(1, 1073741824);

    vector<int> v;
    vector<int> test;
    float result;
    float result1;
    clock_t t1,t2;

    int r[4];
    

    std::ofstream myFile("s.csv");
    myFile << "power of 2" << "," << "insert" << "," << "search" << endl;

    for (int k = 10; k <= 30; k++) {
        int size = pow(2, k);
        int M = find_M(size);
        HashTable ht(M);

        for (int m = 0; m < 4; m++) {
            r[m] = (rand() % M);
        }

        t1 = clock();
        for (int i = 0; i <= size; i++) { //產生insert亂數
            v.push_back(dis(gen));
            ht.insertElement(v[i], r);
        }
              
        t1 = clock() - t1;
        result = ((float)t1 / CLOCKS_PER_SEC);

        t2 = clock();
        for (int i = 0; i <= 100000; i++) { //產生search亂數
            test.push_back(dis(gen));
        }

        for (int i = 0; i < 100000; i++) {
            ht.search(test[i], r);
        }
        t2 = clock() - t2;
        result1 = ((float)t2 / CLOCKS_PER_SEC);



        cout << k << endl;
        cout << result << endl;
        myFile << k << "," << result << "," << result1 << endl;

        vector<int>().swap(v);
        vector<int>().swap(test);



    }
    
    return 0;
}
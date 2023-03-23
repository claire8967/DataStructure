#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <algorithm> //MergeSort、HeapSort會用到

using namespace std;


//Lomuto Partition、Hoare Partition、Dutch Flag Partition實驗程式碼

int main() {
    double sum = 0;
    vector<int> v;
    std::ofstream myFile("k.csv");

    for (int k = 10; k <= 30; k++) {
        long long size = pow(2, k);

        for (int j = 0; j <= 9; j++) {
            double a = 0;
            for (long long i = 0; i <= size; i++) {
                v.push_back(rand() % 1001);
            }

            clock_t t;
            t = clock();
            Quicksort(v, 0, v.size() - 1);
            t = clock() - t;
            cout << j << endl;
            cout << fixed << setprecision(8) << ((float)t / CLOCKS_PER_SEC) << endl;
            a = (float)t / CLOCKS_PER_SEC;

            sum = sum + a;
            vector<int>().swap(v);
        }

        double avg;
        avg = sum / 10;
        cout << avg << endl;
        myFile << k << "," << avg << endl;
        sum = 0;
        avg = 0;
    }
}

//MergeSort 實驗程式碼

int main() {
    double sum = 0;

    std::ofstream myFile("k.csv");
    int k{ 10 };
    while (k <= 30) {
        int size = pow(2,k);
        

        for (int j = 0; j <= 9; j++) {
            double a = 0;
            vector <int> m;
            vector <int> n;
            vector <int> v(size);
            for (int i = 1; i <= size/2; i++) {
                m.push_back(rand() % 1001);
                n.push_back(rand() % 1001);
            }

            clock_t t;
            t = clock();
            sort(m.begin(), m.end());
            sort(n.begin(), n.end());
            merge(m.begin(), m.end(), n.begin(), n.end(), v.begin());
            t = clock() - t;
            cout << j << endl;
            cout << fixed << setprecision(8) << ((float)t / CLOCKS_PER_SEC) << endl;
            a = (float)t / CLOCKS_PER_SEC;
          
            sum = sum + a;
            vector<int>().swap(m);
            vector<int>().swap(n);
            vector<int>().swap(v);
            
        }

        double avg;
        avg = sum / 10;
        cout << avg << endl;
        myFile << k << "," << avg << endl;
        sum = 0;
        avg = 0;
        k++;
    }

    myFile.close();
    return 0;
}

//HeapSort實驗程式碼

int main() {
    double sum = 0;

    std::ofstream myFile("k.csv");
    int k{ 10 };
    while (k <= 30) {
        int size = pow(2, k);


        for (int j = 0; j <= 9; j++) {
            double a = 0;

            vector <int> v;
            for (int i = 1; i <= size; i++) {
                v.push_back(rand() % 1001);
            }

            clock_t t;
            t = clock();
            make_heap(v.begin(), v.end());
            sort_heap(v.begin(), v.end());
            t = clock() - t;
            cout << j << endl;
            cout << fixed << setprecision(8) << ((float)t / CLOCKS_PER_SEC) << endl;
            a = (float)t / CLOCKS_PER_SEC;

            sum = sum + a;

            vector<int>().swap(v);

        }

        double avg;
        avg = sum / 10;
        cout << avg << endl;
        myFile << k << "," << avg << endl;
        sum = 0;
        avg = 0;
        k++;
    }
}
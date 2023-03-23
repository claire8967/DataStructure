# DS_HW3
#107304053統計四 吳苡菡

影片連結
https://youtu.be/U13nLQtK7g4

•	（30%）在報告中請畫出每種資料結構新增資料所需時間：
![](https://i.imgur.com/FHF3Dsu.png)
![](https://i.imgur.com/nb6gy4g.png)

insertion sort 的時間複雜度為 O(n^2)，遠大於其他三個資料結構，若是去除掉insertion，可從圖中看出在其他三種資料結構當中的時間複雜度是相距不遠的，但實際情況下，treap 以及 skipList的insert時間複雜度均為 O(logn)而非 O(1)，我認為這可能是因為雖然 hashtable的insert動作是 O(1)，但在資料筆數較大的時候，計算 hashfuction 需要較多的時間所造成的狀況。

•	（30%）在報告中請畫出每個資料結構搜尋資料所需時間：
![](https://i.imgur.com/VpPRTAZ.png)
![](https://i.imgur.com/KG7EemY.png)

hashtable的搜尋時間為 O(1)，但在曲線中有時候花的時間卻比其他資料結構多，原因在於計算hashfunction所花的時間，但觀察其曲線的變動狀態，可以推論不論hashtable裡的資料有多少筆，在都是搜尋10萬筆資料，且collision的狀況不嚴重的情況下，他所花的時間都會在常數時間內完成，而其他種資料結構為在 O(logn)的時間完成。

o	Hash table外的資料結構程式碼來源（未提供則整份作業以0分計算）
https://www.educative.io/edpresso/how-to-implement-a-hash-table-in-cpp

o	（30%）錄製影片（最長10分鐘）解釋你實作hash table的程式碼。報告請附影片連結。
https://youtu.be/U13nLQtK7g4

o	實驗程式碼（含新增與搜尋的程式碼範例）與使用說明
treap、sortedArray、skipList的程式碼沿用上次 HW2

```
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
```
* hash function 介紹
implement in C++
1. collision處理：使用chaining，也就是當兩個key產生collision時，會用linkedlist將它們串在同一列hashfunction之中
ex：
..:: Hash Table ::..
Index 0: 6 => 
Index 1: 4 => 10 => 
Index 2: 2 => 8 =>
2. hash function 計算
    00000000 10100010 00001001 11110000
    將32bit整數分成4byte，
    以上述為例，則
    x1 = 00000000，x2 = 10100010，x3 = 00001001，x4 = 11110000
    h(x) = (r1*x1 + r2*x2 + r3*x3 + r4*x4) % M

    M 為 比n大 且最接近n的質數
3. insert步驟 
    Steps
    1 決定好n後，呼叫 find_M(n) 找出 M
    2 找出M後，建立 hashtable，HashTable ht(M);
    3 random 出 r1,r2,r3,r4,儲存在陣列r裡
    4 呼叫 ht.insertElement(element,r)
        use cal(key,r) 計算 (r1*x1 + r2*x2 + r3*x3 + r4*x4)
        再用 gethash(cal(key,r)) 計算 mod(M) 之後的結果
        得到的值即為資料所在的 hashfunction 欄位
4. search步驟
   1 決定好要搜尋的key後，呼叫 ht.search(key,r)，用 hashfunction 算出此值如果存在在hashtable，應該要在哪一列
   2 知道在哪一列後，遍歷那一列的元素，若還未遍歷到最後就找到key，則搜尋成功，否則搜尋失敗
   
o	（10%）心得、疑問、與遇到的困難
心得：
做完實驗後了解到，hashtable所花的時間基本上都是在hashfunction的計算，且若是想避免collision，通常需要佔用比較大的空間，且雖然在insert、search時的時間在 O(1)，但卻喪失了 spatial locality，故使用 hashtable 的時機必須要審慎考慮。

遇到的困難：
hashtable的insert及search均在跑到2的25次方後出現記憶體空間不足的情況



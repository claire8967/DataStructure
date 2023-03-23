# DS_HW1
#107304053統計四 吳苡菡

**1. (70%) 一個折線圖（包含5 條折線）。折線圖的x 軸為陣列大小，y 軸為對應的平均執行時間。每個排序方法用一條折線表示其執行時間。請解釋你的實驗結果。**

    
下表是的每一格代表該演算法在2的x次方筆資料情況下所花的平均運行時間(執行十次)，Lomuto實驗在執行到2的27次方時執行時間會超越1小時，其他演算法在執行超過2的28次方時會因為Heap空間不足而無法執行(故無資料)。
![](https://i.imgur.com/GwjTSBw.png)

![](https://i.imgur.com/PETzRGr.png)
x軸為2的x次方取log，y軸為時間(s)

五個演算法的Amortized時間複雜度皆在 O(nlogn) ，但以圖形來看Lomuto的趨勢卻與其他演算法不太相同，在實驗中，造成這五個演算法速度差距的原因應該是重複資料的處理方式，在資料筆數較少(<2^22次方)時速度的差距並不明顯，但資料筆數大時，由於隨機資料的大小在1-1000之間，故重複資料的筆數一定很多

我認為在此情況下，Ustable的演算法速度會明顯受到影響，所以挑選同樣是Unstable的演算法 HeapSort來做實驗，而確實在折線圖中 Lomuto 及 HeapSort 所花的時間與其他三個 Stable 演算法相比較多，但也可明顯觀察到 Lomuto Partition 和 HeapSort雖然同為 Unstable，成長的速率卻不相同。

舉例來說，對A = [5,5,5,5,5] 做 Sorting，
在 Lomuto Partition 演算法中是 Worst Case，但在 Hoare Partition 卻是 Best Case，
而 Lomuto Partition 演算法的 Worst Case 更是會使速度降低到 O(n^2)水準，
計算方法為 
由T(n) = 2T(n-1) + c*n = 2T(n-2)+c*((n-1)+n) = .... = c*1/2(n+2)(n-1)
得到 O(n^2)

而對於 HeapSort來說，雖然是Worst Case，但不管是 Best/Worst case，運算時間皆在 O(nlogn)
計算方法為
先以Bottom-up方法建Heap花 O(n)，
再執行(n-1)round，每一 round 花 logn 時間，將"Max與樹最後一個元素交換並進行adjust" 
故時間複雜度仍然低於 Lomuto Partition


**2.	(5%) 每個Sorting 演算法的程式碼來源。**
        A.	Lomuto Partition：GeeksforGeeks
        https://www.geeksforgeeks.org/hoares-vs-lomuto-partition-scheme-quicksort/
        B.	Hoare Partition：GeeksforGeeks
        https://www.geeksforgeeks.org/hoares-vs-lomuto-partition-scheme-quicksort/
        C.	Dutch Flag Partition：GeeksforGeeks
        https://www.geeksforgeeks.org/3-way-quicksort-dutch-national-flag/
        D.	Merge Sort：C++內建函示庫 
        https://en.cppreference.com/w/cpp/algorithm/merge
        E.	Heap Sort：C++內建函示庫 
        https://en.cppreference.com/w/cpp/algorithm/sort_heap







**3.	(5%) 實驗的程式碼。**
```
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <algorithm> //MergeSort、HeapSort會用到

using namespace std;
```

Lomuto Partition、Hoare Partition、Dutch Flag Partition實驗程式碼
```
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
```
MergeSort 實驗程式碼
```
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
```
HeapSort實驗程式碼
```
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
```

4. **(20%) 心得、疑問、與遇到的困難**
    
    心得：
    * 原本自己寫程式時其實沒有很清楚感受到 Array 和 Vector 的差距在哪，但在遇到這種大筆資料的時候，才感覺到似乎用Array的速度較快，但同時Stack的空間也比較小
    * 在小筆資料時，感覺不管用哪個演算法做Sorting都差不多，但在用大筆資料做實驗時，就能明顯感覺到差距 (Lomuto & Hoare)，也讓我了解到 Stable 的演算法其實有很多好處
    * 因為對於 Python 的畫圖套件比較熟悉，所以最一開始先使用 Python 試了一下，與 C++ 相比，Python的執行速度真的慢了許多，雖然以前理論上了解 C/C++ 的速度較快，但這是第一次這麼有實感
    
    

    遇到的困難：
    * 原本想說因為實驗的資料筆數是固定的，所以程式碼是使用 Array ，但大約在 n>=2^22次方時會遇到StackOverflow的問題，所以改用 Vector
    * 改用 Vector 後資料是存在 Heap ，卻又大約在 n>=2^24次方時遇到 badalloc()問題
    * 原本是使用VScode編譯器，但沒有找到如何從VScode更改Heap空間的方法，所以改用VisualStudio編譯器，啟用大型記憶體以及增加基本堆疊空間後，成功執行到2^27次方，但在2^28次方仍然會遇到badalloc()問題
    * 一開始跑程式時就明顯感受到，明明Lomuto是O(nlogn)的演算法，為何執行的時間會和其他演算法差那麼多

    疑問：
    * 自己明明已經在 VSstudio 將 Heapsize 的權限開到很大，但是不知道為什麼在 2^28次方以上仍然會遇到問題(雖然我了解這不是本次實驗的重點)，但在寫信詢問老師之前真的煩惱滿久的，我想我對於作業系統的了解實在太粗淺導致我在解決這些問題的手法實在是太粗糙
    * 不知道自己上面的分析是否正確，但如果 Lomuto Partition 的演算法在 Worst Case (多筆資料相同) 的代價這麼高，是不是大家在做 QuickSort的時候都會選用 Hoare Partition呢 ?
         




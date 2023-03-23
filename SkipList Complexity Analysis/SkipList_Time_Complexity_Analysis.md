# DS_HW2
#107304053統計四 吳苡菡

•	比較SkipList(p=0.5)、SkipList(p=0.1)、SkipList(p=0.9)、Treap、Sorted_Array

•	**（30%）在報告中請畫出每種資料結構新增資料所需時間：**
![](https://i.imgur.com/vhalH19.jpg)
![](https://i.imgur.com/4dBNWoT.jpg)


這邊的 Sorted_Array 我是用 insertion sort，因為它的處理方式比較像 SkipList 那樣一次一個 node 加上去 ( 若是用 quicksort 那類是等資料都 insert 進去後在 Sort )

由第一張圖知道 Sorted_Array 的趨勢明顯與其他資料結構不同，insertion_sort 的時間複雜度為 O(n^2)，為了方便觀察其他四個資料結構的趨勢，故將其拿掉後觀察第二張圖

可以發現以 SkipList 來說
* SkipList(p=0.5) 與 Treap 的時間複雜度都是典型的以2為底的 O(log(n))
* 若是 p 值太小，insert 的時間會較高，原因是它每次 insert 時有高機率都要遍歷一次 Level 0 的 node，p 值小的 SkipList 與 LinkedList 的相似程度高
* 若是 p 值太大，雖然 insert 時不需要常常遍歷其他 node，但因為它的 p 值高，無法輕易的終止，同樣的 insert 時間應該也會較 p=0.5 時高，雖然這邊我的 p=0.9 高次方數據因為 bad_alloc()沒有顯示出來，但我預測它的執行時間會大於 p=0.5






•	**（30%）在報告中請畫出每個資料結構搜尋資料所需時間：**
![](https://i.imgur.com/ZZBr9g4.jpg)
![](https://i.imgur.com/15MIDbA.jpg)

這邊 Sorted_Array 的搜尋方法我是用 BinarySearch，時間複雜度明顯較其他資料結構高，故跟剛剛一樣把其他四個資料結構分開拿出來討論

可以發現 p=0.1 的搜尋時間最高，因為它的 level 數太少，故與 insert 有相同的問題，每次 search 時高機率要遍歷非常多的 node，而 p=0.9 的雖然 level數高，但速度卻也沒有 p=0.5快，這應該也是因為樹高較高所導致


•	**（10%）在報告中請畫出三種skip list在不同的n值時的list個數。請解釋你得到的結果。**
![](https://i.imgur.com/Vm6eb8B.jpg)

level值 = List數 (level值從1開始算)
1. SkipList 的機率是影響 copy 數的主因，SkipList 的 insert 定義就是在 insert 資料時，有 p 的機率向上增加一個 List，故 numsOfList(p=0.9) > numsOfList(p=0.5) > numsOfList(p=0.1)
2. 直覺來看可能會覺得 p值那麼小，怎麼可能level數那麼高，但因為資料筆數很大的關係，所以其實是可能的，實際計算例子如下：
以p=0.1為例，若是有3個 List ，則代表在 2^k 筆資料之中，至少有一筆資料在 random 時達到了 (0.1)^2 * (0.9)^1=0.00009，P(至少有一筆資料在level3) = 1-(0.9991)^1024 = 0.6023，約等於 60%


        
        
•	**（5%）在報告中請畫出三種skip list在不同的n值時，平均每個data的additional copy個數。**
![](https://i.imgur.com/y5CsbnJ.jpg)

其實 SkipList 的機制有點類似於幾何分配，也就是在 Bernoulli trial 中，得到一次成功所需要的試驗次數X，故平均每個 data 的 additional copy 個數就會是幾何分配的期望值(E(x)=1/p)
故 p=0.1 時，成功機率為1-0.1=0.9，平均 copy 數為 1/0.9，約等於 1.1
故 p=0.5 時，成功機率為1-0.5=0.5，平均 copy 數為 1/0.5，約等於 2
故 p=0.9 時，成功機率為1-0.9=0.1，平均 copy 數為 1/0.1，約等於 10



o	資料結構程式碼來源（未提供則整份作業以0分計算）
    1.     Treap: GeeksforGeeks
    https://www.geeksforgeeks.org/treap-set-2-implementation-of-search-insert-and-delete/
    2.  SkipList: GeeksforGeeks
    https://www.geeksforgeeks.org/skip-list-set-2-insertion/
    https://www.geeksforgeeks.org/skip-list-set-3-searching-deletion/
    3. Insertion_sort (用BinarySearch):
    https://www.geeksforgeeks.org/insertion-sort/
    https://www.geeksforgeeks.org/binary-search/
    
o	（5%）解釋如何修改skip list程式碼（以註解呈現）

```
SkipList::SkipList(int MAXLVL, float P) //透過更改P值修改Probabilty
{
    this->MAXLVL = MAXLVL;
    this->P = P;
    level = 0;
    header = new Node(-1, MAXLVL);
};
int main(){
        SkipList low_prob(15, 0.1);
        SkipList prob(50, 0.5);
        SkipList high_prob(160, 0.9);
}
```
o	（10%）實驗程式碼（含新增與搜尋的程式碼範例）與使用說明。
* 迴圈每跑一次就計算五個不同資料結構的 insert、search 時間，並將結果存在 result 陣列，而SkipList 的List數及AvgCopy數則存在 nums 陣列及 copy 陣列
* 若跑出來的結果大於一小時，則該資料結構下次迴圈就不跑
* 因為 search 的範圍大於 rand_MAX = 2^15-1，故採用 C++ mt19937來產生亂數
* SkipList 的 List 數是直接回傳物件裡的 level+1 即可
* SkipList 的 AvgCopy 數是將 SkipList 每一 level 遍歷一次算出 node 總數後除以 level 0 的資料數
* Treap 在執行到 2^24 次方以上會出現 bad_alloc，SkipList則是在 2^26 次方，故這支程式其實只能順利執行到 2^23 次方， 數據裡 SkipList 在 2^24 次方後的資料是另外跑的
```
#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
    
void insertionSort(vector<int> array , int size) {
      for (int step = 1; step < size; step++){
            int key = array[step];
            int j = step - 1;
            while (key < array[j] && j >= 0) {
              array[j + 1] = array[j];
              --j;
            }
        array[j + 1] = key;
        }
}
struct TreapNode
{
    int key, priority;
    TreapNode* left, * right;
};

TreapNode* rightRotate(TreapNode* y)
{
    TreapNode* x = y->left, * T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}
TreapNode* leftRotate(TreapNode* x)
{
    TreapNode* y = x->right, * T2 = y->left;
    y->left = x;
    x->right = T2;
    return y;
}

TreapNode* newNode(int key)
{   
    random_device rd;
    default_random_engine gen = std::default_random_engine(rd());
    uniform_int_distribution<int> dis(1,1073741824);

    TreapNode* temp = new TreapNode;
    temp->key = key;
    temp->priority = dis(gen);
    temp->left = temp->right = NULL;
    return temp;
}

TreapNode* search(TreapNode* root, int key)
{
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return search(root->right, key);

    return search(root->left, key);
}

TreapNode* insert(TreapNode* root, int key)
{
    if (!root)
        return newNode(key);
 
    if (key <= root->key)
    {
        root->left = insert(root->left, key);
 
        if (root->left->priority > root->priority)
            root = rightRotate(root);
    }
    else 
    {
        root->right = insert(root->right, key);
 
        if (root->right->priority > root->priority)
            root = leftRotate(root);
    }
    return root;
}
 
class Node
{
public:
    int key; 
    Node** forward;
    Node(int, int);
};

Node::Node(int key, int level)
{
    this->key = key;

    forward = new Node * [level + 1];

    memset(forward, 0, sizeof(Node*) * (level + 1));
};


class SkipList
{ 
    int MAXLVL;
    float P;
    int level;
    Node* header;

public:
    SkipList(int, float);
    ~SkipList();
    int randomLevel();
    Node* createNode(int, int);
    void insertElement(int);
    bool search(int);
    int NumsOfList();
    float AvgOfCopy();
    void deleteElement(int);
};

SkipList::SkipList(int MAXLVL, float P)
{
    this->MAXLVL = MAXLVL;
    this->P = P;
    level = 0;
    header = new Node(-1, MAXLVL);
};


int SkipList::randomLevel()
{
    float r = (float)rand() / RAND_MAX;
    int lvl = 0;
    while (r < P && lvl < MAXLVL)
    {
        lvl++;
        r = (float)rand() / RAND_MAX;
    }
    return lvl;
};

Node* SkipList::createNode(int key, int level)
{
    Node* n = new Node(key, level);
    return n;
};

void SkipList::insertElement(int key)
{
    Node* current = header;
    Node* update[MAXLVL + 1];
    memset(update, 0, sizeof(Node*) * (MAXLVL + 1));

    for (int i = level; i >= 0; i--)
    {
        while (current->forward[i] != NULL &&
            current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }
    current = current->forward[0];

    if (current == NULL || current->key != key)
    {
        int rlevel = randomLevel();
        if (rlevel > level)
        {
            for (int i = level + 1; i < rlevel + 1; i++)
                update[i] = header;

            level = rlevel;
        }

        Node* n = createNode(key, rlevel);
        for (int i = 0; i <= rlevel; i++)
        {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
    }
};

bool SkipList::search(int key)
{
    Node *current = header;
  
    for(int i = level; i >= 0; i--)
    {
        while(current->forward[i] &&
               current->forward[i]->key < key)
            current = current->forward[i];
  
    }
    current = current->forward[0];
    if(current and current->key == key) 
        return true;
    else{
        return false;
    }
};

float SkipList::AvgOfCopy()
{   vector <int> p;
    vector <int> d;
    int sum = 0;
    for (int i = 0; i <= level; i++)
    {
        Node* node = header->forward[i];
        while (node != NULL)
        {
            node = node->forward[i];
            sum = sum + 1;
        }
        p.push_back(sum);
        sum = 0;
    }
    float avg=0;
    for (unsigned int k=0;k<p.size();k++){
        avg = avg + p[k];
    }
    return avg/p[0];
    
};
int SkipList::NumsOfList(){
    return (level+1) ;
};

int binarySearch(vector<int>arr, int l, int r, int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;
 
        if (arr[mid] == x)
            return mid;
 
        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);
 
        return binarySearch(arr, mid + 1, r, x);
    }
    return -1;
}

SkipList::~SkipList() {
    cout <<"des"<<endl;
    for (int i=0;i<=level;i++)
    {
        Node *node = header->forward[i];
        while (node != NULL)
        {
            node = node->forward[i];
            deleteElement(node->key);
        }
    }
}

void SkipList::deleteElement(int key)
{
    Node *current = header;
    Node *update[MAXLVL+1];
    memset(update, 0, sizeof(Node*)*(MAXLVL+1));

    for(int i = level; i >= 0; i--)
    {
        while(current->forward[i] != NULL  &&
              current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }
    current = current->forward[0];

    if(current != NULL and current->key == key)
    {
        for(int i=0;i<=level;i++)
        {
            if(update[i]->forward[i] != current)
                break;
  
            update[i]->forward[i] = current->forward[i];
        } 
        while(level>0 &&
              header->forward[level] == 0)
            level--;
    }
};
int main()
{

    std::ofstream myFile("tt.csv");
    myFile << "power of 2" <<","<<"p=0.1 insert"<<","<<"p=0.1 search" <<"," << "p=0.1 numsOfList" <<","<< "p=0.1 AvgOfCopy" <<","<<"p=0.5 insert"<<","<<"p=0.5 search" <<"," << "p=0.5 numsOfList"<<","<< "p=0.5 AvgOfCopy"<<","<<"p=0.9 insert"<<","<<"p=0.9 search" <<"," << "p=0.9 numsOfList"<< ","<<"p=0.9 AvgOfCopy" <<","<< "treap_insert" <<","<<"treap_search"<< ","<<"insertion"<<","<<"insertion_serch"<< endl;
    vector<int> v;
    vector<int> test;
    float result[10]{0}; //五個資料結構在2的k次方大小時的insert、search時間 共十項
    int nums[3]{0}; //三個不同機率的SkipList(在2的k次方大小時)的List數 共三項
    float copy[3]{0}; //三個不同機率的SkipList(在2的k次方大小時)的平均copy數 共三項
    
    random_device rd;
    default_random_engine gen = std::default_random_engine(rd());
    uniform_int_distribution<int> dis(1,1073741824);

    SkipList low_prob(15, 0.1);
    SkipList prob(50, 0.5);
    SkipList high_prob(160, 0.9);

    for (int k = 10; k <= 30; k++) {
        struct TreapNode* root = NULL;

        int size = pow(2, k);

        for (int i = 0; i <= size; i++) { //產生insert亂數
            v.push_back(dis(gen));
        }
        for(int i=0; i<=100000;i++){ //產生search亂數
            test.push_back(dis(gen));
        }

        clock_t t1; 
        clock_t s1;
        if(result[0]<3600){
            t1 = clock();
            for (int i = 0; i <= size; i++) {
                lst.insertElement(v[i]);
            }
            t1 = clock() - t1;
            result[0] = ((float)t1 / CLOCKS_PER_SEC);
            nums[0] = lst.NumsOfList();
            copy[0] = lst.AvgOfCopy();
            }
        if(result[1]<3600){
            s1 = clock();
            for(int i=0; i<=100000;i++){
                lst.search(test[i]);
            }
            s1 = clock() - s1;
            result[1] = ((float)s1 / CLOCKS_PER_SEC);
            }

        clock_t t2;
        clock_t s2;
        if(result[2]<3600){
            t2 = clock();
            for (int i = 0; i <= size; i++) {
                lstt.insertElement(v[i]);
            }
            t2 = clock() - t2;
            result[2] = ((float)t2 / CLOCKS_PER_SEC);
            nums[1] = lstt.NumsOfList();
            copy[1] = lstt.AvgOfCopy();
            }
        if(result[3]<3600){
            s2 = clock();
            for(int i=0; i<=100000;i++){
                lstt.search(test[i]);
            }
            s2 = clock() - s2;
            result[3] = ((float)s2 / CLOCKS_PER_SEC);
            }

        clock_t t3;
        clock_t s3;
        if(result[4]<3600){
            t3 = clock();
            for (int i = 0; i <= size; i++) {
                lsttt.insertElement(v[i]);
            }
            t3 = clock() - t3;
            result[4] = ((float)t3 / CLOCKS_PER_SEC);
            nums[2] = lsttt.NumsOfList();
            copy[2] = lsttt.AvgOfCopy();
            }
        if(result[5]<3600){
            s3 = clock();
            for(int i=0; i<=100000;i++){
                lsttt.search(test[i]);
            }
            s3 = clock() - s3;
            result[5] = ((float)s3 / CLOCKS_PER_SEC);
            }

        clock_t t4;
        clock_t s4;
        if(result[6]<3600){
            t4 = clock();
            for (int i = 0; i <= size; i++) {
                root = insert(root, v[i]);
            }
            t4 = clock() - t4;
            result[6] = ((float)t4 / CLOCKS_PER_SEC);}
        if(result[7]<3600){
            s4 = clock();
            for(int i=0; i<=100000;i++){
                root = search(root,test[i]);
            }
            s4 = clock() - s4;
            result[7] = ((float)s4 / CLOCKS_PER_SEC);}
                                        
        clock_t t5;
        clock_t s5;

        if(result[8]<3600){
            t5 = clock();
            insertionSort(v, size);
            t5 = clock() - t5;
            result[8] = ((float)t5 / CLOCKS_PER_SEC);
            }
        if(result[9]<3600){
            s5 = clock();
            for(int i=0; i<=100000;i++){
                binarySearch(v, 0, v.size()- 1, test[i]);}
            s5 = clock() - s5;
            result[9] = ((float)s5 / CLOCKS_PER_SEC);
        }



        myFile << k << "," << result[0] << "," << result[1] <<"," << nums[0] << "," << copy[0] << "," << result[2] << "," << result[3] << "," << nums[1] << "," << copy[1] << "," << result[4] << "," << result[5] <<"," << nums[2] << "," << copy[2] << "," << result[6] <<"," << result[7] <<"," << result[8] <<"," << result[9] <<endl;
        vector<int>().swap(v);
        vector<int>().swap(test);
    }

    return 0;
}  
```



（10%）心得、疑問、與遇到的困難

心得、疑問
1. 雖然一開始學 SkipList 時覺得將 p 設為 0.5 是一件很直覺的事，但深入去想才知道他是為了讓整個 SkipList 的高度和其他高等樹一樣是以 2 為底的 log(n)
2. p 的大小不是一味的高就好，太高的話會造成樹高不為 log(n)，太低的話則會造成 SkipList 退化成 LinkedList，以致 insert、search 的速度不佳
3. search 的時間複雜度雖然說是 O(logn)，但它的秒數都很短，雖然能從圖大致看得出趨勢，但其實增長的幅度並不大，不知道是否是因為 random 出來的數字其實並不是 random 造成的，這點讓我十分疑惑


遇到的困難
1. 這次作業對於亂數的範圍需求較大，在一開始做實驗時我和上次一樣先使用了一般的 rand() 函數，原以為已經成功取得了實驗數據，但觀察到數據的趨勢似乎不太對才知道，原來 rand() 亂數的範圍只到2^15-1而已，後來才使用 C++ mt19937 內建函示庫解決問題
4. 雖然把不同資料結構寫入同一個檔案，但不同資料結構造成 bad_alloc() 的時間點不一樣，造成若是有一個資料結構 bad_alloc() 會拖累到其他資料結構實驗的進行，有試過用 try catch 去解決，但效果不太好，後來還是把其他資料結構拉出來額外跑
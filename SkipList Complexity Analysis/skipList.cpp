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
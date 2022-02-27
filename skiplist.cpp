#include <iostream>
#include <stdlib.h>
#include <vector>
#include "skiplist.h"
#include <time.h>
using namespace std;

double SkipList::my_rand()   // 这是一个生成p值为0.5的函数
{
    s = (16807 * s) % 2147483647ULL;
    return (s + 0.0) / 2147483647ULL;
}

int SkipList::randomLevel()
{
    int result = 1;
    while (result < MAX_LEVEL && my_rand() < 0.5)
    {
        ++result;
    }
    return result;
}


void SkipList::Insert(int key, int value){

   //  std::vector<SKNode *> update;
     int i = MAX_LEVEL - 1;
    SKNode *node = head;
    if(head->forwards[0] == NIL){  // 还没有节点
        int level = randomLevel();
        this->level = level;
        SKNode * insertNode = new SKNode(key, value, NORMAL);
        for(int i = 0; i < this->level; i++){  // 改变原有指针结构
            insertNode->forwards[i] = NIL;
            head->forwards[i] = insertNode;
        }
        return;
    }
    for( i = MAX_LEVEL - 1; i >= 0; i--){
        while ( node->forwards[i]->key < key){
            node = node->forwards[i];   //  进行一次右移
        }
        // i-- 会导致一次下移
        update[i] = node;  // 每次下移记录一次路线便于insert后修改之前变量的forward指针
    }
    node = node->forwards[0];
    if(node->key == key){
        node->val = value;  // 更新node的值
        return;
    }
    else {   // 不等，则在后面插入新节点
        int level = randomLevel();
        if(level > this->level ){ // 需要更新level
            for(int l = this->level; l <= level - 1; l ++){
                update[l] = head;
            }
            this->level = level;
        }

        SKNode * insertNode = new SKNode(key, value, NORMAL);
        for(int i = 0; i < level; i++){  // 改变原有指针结构
            insertNode->forwards[i] = update[i]->forwards[i];
            update[i]->forwards[i] = insertNode;
        }
    }
}

void SkipList::Search(int key)
{
    // TODO
    int i = MAX_LEVEL - 1;
    SKNode *node = head;
    for( i = MAX_LEVEL - 1; i >= 0; i--){
        while (node->forwards[i]->key < key)
        {
            if(node->type == NORMAL)  // 右移之前输出一次
                cout<<i+1<<','<< (node->key)<<" ";
            else cout<<i+1<<','<< ('h')<<" ";
            node = node->forwards[i];   //  进行一次右移
        }
        if(node->type == NORMAL)  // 下移之前输出一次
            cout<<i+1<<','<< (node->key)<<" ";
        else cout<<i+1<<','<< ('h')<<" ";
        // i++ 会导致一次下移
    }
    i++;
    node = node->forwards[0];
    if(node->type == NORMAL)
        cout<<i+1<<','<< (node->key)<<" ";
    else if(node->type == SKNodeType::NIL)
        cout<<i+1<<','<<'N'<<' ';
    else cout<<i+1<<','<< ('h')<<" ";
    if(node->key == key){  // 找到了
        cout<<node->val<<endl;
    }
    else {  // 没找到
        cout<<"Not Found"<<endl;
    }
}

void SkipList::Delete(int key)
{
  //   vector<SKNode *> update;
     int i = MAX_LEVEL - 1;
    SKNode *node = head;
    for( i = MAX_LEVEL - 1; i >= 0; i--){
        while ( node->forwards[i]->key < key){
            node = node->forwards[i];   //  进行一次右移
        }
        // i++ 会导致一次下移
        update[i] = node;  // 每次下移记录一次路线便于insert后修改之前变量的forward指针
    }
    node = node->forwards[0];
    if(node->key == key){
        for(int i  = 0; i < this->level; i++){
            if(update[i]->forwards[i] != node){  // 该节点的高度不够
                break;
            }
            update[i]->forwards[i] = node->forwards[i];
        }  
        //delete node;
    }
    while (this->level > 1 && head->forwards[this->level]->type == SKNodeType::NIL)  {  // 调整lsit的高度
        this->level--;
    }
    
}

void SkipList::Display()  // 打印当前的skiplist
{   
    for (int i = MAX_LEVEL - 1; i >= 0; --i)
    {
        std::cout << "Level " << i + 1 << ":h";
        SKNode *node = head->forwards[i];
        while (node->type != SKNodeType::NIL)
        {
            std::cout << "-->(" << node->key << "," << node->val << ")";
            node = node->forwards[i];
        }
        std::cout << "-->N" << std::endl;
    }
}
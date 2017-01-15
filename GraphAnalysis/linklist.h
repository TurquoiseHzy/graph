//
//  linklist.h
//  GraphAnalysis
//
//  Created by Ziyi Huang on 2017/1/13.
//  Copyright © 2017年 Ziyi Huang. All rights reserved.
//

#ifndef linklist_h
#define linklist_h

template<class DataType>
class LNode{
public:
    DataType data;
    LNode<DataType>* next;
    
public:
    LNode():
        data(NULL),
        next(NULL)
    {
        
    }
    LNode(const DataType& d):
        data(d),
        next(NULL)
    {
        
    }
};


template<class DataType>
class LList{
public:
    int count;
    LNode<DataType> *head, *tail;
    
public:
    LList():
    head(new LNode<DataType>()),
    tail(head),
    count(0)
    {
        
    }
    
    
public:
    LNode<DataType>* insert(const DataType& d){
        LNode<DataType> *newNode = new LNode<DataType> (d);
        tail -> next = newNode;
        tail = newNode;
        count ++;
        return newNode;
    }
    
    LList<DataType> operator + (const DataType& tailData){
        LList<DataType>* newList = new LList<DataType>();
        LNode<DataType>* now = head->next;
        while(now != NULL){
            newList->insert(now->data);
            now = now -> next;
        }
        newList->insert(tailData);
        return *newList;
    }
};

#endif /* linklist_h */

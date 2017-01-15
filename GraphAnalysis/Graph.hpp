//
//  Graph.h
//  GraphAnalysis
//
//  Created by Ziyi Huang on 2017/1/13.
//  Copyright © 2017年 Ziyi Huang. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <float.h>
#include <vector>

#include "linklist.h"
#include "DataType.h"

#define UNCALC DBL_MAX

class Node;
typedef LList<int> Path;


//classdef Edge
class Edge{
public:
    Node** node;
    int value;

public:
    Edge(Node*, Node*, const double&);
    ~Edge();
};//Edge


//classdef Node
class Node{
public:
    int number;
    DataType data;
    LList<Edge*>* relevantEdge;
    int degree;
    bool isVirtual;
    
public:
    Node(int);
    Node();
    ~Node();
};//Node


//classdef ShortestPath
class ShortestPath{
public:
    std::vector<Path> path;
    bool* inside;
    int graphSize;
    double val;
    
public:
    ShortestPath(const int&);
    
public:
    void flush();
    void print(std::ostream&);
};//ShortestPath


//classdef SpanningTree
class SpanningTree{
public:
    int graphSize;
    Edge** edge;
    double val;
    
public:
    SpanningTree(const int&);
};//SpanningTree


//classdef Graph
class Graph{
public:
    Node** node;
    int size;
    ShortestPath*** shortestPath;
    ShortestPath* shortestPathInGraph;
    SpanningTree** minimumSpanningTree;
    SpanningTree* minimumSpanningTreeInGraph;
    double *betweennessCentrality;
    double *closenessCentrality;
    bool dijskstraAdmittion;
    
public:
    Graph(int);
    ~Graph();
    
public:
    void loadNode(const int&, const DataType&);
    void loadEdge(const int&, const int&, const double&);
    
public:
    ShortestPath* dijsktra(const int&, const int&);
    ShortestPath* spfa(const int&, const int&);
    ShortestPath* getShortestPath(const int&, const int&);
    double prim(const int&,SpanningTree *);
    double calcBC(const int&,double &);
    double calcCC(const int&,double &);
};//Graph

#endif /* Graph_h */

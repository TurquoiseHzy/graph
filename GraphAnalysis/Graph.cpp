//
//  Graph.cpp
//  GraphAnalysis
//
//  Created by Ziyi Huang on 2017/1/14.
//  Copyright © 2017年 Ziyi Huang. All rights reserved.
//

#include <iostream>

#include "Graph.hpp"


//constructor
Graph::Graph(int n):
    size(n),
    shortestPathInGraph(NULL),
    minimumSpanningTreeInGraph(NULL),
    dijskstraAdmittion(true)
{
    shortestPath = new ShortestPath** [n];
    minimumSpanningTree = new SpanningTree* [n];
    betweennessCentrality = new double [n];
    closenessCentrality = new double [n];
    node = new Node* [n];
    for(int i = 0 ; i < n ; i ++){
        node[i] = new Node(i);
        minimumSpanningTree[i] = NULL;
        shortestPath[i] = new ShortestPath* [n];
        betweennessCentrality[i] = UNCALC;
        closenessCentrality[i] = UNCALC;
        for(int j = 0 ; j < n ; j ++){
            shortestPath[i][j] = NULL;
        }
    }
}//Graph::Graph(int)


//constructor
Node::Node(int n):
    number(n),
    relevantEdge(new LList<Edge *> ()),
    degree(0),
    isVirtual(false)
{
    
}//Node::Node(int)


//constructor
Edge::Edge(Node* st, Node* ed, const double& val):
    value(val),
    node(new Node* [2])
{
    node[0] = st;
    node[1] = ed;
}//Edge::Edge(Node*, Node*, const double&)


//constructor
SpanningTree::SpanningTree(const int& gs):
    graphSize(gs),
    val(0)
{
    
}//SpanningTree::SpanningTree(int)


//constructor
ShortestPath::ShortestPath(const int& gs):
    graphSize(gs),
    val(0)
{
    inside = new bool[gs];
    for(int i = 0 ; i < gs ; i ++){
        inside[i] = false;
    }
}//ShortestPath::ShortestPath(int)


//destructor
Graph::~Graph()
{
    for(int i = 0 ; i < size ; i ++){
        delete[] shortestPath[i];
    }
    delete[] shortestPath;
    delete[] node;
    delete[] minimumSpanningTree;
    delete[] closenessCentrality;
    delete[] betweennessCentrality;
}//Graph::~Graph()


//unreachable
void ShortestPath::flush(){
    val = DBL_MAX;
    for(int i = 0 ; i < graphSize ; i ++){
        inside[i] = false;
    }
    path.clear();
}//ShortestPath::flush()


//print
void ShortestPath::print(std::ostream& outputStream){
    outputStream << val << std::endl;
    for(int i = 0 ; i < path.size() ; i ++){
        LNode<int>* iNow = path[i].head->next;
        while(iNow != path[i].tail){
            outputStream << iNow->data << "->";
            iNow = iNow -> next;
        }
        outputStream << path[i].tail->data << std :: endl;
    }
}//ShortestPath::print(std::ostream&)


//load node data
void Graph::loadNode(const int& number, const DataType& data){
    node[number]->data = data;
}//Graph::loadNode(const int&,const DataType&)


//add edge
void Graph::loadEdge(const int& startNodeNumber, const int& endNodeNumber, const double& value){
    Node* startNode = node[startNodeNumber];
    Node* endNode = node[endNodeNumber];
    Edge* newEdge = new Edge(startNode, endNode, value);
    startNode->relevantEdge->insert(newEdge);
    endNode->relevantEdge->insert(newEdge);
    startNode->degree ++;
    endNode->degree ++;
    if(value <= 0){
        dijskstraAdmittion = false;
    }
}//Graph::loadEdge(const int&, const int&, const double&)


//dijkstra
ShortestPath* Graph::dijsktra(const int &startNodeNumber, const int &endNodeNumber){
    ShortestPath* shortest = new ShortestPath(size);
    
    bool *calc = new bool [size];
    int calcNum = 0;
    double* dis = new double [size];
    std::vector<Path>* p = new std::vector<Path>[size];
    
    
    for(int i = 0 ; i < size ; i ++){
        calc[i] = false;
        dis[i] = DBL_MAX;
    }
    
    dis[startNodeNumber] = 0;
    Path primary;
    primary.insert(startNodeNumber);
    p[startNodeNumber].push_back(primary);
    
    LList<Edge*>* list = NULL;
    LNode<Edge*>* now = NULL;
    int minNumber = -1;
    double minDis = DBL_MAX;
    
    while(calcNum < size){
        minDis = DBL_MAX;
        for(int i = 0 ; i < size ; i ++){
            if(!calc[i] && dis[i] < minDis){
                minDis = dis[i];
                minNumber = i;
            }
        }
        
        if(minDis == DBL_MAX){
            shortest->flush();
            shortestPath[startNodeNumber][endNodeNumber] = shortest;
            shortestPath[endNodeNumber][startNodeNumber] = shortest;
            return shortest;
        }
        
        list = node[minNumber]->relevantEdge;
        now = list->head->next;
        while(now != NULL){
            for(int i = 0 ; i < 2 ; i ++){
                if(now->data->node[i]->number == minNumber){
                    continue;
                }
                if(dis[now->data->node[i]->number] > dis[minNumber] + now->data->value){
                    dis[now->data->node[i]->number] = dis[minNumber] + now->data->value;
                    p[now->data->node[i]->number].clear();
                    for(int j = 0 ; j < p[minNumber].size() ; j ++){
                        p[now->data->node[i]->number].push_back(p[minNumber][j] + now->data->node[i]->number);
                    }
                }
                else if(dis[now->data->node[i]->number] == dis[minNumber] + now->data->value){
                    for(int j = 0 ; j < p[minNumber].size() ; j ++){
                        p[now->data->node[i]->number].push_back(p[minNumber][i] + now->data->node[i]->number);
                    }
                }
            }
            now = now -> next;
        }
        calc[minNumber] = true;
        calcNum ++;
    }
    
    shortest->path = p[endNodeNumber];
    shortest->val = dis[endNodeNumber];
    for(int i = 0 ; i < p[endNodeNumber].size() ; i ++){
        LNode<int>* iNow = p[endNodeNumber][i].head->next;
        while(iNow != NULL){
            shortest->inside[iNow->data] = true;
            iNow = iNow -> next;
        }
    }
    
    shortestPath[startNodeNumber][endNodeNumber] = shortest;
    shortestPath[endNodeNumber][startNodeNumber] = shortest;
    return shortest;
}//Graph::dijsktra(const int &, const int &)


//spfa
ShortestPath* Graph::spfa(const int &startNodeNumber, const int &endNodeNumber){
    ShortestPath* shortest = new ShortestPath(size);
    //todo...
    
    shortestPath[startNodeNumber][endNodeNumber] = shortest;
    shortestPath[endNodeNumber][startNodeNumber] = shortest;
    return shortest;
}//Graph::spfa(const int &, const int &)


//shortestpath
ShortestPath* Graph::getShortestPath(const int &startNodeNumber, const int &endNodeNumber){
    if(shortestPath[startNodeNumber][endNodeNumber] != NULL){
        return shortestPath[startNodeNumber][endNodeNumber];
    }
    if(dijskstraAdmittion){
        return dijsktra(startNodeNumber, endNodeNumber);
    }
    else{
        return spfa(startNodeNumber, endNodeNumber);
    }
}//Graph::getShortestPath(const int &, const int &)


//prim
double Graph::prim(const int &startNodeNumber,SpanningTree * spanningTree){
    if(minimumSpanningTree[startNodeNumber] != NULL){
        spanningTree = minimumSpanningTree[startNodeNumber];
        return spanningTree->val;
    }
    spanningTree = new SpanningTree(size);
    //todo...
    
    minimumSpanningTree[startNodeNumber] = spanningTree;
    return spanningTree->val;
}//Graph::prim(const int &, ShortestPath*)


//calc betweenness centrality
double Graph::calcBC(const int &nodeNumber, double &res){
    if(betweennessCentrality[nodeNumber] != UNCALC){
        res = betweennessCentrality[nodeNumber];
        return res;
    }
    res = UNCALC;
    //todo...
    
    betweennessCentrality[nodeNumber] = res;
    return res;
}//Graph::calcBC(const int &, double)


//calc closeness centrality
double Graph::calcCC(const int &nodeNumber, double &res){
    if(closenessCentrality[nodeNumber] != UNCALC){
        res = closenessCentrality[nodeNumber];
        return res;
    }
    res = UNCALC;
    //todo...
    
    closenessCentrality[nodeNumber] = res;
    return res;
}//Graph::calccC(const int &, double)


// End Of Grpah.cpp

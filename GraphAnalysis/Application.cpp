//
//  Application.cpp
//  GraphAnalysis
//
//  Created by Ziyi Huang on 2017/1/14.
//  Copyright © 2017年 Ziyi Huang. All rights reserved.
//

#include "Application.hpp"
#include "DataType.h"

//constructor
Application::Application(std::istream& inputStream){
    int n,m;
    inputStream >> n >> m;
    graph = new Graph(n);
    
    int number = 0;
    DataType data;
    for(int i = 0 ; i < n ; i ++){
        inputStream >> number >> data;
        graph->loadNode(number, data);
    }
    
    int st,ed;
    double val;
    for(int i = 0 ; i < m ; i ++){
        inputStream >> st >> ed >> val;
        graph->loadEdge(st, ed, val);
    }
}//Application::Application(std::istream&)


//dijsktra
void Application::dijsktra(std::ostream &outputStream,const int& st, const int& ed){
    ShortestPath* res;
    res = graph->dijsktra(st, ed);
    res->print(outputStream);
}//Application::dijsktra(std::ostream &)

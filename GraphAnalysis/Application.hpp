//
//  Application.hpp
//  GraphAnalysis
//
//  Created by Ziyi Huang on 2017/1/14.
//  Copyright © 2017年 Ziyi Huang. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include <stdio.h>
#include <iostream>

#include "Graph.hpp"

//classdef
class Application{
private:
    Graph* graph;
    
public:
    Application(std::istream&);
    ~Application();
    
public:
    void dijsktra(std::ostream&, const int&, const int&);
};//Application
#endif /* Application_hpp */

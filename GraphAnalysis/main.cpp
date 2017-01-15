//
//  main.cpp
//  GraphAnalysis
//
//  Created by Ziyi Huang on 2017/1/13.
//  Copyright © 2017年 Ziyi Huang. All rights reserved.
//

#include <iostream>
#include <vector>

#include "Application.hpp"

int main(int argc, const char * argv[]) {
    Application* app = new Application(std::cin);
    app->dijsktra(std::cout, 0, 2);
    return 0;
}

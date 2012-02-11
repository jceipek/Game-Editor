//
//  ResourcePath.cpp.cpp
//  Editor
//
//  Created by Julian Ceipek on 2/8/12.
//  Copyright (c) 2012 Franklin W. Olin College of Engineering. All rights reserved.
//

#include "ResourcePath.hpp"
#include <iostream>
#ifndef USING_OBJ_C
std::string ResourcePath(void)
{
    std::cout << "Using Linux ResourcePath!\n";
    return "../Resources/";
}
#endif

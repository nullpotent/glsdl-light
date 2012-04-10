#pragma once
#define DEBUG
#include <iostream>

#ifndef DEBUG
    #define assert(x)
#else
    #define assert(x) \
                if(!(x)) \
                { \
                   std::cout<<"ERROR - ASSERT "<<#x<<" FAILED"<<std::endl; \
                   std::cout<<" on line "<< __LINE__ <<std::endl; \
                   std::cout<<" in file "<< __FILE__ <<std::endl; \
                }
#endif

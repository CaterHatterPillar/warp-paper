#ifndef DV2549_EXPERIMENT_COMMON_H
#define DV2549_EXPERIMENT_COMMON_H

#include <map>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <exception>

#define ZERO_MEM( arg ) ZeroMemory( &arg, sizeof( arg ) );
#define ASSERT_DELETE( arg ) assert( arg ); delete arg; arg = nullptr;

#endif // DV2549_EXPERIMENT_COMMON_H
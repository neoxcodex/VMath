// profiler.hpp
#pragma once
#include "nanobench.h"


namespace profiler {
    template<typename Func, typename... Args>
    auto profileFunction(const char* name, Func&& func, Args&&... args) {
        
        using RetType = decltype(func(args...));
        RetType result;
        
        ankerl::nanobench::Bench()
        .minEpochIterations(30000000)
        .run(name, [&] {
            // --- ADD THIS LINE ---
            // This forces the compiler to treat all arguments as dynamic
            (ankerl::nanobench::doNotOptimizeAway(args), ...); 
            
            result = func(std::forward<Args>(args)...);
            ankerl::nanobench::doNotOptimizeAway(result);
        });
        
        return result;
    }
}

// Usage:
// #include "profiler.hpp"
// auto result = profiler::profileFunction("myFunc", myFunc, arg1, arg2);
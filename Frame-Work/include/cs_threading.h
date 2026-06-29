#pragma once
#include <thread>
#include <mutex>
#include <shared_mutex>


namespace cs
{
    using Thread = std::thread;
    using Mutex = std::mutex;
    using Guard = std::lock_guard<Mutex>;
}
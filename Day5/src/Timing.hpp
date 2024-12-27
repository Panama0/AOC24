#pragma once

#include <chrono>
#include <iostream>
#include <ratio>

class Timing
{
public:
    Timing() = delete;

    static void start(const char* label = "The code")
    {
        m_label = label;
        if(!m_running)
        {
            m_running = true;
            m_start = m_clock.now();
        }
        else
        {
            std::cerr << "Timer cannont start: Timer already running!\n";
        }
    }

    static void end()
    {
        if(m_running)
        {
            auto end{std::chrono::steady_clock::now()};
            auto duration = std::chrono::duration<double, std::milli>(end - m_start).count();

            std::cout << m_label <<" took: " << duration << "ms.\n";

            m_running = false;
        }
        else
        {
            std::cerr << "Cannot stop timer: No timer to stop!\n";
        }
    }

private:
    static inline std::chrono::steady_clock m_clock;
    static inline std::chrono::steady_clock::time_point m_start;

    static inline const char* m_label;

    static inline bool m_running{false};
};
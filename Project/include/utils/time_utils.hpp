#pragma once

#include <chrono>

namespace utils::time
{
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    using Duration = std::chrono::duration<float>;

    // Get current time
    inline TimePoint Now()
    {
        return Clock::now();
    }

    // Get elapsed time in seconds
    inline float Elapsed(const TimePoint& start)
    {
        return std::chrono::duration_cast<Duration>(Now() - start).count();
    }

    // Get elapsed time between two points in seconds
    inline float ElapsedBetween(const TimePoint& start, const TimePoint& end)
    {
        return std::chrono::duration_cast<Duration>(end - start).count();
    }

    // Simple timer class
    class Timer
    {
    public:
        Timer() : m_Start(Now())
        {
            //
        }

        void Reset()
        {
            m_Start = Now();
        }

        [[nodiscard]] float Elapsed() const
        {
            return std::chrono::duration_cast<Duration>(Now() - m_Start).count();
        }

        [[nodiscard]] float ElapsedMillis() const
        {
            return Elapsed() * 1000.0f;
        }

    private:
        TimePoint m_Start;
    };

    // Scoped timer for profiling (prints on destruction)
    class ScopedTimer
    {
    public:
        explicit ScopedTimer(const char* name) : m_Name(name), m_Start(Now())
        {
            //
        }

        ~ScopedTimer()
        {
            float elapsed = std::chrono::duration_cast<Duration>(Now() - m_Start).count();
            // You can log this or print it
            // For now, we'll keep it silent unless you want to add logging
        }

        [[nodiscard]] float Elapsed() const
        {
            return std::chrono::duration_cast<Duration>(Now() - m_Start).count();
        }

    private:
        const char* m_Name;

        TimePoint m_Start;
    };
}

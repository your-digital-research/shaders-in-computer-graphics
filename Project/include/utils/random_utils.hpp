#pragma once

#include <random>

namespace utils::random
{
    // Random number generator
    class Random
    {
    public:
        Random() : m_Generator(std::random_device{}())
        {
            //
        }

        explicit Random(const unsigned int seed) : m_Generator(seed)
        {
            //
        }

        // Random integer in range [min, max]
        int Int(const int min, const int max)
        {
            std::uniform_int_distribution dist(min, max);

            return dist(m_Generator);
        }

        // Random float in range [min, max]
        float Float(const float min = 0.0f, const float max = 1.0f)
        {
            std::uniform_real_distribution dist(min, max);

            return dist(m_Generator);
        }

        // Random double in range [min, max]
        double Double(const double min = 0.0, const double max = 1.0)
        {
            std::uniform_real_distribution dist(min, max);

            return dist(m_Generator);
        }

        // Random boolean
        bool Bool()
        {
            return Int(0, 1) == 1;
        }

        // Random boolean with probability
        bool Probability(const float probability)
        {
            return Float() < probability;
        }

        // Reset with a new seed
        void Seed(const unsigned int seed)
        {
            m_Generator.seed(seed);
        }

    private:
        std::mt19937 m_Generator;
    };

    // Global random instance for convenience
    inline Random& GlobalRandom()
    {
        static Random instance;

        return instance;
    }

    // Convenience functions using global random
    inline int RandomInt(const int min, const int max) { return GlobalRandom().Int(min, max); }
    inline float RandomFloat(const float min = 0.0f, const float max = 1.0f) { return GlobalRandom().Float(min, max); }
    inline double RandomDouble(const double min = 0.0, const double max = 1.0) { return GlobalRandom().Double(min, max); }
    inline bool RandomBool() { return GlobalRandom().Bool(); }
    inline bool RandomProbability(const float probability) { return GlobalRandom().Probability(probability); }
}

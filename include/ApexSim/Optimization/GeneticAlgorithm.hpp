#pragma once
#include "ApexSim/Core/Types.hpp"
#include <vector>
#include <functional>

namespace ApexSim::Optimization {

struct Genome {
    Core::scalar_t frontSpringRate;
    Core::scalar_t rearSpringRate;
    Core::scalar_t frontAntiRollBar;
    Core::scalar_t rearAntiRollBar;
    Core::scalar_t fitness;
};

class GeneticTuner {
public:
    GeneticTuner(int populationSize);
    
    // Evaluates a genome by running a full step-steer simulation
    // and calculating the Understeer Gradient and Rollover Threshold
    void evaluatePopulation(const std::function<Core::scalar_t(const Genome&)>& fitnessFunc);
    void crossoverAndMutate();
    
    Genome getBestSetup() const;
private:
    std::vector<Genome> m_population;
};

} // namespace ApexSim::Optimization

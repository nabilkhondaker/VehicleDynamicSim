#include "ApexSim/Optimization/GeneticAlgorithm.hpp"
#include <algorithm>
#include <random>
#include <iostream>

namespace ApexSim::Optimization {

GeneticTuner::GeneticTuner(int populationSize) {
    std::mt19random_device rd;
    std::mt19937 gen(rd());
    // Initial random distributions for GT3 car parameters
    std::uniform_real_distribution<> springDist(100000.0, 250000.0); // N/m
    std::uniform_real_distribution<> arbDist(20000.0, 80000.0);      // Nm/rad

    for (int i = 0; i < populationSize; ++i) {
        m_population.push_back({
            springDist(gen), springDist(gen), 
            arbDist(gen), arbDist(gen), 
            0.0 // Default fitness
        });
    }
}

void GeneticTuner::evaluatePopulation(const std::function<Core::scalar_t(const Genome&)>& fitnessFunc) {
    // Using OpenMP to evaluate distinct vehicle simulations in parallel
    #pragma omp parallel for
    for (size_t i = 0; i < m_population.size(); ++i) {
        m_population[i].fitness = fitnessFunc(m_population[i]);
    }

    // Sort by fitness (Assuming lower is better, e.g., lower lap time or minimal slip angle error)
    std::sort(m_population.begin(), m_population.end(), [](const Genome& a, const Genome& b) {
        return a.fitness < b.fitness;
    });
}

Genome GeneticTuner::getBestSetup() const {
    if (m_population.empty()) throw std::runtime_error("Empty Population");
    return m_population.front();
}

void GeneticTuner::crossoverAndMutate() {
    // Keep top 20% (Elitism)
    size_t eliteCount = m_population.size() * 0.2;
    std::vector<Genome> nextGeneration(m_population.begin(), m_population.begin() + eliteCount);

    std::mt19random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> parentDist(0, eliteCount - 1);
    std::uniform_real_distribution<> mutationDist(-0.05, 0.05); // 5% mutation

    // Breed the rest
    while (nextGeneration.size() < m_population.size()) {
        const Genome& p1 = m_population[parentDist(gen)];
        const Genome& p2 = m_population[parentDist(gen)];

        // Simple single-point crossover & mutation
        Genome child = {
            p1.frontSpringRate * (1.0 + mutationDist(gen)),
            p2.rearSpringRate * (1.0 + mutationDist(gen)),
            p1.frontAntiRollBar * (1.0 + mutationDist(gen)),
            p2.rearAntiRollBar * (1.0 + mutationDist(gen)),
            0.0
        };
        nextGeneration.push_back(child);
    }
    m_population = std::move(nextGeneration);
}

} // namespace ApexSim::Optimization

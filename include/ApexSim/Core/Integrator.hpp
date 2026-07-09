#pragma once
#include "ApexSim/Core/Types.hpp"
#include <functional>

namespace ApexSim::Core {

class Integrator {
public:
    // Signature for our derivative function: takes a state, returns state derivatives
    using DerivativeFunc = std::function<StateVector(const StateVector&)>;

    // Runge-Kutta 4th Order Integration
    static StateVector stepRK4(const StateVector& currentState, 
                               scalar_t dt, 
                               const DerivativeFunc& computeDerivatives);
};

} // namespace ApexSim::Core

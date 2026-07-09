#include "ApexSim/Core/Integrator.hpp"

namespace ApexSim::Core {

StateVector Integrator::stepRK4(const StateVector& currentState, 
                                scalar_t dt, 
                                const DerivativeFunc& computeDerivatives) {
    // k1 = f(t, y)
    StateVector k1 = computeDerivatives(currentState);
    
    // k2 = f(t + dt/2, y + dt/2 * k1)
    StateVector k2 = computeDerivatives(currentState + 0.5 * dt * k1);
    
    // k3 = f(t + dt/2, y + dt/2 * k2)
    StateVector k3 = computeDerivatives(currentState + 0.5 * dt * k2);
    
    // k4 = f(t + dt, y + dt * k3)
    StateVector k4 = computeDerivatives(currentState + dt * k3);
    
    // y_new = y + dt/6 * (k1 + 2*k2 + 2*k3 + k4)
    return currentState + (dt / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
}

} // namespace ApexSim::Core

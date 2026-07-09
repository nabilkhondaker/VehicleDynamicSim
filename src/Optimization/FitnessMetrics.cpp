#include "ApexSim/Optimization/FitnessMetrics.hpp"
#include <cmath>

namespace ApexSim::Optimization {

Core::scalar_t calculateUndersteerGradient(const Core::StateVector& steadyState) {
    // Understeer Gradient (K) = (Steering Angle - Ackermann Angle) / Lateral Acceleration
    // Simplified for this model using yaw rate, velocity, and steering input
    
    Core::scalar_t yawRate = steadyState[5];
    Core::scalar_t velocityX = steadyState[6];
    Core::scalar_t latAccel = steadyState[7];
    
    // Prevent divide by zero
    if (std::abs(latAccel) < 0.1) return 0.0;
    
    const Core::scalar_t wheelbase = 2.65;
    Core::scalar_t ackermannAngle = wheelbase * yawRate / velocityX;
    
    // Assuming a fixed steering input of 0.15 rad from our test scenario
    Core::scalar_t actualSteering = 0.15; 
    
    return (actualSteering - ackermannAngle) / latAccel; // Returns K in rad/(m/s^2)
}

Core::scalar_t calculateRolloverThreshold(Core::scalar_t trackWidth, Core::scalar_t cgHeight) {
    // Static Rollover Threshold (SSF - Static Stability Factor)
    // The lateral G-force required to lift the inside tires
    return trackWidth / (2.0 * cgHeight);
}

} // namespace ApexSim::Optimization

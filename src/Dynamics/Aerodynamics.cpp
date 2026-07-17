#include "ApexSim/Dynamics/Aerodynamics.hpp" 

namespace ApexSim::Dynamics {

Aerodynamics::Aerodynamics(AeroMap map) : m_map(map) {}

Core::Vector3 Aerodynamics::calculateForces(Core::scalar_t velocity) const {
    Core::Vector3 forces = Core::Vector3::Zero();
    Core::scalar_t dynamicPressure = 0.5 * m_map.airDensity * velocity * velocity * m_map.frontalArea;

    forces[0] = dynamicPressure * m_map.dragCoefficient;        // Drag
    forces[1] = dynamicPressure * m_map.liftCoefficientFront;   // Front Downforce (Negative lift)
    forces[2] = dynamicPressure * m_map.liftCoefficientRear;    // Rear Downforce

    return forces;
}

} // namespace ApexSim::Dynamics

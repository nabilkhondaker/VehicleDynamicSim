#pragma once
#include "ApexSim/Core/Types.hpp"
#include "ApexSim/Tires/Pacejka.hpp"
#include <vector>
#include <memory>

namespace ApexSim::Dynamics {

class Vehicle14DOF {
public:
    Vehicle14DOF();

    // Compute the derivatives of the state vector (for RK4 integration)
    Core::StateVector computeDerivatives(const Core::StateVector& state, Core::scalar_t steeringAngle, Core::scalar_t throttle);

    // Run a single integration step
    void step(Core::scalar_t dt, Core::scalar_t steeringAngle, Core::scalar_t throttle);

    [[nodiscard]] Core::StateVector getState() const { return m_state; }

private:
    Core::StateVector m_state;
    Core::scalar_t m_mass;
    Core::Matrix3 m_inertia;
    std::vector<Tires::PacejkaModel> m_tires;
    
    // Internal calculations
    Core::Vector4 calculateTireForcesOpenMP(const Core::StateVector& state, Core::scalar_t steeringAngle);
};

} // namespace ApexSim::Dynamics

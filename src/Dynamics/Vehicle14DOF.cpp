#include "ApexSim/Dynamics/Vehicle14DOF.hpp"
#include <omp.h>
#include <iostream>

namespace ApexSim::Dynamics {

Vehicle14DOF::Vehicle14DOF() : m_mass(1500.0) {
    m_state = Core::StateVector::Zero();
    m_inertia = Core::Matrix3::Identity() * 2500.0; // Simplified inertia tensor
    
    // Initialize 4 tires with sample racing slicks parameters
    Tires::PacejkaModel::Parameters slickParams = {10.0, 1.9, 1.0, 0.97};
    for(int i=0; i<4; ++i) {
        m_tires.emplace_back(slickParams);
    }
}

Core::Vector4 Vehicle14DOF::calculateTireForcesOpenMP(const Core::StateVector& state, Core::scalar_t steeringAngle) {
    Core::Vector4 forces = Core::Vector4::Zero();
    Core::Vector4 slipAngles; 
    
    // Dummy slip angles derived from state for demonstration
    slipAngles << 0.05 + steeringAngle, 0.05 + steeringAngle, 0.02, 0.02;

    // HIGH-PERFORMANCE PARALLELIZATION: Calculate 4 contact patches simultaneously
    #pragma omp parallel for default(none) shared(forces, slipAngles) schedule(static, 1)
    for(int i = 0; i < 4; ++i) {
        // Evaluate Pacejka Magic Formula for each tire
        forces[i] = m_tires[i].calculateForce(slipAngles[i]) * (m_mass * 9.81 / 4.0); 
    }
    
    return forces;
}

Core::StateVector Vehicle14DOF::computeDerivatives(const Core::StateVector& state, Core::scalar_t steeringAngle, Core::scalar_t throttle) {
    Core::StateVector dState = Core::StateVector::Zero();
    
    // 1. Calculate aerodynamic forces (simplified)
    Core::scalar_t velocity = state.segment<3>(6).norm();
    Core::scalar_t aeroDrag = 0.5 * 1.225 * 2.2 * 0.35 * velocity * velocity;

    // 2. Multithreaded Tire Force evaluation
    Core::Vector4 tireForces = calculateTireForcesOpenMP(state, steeringAngle);
    Core::scalar_t totalLateralForce = tireForces.sum();

    // 3. Newton-Euler Equations of Motion (Translation)
    Core::Vector3 acceleration;
    acceleration[0] = (throttle * 5000.0 - aeroDrag) / m_mass; // Longitudinal
    acceleration[1] = totalLateralForce / m_mass;              // Lateral
    acceleration[2] = 0.0;                                     // Vertical (ignoring heave for basic demo)

    // Update position derivatives (velocities)
    dState.segment<3>(0) = state.segment<3>(6);
    // Update velocity derivatives (accelerations)
    dState.segment<3>(6) = acceleration;

    return dState;
}

void Vehicle14DOF::step(Core::scalar_t dt, Core::scalar_t steeringAngle, Core::scalar_t throttle) {
    // Simple Euler Integration for demonstration (Replace with RK4 from Integrator module)
    Core::StateVector k1 = computeDerivatives(m_state, steeringAngle, throttle);
    m_state += k1 * dt;
}

} // namespace ApexSim::Dynamics

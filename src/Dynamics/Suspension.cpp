#include "ApexSim/Dynamics/Suspension.hpp"
#include <algorithm>

namespace ApexSim::Dynamics {

Suspension::Suspension(Setup frontSetup, Setup rearSetup) 
    : m_front(frontSetup), m_rear(rearSetup) {
    m_staticWeightPerWheel = (1500.0 * 9.81) / 4.0; // Assuming 1500kg, 50/50 weight distribution
}

Core::Vector4 Suspension::calculateVerticalLoads(const Core::StateVector& state) {
    Core::Vector4 loads;
    
    // Extract chassis kinematics (indices 3, 4, 5 are roll, pitch, yaw)
    Core::scalar_t rollAngle = state[3];
    Core::scalar_t pitchAngle = state[4];
    
    // Simple load transfer math (Simplified for real-time demo)
    // Lateral load transfer via anti-roll bars
    Core::scalar_t frontLatTransfer = (rollAngle * m_front.antiRollStiffness);
    Core::scalar_t rearLatTransfer  = (rollAngle * m_rear.antiRollStiffness);
    
    // Longitudinal load transfer via springs (Pitch)
    Core::scalar_t longTransfer = (pitchAngle * m_front.springRate * 2.0); // Track/wheelbase approx
    
    // [FL, FR, RL, RR]
    loads[0] = m_staticWeightPerWheel + frontLatTransfer - longTransfer;
    loads[1] = m_staticWeightPerWheel - frontLatTransfer - longTransfer;
    loads[2] = m_staticWeightPerWheel + rearLatTransfer + longTransfer;
    loads[3] = m_staticWeightPerWheel - rearLatTransfer + longTransfer;

    // Prevent negative loads (tires leaving the ground)
    for(int i = 0; i < 4; ++i) {
        loads[i] = std::max(0.0, loads[i]);
    }

    return loads;
}

} // namespace ApexSim::Dynamics

#include "ApexSim/Control/ESCSimulator.hpp"
#include <cmath>

namespace ApexSim::Control {

ESCSimulator::ESCSimulator(Core::scalar_t maxYawError) 
    : m_yawErrorThreshold(maxYawError), m_proportionalGain(5000.0) {}

Core::Vector4 ESCSimulator::computeCorrection(Core::scalar_t targetYawRate, 
                                              Core::scalar_t actualYawRate, 
                                              const Core::Vector4& currentBrakes) {
    Core::Vector4 correctedBrakes = currentBrakes;
    Core::scalar_t yawError = actualYawRate - targetYawRate;

    // Deadband to prevent micro-corrections
    if (std::abs(yawError) > m_yawErrorThreshold) {
        Core::scalar_t correctionTorque = std::abs(yawError) * m_proportionalGain;

        if (yawError > 0) {
            // Oversteering left (or understeering right): Brake outside front wheel
            correctedBrakes[1] += correctionTorque; // Front Right
        } else {
            // Oversteering right (or understeering left): Brake outside front wheel
            correctedBrakes[0] += correctionTorque; // Front Left
        }
        
        // Clamp maximum brake pressure to 1.0 (100%)
        for(int i=0; i<4; ++i) {
            if (correctedBrakes[i] > 1.0) correctedBrakes[i] = 1.0;
        }
    }
    return correctedBrakes;
}

} // namespace ApexSim::Control

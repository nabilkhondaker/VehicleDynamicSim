#pragma once
#include "ApexSim/Core/Types.hpp"

namespace ApexSim::Control {

class ESCSimulator {
public:
    ESCSimulator(Core::scalar_t maxYawError = 0.1);

    // Modifies individual wheel brake pressures to create a corrective yaw moment
    Core::Vector4 computeCorrection(Core::scalar_t targetYawRate, 
                                    Core::scalar_t actualYawRate, 
                                    const Core::Vector4& currentBrakes);

private:
    Core::scalar_t m_yawErrorThreshold;
    Core::scalar_t m_proportionalGain;
};

} // namespace ApexSim::Control

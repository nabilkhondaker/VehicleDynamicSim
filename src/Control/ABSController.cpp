#include "ApexSim/Control/ABSController.hpp"
#include <cmath>

namespace ApexSim::Control {

ABSController::ABSController(Core::scalar_t targetSlip, Core::scalar_t slipTolerance)
    : m_targetSlip(targetSlip), m_tolerance(slipTolerance) {}

Core::Vector4 ABSController::modulateBrakes(const Core::Vector4& rawBrakeInput, 
                                            const Core::Vector4& wheelSpeeds, 
                                            Core::scalar_t vehicleSpeed) {
    Core::Vector4 modulatedBrakes = rawBrakeInput;
    const Core::scalar_t wheelRadius = 0.33; // meters

    // Prevent divide-by-zero at standstill
    if (vehicleSpeed < 1.0) return modulatedBrakes;

    for (int i = 0; i < 4; ++i) {
        // Calculate longitudinal slip ratio: (V - w*r) / V
        Core::scalar_t slipRatio = (vehicleSpeed - (wheelSpeeds[i] * wheelRadius)) / vehicleSpeed;

        // Bang-bang slip logic
        if (slipRatio > (m_targetSlip + m_tolerance)) {
            // Wheel is locking up, release brake pressure entirely
            modulatedBrakes[i] = 0.0;
        } else if (slipRatio < (m_targetSlip - m_tolerance)) {
            // Under peak slip, allow full requested brake pressure
            modulatedBrakes[i] = rawBrakeInput[i];
        }
        // Else hold current pressure (handled by retaining raw input or previous state in a full implementation)
    }

    return modulatedBrakes;
}

} // namespace ApexSim::Control

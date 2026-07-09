#pragma once
#include "ApexSim/Core/Types.hpp"

namespace ApexSim::Control {

class ABSController {
public:
    ABSController(Core::scalar_t targetSlip = 0.12, Core::scalar_t slipTolerance = 0.02);

    // Returns modulated brake pressure [0.0, 1.0] for each of the 4 wheels
    Core::Vector4 modulateBrakes(const Core::Vector4& rawBrakeInput, 
                                 const Core::Vector4& wheelSpeeds, 
                                 Core::scalar_t vehicleSpeed);

private:
    Core::scalar_t m_targetSlip;
    Core::scalar_t m_tolerance;
};

} // namespace ApexSim::Control

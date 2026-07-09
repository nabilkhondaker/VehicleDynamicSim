#pragma once
#include "ApexSim/Core/Types.hpp"

namespace ApexSim::Optimization {
    // Calculates the Understeer Gradient (deg/g) from simulation telemetry
    Core::scalar_t calculateUndersteerGradient(const Core::StateVector& steadyState);
    
    // Calculates lateral Gs required to lift inside wheels
    Core::scalar_t calculateRolloverThreshold(Core::scalar_t trackWidth, Core::scalar_t cgHeight);
}

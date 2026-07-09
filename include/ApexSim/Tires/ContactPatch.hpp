#pragma once
#include "ApexSim/Core/Types.hpp"

namespace ApexSim::Tires {
    // Utility to calculate exact slip angles and ratios based on road camber and tire deflection
    struct ContactPatch {
        Core::scalar_t dynamicRadius;
        Core::scalar_t slipAngle;
        Core::scalar_t slipRatio;
        Core::scalar_t normalLoad;
    };
}

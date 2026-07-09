#pragma once
#include "ApexSim/Core/Types.hpp"

namespace ApexSim::Dynamics {

class Suspension {
public:
    struct Setup {
        Core::scalar_t springRate;    // N/m
        Core::scalar_t bumpDamping;   // Ns/m
        Core::scalar_t reboundDamping;// Ns/m
        Core::scalar_t antiRollStiffness; // Nm/rad
    };

    Suspension(Setup frontSetup, Setup rearSetup);

    // Returns a Vector4 of vertical loads (Fz) on each tire based on chassis roll/pitch/heave
    Core::Vector4 calculateVerticalLoads(const Core::StateVector& state);

private:
    Setup m_front;
    Setup m_rear;
    Core::scalar_t m_staticWeightPerWheel;
};

} // namespace ApexSim::Dynamics

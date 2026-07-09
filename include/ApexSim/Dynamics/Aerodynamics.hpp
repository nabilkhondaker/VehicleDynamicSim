#pragma once
#include "ApexSim/Core/Types.hpp"

namespace ApexSim::Dynamics {

class Aerodynamics {
public:
    struct AeroMap {
        Core::scalar_t frontalArea; // m^2
        Core::scalar_t dragCoefficient; // Cd
        Core::scalar_t liftCoefficientFront; // Cl_f
        Core::scalar_t liftCoefficientRear; // Cl_r
        Core::scalar_t airDensity; // kg/m^3
    };

    Aerodynamics(AeroMap map);

    // Returns [Drag, FrontDownforce, RearDownforce] in Newtons
    Core::Vector3 calculateForces(Core::scalar_t velocity) const;

private:
    AeroMap m_map;
};

} // namespace ApexSim::Dynamics

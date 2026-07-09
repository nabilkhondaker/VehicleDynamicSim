#pragma once
#include "ApexSim/Core/Types.hpp"
#include <cmath>

namespace ApexSim::Tires {

class PacejkaModel {
public:
    struct Parameters {
        Core::scalar_t B; // Stiffness factor
        Core::scalar_t C; // Shape factor
        Core::scalar_t D; // Peak value
        Core::scalar_t E; // Curvature factor
    };

    PacejkaModel(Parameters params) : m_params(params) {}

    // Magic formula calculation
    [[nodiscard]] Core::scalar_t calculateForce(Core::scalar_t slip) const {
        const auto& [B, C, D, E] = m_params;
        // F = D * sin(C * arctan(B*x - E*(B*x - arctan(B*x))))
        Core::scalar_t Bx = B * slip;
        Core::scalar_t atanBx = std::atan(Bx);
        return D * std::sin(C * std::atan(Bx - E * (Bx - atanBx)));
    }

private:
    Parameters m_params;
};

} // namespace ApexSim::Tires

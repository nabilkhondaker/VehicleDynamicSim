#include <gtest/gtest.h>
#include "ApexSim/Core/Integrator.hpp"

TEST(IntegratorTest, RK4MaintainsStability) {
    ApexSim::Core::StateVector state = ApexSim::Core::StateVector::Zero();
    auto dummyDerivative = [](const ApexSim::Core::StateVector& s) {
        return s * -0.1; // Simple exponential decay
    };
    
    state[0] = 100.0;
    auto newState = ApexSim::Core::Integrator::stepRK4(state, 0.1, dummyDerivative);
    
    EXPECT_LT(newState[0], 100.0);
    EXPECT_GT(newState[0], 90.0);
}

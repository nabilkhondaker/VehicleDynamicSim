#include <gtest/gtest.h>
#include "ApexSim/Tires/Pacejka.hpp"

TEST(PacejkaModelTest, ComputesZeroForceAtZeroSlip) {
    ApexSim::Tires::PacejkaModel::Parameters params = {10.0, 1.9, 1.0, 0.97};
    ApexSim::Tires::PacejkaModel tire(params);
    
    EXPECT_NEAR(tire.calculateForce(0.0), 0.0, 1e-6);
}

TEST(PacejkaModelTest, ComputesPeakForceCorrectly) {
    ApexSim::Tires::PacejkaModel::Parameters params = {10.0, 1.9, 1.0, 0.97};
    ApexSim::Tires::PacejkaModel tire(params);
    
    // Evaluate near slip = 0.1 (common peak for racing slicks)
    double force = tire.calculateForce(0.1);
    EXPECT_GT(force, 0.8); // Should be near peak D value
}

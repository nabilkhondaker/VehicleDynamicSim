#pragma once
#include "ApexSim/Core/Types.hpp"

namespace ApexSim::Core {

struct VehicleStateData {
    Vector3 position;
    Vector3 eulerAngles; // Roll, Pitch, Yaw
    Vector3 linearVelocity;
    Vector3 angularVelocity;
    Vector4 wheelAngularVelocities;

    // Convert from Eigen 16x1 to readable struct
    void fromVector(const StateVector& v) {
        position = v.segment<3>(0);
        eulerAngles = v.segment<3>(3);
        linearVelocity = v.segment<3>(6);
        angularVelocity = v.segment<3>(9);
        wheelAngularVelocities = v.segment<4>(12);
    }
};

} // namespace ApexSim::Core

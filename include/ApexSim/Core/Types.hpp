#pragma once
#include <Eigen/Dense>

namespace ApexSim::Core {
    // Standardize precision for the simulator (double precision for physics)
    using scalar_t = double;
    using Vector3  = Eigen::Matrix<scalar_t, 3, 1>;
    using Vector4  = Eigen::Matrix<scalar_t, 4, 1>;
    using Matrix3  = Eigen::Matrix<scalar_t, 3, 3>;
    
    // 14 DOF State Vector: 
    // [x, y, z, roll, pitch, yaw, vx, vy, vz, wx, wy, wz, wheel_speeds(4)]
    using StateVector = Eigen::Matrix<scalar_t, 16, 1>; 
}

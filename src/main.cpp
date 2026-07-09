#include "ApexSim/Dynamics/Vehicle14DOF.hpp"
#include <iostream>
#include <iomanip>
#include <omp.h>

int main() {
    std::cout << "==========================================\n";
    std::cout << "  ApexDynamics Hi- Sim By Nabil Khondaker \n";
    std::cout << "==========================================\n";
    
    std::cout << "OpenMP Threads Available: " << omp_get_max_threads() << "\n\n";

    ApexSim::Dynamics::Vehicle14DOF gt3_car;

    // Simulation Parameters
    const double dt = 0.001; // 1000Hz Physics loop
    const double simDuration = 2.0; // Simulate 2 seconds
    const int steps = static_cast<int>(simDuration / dt);

    std::cout << "Initiating Step-Steer Scenario (ISO 3888)...\n";
    
    double steeringInput = 0.0;
    double throttleInput = 1.0; // Full throttle

    for (int i = 0; i < steps; ++i) {
        double time = i * dt;

        // Apply a sharp steering input at t = 0.5s (Step Steer)
        if (time > 0.5) {
            steeringInput = 0.15; // rad
        }

        // Run real-time physics integration step
        gt3_car.step(dt, steeringInput, throttleInput);

        // Telemetry logging every 0.25 seconds
        if (i % 250 == 0) {
            auto state = gt3_car.getState();
            std::cout << std::fixed << std::setprecision(3);
            std::cout << "Time: " << time << "s | "
                      << "Speed: " << state[6] << " m/s | "
                      << "Lat Accel: " << state[7] << " m/s^2 | "
                      << "Yaw: " << state[5] << " rad\n";
        }
    }

    std::cout << "\nSimulation Complete. Telemetry saved to logger.\n";
    return 0;
}

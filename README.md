# Vehicle Dynamics Simulator 🏎️
Engineered by Nabil Khondaker.

![C++](https://img.shields.io/badge/C%2B%2B-20-blue.svg)
![CMake](https://img.shields.io/badge/CMake-3.15%2B-green.svg)
![OpenMP](https://img.shields.io/badge/OpenMP-Enabled-orange.svg)
![Eigen](https://img.shields.io/badge/Eigen-3.3%2B-red.svg)

**Vehicle Dynamics Simulator** is an enterprise-grade, high-performance vehicle dynamics simulator written in modern C++. It is designed for motorsport and mechatronics applications, featuring real-time Runge-Kutta 4 (RK4) state integration, multi-threaded tire physics via the Pacejka Magic Formula, and active control systems like ABS and ESC.

---

## 🚀 Features

* **14-DOF Multi-body Physics:** Full rigid-body dynamics for the chassis (6 DOF), wheel vertical motion (4 DOF), and wheel spin (4 DOF) solved using Eigen.
* **High-Fidelity Tire Model:** Pacejka 2002 Magic Formula implementation for nonlinear tire forces.
* **Parallel Processing:** Heavy physics calculations (tire contact patches, suspension kinematics) are parallelized using OpenMP to ensure real-time performance.
* **Active Mechatronics Systems:** * Bang-bang ABS Controller based on tire slip ratios.
  * Electronic Stability Control (ESC) utilizing asymmetric brake vectoring.
* **Genetic Algorithm Optimization:** Built-in multi-objective optimizer for tuning suspension parameters (spring rates, anti-roll bars) to minimize understeer gradients and maximize rollover thresholds.
* **Aerodynamics:** Ride-height and velocity-dependent lift and drag maps.
* **Python Telemetry Tooling:** Automated scripts for plotting time-series data (Yaw Rate, Lateral Gs, Velocity).

---

## 📁 Directory Structure

```
VehicleDynamicSim/
├── CMakeLists.txt
├── README.md
├── .clang-format
├── include/
│   ├── ApexSim/
│   │   ├── Core/
│   │   │   ├── Integrator.hpp          # Runge-Kutta 4 (RK4) Eigen solver
│   │   │   ├── Types.hpp               # Eigen typedefs (VectorXd, MatrixXd)
│   │   │   └── SystemState.hpp
│   │   ├── Dynamics/
│   │   │   ├── Vehicle14DOF.hpp        # Full multi-body vehicle model
│   │   │   ├── Suspension.hpp          # Spring/damper kinetics
│   │   │   └── Aerodynamics.hpp        # Downforce and drag maps
│   │   ├── Tires/
│   │   │   ├── Pacejka.hpp             # Magic Formula 2002 implementation
│   │   │   └── ContactPatch.hpp        # Road/tire interface processing
│   │   ├── Control/
│   │   │   ├── ABSController.hpp       # Slip-ratio based braking control
│   │   │   └── ESCSimulator.hpp        # Yaw-moment control logic
│   │   └── Optimization/
│   │       ├── GeneticAlgorithm.hpp    # Multi-objective GA tuning
│   │       └── FitnessMetrics.hpp      # Understeer gradient/rollover threshold
├── src/
│   ├── Core/
│   │   └── Integrator.cpp
│   ├── Dynamics/
│   │   ├── Vehicle14DOF.cpp
│   │   ├── Suspension.cpp
│   │   └── Aerodynamics.cpp
│   ├── Tires/
│   │   └── Pacejka.cpp
│   ├── Control/
│   │   ├── ABSController.cpp
│   │   └── ESCSimulator.cpp
│   ├── Optimization/
│   │   └── GeneticAlgorithm.cpp
│   └── main.cpp                        # Entry point and scenario runner
├── data/
│   ├── vehicles/
│   │   └── gt3_spec.json               # Vehicle parameters
│   └── tracks/
│       └── nurburgring_profile.csv     # Road surface elevations
├── scripts/
│   ├── plot_telemetry.py               # Python visualization of output
│   └── ga_convergence.py
└── tests/
    ├── test_pacejka.cpp                # Google Test suites
    └── test_integration.cpp
```

--- 

## *More information coming soon, as this project is a work in progress!*

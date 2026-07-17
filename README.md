# Vehicle Dynamics Simulator 🏎️
Engineered by Nabil Khondaker.

![C++](https://img.shields.io/badge/C%2B%2B-20-blue.svg)
![CMake](https://img.shields.io/badge/CMake-3.15%2B-green.svg)
![OpenMP](https://img.shields.io/badge/OpenMP-Enabled-orange.svg)
![Eigen](https://img.shields.io/badge/Eigen-3.3%2B-red.svg)

**Vehicle Dynamics Simulator** is an enterprise-grade, high-performance vehicle dynamics simulator written in modern C++. It is designed for motorsport and mechatronics applications, featuring real-time Runge-Kutta 4 (RK4) state integration, multi-threaded tire physics via the Pacejka Magic Formula, and active control systems like ABS and ESC.

---

<details>
<summary><b>Contents</b></summary>

- [✨ Key Features](#-key-features)
- [📁 Project Structure](#-project-structure)
- [🛠️ Tech Stack](#️-tech-stack)
- [⚙️ Quick Start](#️-quick-start)
  - [1. Prerequisites](#1-prerequisites)
  - [2. Build & Run](#2-build--run)
  - [3. Basic Usage Example](#3-basic-usage-example)
- [📊 Simulation Capabilities](#-simulation-capabilities)
- [🎯 Use Cases](#-use-cases)
- [📋 Roadmap](#-roadmap)
- [👤 Author](#-author)

</details>

---

## ✨ Key Features

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

## 🛠️ Tech Stack

* **Core Language:** C++ (C++20)
* **Build System:** CMake
* **Mathematics:** Eigen3 for linear algebra
* **Parallelism:** OpenMP
* **Testing:** Google Test
* **Visualization:** Python (matplotlib/seaborn scripts)
* **Data:** JSON for vehicle params, CSV for road profiles

---

## ⚙️ Quick Start

### 1. Prerequisites

* CMake (>= 3.15)
* C++ compiler with C++20 support (GCC/Clang/MSVC)
* Eigen3 library
* OpenMP support
* (Optional) Google Test for running tests
* Python 3 with matplotlib for visualization

### 2. Build & Run

```bash
git clone https://github.com/nabilkhondaker/VehicleDynamicSim.git
cd VehicleDynamicSim

mkdir build && cd build
cmake ..
make

# Run the simulator
./ApexDynamicsSim
```

### 3. Basic Usage Example

```cpp
// Example from main.cpp or test scenarios
#include "ApexSim/Dynamics/Vehicle14DOF.hpp"
#include "ApexSim/Core/Integrator.hpp"
// ... other includes

// Load vehicle and track data
VehicleParams params = loadFromJSON("data/vehicles/gt3_spec.json");
RoadProfile road = loadCSV("data/tracks/nurburgring_profile.csv");

Vehicle14DOF vehicle(params);
Integrator integrator(0.001);  // 1ms timestep

for (double t = 0; t < simTime; t += dt) {
    double steering = ...; // driver input
    double throttle = ...;
    double brake = ...;
    
    vehicle.updateControls(steering, throttle, brake);
    integrator.step(vehicle, dt, road.getElevation(t));
    
    // Log telemetry
}
```

--- 

## 📊 Simulation Capabilities

- **Full Vehicle Dynamics:** 14 DOF rigid body with suspension compliance and tire-road interaction.
- **Nonlinear Tire Forces:** Pacejka model capturing combined slip, load sensitivity, and transients.
- **Control Systems:** Real-time ABS and ESC for stability and performance.
- **Optimization:** Genetic algorithms for parameter identification and setup optimization.
- **Road Interaction:** Arbitrary road profile inputs for bump, banking, and elevation studies.
- **Output:** Comprehensive telemetry logs for post-processing and visualization.

## 🎯 Use Cases

- Vehicle dynamics research and parameter studies
- Motorsport suspension and setup optimization
- Autonomous vehicle control algorithm validation
- Driver-in-the-loop simulation prototyping
- Tire model benchmarking and development
- Pre-hardware testing of mechatronic systems (ABS, ESC, etc.)

## 📋 Roadmap

- Full 3D visualization (e.g., using OpenGL or Unity integration)
- More advanced tire models (e.g., MF 5.2 or brush models)
- Real-time hardware-in-the-loop (HIL) support
- Additional control systems (TCS, active suspension)
- Stochastic road and driver modeling
- ROS2 integration for autonomous vehicle simulation
- Expanded Python API for easier experimentation

---

## 👤 Author
*Engineered by Nabil Khondaker*

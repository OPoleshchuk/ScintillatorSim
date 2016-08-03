# ScintillatorSim
This simulation was written during studying of GEANT4 and evolve over time from a one crystal into a crystal array. Now it forms the basis of SpecMATscint. The latest stable version with a one crystal is stored here. Crystal could take two of the most widespread detector shapes, cubic and cylinder.

Cube                       |  Cylinder
:-------------------------:|:-------------------------:
![](https://cloud.githubusercontent.com/assets/17125100/17373199/7943f564-59a7-11e6-957a-0361878d7e28.png)  |  ![](https://cloud.githubusercontent.com/assets/17125100/17373191/7492d954-59a7-11e6-87d3-524c2692a318.png)

## How to Build and Run

1. Clone the simulation code
 ```
 $ git clone https://github.com/OPoleshchuk/ScintillatorSim.git
 ```

2. Build with CMake
 ```
 $ cd path_to_ScintillatorSim         # go to directory which contains the code
 $ mkdir ScintillatorSim_build
 $ cd ScintillatorSim_build
 $ cmake -DGeant4_DIR=path_to_Geant4_installation/lib[64]/Geant4-[Version]/ ../ScintillatorSim
 $ make -jN                        # "N" is the number of processes
 ```

3. Run through one of the following options
  - Execute in the interactive mode:

    ```
    $ ./SpecMATsim
    ```
    ```
    Idle> /control/execute vis.mac    # visualization
    Idle> run/beamOn 1                # beam on
    ```
  - Execute in batch mode from a macro file

    ```
    $ ./SpecMATsim SpecMATsim.in > SpecMATsim.out
    ```
  - or run the script to execute in batch mode and have a progress bar

    ```
    $ ./SpecMATsim.sh
    ```

## Requirements

- [GEANT4 9.6] (http://geant4.web.cern.ch/geant4/support/source_archive.shtml)
- [ROOT 5.34/34] (https://root.cern.ch/downloading-root)
- [CMAKE] (https://cmake.org/download/)

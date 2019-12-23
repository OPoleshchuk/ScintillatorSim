///Author: Oleksii Poleshchuk
///
///KU Leuven 2016-2019
///
///ScintillatorSim is a GEANT4 code for simulation
///of gamma-rays detection efficiency of a single scintillation detector.
///
/// \file ScintSimPhysicsList.hh
/// \brief Definition of the ScintSimPhysicsList class

#ifndef ScintSimPhysicsList_h
#define ScintSimPhysicsList_h 1

#include "G4VModularPhysicsList.hh"

/// Modular physics list
///
/// It includes the folowing physics builders
/// - G4DecayPhysics
/// - G4RadioactiveDecayPhysics
/// - G4EmStandardPhysics

class ScintSimPhysicsList: public G4VModularPhysicsList
{
public:
  ScintSimPhysicsList();
  virtual ~ScintSimPhysicsList();

  virtual void SetCuts();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

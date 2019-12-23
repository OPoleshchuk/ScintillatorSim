///Author: Oleksii Poleshchuk
///
///KU Leuven 2016-2019
///
///ScintillatorSim is a GEANT4 code for simulation
///of gamma-rays detection efficiency of a single scintillation detector.
///
/// \file ScintSimPhysicsList.cc
/// \brief Implementation of the ScintSimPhysicsList class

#include "ScintSimPhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ScintSimPhysicsList::ScintSimPhysicsList()
: G4VModularPhysicsList(){
  SetVerboseLevel(1);

  // Default physics
  RegisterPhysics(new G4DecayPhysics());

  // Radioactive decay
  RegisterPhysics(new G4RadioactiveDecayPhysics());

  // EM physics
  RegisterPhysics(new G4EmStandardPhysics());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ScintSimPhysicsList::~ScintSimPhysicsList()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ScintSimPhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

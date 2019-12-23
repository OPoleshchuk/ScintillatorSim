///Author: Oleksii Poleshchuk
///
///KU Leuven 2016-2019
///
///ScintillatorSim is a GEANT4 code for simulation
///of gamma-rays detection efficiency of a single scintillation detector.
///
/// \file ScintSimStackingAction.cc
/// \brief Implementation of the ScintSimStackingAction class

#include "ScintSimStackingAction.hh"

#include "G4Track.hh"
#include "G4NeutrinoE.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ScintSimStackingAction::ScintSimStackingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ScintSimStackingAction::~ScintSimStackingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
ScintSimStackingAction::ClassifyNewTrack(const G4Track* track)
{
  //keep primary particle
  if (track->GetParentID() == 0) return fUrgent;

  //kill secondary neutrino
  if (track->GetDefinition() == G4NeutrinoE::NeutrinoE()) return fKill;
  else return fUrgent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

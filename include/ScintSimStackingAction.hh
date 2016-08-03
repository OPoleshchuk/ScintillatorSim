/// \file ScintSimStackingAction.hh
/// \brief Definition of the ScintSimStackingAction class

#ifndef ScintSimStackingAction_h
#define ScintSimStackingAction_h 1

#include "G4UserStackingAction.hh"
#include "globals.hh"

/// Stacking action class : manage the newly generated particles
///
/// One wishes do not track secondary neutrino.Therefore one kills it
/// immediately, before created particles will  put in a stack.

class ScintSimStackingAction : public G4UserStackingAction
{
  public:
    ScintSimStackingAction();
    virtual ~ScintSimStackingAction();

    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*);
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

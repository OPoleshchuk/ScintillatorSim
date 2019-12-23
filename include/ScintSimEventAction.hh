///Author: Oleksii Poleshchuk
///
///KU Leuven 2016-2019
///
///ScintillatorSim is a GEANT4 code for simulation
///of gamma-rays detection efficiency of a single scintillation detector.
///
/// \file ScintSimEventAction.hh
/// \brief Definition of the ScintSimEventAction class

#ifndef ScintSimEventAction_h
#define ScintSimEventAction_h 1

#include "G4UserEventAction.hh"
#include "G4THitsMap.hh"
#include "G4Material.hh"
#include "globals.hh"

class ScintSimRunAction;
class G4GenericMessenger;
class ScintSimDetectorConstruction;

/// Event action class
///
/// In EndOfEventAction() there is collected information event per event
/// from Hits Collections, and accumulated statistic for
/// ScintSimRunAction::EndOfRunAction().

class ScintSimEventAction : public G4UserEventAction
{
  public:
    ScintSimEventAction(ScintSimRunAction* runAction);
    virtual ~ScintSimEventAction();

    virtual void  BeginOfEventAction(const G4Event* );
    virtual void    EndOfEventAction(const G4Event* );

    void SetPrintModulo(G4int value);

  private:
  // methods
    G4THitsMap<G4double>* GetHitsCollection(const G4String& hcName,
                                          const G4Event* event) const;
    G4double GetSum(G4THitsMap<G4double>* hitsMap) const;
    void PrintEventStatistics(G4double absoEdep) const;
    ScintSimDetectorConstruction* sciCryst;
    ScintSimRunAction*  fRunAct;


    G4int fCollID_cryst;

    G4double absoEdep;

    G4GenericMessenger*  fMessenger;
    G4Material* crystMat;
    G4int fPrintModulo;
};

// inline functions

inline void ScintSimEventAction::SetPrintModulo(G4int value) {
  fPrintModulo = value;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

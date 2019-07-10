/// \file ScintSimRunAction.hh
/// \brief Definition of the ScintSimRunAction class

#ifndef ScintSimRunAction_h
#define ScintSimRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4Material.hh"

class G4Run;
class ScintSimDetectorConstruction;
class ScintSimPrimaryGeneratorAction;
/// Run action class

class ScintSimRunAction : public G4UserRunAction
{
  public:
    ScintSimRunAction();
    virtual ~ScintSimRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);


  private:
    ScintSimDetectorConstruction* sciCryst;
    ScintSimPrimaryGeneratorAction* gammaSource;
    G4Material* crystMat;

    G4String fileName;
    G4String crystSizeX;
    G4String crystSizeY;
    G4String crystSizeZ;
    G4String crystMatName;
    G4String crystShape;
    G4String gammaEnergyStr;
    G4String crystSourceDist;
    G4String numberOfEvents;
    G4String partName;
    G4String sourceDist;
    G4int numberOfGeneratedEvents;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

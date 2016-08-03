/// \file ScintSimPrimaryGeneratorAction.hh
/// \brief Definition of the ScintSimPrimaryGeneratorAction class

#ifndef ScintSimPrimaryGeneratorAction_h
#define ScintSimPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class ScintSimDetectorConstruction;

/// The primary generator action class with particle gum.
///
/// It defines an ion (Co60), at rest). Ion can be changed
/// with the G4ParticleGun commands (see run2.mac).

class ScintSimPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    ScintSimPrimaryGeneratorAction();
    virtual ~ScintSimPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);

    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

    void SetDistFromCrystSurfToSource(G4double val) { distFromCrystSurfToSource = val; }
    G4double GetDistFromCrystSurfToSource(void) { return distFromCrystSurfToSource;}

    void SetGammaEnergy(G4double val) { gammaEnergy = val; }
    G4double GetGammaEnergy(void) { return gammaEnergy;}
  private:
    ScintSimDetectorConstruction* sciCryst;

    G4ParticleGun*  fParticleGun;

    G4double crystSizeZ;
    G4double distFromCrystSurfToSource;
    G4double gammaEnergy;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

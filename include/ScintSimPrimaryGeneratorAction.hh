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

    G4int Z;
    G4int A;
    G4int n_particle;
    G4double ionCharge;
    G4double excitEnergy;
    G4double ionEnergy;
    G4String source;
    G4int randomNum;
    G4double distFromCrystSurfToSource;

    ScintSimPrimaryGeneratorAction();
    virtual ~ScintSimPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);

    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

    void SetDistFromCrystSurfToSource(G4double val) { distFromCrystSurfToSource = val; }
    G4double GetDistFromCrystSurfToSource(void) { return distFromCrystSurfToSource;}

    void SetGammaEnergy(G4double val) { gammaEnergy = val; }
    G4double GetGammaEnergy(void) { return gammaEnergy;}

    void SetZ(G4double val) { Z = val; }
    G4double GetZ(void) { return Z;}

    void SetA(G4double val) { A = val; }
    G4double GetA(void) { return A;}

    void SetIonCharge(G4double val) { ionCharge = val; }
    G4double GetIonCharge(void) { return ionCharge;}

    void SetExcitEnergy(G4double val) { excitEnergy = val; }
    G4double GetExcitEnergy(void) { return excitEnergy;}

    void SetIonEnergy(G4double val) { ionEnergy = val; }
    G4double GetIonEnergy(void) { return ionEnergy;}

    void SetSource(G4String val) { source = val; }
    G4String GetSource(void) { return source;}

  private:
    ScintSimDetectorConstruction* sciCryst;

    G4ParticleGun*  fParticleGun;

    G4double crystSizeZ;

    G4double gammaEnergy;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

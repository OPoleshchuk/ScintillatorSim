/// \file ScintSimPrimaryGeneratorAction.cc
/// \brief Implementation of the ScintSimPrimaryGeneratorAction class

#include "ScintSimPrimaryGeneratorAction.hh"
#include "ScintSimDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Geantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <stdlib.h>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ScintSimPrimaryGeneratorAction::ScintSimPrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   sciCryst(0),
   fParticleGun(0)
{
  /*
  //################### Monoenergetic gamma source ############################//
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);
  sciCryst = new ScintSimDetectorConstruction();

  distFromCrystSurfToSource = 200*mm;
  gammaEnergy = 15000*keV;
  // default particle kinematic
  //

  G4ParticleDefinition* particle
           = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
  fParticleGun->SetParticleDefinition(particle);
  //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,10.,0.));
  //fParticleGun->SetParticleEnergy(0*MeV);
  //fParticleGun->SetParticlePosition(G4ThreeVector(0.*mm,0.*mm,100*mm));
  */

  //################### Isotope source ################################//

	G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);
  sciCryst = new ScintSimDetectorConstruction();

  distFromCrystSurfToSource = 20*mm;
  gammaEnergy = 0.01*keV;
  // default particle kinematic

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle
                    = particleTable->FindParticle("geantino");
  fParticleGun->SetParticleDefinition(particle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ScintSimPrimaryGeneratorAction::~ScintSimPrimaryGeneratorAction()
{
  delete fParticleGun;
  delete sciCryst;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ScintSimPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  /*
  //################### Monoenergetic gamma source ############################//

  //this function is called at the begining of event
  //
  //distribution uniform in solid angle
  //
  fParticleGun->SetParticleEnergy(gammaEnergy);

  //fParticleGun->SetParticleEnergy(G4RandGauss::shoot(gammaEnergy, (30/2.355)*keV));

  G4double cosTheta = 2*G4UniformRand() - 1., phi = twopi*G4UniformRand();
  G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
  G4double ux = sinTheta*std::cos(phi),
           uy = sinTheta*std::sin(phi),
           uz = cosTheta;
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));

  crystSizeZ = sciCryst->GetSciCrystSizeZ();
  fParticleGun->SetParticlePosition(G4ThreeVector(0.*mm,0.*mm,-(distFromCrystSurfToSource+crystSizeZ+1.2*mm+0.8*mm)));
  fParticleGun->GeneratePrimaryVertex(anEvent);
  */

  //################### Isotope source ################################//
  G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition();
  G4String particleName = particle->GetParticleName();

  //1st source
  int randNumb = rand() % 100 + 1;            // random number within 1 - 100
  if (21 > randNumb > 0) {                    //branching
  crystSizeZ = sciCryst->GetSciCrystSizeZ();
    G4int Z = 27, A = 60;
    G4double ionCharge   = 0.*eplus;
    G4double excitEnergy = 0.*MeV;
    G4ParticleDefinition* ion
       = G4ParticleTable::GetParticleTable()->GetIon(Z,A,excitEnergy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(ionCharge);

    fParticleGun->SetParticlePosition(G4ThreeVector(0.*mm,0.*mm,-(distFromCrystSurfToSource+crystSizeZ+1.2*mm+0.8*mm)));
    fParticleGun->SetParticleEnergy(0*MeV);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
    fParticleGun->GeneratePrimaryVertex(anEvent);
  }

  else {
    G4int Z1 = 55, A1 = 137;
    G4double ionCharge1   = 0.*eplus;
    G4double excitEnergy1 = 0.*MeV;
    G4ParticleDefinition* ion1
       = G4ParticleTable::GetParticleTable()->GetIon(Z1,A1,excitEnergy1);
    fParticleGun->SetParticleDefinition(ion1);
    fParticleGun->SetParticleCharge(ionCharge1);

    fParticleGun->SetParticlePosition(G4ThreeVector(0.*mm,0.*mm,-(distFromCrystSurfToSource+crystSizeZ+1.2*mm+0.8*mm)));
    fParticleGun->SetParticleEnergy(0*MeV);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
    fParticleGun->GeneratePrimaryVertex(anEvent);
  }


}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

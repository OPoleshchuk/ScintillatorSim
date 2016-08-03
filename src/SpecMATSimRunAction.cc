/// \file SpecMATSimRunAction.cc
/// \brief Implementation of the SpecMATSimRunAction class

#include "SpecMATSimRunAction.hh"
#include "SpecMATSimPrimaryGeneratorAction.hh"
#include "SpecMATSimAnalysis.hh"
#include "SpecMATSimDetectorConstruction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4String.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SpecMATSimRunAction::SpecMATSimRunAction()
 : G4UserRunAction(),
   fGoodEvents(0),
   sciCryst(0),
   gammaSource(0)
{ 
  sciCryst = new SpecMATSimDetectorConstruction();
  gammaSource = new SpecMATSimPrimaryGeneratorAction();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SpecMATSimRunAction::~SpecMATSimRunAction()
{
  delete sciCryst;
  delete gammaSource;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SpecMATSimRunAction::BeginOfRunAction(const G4Run* run)
{ 
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;
  
  fGoodEvents = 0;
  
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in SpecMATSimAnalysis.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() 
         << " analysis manager" << G4endl;

  // Create directories 
  analysisManager->SetHistoDirectoryName("histograms");
  analysisManager->SetNtupleDirectoryName("ntuple");
  // Open an output file
  //
  crystMat = sciCryst->GetSciCrystMat();
  crystMatName = crystMat->GetName();
  crystShape = sciCryst->GetSciCrystShape();
  crystSizeX = G4UIcommand::ConvertToString(sciCryst->GetSciCrystSizeX()*2);
  crystSizeY = G4UIcommand::ConvertToString(sciCryst->GetSciCrystSizeY()*2);
  crystSizeZ = G4UIcommand::ConvertToString(sciCryst->GetSciCrystSizeZ()*2);
  crystSourceDist = G4UIcommand::ConvertToString(gammaSource->GetDistFromCrystSurfToSource());
  gammaEnergyStr = G4UIcommand::ConvertToString(gammaSource->GetGammaEnergy());
  
  if (crystShape == "box") {
  fileName = crystMatName+"_"+crystShape+"_"+crystSizeX+"mmx"+crystSizeY+"mmx"+crystSizeZ+"mm_"+crystSourceDist+"mm_"+gammaEnergyStr+"MeV"+"_demo"+".root";
  }
  else if (crystShape == "cylinder") { 
  fileName = crystMatName+"_"+crystShape+"_R"+crystSizeX+"mmx"+crystSizeZ+"mm_"+crystSourceDist+"mm_"+gammaEnergyStr+"MeV"+".root";
  }
  else {
  fileName = "smth_went_wrong";
  }

  analysisManager->OpenFile(fileName);
  analysisManager->SetFirstHistoId(1);

  // Creating histograms
  //
  analysisManager->CreateH1("1","Edep in crystal", 15501, 0., 15500*MeV);

  // Creating ntuple
  //
  analysisManager->CreateNtuple("Edep_in_crystal", "Edep in crystal");
  analysisManager->CreateNtupleDColumn("Edep");
  analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SpecMATSimRunAction::EndOfRunAction(const G4Run* aRun)
{
  G4int NbOfEvents = aRun->GetNumberOfEvent();
  if (NbOfEvents == 0) return;
  
  //aRun conditions
  //
  const SpecMATSimPrimaryGeneratorAction* kinematic 
    = static_cast<const SpecMATSimPrimaryGeneratorAction*>(
        G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4ParticleDefinition* particle 
    = kinematic->GetParticleGun()->GetParticleDefinition();
  G4String partName = particle->GetParticleName();                       
  
  // save histograms 
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
  
  // complete cleanup
  //
  delete G4AnalysisManager::Instance();  

  //print
  //  
  G4cout
     << "\n--------------------End of Run------------------------------\n"
     << " The Run was " << NbOfEvents << " "<< partName
     << "\n------------------------------------------------------------\n"
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

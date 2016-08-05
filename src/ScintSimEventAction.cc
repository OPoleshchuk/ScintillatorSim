/// \file ScintSimEventAction.cc
/// \brief Implementation of the ScintSimEventAction class

#include "ScintSimEventAction.hh"
#include "ScintSimRunAction.hh"
#include "ScintSimAnalysis.hh"
#include "ScintSimDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4GenericMessenger.hh"
#include "G4THitsMap.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ScintSimEventAction::ScintSimEventAction(ScintSimRunAction* runAction)
 : G4UserEventAction(),
   sciCryst(0),
   fRunAct(runAction),
   fCollID_cryst(0),
   fPrintModulo(10000000)
{
  sciCryst = new ScintSimDetectorConstruction();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ScintSimEventAction::~ScintSimEventAction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4THitsMap<G4double>*
ScintSimEventAction::GetHitsCollection(const G4String& hcName,
                                         const G4Event* event) const
{
  G4int hcID
    = G4SDManager::GetSDMpointer()->GetCollectionID(hcName);
  G4THitsMap<G4double>* hitsCollection
    = static_cast<G4THitsMap<G4double>*>(
        event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4cerr << "Cannot access hitsCollection " << hcName << G4endl;
    exit(1);
  }

  return hitsCollection;
}

G4double ScintSimEventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
  G4double sumValue = 0;
  std::map<G4int, G4double*>::iterator it;
  for ( it = hitsMap->GetMap()->begin(); it != hitsMap->GetMap()->end(); it++) {
    sumValue += *(it->second);
  }
  return sumValue;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ScintSimEventAction::BeginOfEventAction(const G4Event* event )
{
  G4int eventNb = event->GetEventID();
  G4cout << "\nEvent №" << eventNb << G4endl;

  if (eventNb == 0) {
    G4SDManager* SDMan = G4SDManager::GetSDMpointer();
    fCollID_cryst   = SDMan->GetCollectionID("crystal/edep");
  }

  if (eventNb%fPrintModulo == 0) {
    G4cout << "\n---> Begin of event: " << eventNb << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ScintSimEventAction::EndOfEventAction(const G4Event* event )
{
  //Hits collections
  //
  G4HCofThisEvent* HCE = event->GetHCofThisEvent();
  if(!HCE) return;
  //Energy in crystals : identify 'good events'
  //
  const G4double eThreshold = 0*eV;
  G4int nbOfFired = 0;

  G4THitsMap<G4double>* eventMap =
                     (G4THitsMap<G4double>*)(HCE->GetHC(fCollID_cryst));

  std::map<G4int,G4double*>::iterator itr;
  for (itr = eventMap->GetMap()->begin(); itr != eventMap->GetMap()->end(); itr++) {
    G4int copyNb  = (itr->first);
    G4double edep = *(itr->second);
    if (edep > eThreshold) nbOfFired++;
    crystMat = sciCryst->GetSciCrystMat();
    G4cout << crystMat->GetName() +  " Nb" << copyNb << ": " << edep/keV << " keV " << G4endl;


    if (crystMat->GetName() == "CeBr3") {
    //Resolution correction of registered gamma energy for CeBr3.
    absoEdep = G4RandGauss::shoot(edep/keV, (((edep/keV)*(108*pow(edep/keV, -0.498))/100)/2.355));
    }
    else if (crystMat->GetName() == "LaBr3") {
    //Resolution correction of registered gamma energy for LaBr3.
    absoEdep = G4RandGauss::shoot(edep/keV, (((edep/keV)*(81*pow(edep/keV, -0.501))/100)/2.355));
    }

    else {
    absoEdep = edep/keV;
    }

    // get analysis manager
    //
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // fill histograms
    //
    analysisManager->FillH1(1, absoEdep);

    // fill ntuple
    //
    analysisManager->FillNtupleDColumn(0, absoEdep);
    analysisManager->AddNtupleRow();
  }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

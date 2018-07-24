/// \file ScintSimDetectorConstruction.cc
/// \brief Implementation of the ScintSimDetectorConstruction class

#include "ScintSimDetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"
#include "G4VSensitiveDetector.hh"
#include "G4GDMLParser.hh"
#include "G4String.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ScintSimDetectorConstruction::ScintSimDetectorConstruction()
: G4VUserDetectorConstruction(),
  //fLogicCryst(0),
  fCheckOverlaps(true)
{

  fReadFile ="./geometry/SD.gdml";
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ScintSimDetectorConstruction::~ScintSimDetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4VPhysicalVolume* ScintSimDetectorConstruction::Construct()
{
  G4VPhysicalVolume* fWorldPhysVol;
  fParser.Read(fReadFile);
  fWorldPhysVol = fParser.GetWorldVolume();
  CreateScorers();
  return fWorldPhysVol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ScintSimDetectorConstruction::CreateScorers()
{

  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  SDman->SetVerboseLevel(1);

  // declare crystal as a MultiFunctionalDetector scorer
  //

  G4MultiFunctionalDetector* cryst = new G4MultiFunctionalDetector("crystal");
  G4PSEnergyDeposit* primitiv = new G4PSEnergyDeposit("edep");
  cryst->RegisterPrimitive(primitiv);
  SDman->AddNewDetector(cryst);
  //fLogicCryst->SetSensitiveDetector(cryst);

  /*
  G4String trackerChamberSDname = "crystal";
  G04SensitiveDetector* aTrackerSD = new G04SensitiveDetector(trackerChamberSDname);
  SDman->AddNewDetector( aTrackerSD ); */

  ///////////////////////////////////////////////////////////////////////
  //
  // Example how to retrieve Auxiliary Information for sensitive detector
  //
  const G4GDMLAuxMapType* auxmap = fParser.GetAuxMap();
  std::cout << "Found " << auxmap->size()
            << " volume(s) with auxiliary information."
            << G4endl << G4endl;
  for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();
      iter!=auxmap->end(); iter++)
  {
    G4cout << "Volume " << ((*iter).first)->GetName()
           << " has the following list of auxiliary information: "
           << G4endl << G4endl;
    for (G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();
         vit!=(*iter).second.end(); vit++)
    {
      std::cout << "--> Type: " << (*vit).type
                << " Value: " << (*vit).value << std::endl;
    }
  }
  G4cout << G4endl;

  // The same as above, but now we are looking for
  // sensitive detectors setting them for the volumes

  for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin();
      iter!=auxmap->end(); iter++)
  {
    G4cout << "Volume " << ((*iter).first)->GetName()
           << " has the following list of auxiliary information: "
           << G4endl << G4endl;
    for (G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();
         vit!=(*iter).second.end();vit++)
    {
      if ((*vit).type=="SensDet")
      {
        G4cout << "Attaching sensitive detector " << (*vit).value
               << " to volume " << ((*iter).first)->GetName()
               <<  G4endl << G4endl;

        G4VSensitiveDetector* mydet = SDman->FindSensitiveDetector((*vit).value);
        if(mydet)
        {
          G4LogicalVolume* myvol = (*iter).first;
          myvol->SetSensitiveDetector(mydet);
        }
        else
        {
          G4cout << (*vit).value << " detector not found" << G4endl;
        }
      }
      if ((*vit).type=="Color")
      {
        G4cout << "Painting " << ((*iter).first)->GetName()
               << " into " << (*vit).value
               <<  G4endl << G4endl;
        G4LogicalVolume* myvolColor = (*iter).first;
        G4String colourName = (*vit).value;
        G4Colour volumeColour;
        if (colourName == "Pink") volumeColour =  G4Colour(0.94, 0.5, 0.5);
        else if(colourName == "White") volumeColour =  G4Colour(1.0, 1.0, 1.0);
        else if (colourName == "Grey") volumeColour =  G4Colour(0.46, 0.53, 0.6);
        else if (colourName == "LightGrey") volumeColour =  G4Colour(0.7, 0.7, 0.7);
        else if (colourName == "Yellow") volumeColour =  G4Colour(1.0, 1.0, 0.);
        else if (colourName == "Blue") volumeColour =  G4Colour(0.25,0.41, 0.88 );
        else if (colourName == "LightBlue") volumeColour =  G4Colour(0.28, 0.82, 0.8);
        else if (colourName == "Green") volumeColour =  G4Colour(0., 1., 0.);
        else if (colourName == "Brown") volumeColour =  G4Colour(0.5, 0.5, 0.);
        else if (colourName == "Purple") volumeColour =  G4Colour(0.85,0.44,0.84);
        else if (colourName == "Red") volumeColour =  G4Colour(1.0, 0.0, 0.0);
        else if (colourName == "Orange") volumeColour =  G4Colour(1.,0.5,0.);
        else if  (colourName == "Black") volumeColour =  G4Colour(0.,0.,0.);
        else {G4cout<< colourName << "does not exist !!!"<< G4endl; volumeColour =  G4Colour(1.0, 1.0, 1.0);}

        G4VisAttributes* VisAtt = new G4VisAttributes(volumeColour);
        VisAtt->SetVisibility(true);
        myvolColor->SetVisAttributes(VisAtt);

      }



    }
  }

  //
  // End of Auxiliary Information block
  //
  ////////////////////////////////////////////////////////////////////////


}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

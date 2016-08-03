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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ScintSimDetectorConstruction::ScintSimDetectorConstruction()
: G4VUserDetectorConstruction(),
  fLogicCryst(0),
  fCheckOverlaps(true)
{
  DefineMaterials();
  //****************************************************************************//
  //********************************* World ************************************//
  //****************************************************************************//
  // Dimensions of world
  worldSizeXY = 40*cm;
  worldSizeZ  = 40*cm;

  // Define world material
  G4NistManager* nist = G4NistManager::Instance();
  default_mat = nist->FindOrBuildMaterial("G4_AIR", false);


  //****************************************************************************//
  //******************* CeBr3 scintillator 1.5"x1.5"x1.5" **********************//
  //****************************************************************************//

  //################ Dimensions and materials of the components ################//
  //--------------------------------------------------------//
  //***************** Scintillation crystal ****************//
  //--------------------------------------------------------//
  //Dimensions of the crystal (half-side)//

  //sciCrystShape = "box";
  sciCrystShape = "cylinder";

  sciCrystSizeX = 1.5*25*mm;					//All components are depends on Crystal size, Qartz window size Z, sciReflWindThick and sciHousWindThick, SizeX also is used as radius
  sciCrystSizeY = 1.5*25*mm;					//This dimension is not used for cylindrical shape
  sciCrystSizeZ = 1.5*25*mm;

  //Define LaBr3 material and its compounds//
  La =
	  new G4Element("Lanthanum",
		  	"La",
			z=57.,
			a=138.9055*g/mole);

  Br =
	  new G4Element("Bromine",
		  	"Br",
			z=35.,
			a=79.904*g/mole);

  density = 5.1*g/cm3;
  LaBr3 =
	  new G4Material("LaBr3",
		  	 density,
		         ncomponents=2);
  LaBr3->AddElement (La, natoms=1);
  LaBr3->AddElement (Br, natoms=3);

  sciCrystMat = LaBr3;

  /*
  //Define NaI material and its compounds//
  Na =
	  new G4Element("Sodium",
		  	"Na",
			z=11.,
			a=0.971*23.7*g/mole);
  I =
	  new G4Element("Iodine",
		  	"I",
			z=53.,
			a=4.93*25.7*g/mole);

  density = 3.67*g/cm3;
  NaI =
	  new G4Material("NaI",
		  	 density,
		         ncomponents=2);
  NaI->AddElement (Na, natoms=1);
  NaI->AddElement (I, natoms=1);

  sciCrystMat = NaI;
  */
  /*
  //Define CeBr3 material and its compounds//
  Ce =
	  new G4Element("Cerium",
		  	"Ce",
			z=58.,
			a=140.116*g/mole);
  Br =
	  new G4Element("Bromine",
		  	"Br",
			z=35.,
			a=79.904*g/mole);

  density = 5.1*g/cm3;
  CeBr3 =
	  new G4Material("CeBr3",
		  	 density,
		         ncomponents=2);
  CeBr3->AddElement (Ce, natoms=1);
  CeBr3->AddElement (Br, natoms=3);

  sciCrystMat = CeBr3;
  */
  //--------------------------------------------------------//
  //******************** Quartz window *********************//
  //--------------------------------------------------------//
  //Dimensions of the Window (half-side)//
  sciWindSizeX = sciCrystSizeX + 2.85*mm;						//X half-size of the Window
  sciWindSizeY = sciCrystSizeY + 2.85*mm;						//Y half-size of the Window
  sciWindSizeZ = 1.*mm;									//Z half-size of the Window

  //Define compound elements for Quartz material//
  O = 								//Define object for an element
	  new G4Element("Oxygen", 						//Name of the element
		  	"O", 							//Symbol of the element
			z=8., 							//Atomic number of the element
			a=15.9994*g/mole);					//Molar mass of the element
  Si =
	  new G4Element("Silicon",
		  	"Si",
			z=14.,
			a=28.09*g/mole);

  //Define Quartz material//
  density = 2.66*g/cm3;								//Assign density of Quartz ot the density variable
  Quartz = 								//Define object for the Qartz material
	  new G4Material("Quartz", 						//Name of the material
		  	 density, 						//Density of the material
			 ncomponents=2);					//Number of the compound elements in the material
  Quartz->AddElement (Si, natoms=1);						//Adds chemical element and number of atoms of this element to the material
  Quartz->AddElement (O, natoms=2);
  //--------------------------------------------------------//
  //*********************** Reflector **********************//
  //--------------------------------------------------------//
  //Dimensions of reflector (half-side)//
  sciReflWallThickX = 0.5*mm;
  sciReflWallThickY = 0.5*mm;
  sciReflWindThick = 1.2*mm;

  //Define Reflector (white powder TiO2) material and its compounds//
  Ti =
	  new G4Element("Titanium",
			"Ti",
			z=22.,
			a=47.9*g/mole);

  density = 4.23*g/cm3;
  TiO2 =
	  new G4Material("TiO2",
			 density,
			 ncomponents=2);
  TiO2->AddElement (Ti, natoms=1);
  TiO2->AddElement (O, natoms=2);
  //--------------------------------------------------------//
  //******************** Aluminum Housing ******************//
  //--------------------------------------------------------//
  //Dimensions of Housing (half-side)//
  sciHousWallThickX = 3.5*mm;
  sciHousWallThickY = 3.5*mm;
  sciHousWindThick = 0.8*mm;

  //Define Housing material and its compounds//
  Al =
	  new G4Element("Aluminum",
			"Al",
			z=13.,
			a=26.98*g/mole);

  density = 2.7*g/cm3;
  Al_Alloy =
          new G4Material("Aluminum_Alloy",
			 density,
			 ncomponents=1);
  Al_Alloy->AddElement (Al, natoms=1);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ScintSimDetectorConstruction::~ScintSimDetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ScintSimDetectorConstruction::DefineMaterials()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* ScintSimDetectorConstruction::Construct()
{

  //####################### Define world  #######################//

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       worldSizeXY, worldSizeXY, worldSizeZ); //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        default_mat,         //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      fCheckOverlaps);       // checking overlaps

  G4VisAttributes* WorldVisAtt =
	  new G4VisAttributes(G4Colour(0.0, 0.0, 4.0));				//Instantination of visualization atributes with some color
  WorldVisAtt->SetVisibility(true);						//Pass this object to Visualization Manager for visualization
  WorldVisAtt->SetForceWireframe(true);					//I still believe that it might make Crystal transparent
  logicWorld->SetVisAttributes(WorldVisAtt);				//Assignment of visualization atributes to the logical volume of the Crystal
  //############################################################################//


  //################ Position of the components ################//

  //--------------------------------------------------------//
  //***************** Scintillation crystal ****************//
  //--------------------------------------------------------//

  G4double sciCrystPosX = 0 ;						//Position of the Crystal along the X axis
  G4double sciCrystPosY = 0 ;						//Position of the Crystal along the Y axis
  G4double sciCrystPosZ = 0 ;

  G4ThreeVector sciCrystPos = G4ThreeVector(sciCrystPosX,
		  			    sciCrystPosY,
					    sciCrystPosZ);

  //--------------------------------------------------------//
  //******************** Quartz window *********************//
  //--------------------------------------------------------//
  G4double sciWindPosX = sciCrystPosX ;						//Position of the Window along the X axis
  G4double sciWindPosY = sciCrystPosY ;						//Position of the Window along the Y axis
  G4double sciWindPosZ = sciCrystPosZ + sciCrystSizeZ + sciWindSizeZ;	 	//Position of the Window relative to the Al Housing along the Z axis

  G4ThreeVector sciWindPos = G4ThreeVector(sciWindPosX, 			//Position of the Window in space relative to the Al Housing
		  			   sciWindPosY,
					   sciWindPosZ);

  //--------------------------------------------------------//
  //*********************** Reflector **********************//
  //--------------------------------------------------------//
  G4double sciReflSizeX = sciCrystSizeX + sciReflWallThickX;
  G4double sciReflSizeY = sciCrystSizeY + sciReflWallThickY;
  G4double sciReflSizeZ = sciCrystSizeZ + sciReflWindThick/2;

  G4double sciReflPosX = sciCrystPosX;
  G4double sciReflPosY = sciCrystPosY;
  G4double sciReflPosZ = sciCrystPosZ - sciReflWindThick/2;	//Position of the Reflector relative to the Al Housing along the Z axis

  G4ThreeVector sciReflPos = G4ThreeVector(sciReflPosX,
		  			   sciReflPosY,
					   sciReflPosZ);

  //--------------------------------------------------------//
  //******************** Aluminum Housing ******************//
  //--------------------------------------------------------//
  G4double sciHousSizeX = sciCrystSizeX + sciReflWallThickX + sciHousWallThickX;
  G4double sciHousSizeY = sciCrystSizeY + sciReflWallThickY + sciHousWallThickY;
  G4double sciHousSizeZ = sciCrystSizeZ + sciReflWindThick/2 + sciHousWindThick/2 + sciWindSizeZ;


  G4double sciHousPosX = sciCrystPosX;
  G4double sciHousPosY = sciCrystPosY;
  G4double sciHousPosZ = sciCrystPosZ - (sciReflWindThick/2 + sciHousWindThick/2);

  G4ThreeVector sciHousPos = G4ThreeVector(sciHousPosX,
		  			   sciHousPosY,
					   sciHousPosZ);
  //############################################################################//

  //######################### Volumes of the components ########################//

  if (sciCrystShape == "box" )
  {
  //--------------------------------------------------------//
  //***************** Scintillator crystal *****************//
  //--------------------------------------------------------//
  //Define box for Crystal//
  G4VSolid* sciCrystSolid =
	  new G4Box("sciCrystSolid",
		    sciCrystSizeX,
		    sciCrystSizeY,
		    sciCrystSizeZ);

  //Define Logical Volume for Crystal//
  fLogicCryst =
	  new G4LogicalVolume(sciCrystSolid,
			      sciCrystMat,
			      "crystal");
	  new G4PVPlacement(0,                       				//no rotation
                    	    sciCrystPos,         				//at sciCrystPos
                    	    fLogicCryst,                			//Crystal logical volume
                    	    "sciCrystPl",              				//Crystal positioning name
                    	    logicWorld,              				//its mother  volume
                    	    false,                   				//no boolean operation
                    	    0,                       				//copy number
                    	    fCheckOverlaps);          				//overlaps checking

  // Visualization attributes for the Crystal logical volume
  G4VisAttributes* sciCrystVisAtt =
	  new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));				//Instantination of visualization atributes with blue color
  sciCrystVisAtt->SetVisibility(true);						//Pass this object to Visualization Manager for visualization
  sciCrystVisAtt->SetForceWireframe(true);					//I still believe that it might make Crystal transparent
  fLogicCryst->SetVisAttributes(sciCrystVisAtt);				//Assignment of visualization atributes to the logical volume of the Crystal
  //--------------------------------------------------------//

  //--------------------------------------------------------//
  //******************** Quartz window *********************//
  //--------------------------------------------------------//
  //Define solid for the Window//
  G4VSolid* sciWindSolid = 							//Define object for the Window's box
	  new G4Box("sciWindSolid",						//Name of the Window's box
		    sciWindSizeX, 						//X half_size of the box
		    sciWindSizeY, 						//Y half_size of the box
		    sciWindSizeZ);						//Z half_size of the box


  //Define Logical Volume for Window//
  G4LogicalVolume* sciWindLog =
	  new G4LogicalVolume(sciWindSolid,
		  	      Quartz,
			      "sciWindLog");
  	  new G4PVPlacement(0,                       				//no rotation
                    	    sciWindPos,         				//at sciWindPos
                    	    sciWindLog,                				//Window logical volume
                    	    "sciWindPl",              				//Window positioning name
                    	    logicWorld,              				//its mother  volume
                    	    false,                   				//no boolean operation
                    	    0,                       				//copy number
                    	    fCheckOverlaps);          				//overlaps checking

  // Visualization attributes for the Window
  G4VisAttributes* sciWindVisAtt =
	  new G4VisAttributes(G4Colour(0.0, 1.0, 1.0));				//Instantination of visualization atributes with cyan color
  sciWindVisAtt->SetVisibility(true);						//Pass this object to Visualization Manager for visualization
  sciWindVisAtt->SetForceWireframe(true);					//I believe that it might make Window transparent
  sciWindLog->SetVisAttributes(sciWindVisAtt);					//Assignment of visualization atributes to the logical volume of the Window
  //--------------------------------------------------------//

  //--------------------------------------------------------//
  //*********************** Reflector **********************//
  //--------------------------------------------------------//
  //Define box for Reflector//
  G4VSolid* reflBoxSolid =
	  new G4Box("reflBoxSolid",
		    sciReflSizeX,
		    sciReflSizeY,
		    sciReflSizeZ);

  //Subtracts Crystal box from Reflector box//

  G4VSolid* sciReflSolid =
	  new G4SubtractionSolid("sciReflSolid",
		  		 reflBoxSolid,
				 sciCrystSolid,
				 0,
				 G4ThreeVector(sciCrystPosX, sciCrystPosY, sciReflWindThick/2));


  //Define Logical Volume for Reflector//
  G4LogicalVolume* sciReflLog =
	  new G4LogicalVolume(sciReflSolid,
			      TiO2,
			      "sciReflLog");
  	  new G4PVPlacement(0,                       				//no rotation
                    	    sciReflPos,         				//at sciReflPos
                    	    sciReflLog,                				//Reflector logical volume
                    	    "sciReflPl",              				//Relfector positioning name
                    	    logicWorld,              				//its mother  volume
                    	    false,                   				//no boolean operation
                    	    0,                       				//copy number
                    	    fCheckOverlaps);          				//overlaps checking
  // Visualization attributes for the Reflector logical volume
  G4VisAttributes* sciReflVisAtt =
	  new G4VisAttributes(G4Colour(1.0, 1.0, 0.0));				//Instantination of visualization atributes with yellow color
  sciReflVisAtt->SetVisibility(true);						//Pass this object to Visualization Manager for visualization
  sciReflLog->SetVisAttributes(sciReflVisAtt);					//Assignment of visualization atributes to the logical volume of the Reflector
  //--------------------------------------------------------//

  //--------------------------------------------------------//
  //******************** Aluminum Housing ******************//
  //--------------------------------------------------------//
  //Define box for Housing//
  G4VSolid* housBoxASolid =
	  new G4Box("housBoxASolid",
	  	    sciHousSizeX,
		    sciHousSizeY,
		    sciHousSizeZ);
  //Subtracts Reflector box from Housing box//
  G4VSolid* housBoxBSolid =
	  new G4SubtractionSolid("housBoxBSolid",
	  			 housBoxASolid,
				 reflBoxSolid,
				 0,
				 G4ThreeVector(sciCrystPosX, sciCrystPosY, -(sciHousSizeZ - sciReflSizeZ - sciHousWindThick)));
  //Subtracts Window box from Housing box withouh Reflector box//
  G4VSolid* sciHousSolid =
	  new G4SubtractionSolid("sciHousSolid",
	  			 housBoxBSolid,
				 sciWindSolid,
				 0,
				 G4ThreeVector(sciCrystPosX, sciCrystPosY, (sciHousSizeZ - sciWindSizeZ)));


  //Define Logical Volume for Housing//
  G4LogicalVolume* sciHousLog =
  	  new G4LogicalVolume(sciHousSolid, 	     				//Housing solid shape
			      Al_Alloy,              				//Housing material
			      "sciCaseLog");         				//Housing logic volume name
  //Define position of Case//
  	  new G4PVPlacement(0,                       				//no rotation
                    	    sciHousPos,         				//at (0,0,0)
                    	    sciHousLog,              				//Hous logical volume
                    	    "sciHousPl",             				//Hous positioning name
                    	    logicWorld,                				//its mother  volume
                    	    false,                   				//no boolean operation
                    	    0,                       				//copy number
                    	    fCheckOverlaps);          				//overlaps checking
  // Visualization attributes for the Housing logical volume
  G4VisAttributes* sciHousVisAtt =
	  new G4VisAttributes(G4Colour(0.5, 0.5, 0.5));				//Instantination of visualization atributes with grey color
  sciHousVisAtt->SetVisibility(true);						//Pass this object to Visualization Manager for visualization
  sciHousLog->SetVisAttributes(sciHousVisAtt);					//Assignment of visualization atributes to the logical volume of the Housing
  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
  //
  CreateScorers();

  //
  //always return the physical World
  //
  return physWorld;
}

  else if(sciCrystShape == "cylinder")
{
  //--------------------------------------------------------//
  //***************** Scintillator crystal *****************//
  //--------------------------------------------------------//
  //Define box for Crystal//
  G4VSolid* sciCrystSolid =
	  new G4Tubs("sciCrystSolid",
		    0.*mm,
		    sciCrystSizeX,
		    sciCrystSizeZ,
		    0.*deg,
		    360.*deg);

  //Define Logical Volume for Crystal//
  fLogicCryst =
	  new G4LogicalVolume(sciCrystSolid,
			      sciCrystMat,
			      "crystal");
	  new G4PVPlacement(0,                       				//no rotation
                    	    sciCrystPos,         				//at sciCrystPos
                    	    fLogicCryst,                			//Crystal logical volume
                    	    "sciCrystPl",              				//Crystal positioning name
                    	    logicWorld,              				//its mother  volume
                    	    false,                   				//no boolean operation
                    	    0,                       				//copy number
                    	    fCheckOverlaps);          				//overlaps checking

  // Visualization attributes for the Crystal logical volume
  G4VisAttributes* sciCrystVisAtt =
	  new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));				//Instantination of visualization atributes with blue color
  sciCrystVisAtt->SetVisibility(true);						//Pass this object to Visualization Manager for visualization
  sciCrystVisAtt->SetForceWireframe(true);					//I still believe that it might make Crystal transparent
  fLogicCryst->SetVisAttributes(sciCrystVisAtt);				//Assignment of visualization atributes to the logical volume of the Crystal
  //--------------------------------------------------------//

  //--------------------------------------------------------//
  //******************** Quartz window *********************//
  //--------------------------------------------------------//
  //Define solid for the Window//
  G4VSolid* sciWindSolid = 							//Define object for the Window's box
	  new G4Tubs("sciWindSolid",						//Name of the Window's box
		    0.*mm, 						//X half_size of the box
		    sciWindSizeX, 						//Y half_size of the box
		    sciWindSizeZ,
		    0.*deg,
		    360.*deg);						//Z half_size of the box


  //Define Logical Volume for Window//
  G4LogicalVolume* sciWindLog =
	  new G4LogicalVolume(sciWindSolid,
		  	      Quartz,
			      "sciWindLog");
  	  new G4PVPlacement(0,                       				//no rotation
                    	    sciWindPos,         				//at sciWindPos
                    	    sciWindLog,                				//Window logical volume
                    	    "sciWindPl",              				//Window positioning name
                    	    logicWorld,              				//its mother  volume
                    	    false,                   				//no boolean operation
                    	    0,                       				//copy number
                    	    fCheckOverlaps);          				//overlaps checking

  // Visualization attributes for the Window
  G4VisAttributes* sciWindVisAtt =
	  new G4VisAttributes(G4Colour(0.0, 1.0, 1.0));				//Instantination of visualization atributes with cyan color
  sciWindVisAtt->SetVisibility(true);						//Pass this object to Visualization Manager for visualization
  sciWindVisAtt->SetForceWireframe(true);					//I believe that it might make Window transparent
  sciWindLog->SetVisAttributes(sciWindVisAtt);					//Assignment of visualization atributes to the logical volume of the Window
  //--------------------------------------------------------//

  //--------------------------------------------------------//
  //*********************** Reflector **********************//
  //--------------------------------------------------------//
  //Define box for Reflector//
  G4VSolid* reflCylSolid =
	  new G4Tubs("reflCylSolid",
		    0.*mm,
		    sciReflSizeX,
		    sciReflSizeZ,
		    0.*deg,
		    360.*deg);

  //Subtracts Crystal box from Reflector box//

  G4VSolid* sciReflSolid =
	  new G4SubtractionSolid("sciReflSolid",
		  		 reflCylSolid,
				 sciCrystSolid,
				 0,
				 G4ThreeVector(sciCrystPosX, sciCrystPosY, sciReflWindThick/2));


  //Define Logical Volume for Reflector//
  G4LogicalVolume* sciReflLog =
	  new G4LogicalVolume(sciReflSolid,
			      TiO2,
			      "sciReflLog");
  	  new G4PVPlacement(0,                       				//no rotation
                    	    sciReflPos,         				//at sciReflPos
                    	    sciReflLog,                				//Reflector logical volume
                    	    "sciReflPl",              				//Relfector positioning name
                    	    logicWorld,              				//its mother  volume
                    	    false,                   				//no boolean operation
                    	    0,                       				//copy number
                    	    fCheckOverlaps);          				//overlaps checking
  // Visualization attributes for the Reflector logical volume
  G4VisAttributes* sciReflVisAtt =
	  new G4VisAttributes(G4Colour(1.0, 1.0, 0.0));				//Instantination of visualization atributes with yellow color
  sciReflVisAtt->SetVisibility(true);						//Pass this object to Visualization Manager for visualization
  sciReflLog->SetVisAttributes(sciReflVisAtt);					//Assignment of visualization atributes to the logical volume of the Reflector
  //--------------------------------------------------------//

  //--------------------------------------------------------//
  //******************** Aluminum Housing ******************//
  //--------------------------------------------------------//
  //Define box for Housing//
  G4VSolid* housCylASolid =
	  new G4Tubs("housCylASolid",
	  	    0.*mm,
		    sciHousSizeX,
		    sciHousSizeZ,
		    0.*deg,
		    360.*deg);

  //Subtracts Reflector box from Housing box//
  G4VSolid* housCylBSolid =
	  new G4SubtractionSolid("housCylBSolid",
	  			 housCylASolid,
				 reflCylSolid,
				 0,
				 G4ThreeVector(sciCrystPosX, sciCrystPosY, -(sciHousSizeZ - sciReflSizeZ - sciHousWindThick)));
  //Subtracts Window box from Housing box withouh Reflector box//
  G4VSolid* sciHousSolid =
	  new G4SubtractionSolid("sciHousSolid",
	  			 housCylBSolid,
				 sciWindSolid,
				 0,
				 G4ThreeVector(sciCrystPosX, sciCrystPosY, (sciHousSizeZ - sciWindSizeZ)));


  //Define Logical Volume for Housing//
  G4LogicalVolume* sciHousLog =
  	  new G4LogicalVolume(sciHousSolid, 	     				//Housing solid shape
			      Al_Alloy,              				//Housing material
			      "sciCaseLog");         				//Housing logic volume name
  //Define position of Case//
  	  new G4PVPlacement(0,                       				//no rotation
                    	    sciHousPos,         				//at (0,0,0)
                    	    sciHousLog,              				//Hous logical volume
                    	    "sciHousPl",             				//Hous positioning name
                    	    logicWorld,                				//its mother  volume
                    	    false,                   				//no boolean operation
                    	    0,                       				//copy number
                    	    fCheckOverlaps);          				//overlaps checking
  // Visualization attributes for the Housing logical volume
  G4VisAttributes* sciHousVisAtt =
	  new G4VisAttributes(G4Colour(0.5, 0.5, 0.5));				//Instantination of visualization atributes with grey color
  sciHousVisAtt->SetVisibility(true);						//Pass this object to Visualization Manager for visualization
  sciHousLog->SetVisAttributes(sciHousVisAtt);					//Assignment of visualization atributes to the logical volume of the Housing
  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
  //
  CreateScorers();

  //
  //always return the physical World
  //
  return physWorld;
}
  else
{
  return physWorld;
}
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
  fLogicCryst->SetSensitiveDetector(cryst);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

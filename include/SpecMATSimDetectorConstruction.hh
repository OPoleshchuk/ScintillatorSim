/// \file SpecMATSimDetectorConstruction.hh
/// \brief Definition of the SpecMATSimDetectorConstruction class

#ifndef SpecMATSimDetectorConstruction_h
#define SpecMATSimDetectorConstruction_h 1

#include "G4Material.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.
///

class SpecMATSimDetectorConstruction : public G4VUserDetectorConstruction
{
  private:
    void DefineMaterials();
    void CreateScorers();

    G4double a, z, density;
    G4int natoms, ncomponents;

    G4double worldSizeXY;
    G4double worldSizeZ;

    G4double sciCrystSizeX;      
    G4double sciCrystSizeY;
    G4double sciCrystSizeZ;

    G4double sciWindSizeX;
    G4double sciWindSizeY;
    G4double sciWindSizeZ;

    G4double sciReflWallThickX;
    G4double sciReflWallThickY;
    G4double sciReflWindThick;

    G4double sciHousWallThickX;
    G4double sciHousWallThickY;
    G4double sciHousWindThick;
    
    G4Element* La;
    G4Element* Ce;
    G4Element* Br;
    G4Element* O;
    G4Element* Si;
    G4Element* Ti;
    G4Element* Al;
    G4Element* Na;
    G4Element* I;

    G4Material* default_mat;
    G4Material* LaBr3;
    G4Material* CeBr3;
    G4Material* NaI;
    G4Material* sciCrystMat;
    G4Material* Quartz;
    G4Material* TiO2;
    G4Material* Al_Alloy;
    
    G4String sciCrystShape;

    G4LogicalVolume*  fLogicCryst;
    
    G4bool  fCheckOverlaps;

  public:
    SpecMATSimDetectorConstruction();
    virtual ~SpecMATSimDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    void SetSciCrystSizeX(G4double val){sciCrystSizeX = val;}
    G4double GetSciCrystSizeX(void){return sciCrystSizeX;}

    void SetSciCrystSizeY(G4double val){sciCrystSizeY = val;}
    G4double GetSciCrystSizeY(void){return sciCrystSizeY;}

    void SetSciCrystSizeZ(G4double val){sciCrystSizeZ = val;}
    G4double GetSciCrystSizeZ(void){return sciCrystSizeZ;}

    void SetSciCrystMat (G4String);
    G4Material* GetSciCrystMat(){return sciCrystMat;}
    
    void SetSciCrystShape (G4String);
    G4String GetSciCrystShape(){return sciCrystShape;}
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


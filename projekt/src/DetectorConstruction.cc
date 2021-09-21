//
// $Id: DetectorConstruction.cc 12.16.2016 A. Fijalkowska $
//	+ A.Djakonow
/// \file DetectorConstruction.cc
/// \brief DetectorConstruction class
//
//
#include "DetectorConstruction.hh"
#include "G4PVPlacement.hh" //tworzenie physical volume
#include "G4SystemOfUnits.hh" //jednostki
#include "G4VisAttributes.hh" //sposob wyświetlania, kolory itp

#include "G4Box.hh" //prostopadłościan
#include "G4Tubs.hh" //walec
#include "G4ThreeVector.hh" //trzyelementowy wektor wbudowany w geant
#include "globals.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4SDManager.hh"
#include "G4PSEnergyDeposit.hh"
#include "DetectorTube.hh"
#include "MakeHel.hh"


DetectorConstruction::DetectorConstruction()
{
    worldLogic = 0L;
    tubeLogVol=0L;
    boxLogVol = 0L;
    helLogVol = 0L;

    man = G4NistManager::Instance();
}



DetectorConstruction::~DetectorConstruction() 
{
    if(worldLogic != 0L)
        delete worldLogic;
    if(tubeLogVol != 0L)
        delete tubeLogVol;
    if(boxLogVol !=0L)
        delete boxLogVol;
    if(helLogVol != 0L)
        delete helLogVol;
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4VPhysicalVolume* worldPhys = ConstructWorld();
    ConstructDetectorTube();
    ConstructHel();

    return worldPhys;
}


G4VPhysicalVolume* DetectorConstruction::ConstructWorld()
{

    G4double worldX = 0.4*m;
    G4double worldY = 0.4*m;
    G4double worldZ = 0.4*m;
    G4Box* worldSolid = new G4Box("worldSolid",worldX,worldY,worldZ);
    
    G4Material* vaccum = new G4Material("GalacticVacuum", 1., 1.01*g/mole,
                           CLHEP::universe_mean_density, 
                           kStateGas, 3.e-18*pascal, 2.73*kelvin);
                           
    worldLogic = new G4LogicalVolume(worldSolid, vaccum,"worldLogic", 0,0,0);
                                             
    //worldLogic->SetVisAttributes(G4VisAttributes::Invisible);
    G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "world", 0, false, 0);
    return worldPhys;

}
void DetectorConstruction::ConstructDetectorTube()
{   
    G4double radiusMax = 1.25*cm;
    G4double length = 50*cm;
    DetectorTube *licznik = new DetectorTube(length, radiusMax);


        G4ThreeVector pos(0,0,0);
	G4RotationMatrix *pRot = new G4RotationMatrix();
        licznik->Place(pRot, pos, "licznik", worldLogic, 0);
	
}

void DetectorConstruction::ConstructHel()
{
    G4double radiusMax = 1.25*cm;
    G4double length = 50*cm;
    MakeHel *hel3 = new MakeHel(length, radiusMax);


    G4ThreeVector pos(0,0,0);
    G4RotationMatrix *pRot = new G4RotationMatrix();
    hel3->Place(pRot, pos, "hel3", worldLogic, 0);

}
void DetectorConstruction::ConstructSDandField() 
{

}





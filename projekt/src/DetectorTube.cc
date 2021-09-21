#include "DetectorTube.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh" //jednostki
#include "G4PVPlacement.hh" 


DetectorTube::DetectorTube(double heigh, double radius)
{
    ConstructTube(heigh, radius);
}

void DetectorTube::ConstructTube(double heigh, double radius)
{
    G4double width = 0.1*cm;
    G4double radiusMin = radius-width;
    G4double radiusMax = radius;
    G4double length = heigh;


    G4Tubs* tubeSolid = new G4Tubs("tubeSolid", radiusMin, radiusMax, length/2., 0*deg, 360*deg);
    G4Tubs* endCapSolid = new G4Tubs("endCapSolid",0, radiusMax, width,0*deg, 360*deg); //zamkniecie tuby detektora

    G4Material* alu = MakeAlu();
    tubeLogVol = new G4LogicalVolume(tubeSolid, alu, "tubeLogVol");
    boxLogVol = new G4LogicalVolume(endCapSolid, alu, "boxLogVol");

     
    G4VisAttributes* tubeVisAtt = new G4VisAttributes( G4Colour(1,0.8,0.8));
        tubeVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
        //tubeVisAtt->SetForceSolid(true);
        tubeLogVol->SetVisAttributes(tubeVisAtt);

                G4ThreeVector pos(0,0,length/2.+0.1*cm);
                new G4PVPlacement(0, pos, boxLogVol, "boxLogVol", tubeLogVol, 0, 0);

                G4ThreeVector pos2(0,0,-length/2.-0.1*cm);
                new G4PVPlacement(0, pos2, boxLogVol, "boxLogVol", tubeLogVol, 0, 1);

            G4VisAttributes* endCapVisAtt = new G4VisAttributes( G4Colour(1,0.8,0.8));
                endCapVisAtt->SetForceAuxEdgeVisible(true);// Can see outline when drawn with lines
                boxLogVol->SetVisAttributes(endCapVisAtt);

}
G4Material* DetectorTube::MakeAlu()
{
    G4NistManager* man=G4NistManager::Instance();

   G4Element* Fe = man->FindOrBuildElement("Fe");
   G4Element* Cr = man->FindOrBuildElement("Cr");
   G4Element* Ni = man->FindOrBuildElement("Ni");
   G4Element* Mo = man->FindOrBuildElement("Mo");
   G4Element* C = man->FindOrBuildElement("C");
   G4Element* Mn = man->FindOrBuildElement("Mn");
   G4Element* Cu = man->FindOrBuildElement("Cu");
   G4Element* P = man->FindOrBuildElement("P");
   G4Element* S = man->FindOrBuildElement("S");
   G4Element* Si = man->FindOrBuildElement("Si");
   G4Element* N = man->FindOrBuildElement("N");

   G4Material* alu = new G4Material("alu", 8.0*g/cm3, 11);

   alu->AddElement(Fe, 64.335*perCent);
   alu->AddElement(Cr, 17*perCent);
   alu->AddElement(Ni, 13*perCent);
   alu->AddElement(Mo, 2.25*perCent);
   alu->AddElement(C, 0.03*perCent);
   alu->AddElement(Mn, 2.0*perCent);
   alu->AddElement(Cu, 0.5*perCent);
   alu->AddElement(P, 0.025*perCent);
   alu->AddElement(S, 0.01*perCent);
   alu->AddElement(Si, 0.075*perCent);
   alu->AddElement(N, 0.1*perCent);

    return alu;

}

void DetectorTube::Place(G4RotationMatrix *pRot,
                        G4ThreeVector &tlate, 
                        const G4String &pName, 
                        G4LogicalVolume *pMotherLogical,  
                        G4int pCopyNo)
{
    new G4PVPlacement(pRot, tlate, tubeLogVol, pName,  pMotherLogical, 0,pCopyNo);
}


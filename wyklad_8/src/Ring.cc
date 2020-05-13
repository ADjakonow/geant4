
#include "Ring.hh"
#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh" //jednostki
#include "G4PVPlacement.hh" 
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4SDManager.hh"
#include "G4PSEnergyDeposit.hh"

Ring::Ring(double rMin, double rMax, double length, G4LogicalVolume* worldLogic)
{

	naiLogic = 0;
	CylinderBuild(rMin,rMax, length, worldLogic);
	ConstructNaIDet();
	
	//ConstructSDandField();

}

void Ring::CylinderBuild(double rMin, double rMax, double length, G4LogicalVolume* worldLogic)
{
	double radiusMin = rMin;
	double radiusMax = rMax;
	double heigh = length;
	G4Tubs* theCylinder = new G4Tubs("theCylinder", radiusMin, radiusMax, heigh/2, 0*deg, 360*deg); 
	G4Material* poli = man->FindOrBuildMaterial("G4_POLYPROPYLENE");
	cylinderLogVol = new G4LogicalVolume(theCylinder,poli, "cylinderLogVol");

	G4VisAttributes* cylinderAtt = new G4VisAttributes(G4Colour(0.5,0.5,0.5, 0.7));
	cylinderAtt->SetForceAuxEdgeVisible(true);
	cylinderAtt->SetForceSolid(true);
	cylinderLogVol->SetVisAttributes(cylinderAtt);
	
	G4ThreeVector pos(0,0,0);
	new G4PVPlacement(0,pos,cylinderLogVol, "cylinderPhy",worldLogic,0,0);
    
}
void Ring::ConstructNaIDet()
{
   G4LogicalVolume* aluLogic = ConstructAluLayer();
   G4LogicalVolume* teflonLogic = ConstructTeflonLayer();  
   naiLogic = ConstructNaI();

   G4ThreeVector pos(0,0,0); 
   new G4PVPlacement(0, pos, naiLogic, "naiPhys", teflonLogic, 0,0);
   new G4PVPlacement(0, pos, teflonLogic, "teflonPhys", aluLogic, 0, 0);
  // new G4PVPlacement(0, pos, aluLogic, "aluPhys", cylinderLogVol, 0, 0);

   double ringRadius = 46.6*cm;
   
   double num = 36.;		//liczba detektorow
   double kat = 360/num;
   for(int i=0; i<num; i++){
   	double angle = i*deg*kat;
   	G4ThreeVector naiDetPos(ringRadius*sin(angle),ringRadius*cos(angle),0);
  	G4RotationMatrix* rot = new G4RotationMatrix();
   	rot->rotateZ(angle);
   	rot->rotateX(90*deg);
   	new G4PVPlacement(rot, naiDetPos, aluLogic, "aluPhys", cylinderLogVol, 0, i);

   }
}
G4LogicalVolume* Ring::ConstructAluLayer()
{
   G4double rMin = 0;
   G4double rMax = 3.6 *cm;
   G4double halfLength = 5.6 *cm; 
   G4Tubs* aluSolid = new G4Tubs("aluSolid", rMin, rMax, halfLength, 0*deg, 360*deg);
   
   G4Material* alu = new G4Material("aluminum", 2.7*g/cm3, 1);
   G4Element* Al = man->FindOrBuildElement("Al");
   alu->AddElement(Al, 1);
   
   G4LogicalVolume* aluLogic = new G4LogicalVolume(aluSolid, alu,"aluLogic");
   G4VisAttributes* aluVis = new G4VisAttributes(G4Colour(255./255,102./255.,0));
   //aluVis->SetForceSolid(true);
   aluVis->SetForceAuxEdgeVisible(true);
   aluLogic->SetVisAttributes(aluVis);
   return aluLogic;
}

G4LogicalVolume* Ring::ConstructTeflonLayer()
{
   G4double rMin = 0;
   G4double rMax = 3.3 *cm;
   G4double halfLength = 5.3 *cm; 
   G4Tubs* solid = new G4Tubs("solid", rMin, rMax, halfLength, 0*deg, 360*deg);
   
   G4Material* teflon = man->FindOrBuildMaterial("G4_TEFLON");

   
   G4LogicalVolume* teflonLogic = new G4LogicalVolume(solid, teflon,"teflonLogic");
   G4VisAttributes* visAttr = new G4VisAttributes(G4Colour(0,204/255.,255/255.));
   //visAttr->SetForceSolid(true);
   visAttr->SetForceAuxEdgeVisible(true);
   teflonLogic->SetVisAttributes(visAttr);
   return teflonLogic;
}

G4LogicalVolume* Ring::ConstructNaI()
{
   G4double rMin = 0;
   G4double rMax = 3 *cm;
   G4double halfLength = 5*cm; 
   G4Tubs* NaIsolid = new G4Tubs("NaIsolid", rMin, rMax, halfLength, 0*deg, 360*deg);
   
   G4Material* nai = man->FindOrBuildMaterial("G4_SODIUM_IODIDE");

   
   G4LogicalVolume* naiLogic = new G4LogicalVolume(NaIsolid, nai,"naiLogic");
   G4VisAttributes* visAttr = new G4VisAttributes(G4Colour(44/255.,160/255.,44/255.));
   visAttr->SetForceSolid(true);
   visAttr->SetForceAuxEdgeVisible(true);
   naiLogic->SetVisAttributes(visAttr);
   return naiLogic;
}

void Ring::ConstructSDandField()
{
	G4MultiFunctionalDetector* detector = new G4MultiFunctionalDetector("naISensitiveDet");
	G4int depth = 2;
	G4VPrimitiveScorer* energyDepScorer = new G4PSEnergyDeposit("eDep", depth);
	detector->RegisterPrimitive(energyDepScorer);
	naiLogic->SetSensitiveDetector(detector);
	G4SDManager* SDmanager = G4SDManager::GetSDMpointer();
	SDmanager->AddNewDetector(detector);


}









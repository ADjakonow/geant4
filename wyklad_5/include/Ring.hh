//Zadanie do wykladu 5
//class Ring -- budowa rigu z polipropylenu z detektorami z NaI
// A.Djakonow 3.04.2020


#ifndef Ring_H
#define Ring_H 1

#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"  //wbudowane materiały
#include "G4LogicalVolume.hh"

class Ring
{
	public:
	Ring(double rMin, double rMax, double length, G4LogicalVolume* worldLogic);
	
	private:
	void CylinderBuild(double rMin, double rMax, double length, G4LogicalVolume* worldLogic);
	void ConstructNaIDet();
	G4LogicalVolume* ConstructAluLayer();
	G4LogicalVolume* ConstructTeflonLayer();
	G4LogicalVolume* ConstructNaI();
    
	//G4LogicalVolume* worldLogic; //świat
	G4NistManager* man=G4NistManager::Instance();
 	G4LogicalVolume* cylinderLogVol;
};    

#endif

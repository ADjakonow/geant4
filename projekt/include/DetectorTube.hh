//A.Djakonow
//klasa tworząca obudowę detektora

#ifndef DetectorTube_H
#define DetectorTube_H 1
#include "G4Material.hh"
#include "G4LogicalVolume.hh"

class DetectorTube
{
    public:
    DetectorTube(double heigh, double radius);
    void Place(G4RotationMatrix *pRot, 
                        G4ThreeVector &tlate, 
                        const G4String &pName, 
                        G4LogicalVolume *pMotherLogical,  
                        G4int pCopyNo);
    
    private:
    void ConstructTube(double heigh, double radius);
    G4Material* MakeAlu();
    
    G4LogicalVolume* tubeLogVol;
    G4LogicalVolume* boxLogVol;


};

#endif

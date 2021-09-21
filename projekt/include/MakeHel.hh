//A.Djakonow
//klasa tworząca bryłę helu
#ifndef MakeHel_H
#define MakeHel_H 1
#include "G4Material.hh"
#include "G4LogicalVolume.hh"

class MakeHel
{
    public:
    MakeHel(double heigh, double radius);
    void Place(G4RotationMatrix *pRot,
                        G4ThreeVector &tlate,
                        const G4String &pName,
                        G4LogicalVolume *pMotherLogical,
                        G4int pCopyNo);

    private:
    void ConstructHel(double heigh, double radius);
    G4Material* MakeGas();

    G4LogicalVolume* helLogVol;

};



#endif // MAKEHEL_HH


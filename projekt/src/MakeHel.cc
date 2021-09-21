//A.Djakonow
#include "MakeHel.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh" //jednostki
#include "G4PVPlacement.hh"

MakeHel::MakeHel(double heigh, double radius){

    ConstructHel(heigh, radius);

}
void MakeHel::ConstructHel(double heigh, double radius)
{
   G4double width = 0.1*cm;
   G4double rMin = 0;
   G4double rMax = radius - width;
   G4double halfLength = heigh/2.;
   G4Tubs* helSolid = new G4Tubs("helSolid", rMin, rMax, halfLength, 0*deg, 360*deg);

    G4Material *hel = MakeGas();

   helLogVol = new G4LogicalVolume(helSolid, hel,"helLogic");
   G4VisAttributes* helVis = new G4VisAttributes(G4Colour::Yellow());
   helVis->SetForceSolid(true);
   helVis->SetForceAuxEdgeVisible(true);
   helLogVol->SetVisAttributes(helVis);



}

G4Material* MakeHel::MakeGas()
{

    G4int protons=2, neutrons=1, nucleons=protons+neutrons;
    G4double atomicMass = 3.016*g/mole;
    G4Isotope* he3 = new G4Isotope("He3", protons, nucleons, atomicMass);
    G4Element* He3 = new G4Element("Helium3", "He3", 1);
    He3->AddIsotope(he3, 100*perCent);
    G4double pressure = 4*atmosphere;
    G4double temperature = 293*kelvin;
    G4double molar_constant = CLHEP::Avogadro*CLHEP::k_Boltzmann;  //from clhep
    G4double density = (atomicMass*pressure)/(temperature*molar_constant);

    G4Material* Helium3 = new G4Material("Helium3", density, 1, kStateGas, temperature, pressure);
    Helium3->AddElement(He3, 100*perCent);

    return Helium3;
}

void MakeHel::Place(G4RotationMatrix *pRot,
                        G4ThreeVector &tlate,
                        const G4String &pName,
                        G4LogicalVolume *pMotherLogical,
                        G4int pCopyNo)
{
    new G4PVPlacement(pRot, tlate, helLogVol, pName,  pMotherLogical, 0,pCopyNo);
}

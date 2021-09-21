//
// $Id: PrimaryGeneratorAction.hh 15.10.2018 A Fijalkowska $
//	+ A.Djakonow
/// \file PrimaryGeneratorAction.hh
/// \brief Definition of the PrimaryGeneratorAction class

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event*);

  private:
	void SetUpDefault();	
        G4ThreeVector GenerateIsotropicDirection(G4double thetaMin,G4double thetaMax,G4double phiMin, G4double phiMax);
        void GenerateNeutronIncident(G4Event*);
    G4ParticleGun* particleGun;
    G4ParticleTable* particleTable;

};


#endif 



// $Id: PrimaryGeneratorAction.cc 15.10.2018 A Fijalkowska $
//	+A.Djakonow 
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction()
{
    particleGun = new G4ParticleGun();
    particleTable = G4ParticleTable::GetParticleTable();
	SetUpDefault();
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

void PrimaryGeneratorAction::SetUpDefault()
{
	
        G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
        particleGun->SetParticleDefinition(particle);
        particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,0.0*cm));
        particleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
        particleGun->SetParticleEnergy(500.0*keV);
	
	int size = particleTable->size();
        std::cout<<"Rozmiar "<<size<<std::endl;
	
	for(int i = 0; i<size; i++){
                std::cout<<particleTable->GetParticleName(i)<<" ";
	}


}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{		
        GenerateNeutronIncident(anEvent);
       // particleGun->SetParticleMomentumDirection(GenerateIsotropicDirection());
       // particleGun->GeneratePrimaryVertex(anEvent);
        //std::cout<<GenerateIsotropicDirection()<<std::endl;

}	

G4ThreeVector PrimaryGeneratorAction::GenerateIsotropicDirection(G4double thetaMin,
                                                                 G4double thetaMax,
                                                                 G4double phiMin,
                                                                 G4double phiMax)
{

    double phi = G4UniformRand()*(phiMax-phiMin)+phiMin;
    double theta = G4UniformRand()*(thetaMax-thetaMin)+thetaMin;
    double sinTheta;
    double cosTheta;
    double cosPhi;
    double sinPhi;

    cosTheta = cos(theta);
    sinTheta = sin(theta);
    cosPhi = cos(phi);
    sinPhi = sin(phi);
    return G4ThreeVector(-sinTheta*cosPhi,-sinTheta*sinPhi,-cosTheta);

}
void PrimaryGeneratorAction::GenerateNeutronIncident(G4Event *anEvent)
{
    G4double thetaMin = 1.1*M_PI;
    G4double thetaMax = 1.9*M_PI;
    G4double phiMin = 1.3*M_PI;
    G4double phiMax = 1.7*M_PI;


        G4ThreeVector p(0.0*cm,10.0*cm,0*cm);		//poczatek ganu
        G4ParticleDefinition* particle = particleTable->FindParticle("neutron");
	particleGun->SetParticleDefinition(particle);
        particleGun->SetParticlePosition(p);	//start działa neutronowego
        particleGun->SetParticleMomentumDirection(GenerateIsotropicDirection(thetaMin,thetaMax,phiMin,phiMax));
        particleGun->SetParticleEnergy(0.024*eV);	//energia neutronu termicznego
	particleGun->GeneratePrimaryVertex(anEvent);	//wyslij czastke
}




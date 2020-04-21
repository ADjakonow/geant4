
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
	std::cout<<std::endl;

}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{		
	GeneratePositionIncident(anEvent);
	//particleGun->SetParticleMomentumDirection(GenerateIsotropicDirection());
   //particleGun->GeneratePrimaryVertex(anEvent);
}	

G4ThreeVector PrimaryGeneratorAction::GenerateIsotropicDirection()
{
	double cosTheta = 2* G4UniformRand() - 1;
	double sinTheta = pow(1.-cosTheta*cosTheta, 0.5);
	double phi = G4UniformRand()*2.*M_PI;
	return G4ThreeVector(sinTheta*cos(phi), sinTheta*sin(phi), cosTheta);
}
void PrimaryGeneratorAction::GeneratePositionIncident(G4Event *anEvent)
{
	G4ThreeVector p(0.0*cm,0.0*cm,0.0*cm);		//poczatek ganu
	G4ParticleDefinition* particle = particleTable->FindParticle("e+");
	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticlePosition(p);	//start działa pozytonowego
	particleGun->SetParticleMomentumDirection(GenerateIsotropicDirection());
	particleGun->SetParticleEnergy(587.0*keV);	//energia pozytonu ze strontu
	particleGun->GeneratePrimaryVertex(anEvent);	//wyslij czastke
}




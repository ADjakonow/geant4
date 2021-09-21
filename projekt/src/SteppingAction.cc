//
// $Id: SteppingAction.cc 15.10.2018 A. Fijalkowska $
//			+A.Djakonow
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class
//
//
#include "SteppingAction.hh"
#include "G4SystemOfUnits.hh"
#include "DetectorConstruction.hh"
#include "G4SteppingManager.hh"
#include "G4TouchableHandle.hh"
#include "G4Step.hh"

SteppingAction::SteppingAction():G4UserSteppingAction()
{

}

SteppingAction::~SteppingAction() {}


void SteppingAction::UserSteppingAction(const G4Step* theStep)
{

      /*  auto seconadries = theStep->GetSecondaryInCurrentStep();

        if(seconadries->size()>0){
            std::cout<< " size "<<seconadries->size();
            PrintStep(theStep);
        }
*/

        G4Track* theTrack = theStep->GetTrack();
	G4String volumeName = theTrack->GetVolume()->GetName();

        if(volumeName == "hel3")
	{
		auto secondaries = theStep->GetSecondaryInCurrentStep();
		nrOfSec+=secondaries->size();
                helEnergyDep += theStep->GetTotalEnergyDeposit();
	}


        // get the status of the pre step point
        G4StepStatus PreStepStatus = theStep->GetPreStepPoint()->GetStepStatus();
        // get the volume of the post step point
        G4StepPoint* PostStepPoint = theStep->GetPostStepPoint();

        // std::cout<<theTrack->GetPosition()<<std::endl; //wektor pozycji z tracku

            if ((PreStepStatus == fGeomBoundary) && (volumeName == "hel3")){
                PostStepPointX = PostStepPoint->GetPosition().x();
                PostStepPointY = PostStepPoint->GetPosition().y();
                PostStepPointZ = PostStepPoint->GetPosition().z();
           }
}

void SteppingAction::PrintStep(const G4Step* theStep)
{
	G4Track* theTrack = theStep->GetTrack();
	G4String particleName = theTrack->GetDefinition()->GetParticleName();
	G4String processName = theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
	G4double energy = theTrack->GetKineticEnergy();
	G4String volumeName = theTrack->GetVolume()->GetName();
        //G4double deltaEn = theStep->GetDeltaEnergy();
	int trackNr = theTrack->GetTrackID();

	std::cout<<" trackNr: "<<trackNr
		 <<" particle: "<<particleName
		 <<" process: "<<processName
                 <<" part energy: "<<energy/eV
                // <<" delta en: "<<deltaEn
		 <<" volume name: "<<volumeName<<std::endl;


}
int SteppingAction::nrOfSec = 0;
double SteppingAction::helEnergyDep = 0;
double SteppingAction::PostStepPointX = 0;
double SteppingAction::PostStepPointY = 0;
double SteppingAction::PostStepPointZ = 0;


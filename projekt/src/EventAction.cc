
// $Id: EventAction.cc 15.10.2018 A. Fijalkowska $
//		+ A. Djakonow
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "G4VPrimaryGenerator.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "G4SystemOfUnits.hh"



EventAction::EventAction()
{
	output.open("Secondaries.txt");
}
 
EventAction::~EventAction()
{
	output.close();
}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{

}
 

void EventAction::EndOfEventAction(const G4Event* anEvent)
{
	
    G4double energy = SteppingAction::helEnergyDep;

    if(energy!=0){
        std::cout<<anEvent->GetEventID()<<" "<<energy/keV<<std::endl; //depozyt energii
        //gdzie zaszla reakcja:
        std::cout<<" x= " << SteppingAction::PostStepPointX/cm
                 <<" y= " << SteppingAction::PostStepPointY/cm
                 <<" z= " << SteppingAction::PostStepPointZ/cm
                 <<std::endl;
        output<<anEvent->GetEventID()<<" "
              <<energy/keV<<" "
              <<SteppingAction::PostStepPointX/cm<<" "
              <<SteppingAction::PostStepPointY/cm<<" "
              <<SteppingAction::PostStepPointZ/cm<<
                std::endl;

    }
        SteppingAction::nrOfSec = 0;
        SteppingAction::helEnergyDep = 0;
        SteppingAction::PostStepPointX = 0;
        SteppingAction::PostStepPointY = 0;
        SteppingAction::PostStepPointZ = 0;

}




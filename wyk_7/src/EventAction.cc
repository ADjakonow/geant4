
// $Id: EventAction.cc 15.10.2018 A. Fijalkowska $
//		+ A. Djakonow
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
#include "EventAction.hh"
#include "SteppingAction.hh"

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
	if(SteppingAction::spineEnergyDep!=0)
	output<<SteppingAction::nrOfSec<<" "<< SteppingAction::spineEnergyDep <<std::endl;	
	else
	output<<SteppingAction::nrOfSec<<" "<< SteppingAction::spineEnergyDep<<" "<<"--> krok nie miał miejsca w kręgosłupie"<<std::endl;
	//std::cout<<SteppingAction::nrOfSec<<" "<< SteppingAction::spineEnergyDep <<std::endl;
	SteppingAction::nrOfSec = 0;
	SteppingAction::spineEnergyDep = 0;
}




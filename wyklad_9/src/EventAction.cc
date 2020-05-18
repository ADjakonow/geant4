
// $Id: EventAction.cc 15.10.2018 A. Fijalkowska $
//		+ A. Djakonow
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
//
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "NaIHit.hh"


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
        /*
         * zadanie do wykladu 7
        if(SteppingAction::spineEnergyDep!=0)
		output<<SteppingAction::nrOfSec<<" "<<SteppingAction::spineEnergyDep <<std::endl;	
	else
	output<<SteppingAction::nrOfSec<<" "<<SteppingAction::spineEnergyDep<<" "<<"--> krok nie miał miejsca w kręgosłupie"<<std::endl;
	//std::cout<<SteppingAction::nrOfSec<<" "<< SteppingAction::spineEnergyDep <<std::endl;
	SteppingAction::nrOfSec = 0;
	SteppingAction::spineEnergyDep = 0;
        */
        //zad. do wykladu 8, porownanie liczby czastek wtornych z kroku i licznika, tu z kroku:
        output<<SteppingAction::nrOfSec<<std::endl;
        //std::cout<<"secodnaries"<<SteppingAction::nrOfSec<<std::endl;
        SteppingAction::nrOfSec = 0;

	G4HCofThisEvent *hitsCollOfThisEvent = anEvent->GetHCofThisEvent();
	if(!hitsCollOfThisEvent)
		return;
	
        G4SDManager* SDmanager = G4SDManager::GetSDMpointer();

        G4int naIcollId = SDmanager->GetCollectionID("naiSD/eDep");
	//std::cout<<naIcollId<<std::endl;

        //G4THitsMap<G4double>* NaIHitsCollection = static_cast<G4THitsMap<G4double>*>(hitsCollOfThisEvent->GetHC(naIcollId));
        NaIHitsCollection* naiHC = (NaIHitsCollection*)(hitsCollOfThisEvent->GetHC(naIcollId));

        G4int nrOfDetectors = naiHC->entries();

        for(G4int i=0; i!=nrOfDetectors; i++){
            G4int moduleIndex = (*naiHC)[i]->GetCopyNr();
            G4double energyDep = (*naiHC)[i]->GetEdep();
            G4double trackLength = (*naiHC)[i]->GetTrackLength();
            G4double timeNonZeros = (*naiHC)[i]->GetTime();
            std::cout<<moduleIndex<<" "<< energyDep<<" "<<trackLength<<" "<<timeNonZeros<<std::endl;
        }



        /*
	std::map<G4int,G4double*>* NaIcolMap = NaIHitsCollection->GetMap();
	std::map<G4int,G4double*>::iterator itr;
	for(itr = NaIcolMap->begin(); itr!=NaIcolMap->end(); itr++)
	{	
		std::cout << (itr->first) <<" "<<*(itr->second) <<std::endl;
        }
        G4int fantomCollID = SDmanager->GetCollectionID("hfSensitiveDet/nPositron");
       // std::cout<<fantomCollID<<std::endl;

        G4THitsMap<G4double>* fanHitsCollection = static_cast<G4THitsMap<G4double>*>(hitsCollOfThisEvent->GetHC(fantomCollID));
        //std::cout<<"Czastki wtorne wyliczone z licznika: "<<std::endl;
        std::map<G4int,G4double*>* fanColMap = fanHitsCollection->GetMap();
        std::map<G4int,G4double*>::iterator i;
        for(i = fanColMap->begin(); i!=fanColMap->end(); i++)
        {

            std::cout << (i->first) <<" "<<*(i->second) <<std::endl;
        }

*/

}




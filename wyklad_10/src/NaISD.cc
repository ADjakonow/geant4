//A.Djakonow 11/05/20
//NaISD.cc ->Sensitive Detector
/// \file NaISD.cc
/// \brief Implementation of the NaISD class

#include "NaISD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"


NaISD::NaISD(
                            const G4String& name, 
                            const G4String& hitsCollectionName,
                            G4int depthVal)
 : G4VSensitiveDetector(name)
{

  collectionName.insert(hitsCollectionName);
  hitCollection = 0L;
  depth = depthVal;
}

NaISD::~NaISD()
{ 
}


void NaISD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
  hitCollection
    = new NaIHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce
  auto hcID 
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, hitCollection );


}


G4bool NaISD::ProcessHits(G4Step* step,
                                     G4TouchableHistory*)
{  
    G4double edep = GetEnergyDeposit(step);
    G4double stepLength = GetTrackLength(step);
    G4int copyNr = GetCopyNr(step);
    G4double time = GetTime(step);
    G4ThreeVector pos = GetPosition(step);
    std::cout<<"NaISD::pos = "<<pos<<std::endl;

  if ( edep==0. && stepLength == 0. ) return false;      

    G4int hitsNr = hitCollection->entries();
    G4bool moduleAlreadyHit = false;
    for(G4int i =0; i<hitsNr; i++){
        G4int moduleCopyNr = (*hitCollection)[i]->GetCopyNr();
        if(copyNr == moduleCopyNr){ 
            if(edep!=0)
            (*hitCollection)[i]->Add(edep, stepLength, time, pos);

             //time = GetTime(step);
           // (*hitCollection)[i]->GetTime();
            moduleAlreadyHit = true;
            break;
        }
    }

    if(!moduleAlreadyHit){
        NaIHit* aHit = new NaIHit(copyNr);
        if(edep!=0)
        aHit->Add(edep, stepLength, time, pos);
        hitCollection->insert(aHit);
    }
    return true;
}

G4double NaISD::GetEnergyDeposit(G4Step* step)
{
    return step->GetTotalEnergyDeposit();

}
G4ThreeVector NaISD::GetPosition(G4Step* step)
{
    G4StepPoint* preStepPoint = step->GetPreStepPoint();
    G4TouchableHandle theTouchable = preStepPoint->GetTouchableHandle();
    G4int copyNo = theTouchable->GetCopyNumber();
    G4int motherCopyNo = theTouchable->GetCopyNumber(1);

    G4ThreeVector worldPosition = preStepPoint->GetPosition();
    G4ThreeVector localPosition = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPosition);
    return localPosition;

}


G4double NaISD::GetTrackLength(G4Step* step)
{
    G4double stepLength = 0.;
   // if (step->GetTrack()->GetDefinition()->GetPDGCharge() !=0.)//dla czastek naladowanych
    //{
        stepLength = step->GetStepLength();

    //}

    return stepLength;
}
G4int NaISD::GetCopyNr(G4Step* step)
{
    G4int volumeNr =
            step->GetPostStepPoint()->GetTouchable()->GetReplicaNumber(depth);
    return volumeNr;
}

G4double NaISD::GetTime(G4Step* step)
{
    G4double time = step->GetPostStepPoint()->GetGlobalTime();
    return time;
}

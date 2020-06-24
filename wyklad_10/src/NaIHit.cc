//A.Djakonow 11/05/20
//NaIHit.cc


// \file NaIHit.cc
/// \brief Implementation of the B4cCalorHit class

#include "NaIHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4Step.hh"


#include <iomanip>

G4ThreadLocal G4Allocator<NaIHit>* NaIHitAllocator = 0;


NaIHit::NaIHit(G4int copyNrVal): G4VHit(), fEdep(0.),fTrackLength(0.), ftime(0.), fpos(0.)
{
    copyNr = copyNrVal;

}

NaIHit::~NaIHit()
{

}

NaIHit::NaIHit(const NaIHit& right)
  : G4VHit()
{
  fEdep        = right.fEdep;
  fTrackLength = right.fTrackLength;
  copyNr = right.copyNr;
  ftime = right.ftime;
  fpos = right.fpos;
}

const NaIHit& NaIHit::operator=(const NaIHit& right)
{
  fEdep        = right.fEdep;
  fTrackLength = right.fTrackLength;
  copyNr = right.copyNr;
  ftime = right.ftime;
  fpos = right.fpos;

  return *this;
}

G4bool NaIHit::operator==(const NaIHit& right) const
{
  return ( this == &right ) ? true : false;
}

void NaIHit::Add(G4double energyDep, G4double trackLen, G4double time, G4ThreeVector pos) {
  fEdep += energyDep;
  fTrackLength += trackLen;
  G4bool ft;
  ft = ZerosTime(time);
  if (ft==true)
      ftime = time;
  else ftime = ftime;

  fpos = pos;
 }

G4double NaIHit::GetEdep() const {
  return fEdep;
}

G4double NaIHit::GetTrackLength() const {
  return fTrackLength;
}

G4int NaIHit::GetCopyNr() {
    return copyNr;
}

G4double NaIHit::GetTime(){
    return ftime;

}

G4ThreeVector NaIHit::GetPosition(){
    return fpos;

}


G4bool NaIHit::ZerosTime(G4double time){
    if (time==0)
        return true;
}

void NaIHit::Print()
{
  /*G4cout
     << "Edep: " 
     << std::setw(7) << G4BestUnit(fEdep,"Energy")
     << " track length: " 
     << std::setw(7) << G4BestUnit( fTrackLength,"Length")
     << std::setw(7) << G4BestUnit( ftime, "time")
     << G4endl;*/
}


//A.Djakonow 11/05/20
//NaIHit.h

/// \file NaIHit.hh
/// \brief Definition of the NaIHit class

#ifndef NaIHit_h
#define NaIHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Threading.hh"

/// Klasa NaIHit

class NaIHit : public G4VHit
{
  public:
    NaIHit(G4int copyNrVal);
    NaIHit(const NaIHit&);
    virtual ~NaIHit();

    // operators
    const NaIHit& operator=(const NaIHit&);
    G4bool operator==(const NaIHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class
    virtual void Draw() {}
    virtual void Print();

    // methods to handle data
    void Add(G4double energyDep, G4double trackLen, G4double time, G4ThreeVector pos);

    // get methods
    G4double GetEdep() const;
    G4double GetTrackLength() const;
    G4int GetCopyNr();  //dla kazdego detekora z jodku sod
    G4double GetTime();
    G4bool ZerosTime(G4double time);
    G4ThreeVector GetPosition();


      
  private:
    G4double fEdep;        ///< Energy deposit in the sensitive volume
    G4double fTrackLength; ///< Track length in the  sensitive volume
    G4int copyNr;
    G4double ftime;
    G4ThreeVector fpos;
};

using NaIHitsCollection = G4THitsCollection<NaIHit>;
extern G4ThreadLocal G4Allocator<NaIHit>* NaIHitAllocator;

inline void* NaIHit::operator new(size_t)
{
  if (!NaIHitAllocator) {
    NaIHitAllocator = new G4Allocator<NaIHit>;
  }
  void *hit;
  hit = (void *) NaIHitAllocator->MallocSingle();
  return hit;
}

inline void NaIHit::operator delete(void *hit)
{
  if (!NaIHitAllocator) {
    NaIHitAllocator = new G4Allocator<NaIHit>;
  }
  NaIHitAllocator->FreeSingle((NaIHit*) hit);
}


#endif

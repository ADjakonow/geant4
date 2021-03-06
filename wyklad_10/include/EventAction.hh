// $Id: EventAction.hh 15.10.2018 A. Fijalkowska $
//		+A.Djakonow
/// \file EventAction.hh
/// \brief Definition of the EventAction class
//

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "OutputRoot.hh"
#include <fstream>

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
    virtual ~EventAction();
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
    
  private:
        //std::ofstream output;
       // OutputRoot* outputFile;

};

#endif

//
// $Id: SteppingAction.hh 15.10.2018 A. Fijalkowska $
//		+A.Djakonow
/// \file SteppingAction.hh
/// \brief Definition of the SteppingAction class
//
#ifndef SteppingAction_H
#define SteppingACtion_H 1

#include "G4UserSteppingAction.hh"
#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"


class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction();
    virtual ~SteppingAction();
    virtual void UserSteppingAction(const G4Step*); 
    static int nrOfSec;
    static double helEnergyDep;
    static double PostStepPointX;
    static double PostStepPointY;
    static double PostStepPointZ;
  private:
    void PrintStep(const G4Step* theStep);

};

#endif

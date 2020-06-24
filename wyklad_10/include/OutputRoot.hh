#ifndef OUTPUTROOT_H
#define OUTPUTROOT_H 1
#include "G4RootAnalysisManager.hh"
#include "G4ThreeVector.hh"

class OutputRoot
{
public:
    static OutputRoot* GetInstance()
    {
         if(instance)
             return instance;
         else
         {
            instance = new OutputRoot();
            return instance;
         }
    }
    void SaveOutput();
    void CreateFile(G4String filename);
    void AddNaIHit(double enDep, G4ThreeVector pos);

private:
    OutputRoot();
    static OutputRoot* instance;
    G4RootAnalysisManager* rootManager;
    void CreateNaITuple();
    int NaIDetectorTupleId;


};

#endif // OUTPUTROOT_HH

#include "OutputRoot.hh"
#include "G4ThreeVector.hh"

OutputRoot::OutputRoot()
 {
     rootManager = G4RootAnalysisManager::Instance();
   // rootManager->OpenFile("output.root");
    rootManager->SetFirstNtupleId(0);


 }
void OutputRoot::CreateFile(G4String filename)
{
    rootManager->OpenFile(filename);
    NaIDetectorTupleId=0;
    CreateNaITuple();
}
void OutputRoot::SaveOutput()
{
    rootManager->Write();
    rootManager->CloseFile();



}

void OutputRoot::CreateNaITuple()
{
    /*rootManager->CreateNtuple("NaIinfo", "Energy deposit and step lenght detector");
    rootManager->CreateNtupleIColumn("eventID");
    rootManager->CreateNtupleIColumn("detectorID");
    rootManager->CreateNtupleDColumn("energyDep");
    rootManager->CreateNtupleDColumn("stepLength");*/


    rootManager->CreateNtuple("NaIinfo", "Energy deposit and position");
    rootManager->CreateNtupleIColumn("energyDep");
    rootManager->CreateNtupleIColumn("xPos");
    rootManager->CreateNtupleIColumn("yPos");
    //rootManager->CreateNtupleIColumn("zPos");

    rootManager->FinishNtuple();


}
/*void OutputRoot::AddNaIHit(int eventId, int detectorId, double enDep, double stepLength)
{
    int colId = 0;
    rootManager->FillNtupleIColumn(NaIDetectorTupleId, colId, eventId);
    rootManager->FillNtupleIColumn(NaIDetectorTupleId, ++colId, detectorId);
    rootManager->FillNtupleDColumn(NaIDetectorTupleId, ++colId, enDep);
    rootManager->FillNtupleDColumn(NaIDetectorTupleId, ++colId, stepLength);
    rootManager->AddNtupleRow(NaIDetectorTupleId);
}
*/
void OutputRoot::AddNaIHit(double enDep, G4ThreeVector pos)
{
    int colId = 0;
    double x = 0;
    double y = 0;
   // double z = 0;
    x = pos.getX();
    y = pos.getY();
    //z = pos->getZ();

    rootManager->FillNtupleIColumn(NaIDetectorTupleId, colId, enDep);
    rootManager->FillNtupleIColumn(NaIDetectorTupleId, ++colId, x);
    rootManager->FillNtupleIColumn(NaIDetectorTupleId, ++colId, y);
   // rootManager->FillNtupleIColumn(NaIDetectorTupleId, ++colId, z);


    rootManager->AddNtupleRow(NaIDetectorTupleId);

}
OutputRoot* OutputRoot::instance=0;

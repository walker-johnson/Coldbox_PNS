//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "SteppingAction.hh"
#include "Run.hh"
#include "HistoManager.hh"
#include "G4OpticalPhoton.hh"
#include "G4Navigator.hh"

#include "G4RunManager.hh"
#include "EventAction.hh"
                           
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* evt, TrackingAction* TrAct)
: G4UserSteppingAction(),fEventAction(evt), fTrackingAction(TrAct)
{ 
  //obtain the detector (needed for volumes)
  fDetector = static_cast<const DetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  
  nav = new G4Navigator();
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  const G4Event* evt = G4RunManager::GetRunManager()->GetCurrentEvent();
  G4Track* track = step->GetTrack();
  G4int e = evt->GetEventID();

  nav->SetWorldVolume(fDetector->fWorldPhysVol);

  static G4ParticleDefinition* opticalphoton = G4OpticalPhoton::OpticalPhotonDefinition();

  
  G4ThreeVector vtx = track->GetVertexPosition();
  G4VPhysicalVolume * vtx_vol = nav->LocateGlobalPointAndSetup(vtx);
  
  G4int this_vol_num = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();
  std::string mat_name = vtx_vol->GetLogicalVolume()->GetMaterial()->GetName();
  G4bool first_step = step->IsFirstStepInVolume();

  if(track->GetDynamicParticle()->GetParticleDefinition() == opticalphoton){
    std::cout<< "op" << std::endl;

    if(step->GetPostStepPoint()->GetStepStatus() == fGeomBoundary){

      G4LogicalVolume* postL = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

      if(postL->GetName() == "VolOpDetSensitive_Tile-0"){
	G4AnalysisManager::Instance()->FillNtupleIColumn(1, 0, e); //ID, column, tag
	G4AnalysisManager::Instance()->FillNtupleIColumn(1, 1, 0); //ID, column, tag
	G4AnalysisManager::Instance()->AddNtupleRow(0); 
      } else if(postL->GetName() == "VolOpDetSensitive_Tile-1"){
	G4AnalysisManager::Instance()->FillNtupleIColumn(1, 0, e); //ID, column, tag
	G4AnalysisManager::Instance()->FillNtupleIColumn(1, 1, 1); //ID, column, tag
	G4AnalysisManager::Instance()->AddNtupleRow(0); 
      } else if(postL->GetName() == "VolOpDetSensitive_Tile-2"){
	G4AnalysisManager::Instance()->FillNtupleIColumn(1, 0, e); //ID, column, tag
	G4AnalysisManager::Instance()->FillNtupleIColumn(1, 1, 2); //ID, column, tag
	G4AnalysisManager::Instance()->AddNtupleRow(0); 
      } else if(postL->GetName() == "VolOpDetSensitive_Tile-3"){
	G4AnalysisManager::Instance()->FillNtupleIColumn(1, 0, e); //ID, column, tag
	G4AnalysisManager::Instance()->FillNtupleIColumn(1, 1, 3); //ID, column, tag
	G4AnalysisManager::Instance()->AddNtupleRow(0); 
      }

    }

    


  }else{
    
    //Get step point data
    G4int trk = track->GetTrackID();
    G4int stp = track->GetCurrentStepNumber();
    G4int vlm = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();
    G4int pdg = track->GetDefinition()->GetPDGEncoding();
    G4int pid = track->GetParentID();
    const G4VProcess *pr = step->GetPostStepPoint()->GetProcessDefinedStep();
    G4int pro = 0;
    if(pr){
      pro = pr->GetProcessType()*1000 + pr->GetProcessSubType();
    } else{
      pro = 900;
    }
    G4double k = track->GetKineticEnergy()/CLHEP::MeV;
    G4double vtx_k = track->GetVertexKineticEnergy()/CLHEP::MeV;
    G4double l = track->GetTrackLength()/CLHEP::cm;
    G4double t = track->GetGlobalTime()/CLHEP::ns + fT0/CLHEP::ns;
    G4double x = track->GetPosition().x()/CLHEP::cm;
    G4double y = track->GetPosition().y()/CLHEP::cm;
    G4double z = track->GetPosition().z()/CLHEP::cm;
    G4double px = track->GetMomentumDirection().x();
    G4double py = track->GetMomentumDirection().y();
    G4double pz = track->GetMomentumDirection().z();
    G4bool first_bool = step->IsFirstStepInVolume();
    G4int first = 0;
    if(first_bool){
      first = 1;
    }

    G4int vtx_vlm = 99;
    G4int is_lar = 0;

    if(vlm == 6){
      vtx_vlm = nav->LocateGlobalPointAndSetup(vtx)->GetCopyNo();
      std::string lar = "LAr";
      if(mat_name == lar){
	is_lar == 1;
      }//else if(first_bool){
	//std::cout << mat_name << std::endl;
	//std::string process  = track->GetCreatorProcess()->GetProcessName();
	//std::cout << "--------------------------------" << std::endl;
      //}
    }

    G4AnalysisManager::Instance()->FillH1(0,1);

  
    G4AnalysisManager::Instance()->FillNtupleIColumn(0, 0, trk); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleIColumn(0, 1, stp); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleIColumn(0, 2, vlm); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleIColumn(0, 3, pro); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleIColumn(0, 4, pdg); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleIColumn(0, 5, pid); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleDColumn(0, 6, l); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleDColumn(0, 7, x); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleDColumn(0, 8, y); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleDColumn(0, 9, z); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleDColumn(0, 10, t); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleDColumn(0, 11, k); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleIColumn(0, 12, e); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleIColumn(0, 13, first); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleIColumn(0, 14, vtx_vlm); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleDColumn(0, 15, vtx_k); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleIColumn(0, 16, is_lar); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleDColumn(0, 17, px); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleDColumn(0, 18, py); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleDColumn(0, 19, pz); //ID, column, tag
    G4AnalysisManager::Instance()->FillNtupleDColumn(0, 20, fT0/CLHEP::ns); //ID, column, tag
    G4AnalysisManager::Instance()->AddNtupleRow(0); 
  
  }
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



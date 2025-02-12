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
//g
/// \file persistency/gdml/G02/src/G02DetectorConstruction.cc
/// \brief Implementation of the G02DetectorConstruction class
//
//
//
// Class G02DetectorConstruction implementation
//
// ----------------------------------------------------------------------------

#include "DetectorConstruction.hh"

// Geant4 includes
//
#include "globals.hh"
#include "G4GeometryManager.hh"
#include "G4VisAttributes.hh"

// Geometry includes
//
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVParameterised.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"

// Reflected solids
//
#include "G4ReflectedSolid.hh"
#include "G4DisplacedSolid.hh"
#include "G4ReflectionFactory.hh"
#include "G4RotationMatrix.hh"
#include "G4AffineTransform.hh"
#include "G4Transform3D.hh"

// Assembly volumes
//
#include "G4AssemblyVolume.hh"

// GDML parser include
//
#include "G4GDMLParser.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// Constructor
//
DetectorConstruction::DetectorConstruction()
  : G4VUserDetectorConstruction()
{
  fReadFile = "detector.gdml";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// Destructor
//
DetectorConstruction::~DetectorConstruction()
{
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// Constructs geometries and materials
//
G4VPhysicalVolume* DetectorConstruction::Construct()
{ 

  // **** LOOK HERE*** FOR READING GDML FILES
  //
    
  // ACTIVATING OVERLAP CHECK when read volumes are placed.
  // Can take long time in case of complex geometries
  //
  fParser.SetOverlapCheck(true);

  fParser.Read(fReadFile);

  // READING GDML FILES OPTION: 2nd Boolean argument "Validate".
  // Flag to "false" disables check with the Schema when reading GDML file.
  // See the GDML Documentation for more information.
  //
  // fParser.Read(fReadFile,false);
     
  // Prints the material information
  //
  G4cout << *(G4Material::GetMaterialTable() ) << G4endl;
         
  // Giving World Physical Volume from GDML Parser
  //
  fWorldPhysVol = fParser.GetWorldVolume();

  // Set Visualization attributes to world
  //
  G4VisAttributes* BoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  fWorldPhysVol->GetLogicalVolume()->SetVisAttributes(BoxVisAtt);  

  return fWorldPhysVol;
}

void DetectorConstruction::SetReadFile( const G4String& File )
{
  fReadFile=File;
}

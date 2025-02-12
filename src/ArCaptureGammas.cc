
///////////////////////////////////////////////////////////////////////////////
//                 Spectrum of radiative neutron capture by Gadolinium            
//                                    version 1.0.0                                
//                                    (Sep.09.2005)                               
                            
//                Author : karim.zbiri@subatech.in2p3.fr                  

//This file contains the gammas spectrum produced in radiative capture of 
//neutrons by gadolinium.
//This work is adapted from earlier work in geant3 for chooz 1.

//First version by Karim Zbiri, April, 2005
///////////////////////////////////////////////////////////////////////////////


#include "ArCaptureGammas.hh"
#include "Randomize.hh"
#include <vector>
#include "G4Gamma.hh"
using namespace std;

ArCaptureGammas::ArCaptureGammas () {}

ArCaptureGammas::~ArCaptureGammas () {}

G4ReactionProductVector *  ArCaptureGammas::GetGammas () 
{
  G4ReactionProductVector * theGammas = new G4ReactionProductVector;
  vector<double> nrj = Initialize();
  for(unsigned int i=0; i<nrj.size(); i++)
    {
      G4ReactionProduct * theOne = new G4ReactionProduct;
      theOne->SetDefinition( G4Gamma::Gamma() );
    
      G4double costheta = 2.*G4UniformRand()-1;
      G4double theta = acos(costheta);
      G4double phi = CLHEP::twopi*G4UniformRand();
      G4double sinth = sin(theta);
      
      theOne->SetTotalEnergy( nrj[i] );
      G4ThreeVector temp(nrj[i]*sinth*cos(phi), nrj[i]*sinth*sin(phi),nrj[i]*cos(theta) );
      theOne->SetMomentum( temp ) ;
      theGammas->push_back(theOne);  
    }
   return theGammas;
}

vector<double>  ArCaptureGammas::Initialize ()
{
  vector<double> Eg;
  //here the correct gamma cascade is chosen based on the Isotope
  //other argon isotopes can be added with their own function, and
  //selected in this if statement
  if (A == 40){
    Eg = CapAr40(); 
  }else if (A == 36){
    Eg = CapAr36();
  }
  return Eg;
}

vector<double> ArCaptureGammas::CapAr36() // added by W. Johnson
{
    vector<double> v_gammas;
   // List of levels    0        1         2       3       4        5    6      7         8     9        10     11       12     13
    double Levels[14] = {8791.2, 6826.2, 6583.7, 5090.5, 4637.6, 4578.7, 4448.6, 3981.1, 3938.5, 3518.0, 2490.9, 1611.9, 1410.6, 0.0};
    double level = 0.0;
    
    int nb_gammas = 0; // number of gammas for this decay
    int probability = 0.; // the probability we'll use in the loop
    int Etot = 0.;
    level = Levels[0];
    nb_gammas = 0;
    
      while (level != Levels[13]) {
	
	if (level == Levels[0]) {
	  probability = G4UniformRand()*(10.9+37.5+25.0+0.8+1.6+3.2+0.8+1.8+13.4+2.7+2.4);
	  if (probability <= 10.9){
	    level = Levels[13];
	    v_gammas.push_back(8.7904); nb_gammas++;
	    continue;
	  } else if (probability > 10.9 && probability <= 10.9+37.5) {
	    level = Levels[10];
	    v_gammas.push_back(6.2997); nb_gammas++;
	    continue;
	  } else if (probability > 10.9+37.5 && probability <= 10.9+37.5+25.0) {
	    level = Levels[9];
	    v_gammas.push_back(5.2726); nb_gammas++;
	    continue;
	  } else if (probability > 10.9+37.5+25.0 && probability <= 10.9+37.5+25.0+0.8) {
	    level = Levels[8];
	    v_gammas.push_back(4.8518); nb_gammas++;
	    continue;
	  } else if (probability > 10.9+37.5+25.0+0.8 && probability <= 10.9+37.5+25.0+0.8+1.6) {
	    level = Levels[7];
	    v_gammas.push_back(4.8103); nb_gammas++;
	    continue;
	  } else if (probability > 10.9+37.5+25.0+0.8+1.6 && probability <= 10.9+37.5+25.0+0.8+1.6+3.2) {
	    level = Levels[6];
	    v_gammas.push_back(4.3423); nb_gammas++;
	    continue;
	  } else if (probability > 10.9+37.5+25.0+0.8+1.6+3.2 && probability <= 10.9+37.5+25.0+0.8+1.6+3.2+0.8) {
	    level = Levels[5];
	    v_gammas.push_back(4.2116); nb_gammas++;
	    continue;
	  } else if (probability > 10.9+37.5+25.0+0.8+1.6+3.2+0.8 && probability <= 10.9+37.5+25.0+0.8+1.6+3.2+0.8+1.8) {
	    level = Levels[4];
	    v_gammas.push_back(4.1530); nb_gammas++;
	    continue;
	  } else if (probability > 10.9+37.5+25.0+0.8+1.6+3.2+0.8+1.8 && probability <= 10.9+37.5+25.0+0.8+1.6+3.2+0.8+1.8+13.4) {
	    level = Levels[3];
	    v_gammas.push_back(3.7002); nb_gammas++;
	    continue;
	  } else if (probability > 10.9+37.5+25.0+0.8+1.6+3.2+0.8+1.8+13.4 && probability <= 10.9+37.5+25.0+0.8+1.6+3.2+0.8+1.8+13.4+2.7) {
	    level = Levels[2];
	    v_gammas.push_back(2.2076); nb_gammas++;
	    continue;
	  } else if (probability > 10.9+37.5+25.0+0.8+1.6+3.2+0.8+1.8+13.4+2.7 && probability <= 10.9+37.5+25.0+0.8+1.6+3.2+0.8+1.8+13.4+2.7+2.4) {
	    level = Levels[1];
	    v_gammas.push_back(1.9667); nb_gammas++;
	    continue;
	  }	
	}
	
	if (level == Levels[1]) {
	  probability = G4UniformRand()*5.0; //it's ACTUALLY < 5.0
	  if (probability <= 5.0){
	    level = Levels[5];
	    v_gammas.push_back(2.2479); nb_gammas++;
	    continue;
	  }
	}
	
	if (level == Levels[2]) {
	  probability = G4UniformRand()*0.2;
	  if (probability <= 0.2){
	    level = Levels[6];
	    v_gammas.push_back(2.1353); nb_gammas++;
	    continue;
	  }
	}
	
	if (level == Levels[3]) {
	  probability = G4UniformRand()*(7.9+3.1);
	  if (probability <= 7.9){
	    level = Levels[12];
	    v_gammas.push_back(3.6793); nb_gammas++;
	    continue;
	  } else if (probability > 7.9 && probability <= 7.9+3.1) {
	    level = Levels[10];
	    v_gammas.push_back(2.5996); nb_gammas++;
	    continue;
	  }
	}
	
	if (level == Levels[4]) {
	  probability = G4UniformRand()*(1.0+0.2);
	  if (probability <= 1.0){
	    level = Levels[12];
	    v_gammas.push_back(3.2269); nb_gammas++;
	    continue;
	  } else if (probability > 1.0 && probability <= 1.0+0.2) {
	    level = Levels[10];
	    v_gammas.push_back(2.1452); nb_gammas++;
	    continue;
	  }
	}
	
	if (level == Levels[5]) {
	  probability = G4UniformRand()*(0.3);
	  if (probability <= 0.3) {
	    level = Levels[10];
	    v_gammas.push_back(2.0873); nb_gammas++;
	    continue;
	  }
	}
	
	if (level == Levels[6]) {
	  probability = G4UniformRand()*(2.0);
	  if (probability <= 2.0) {
	    level = Levels[10];
	    v_gammas.push_back(1.9573); nb_gammas++;
	    continue;
	  }
	}
	
	if (level == Levels[7]) {
	  probability = G4UniformRand()*(1.3);
	  if (probability <= 1.3) {
	    level = Levels[13];
	    v_gammas.push_back(3.9814); nb_gammas++;
	    continue;
	  }
	}
	
	if (level == Levels[8]) {
	  probability = G4UniformRand()*(1.0);
	  if (probability <= 1.0) {
	    level = Levels[13];
	    v_gammas.push_back(3.9380); nb_gammas++;
	    continue;
	  }
	}
	
	if (level == Levels[9]) {
	  probability = G4UniformRand()*(23.7+2.7);
	  if (probability <= 23.7){
	    level = Levels[12];
	    v_gammas.push_back(2.1075); nb_gammas++;
	    continue;
	  } else if (probability > 23.7 && probability <= 23.7+2.7) {
	    level = Levels[10];
	    v_gammas.push_back(1.0267); nb_gammas++;
	    continue;
	  }
	}
	
	if (level == Levels[10]) {
	  probability = G4UniformRand()*(57.0+0.5);
	  if (probability <= 57.0){
	    level = Levels[13];
	    v_gammas.push_back(2.4906); nb_gammas++;
	    continue;
	  } else if (probability > 57.0 && probability <= 57.0+0.5) {
	    level = Levels[11];
	    v_gammas.push_back(.8785); nb_gammas++;
	    continue;
	  }
	}
	
	if (level == Levels[11]) {
	  probability = G4UniformRand()*(3.4);
	  if (probability <= 3.4) {
	    level = Levels[13];
	    v_gammas.push_back(1.6117); nb_gammas++;
	    continue;
	  }
	}
	
	if (level == Levels[12]) {
	  probability = G4UniformRand()*(33.0);
	  if (probability <= 33.0) {
	    level = Levels[13];
	    v_gammas.push_back(1.4103); nb_gammas++;
	    continue;
	  }
	}	
      }
      return v_gammas;
}

vector<double>  ArCaptureGammas::CapAr40()
{
  //  gammas from Ar40
  //                   either 2 gammas
  //                   either a continuum
  //                   total energy = 8.46 MeV

  vector<double> Egammas; 
  
  // List of levels    0        1         2       3       4        5    6      7         8     9        10     11     12
  double Levels[13] = {6.0989, 4.2700, 3.9682, 3.3268, 3.0096, 2.9487, 2.7334, 2.3981, 1.3539, 1.0347, 0.5161, 0.1673, 0.0};
  double level = 0.0;
  
  int nb_gammas = 0; // number of gammas for this decay
  double probability = 0.; // the probability we'll use in the loop
  double Etot = 0.;
  
  double probMyGamma = 51.2;
  
  int nb1 = 0, nb2 = 0, nb3 = 0, nb4 = 0, nb5 = 0;
  // 1 is 4.7+1.18+0.167
  // 2 is 5.582+0.516
  // 3 is 4.7+0.8+0.5
  // 4 is 3.7+1+1.18+0.167
  // 5 is 2.7718 1.9726 0.8377 0.3487 0.1673
  
  nb_gammas = 0;
  level = Levels[0];   
  
  // generate gammas
  while (level != Levels[12]) {
	
	  if (level == Levels[0]) {
	    probability = G4UniformRand()*(10.79+0.242+probMyGamma+9.11+3.91+3.72+1.02+8.00+4.09+0.93);
	    if (probability <= 10.79){
	      level = Levels[10];
	      Egammas.push_back(5.5820); nb_gammas++;
	      continue;
	    } else if (probability > 10.79 && probability <= 10.79+0.242) {
	      level = Levels[9];
	      Egammas.push_back(5.0637); nb_gammas++;
	      continue;
	    } else if (probability > 10.79+0.242 && probability <= 10.79+0.242+probMyGamma) {
	      level = Levels[8];
	      Egammas.push_back(4.7450); nb_gammas++;
	      continue;
	    } else if (probability > 10.79+0.242+probMyGamma && probability <= 10.79+0.242+probMyGamma+9.11) {
	      level = Levels[7];
	      Egammas.push_back(3.7004); nb_gammas++;
	      continue;
	    } else if (probability > 10.79+0.242+probMyGamma+9.11 && probability <= 10.79+0.242+probMyGamma+9.11+3.91) {
	      level = Levels[6];
	      Egammas.push_back(3.3655); nb_gammas++;
	      continue;
	    } else if (probability > 10.79+0.242+probMyGamma+9.11+3.91 && probability <= 10.79+0.242+probMyGamma+9.11+3.91+3.72) {
	      level = Levels[5];
	      Egammas.push_back(3.1502); nb_gammas++;
	      continue;
	    } else if (probability > 10.79+0.242+probMyGamma+9.11+3.91+3.72 && probability <= 10.79+0.242+probMyGamma+9.11+3.91+3.72+1.02) {
	      level = Levels[4];
	      Egammas.push_back(3.0894); nb_gammas++;
	      continue;
	    } else if (probability > 10.79+0.242+probMyGamma+9.11+3.91+3.72+1.02 && probability <= 10.79+0.242+probMyGamma+9.11+3.91+3.72+1.02+8.00) {
	      level = Levels[3];
	      Egammas.push_back(2.7718); nb_gammas++;
	      continue;
	    } else if (probability > 10.79+0.242+probMyGamma+9.11+3.91+3.72+1.02+8.00 && probability <= 10.79+0.242+probMyGamma+9.11+3.91+3.72+1.02+8.00+4.09) {
	      level = Levels[2];
	      Egammas.push_back(2.1307); nb_gammas++;
	      continue;
	    } else if (probability > 10.79+0.242+probMyGamma+9.11+3.91+3.72+1.02+8.00+4.09 && probability <= 10.79+0.242+probMyGamma+9.11+3.91+3.72+1.02+8.00+4.09+0.93) {
	      level = Levels[1];
	      Egammas.push_back(1.8288); nb_gammas++;
	      continue;
	    } 	
	  }
	  
	  if (level == Levels[1]) {
	    probability = G4UniformRand()*0.93;
	    if (probability <= 0.93){
	      level = Levels[11];
	      Egammas.push_back(4.1025); nb_gammas++;
	      continue;
	    }
	  }
	  
	  if (level == Levels[2]) {
	    probability = G4UniformRand()*(1.86+2.7);
	    if (probability <= 1.86){
	      level = Levels[10];
	      Egammas.push_back(3.4518); nb_gammas++;
	      continue;
	    } else if (probability > 1.86 && probability <= 1.86+2.7) {
	      level = Levels[8];
	      Egammas.push_back(2.6143); nb_gammas++;
	      continue;
	    }
	  }
	  
	  if (level == Levels[3]) {
	    probability = G4UniformRand()*(5.49+0.186+0.502);
	    if (probability <= 5.49){
	      level = Levels[10];
	      Egammas.push_back(2.8105); nb_gammas++;
	      continue;
	    } else if (probability > 5.49 && probability <= 5.49+0.186) {
	      level = Levels[9];
	      Egammas.push_back(2.2916); nb_gammas++;
	      continue;
	    } else if (probability >  5.49+0.186 && probability <=  5.49+0.186+ 0.502) {
	      level = Levels[8];
	      Egammas.push_back(1.9726); nb_gammas++;
	      continue;
	    }
	  }
	  
	  if (level == Levels[4]) {
	    probability = G4UniformRand()*(0.818);
	    if (probability <= 0.818) {
	      level = Levels[11];
	      Egammas.push_back(2.8425); nb_gammas++;
	      continue;
	    }
	  }
	  
	  if (level == Levels[5]) {
	    probability = G4UniformRand()*(1.58+0.781);
	    if (probability <= 1.58){
	      level = Levels[11];
	      Egammas.push_back(2.7818); nb_gammas++;
	      continue;
	    } else if (probability > 1.58 && probability <= 1.58+0.781) {
	      level = Levels[10];
	      Egammas.push_back(2.4325); nb_gammas++;
	      continue;
	    }
	  }
	  
	  if (level == Levels[6]) {
	    probability = G4UniformRand()*(2.6);
	    if (probability <= 2.6) {
	      level = Levels[11];
	      Egammas.push_back(2.5661); nb_gammas++;
	      continue;
	    }
	  }
	  
	  if (level == Levels[7]) {
	    probability = G4UniformRand()*(0.27+1.3+5.58);
	    if (probability <= 0.27){
	      level = Levels[11];
	      Egammas.push_back(2.2295); nb_gammas++;
	      continue;
	    } else if (probability > 0.27 && probability <= 0.27+1.3) {
	      level = Levels[10];
	      Egammas.push_back(1.8815); nb_gammas++;
	      continue;
	    } else if (probability >  0.27+1.3 && probability <=  0.27+1.3+5.58) {
	      level = Levels[8];
	      Egammas.push_back(1.0443); nb_gammas++;
	      continue;
	    }
	  }
	  
	  if (level == Levels[8]) {
	    probability = G4UniformRand()*(2.14+48.5+8.93);
	    if (probability <= 2.14){
	      level = Levels[12];
	      Egammas.push_back(1.3540); nb_gammas++;
	      continue;
	    } else if (probability > 2.14 && probability <= 2.14+48.5) {
	      level = Levels[11];
	      Egammas.push_back(1.1868); nb_gammas++;
	      continue;
	    } else if (probability >  2.14+48.5 && probability <=  2.14+48.5+8.93) {
	      level = Levels[10];
	      Egammas.push_back(0.8377); nb_gammas++;
	      continue;
	    }
	  }
	  
	  if (level == Levels[9]) {
	    probability = G4UniformRand()*(1.02);
	    if (probability <= 1.02) {
	      level = Levels[11];
	      Egammas.push_back(0.8673); nb_gammas++;
	      continue;
	    }
	  }
	  
	  if (level == Levels[10]) {
	    probability = G4UniformRand()*(23.5+6.14);
	    if (probability <= 23.5){
	      level = Levels[12];
	      Egammas.push_back(0.5160); nb_gammas++;
	      continue;
	    } else if (probability > 23.5 && probability <= 23.5+6.14) {
	      level = Levels[11];
	      Egammas.push_back(0.3487); nb_gammas++;
	      continue;
	    }
	  }
	  
	  if (level == Levels[11]) {
	    probability = G4UniformRand()*(74.0);
	    if (probability <= 74.0) {
	      level = Levels[12];
	      Egammas.push_back(0.1673); nb_gammas++;
	      continue;
	    }
	  }
	
  }  
  return Egammas;
}


vector<double>  ArCaptureGammas::continuum()
{
  vector<double> energy;
  
  return energy;
}





#ifndef EVTYMSTOYNSPIPICLEO_HH
#define EVTYMSTOYNSPIPICLEO_HH

// #include "EvtGenBase/EvtDecayProb.hh"
#include "EvtGenBase/EvtDecayAmp.hh"

class EvtParticle;

// Description: This model is based on matrix element method used by
//              CLEO in Phys.Rev.D76:072001,2007 to model the dipion mass
//              and helicity angle distribution in the decays Y(mS) -> pi pi Y(nS),
//              where m,n are integers and m>n and m<4.
//              This model has two parameters, Re(B/A) and Im(B/A), which
//              are coefficients of the matrix element's terms determined by
//              the CLEO fits.
//
// Example:
//
// Decay  Upsilon(3S)
//  1.0000    Upsilon      pi+  pi-     YMSTOYNSPIPICLEO -2.523 1.189;
// Enddecay
// Decay  Upsilon(3S)
//  1.0000    Upsilon(2S)  pi+  pi-     YMSTOYNSPIPICLEO -0.395 0.001;
// Enddecay
// Decay  Upsilon(2S)
//  1.0000    Upsilon      pi+  pi-     YMSTOYNSPIPICLEO -0.753 0.000;
// Enddecay
//
//   --> the order of parameters is: Re(B/A) Im(B/A)

class EvtYmSToYnSpipiCLEO : public EvtDecayAmp {
    //EvtDecayProb  {

  public:
    std::string getName() override;
    EvtDecayBase* clone() override;

    void decay( EvtParticle* p ) override;
    void init() override;
    void initProbMax() override;
};

#endif

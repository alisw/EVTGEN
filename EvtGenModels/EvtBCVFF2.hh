#ifndef EVTBCVFF2_HH
#define EVTBCVFF2_HH

#include "EvtGenBase/EvtId.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtPatches.hh"
#include "EvtGenBase/EvtReport.hh"
#include "EvtGenBase/EvtSemiLeptonicFF.hh"

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>

class EvtId;

// Description: form factors for B->Vlnu

class EvtBCVFF2 : public EvtSemiLeptonicFF {
  public:
    EvtBCVFF2( int idV, int fit );
    void getvectorff( EvtId parent, EvtId daught, double t, double mass,
                      double* a1f, double* a2f, double* vf,
                      double* a0f ) override;

    void getscalarff( EvtId, EvtId, double, double, double*, double* ) override;

    void gettensorff( EvtId, EvtId, double, double, double*, double*, double*,
                      double* ) override;

    void getbaryonff( EvtId, EvtId, double, double, double*, double*, double*,
                      double* ) override;

    void getdiracff( EvtId, EvtId, double, double, double*, double*, double*,
                     double*, double*, double* ) override;

    void getraritaff( EvtId, EvtId, double, double, double*, double*, double*,
                      double*, double*, double*, double*, double* ) override;

  private:
    int idVector, whichfit;
};

#endif

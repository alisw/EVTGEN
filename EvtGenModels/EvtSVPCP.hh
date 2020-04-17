#ifndef EVTSVPCP_HH
#define EVTSVPCP_HH

#include "EvtGenBase/EvtDecayAmp.hh"

class EvtParticle;

// Description: Routine to decay scalar -> vectors+photon
//              including CP violation effects
//
//Class to handle decays of the form SCALAR ->VECTOR PHOTON
//where the helicity amplitudes must be specified.  The
//first and third arguements are the magnetudes of the H+
//and H- helicity amplitudes respectively.  The second and
//fourth arguements are the phases.
//Calls EvtSVPHel.

class EvtSVPCP : public EvtDecayAmp {
  public:
    std::string getName() override;
    EvtDecayBase* clone() override;

    void init() override;
    void initProbMax() override;
    void decay( EvtParticle* p ) override;
    static void SVPHel( EvtParticle* parent, EvtAmp& amp, EvtId n_v1,
                        EvtId n_v2, const EvtComplex& hp, const EvtComplex& hm );

    std::string getParamName( int i ) override;
    std::string getParamDefault( int i ) override;
};

#endif

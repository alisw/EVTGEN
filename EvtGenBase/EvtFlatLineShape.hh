#ifndef EVTFLATLINESHAPE_HH
#define EVTFLATLINESHAPE_HH

#include "EvtGenBase/EvtAbsLineShape.hh"

class EvtFlatLineShape : public EvtAbsLineShape {
  public:
    EvtFlatLineShape() = default;
    EvtFlatLineShape( double mass, double width, double maxRange,
                      EvtSpinType::spintype sp );
    //figure the m1 and l on the fly
    //			       double mDaug1, double mDaug2, int l);
    EvtFlatLineShape& operator=( const EvtFlatLineShape& x );
    EvtFlatLineShape( const EvtFlatLineShape& x );

    EvtAbsLineShape* clone() override;

    double getMassProb( double mass, double massPar, int nDaug,
                        double* massDau ) override;
    // othDaugId is the other daughter of the parent in the case of a two body decay (only!)
    // ie B->rho K rho->pipi, othDaugId = K
    double getRandMass( EvtId* parId, int nDaug, EvtId* dauId, EvtId* othDaugId,
                        double maxMass, double* dauMasses ) override;
};

#endif

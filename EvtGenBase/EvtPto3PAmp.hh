#ifndef EVT_PTO3P_AMP_HH
#define EVT_PTO3P_AMP_HH

#include "EvtGenBase/EvtCyclic3.hh"
#include "EvtGenBase/EvtSpinType.hh"

#include <vector>
using std::vector;
#include "EvtGenBase/EvtAmplitude.hh"
#include "EvtGenBase/EvtDalitzPoint.hh"
#include "EvtGenBase/EvtPropagator.hh"
#include "EvtGenBase/EvtTwoBodyVertex.hh"

class EvtComplex;
class EvtBlattWeisskopf;

class EvtPto3PAmp : public EvtAmplitude<EvtDalitzPoint> {
  public:
    // Numerator type
    enum NumType
    {
        NBW = 0,
        RBW_ZEMACH = 1,
        RBW_KUEHN = 2,
        RBW_CLEO = 3,
        FLATTE,
        GAUSS,
        DOUBLE_GAUSS,
        NONRES,
        NONRES_LIN,
        NONRES_EXP,
        NONRES_EXP_ADD,
        NONRES_CCS,
        NONRES_LAURA,
        LASS,
        LASS_ELASTIC,
        LASS_RESONANT,
        GS
    };

    EvtPto3PAmp( EvtDalitzPlot dp, EvtCyclic3::Pair pairAng,
                 EvtCyclic3::Pair pairRes, EvtSpinType::spintype spin,
                 const EvtPropagator& prop, NumType typeN );

    EvtPto3PAmp( const EvtPto3PAmp& other );

    ~EvtPto3PAmp();

    EvtAmplitude<EvtDalitzPoint>* clone() const override
    {
        return new EvtPto3PAmp( *this );
    }

    EvtComplex amplitude( const EvtDalitzPoint& p ) const override;
    EvtComplex numerator( const EvtDalitzPoint& p ) const;
    double angDep( const EvtDalitzPoint& p ) const;

    void set_fd( double R );
    void set_fb( double R );

    void setmin( double min ) { _min = min; }
    void setmax( double max ) { _max = max; }

    virtual EvtComplex evalPropagator( double m ) const
    {
        return _prop->evaluate( m );
    }

  private:
    // Pairing indices:

    EvtCyclic3::Pair _pairAng;    // angular
    EvtCyclic3::Pair _pairRes;    // resonance

    // Spin

    EvtSpinType::spintype _spin;

    // Numerator type

    NumType _typeN;

    // _Owned_ pointer to propagator factor

    EvtPropagator* _prop;
    double _g0;     // nominal width
    double _min;    //min and max values on which
    double _max;    //the resonance is defined

    // Vertices

    EvtTwoBodyVertex _vb;
    EvtTwoBodyVertex _vd;
};

#endif

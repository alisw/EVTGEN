#include "EvtGenBase/EvtFlatLineShape.hh"

#include "EvtGenBase/EvtBlattWeisskopf.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtPatches.hh"
#include "EvtGenBase/EvtPropBreitWigner.hh"
#include "EvtGenBase/EvtPropBreitWignerRel.hh"
#include "EvtGenBase/EvtRandom.hh"
#include "EvtGenBase/EvtSpinType.hh"
#include "EvtGenBase/EvtTwoBodyVertex.hh"

EvtFlatLineShape::EvtFlatLineShape( double mass, double width, double maxRange,
                                    EvtSpinType::spintype sp )
{
    _mass = mass;
    _width = width;
    _spin = sp;
    _maxRange = maxRange;

    double maxdelta = width;

    _massMax = mass + maxdelta;
    _massMin = mass - maxdelta;

    if ( _massMin < 0. )
        _massMin = 0.;
}

EvtFlatLineShape::EvtFlatLineShape( const EvtFlatLineShape& x ) :
    EvtAbsLineShape( x )
{
    _mass = x._mass;
    _width = x._width;
    _spin = x._spin;
    _massMax = x._massMax;
    _massMin = x._massMin;
    _maxRange = x._maxRange;
}

EvtFlatLineShape& EvtFlatLineShape::operator=( const EvtFlatLineShape& x )
{
    _mass = x._mass;
    _massMax = x._massMax;
    _massMin = x._massMin;
    _width = x._width;
    _maxRange = x._maxRange;
    _spin = x._spin;
    return *this;
}

EvtAbsLineShape* EvtFlatLineShape::clone()
{
    return new EvtFlatLineShape( *this );
}

double EvtFlatLineShape::getMassProb( double mass, double massPar, int nDaug,
                                      double* massDau )
{
    double dTotMass = 0.;

    int i;
    for ( i = 0; i < nDaug; i++ ) {
        dTotMass += massDau[i];
    }
    if ( ( mass < dTotMass ) )
        return 0.;

    if ( massPar > 0.0000000001 ) {
        if ( mass > massPar )
            return 0.;
    }

    return 1.;
}

double EvtFlatLineShape::getRandMass( EvtId*, int, EvtId*, EvtId*, double,
                                      double* )
{
    return EvtRandom::Flat( _massMin, _massMax );
}

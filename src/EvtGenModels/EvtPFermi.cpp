#include "EvtGenModels/EvtPFermi.hh"

#include "EvtGenBase/EvtPatches.hh"
#include "EvtGenBase/EvtReport.hh"

#include <math.h>
#include <stdlib.h>

//----------------
// Constructors --
//----------------

//for DFN model
EvtPFermi::EvtPFermi( const double& a, const double& mB, const double& mb )
{
    _a = a;
    _mb = mb;
    _mB = mB;
}

// for BLNP modell
EvtPFermi::EvtPFermi( const double& Lambda, const double& b )
{
    _Lambda = Lambda;
    _b = b;
}

//-----------
// Methods --
//-----------

double EvtPFermi::getFPFermi( const double& kplus )
{
    double FKplus;
    double x = kplus / ( _mB - _mb );

    if ( x >= 1 )
        return 0;
    if ( kplus <= -_mb )
        return 0;

    FKplus = pow( 1 - x, _a ) * exp( ( 1 + _a ) * x );

    return FKplus;
}

// get value for the leading order exponential SF
double EvtPFermi::getSFBLNP( const double& what )
{
    double SF;
    double massB = 5.2792;

    if ( what > massB )
        return 0;
    if ( what < 0 )
        return 0;

#if defined( __SUNPRO_CC )
    EvtGenReport( EVTGEN_ERROR, "EvtGen" )
        << "The tgamma function is not available on this platform\n";
    EvtGenReport( EVTGEN_ERROR, "EvtGen" )
        << "Presumably, you are getting the wrong answer, so I abort..";
    ::abort();
#else
    SF = pow( _b, _b ) / ( tgamma( _b ) * _Lambda ) *
         pow( what / _Lambda, _b - 1 ) * exp( -_b * what / _Lambda );
#endif

    return SF;
}

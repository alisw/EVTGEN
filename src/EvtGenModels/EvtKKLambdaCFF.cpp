#include "EvtGenModels/EvtKKLambdaCFF.hh"

#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtPatches.hh"
#include "EvtGenBase/EvtReport.hh"

#include <math.h>
#include <stdlib.h>
#include <string>

EvtKKLambdaCFF::EvtKKLambdaCFF( int numarg, double* arglist )
{
    _nargs = numarg;
    for ( int i = 0; i < numarg; i++ ) {
        _args[i] = arglist[i];
    }

    return;
}

void EvtKKLambdaCFF::getbaryonff( EvtId /*parent*/, EvtId /*daught*/, double t,
                                  double /*mass*/, double* f1v, double* f1a,
                                  double* f2v, double* f2a )
{
    *f1v = ( _args[0] ) / ( 1.0 - ( t / ( _args[1] * _args[1] ) ) );

    *f2v = 0.;
    *f2a = 0.;
    *f1a = -1.0 * ( *f1v );
}

void EvtKKLambdaCFF::getscalarff( EvtId, EvtId, double, double, double*, double* )
{
    EvtGenReport( EVTGEN_ERROR, "EvtGen" )
        << "Not implemented :getscalarff in EvtKKLambdaCFF.\n";
    ::abort();
}

void EvtKKLambdaCFF::getvectorff( EvtId, EvtId, double, double, double*,
                                  double*, double*, double* )
{
    EvtGenReport( EVTGEN_ERROR, "EvtGen" )
        << "Not implemented :getvectorff in EvtKKLambdaCFF.\n";
    ::abort();
}

void EvtKKLambdaCFF::gettensorff( EvtId, EvtId, double, double, double*,
                                  double*, double*, double* )
{
    EvtGenReport( EVTGEN_ERROR, "EvtGen" )
        << "Not implemented :gettensorff in EvtKKLambdaCFF.\n";
    ::abort();
}

void EvtKKLambdaCFF::getdiracff( EvtId, EvtId, double, double, double*, double*,
                                 double*, double*, double*, double* )
{
    EvtGenReport( EVTGEN_ERROR, "EvtGen" )
        << "Not implemented :getdiracff in EvtKKLambdaCFF.\n";
    ::abort();
}

void EvtKKLambdaCFF::getraritaff( EvtId, EvtId, double, double, double*,
                                  double*, double*, double*, double*, double*,
                                  double*, double* )
{
    EvtGenReport( EVTGEN_ERROR, "EvtGen" )
        << "Not implemented :getraritaff in EvtKKLambdaCFF.\n";
    ::abort();
}

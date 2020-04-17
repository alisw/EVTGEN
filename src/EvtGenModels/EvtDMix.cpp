#include "EvtGenModels/EvtDMix.hh"

#include "EvtGenBase/EvtGenKine.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtPatches.hh"
#include "EvtGenBase/EvtRandom.hh"
#include "EvtGenBase/EvtReport.hh"

#include <stdlib.h>
#include <string>

std::string EvtDMix::getName()
{
    return "DMIX";
}

EvtDecayBase* EvtDMix::clone()
{
    return new EvtDMix;
}

void EvtDMix::init()
{
    // check that there are 0 arguments
    checkNArg( 3 );
    _rd = getArg( 0 );
    _xpr = getArg( 1 );
    _ypr = getArg( 2 );
}

void EvtDMix::initProbMax()
{
    noProbMax();
}

void EvtDMix::decay( EvtParticle* p )
{
    //unneeded - lange - may13-02
    //if ( p->getNDaug() != 0 ) {
    //Will end up here because maxrate multiplies by 1.2
    //  EvtGenReport(EVTGEN_DEBUG,"EvtGen") << "In EvtDMix: has "
    //			   <<" daugthers should not be here!"<<endl;
    //  return;
    //}

    p->initializePhaseSpace( getNDaug(), getDaugs() );

    double ctau = EvtPDL::getctau( p->getId() );
    if ( ctau == 0. )
        return;

    double pdf, random, gt, weight;

    double maxPdf = _rd + sqrt( _rd ) * _ypr * 50. +
                    2500.0 * ( _xpr * _xpr + _ypr * _ypr ) / 4.0;
    bool keepGoing = true;
    while ( keepGoing ) {
        random = EvtRandom::Flat();
        gt = -log( random );
        weight = random;
        pdf = _rd + sqrt( _rd ) * _ypr * gt +
              gt * gt * ( _xpr * _xpr + _ypr * _ypr ) / 4.0;
        pdf *= exp( -1.0 * gt );
        pdf /= weight;
        if ( pdf > maxPdf )
            std::cout << pdf << " " << weight << " " << maxPdf << " " << gt
                      << std::endl;
        if ( pdf > maxPdf * EvtRandom::Flat() )
            keepGoing = false;
    }

    p->setLifetime( gt * ctau );

    return;
}

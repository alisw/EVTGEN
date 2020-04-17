#include "EvtGenBase/EvtDalitzCoord.hh"

#include "EvtGenBase/EvtPatches.hh"

#include <assert.h>
#include <iostream>
using EvtCyclic3::Pair;
using std::endl;
using std::ostream;

// For coordinates it's good to alway have a
// default ctor. Initialize to something invalid.

EvtDalitzCoord::EvtDalitzCoord() :
    _i1( EvtCyclic3::AB ), _i2( EvtCyclic3::BC ), _q1( -1. ), _q2( -1. )
{
}

EvtDalitzCoord::EvtDalitzCoord( const EvtDalitzCoord& other ) :
    _i1( other._i1 ), _i2( other._i2 ), _q1( other._q1 ), _q2( other._q2 )
{
}

EvtDalitzCoord::EvtDalitzCoord( Pair i1, double q1, Pair i2, double q2 ) :
    _i1( i1 ), _i2( i2 ), _q1( q1 ), _q2( q2 )
{
}

bool EvtDalitzCoord::operator==( const EvtDalitzCoord& other ) const
{
    return ( _i1 == other._i1 && _i2 == other._i2 && _q1 == other._q1 &&
             _q2 == other._q2 );
}

void EvtDalitzCoord::print( ostream& os ) const
{
    os << _i1 << " " << _q1 << endl;
    os << _i2 << " " << _q2 << endl;
}

ostream& operator<<( ostream& os, const EvtDalitzCoord& p )
{
    p.print( os );
    return os;
}


/***********************************************************************
* Copyright 1998-2020 CERN for the benefit of the EvtGen authors       *
*                                                                      *
* This file is part of EvtGen.                                         *
*                                                                      *
* EvtGen is free software: you can redistribute it and/or modify       *
* it under the terms of the GNU General Public License as published by *
* the Free Software Foundation, either version 3 of the License, or    *
* (at your option) any later version.                                  *
*                                                                      *
* EvtGen is distributed in the hope that it will be useful,            *
* but WITHOUT ANY WARRANTY; without even the implied warranty of       *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
* GNU General Public License for more details.                         *
*                                                                      *
* You should have received a copy of the GNU General Public License    *
* along with EvtGen.  If not, see <https://www.gnu.org/licenses/>.     *
***********************************************************************/

#include "EvtGenModels/EvtBcVHad.hh"

#include "EvtGenBase/EvtIdSet.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtReport.hh"
#include "EvtGenBase/EvtSpinType.hh"
#include "EvtGenBase/EvtTensor4C.hh"
#include "EvtGenBase/EvtVector4R.hh"

#include "EvtGenModels/EvtBCVFF2.hh"
#include "EvtGenModels/EvtWHad.hh"

#include <iostream>

std::string EvtBcVHad::getName()
{
    return "BC_VHAD";
}

EvtDecayBase* EvtBcVHad::clone()
{
    return new EvtBcVHad;
}

//======================================================

void EvtBcVHad::init()
{
    checkNArg( 1 );
    checkSpinParent( EvtSpinType::SCALAR );
    checkSpinDaughter( 0, EvtSpinType::VECTOR );
    for ( int i = 1; i <= ( getNDaug() - 1 ); i++ ) {
        checkSpinDaughter( i, EvtSpinType::SCALAR );
    }

    idVector = getDaug( 0 ).getId();
    whichfit = int( getArg( 0 ) + 0.1 );
    ffmodel = std::make_unique<EvtBCVFF2>( idVector, whichfit );

    wcurr = std::make_unique<EvtWHad>();

    // determine the code of final hadronic state
    EvtIdSet thePis( "pi+", "pi-", "pi0" );
    EvtIdSet theK( "K+", "K-", "K_S0" );
    if ( getNDaug() == 2 && thePis.contains( getDaug( 1 ) ) ) {
        out_code = 1;    // pi+
    } else if ( getNDaug() == 3 && thePis.contains( getDaug( 1 ) ) &&
                thePis.contains( getDaug( 2 ) ) ) {
        out_code = 2;    // pi+ pi0
    } else if ( getNDaug() == 4 && thePis.contains( getDaug( 1 ) ) &&
                thePis.contains( getDaug( 2 ) ) &&
                thePis.contains( getDaug( 3 ) ) ) {
        out_code = 3;    // pi+ pi+ pi-
    } else if ( getNDaug() == 5 && thePis.contains( getDaug( 1 ) ) &&
                thePis.contains( getDaug( 2 ) ) &&
                thePis.contains( getDaug( 3 ) ) &&
                thePis.contains( getDaug( 4 ) ) ) {
        out_code = 4;    //4pi
    } else if ( getNDaug() == 6 && thePis.contains( getDaug( 1 ) ) &&
                thePis.contains( getDaug( 2 ) ) &&
                thePis.contains( getDaug( 3 ) ) &&
                thePis.contains( getDaug( 4 ) ) &&
                thePis.contains( getDaug( 5 ) ) ) {
        out_code = 5;    //5pi
    } else if ( getNDaug() == 4 && theK.contains( getDaug( 1 ) ) &&
                theK.contains( getDaug( 2 ) ) &&
                thePis.contains( getDaug( 3 ) ) ) {
        out_code = 6;    //KKpi
    } else if ( getNDaug() == 4 && theK.contains( getDaug( 1 ) ) &&
                thePis.contains( getDaug( 2 ) ) &&
                thePis.contains( getDaug( 3 ) ) ) {
        out_code = 7;    // Kpi pi
    } else if ( getNDaug() == 3 && theK.contains( getDaug( 1 ) ) &&
                theK.contains( getDaug( 2 ) ) ) {
        out_code = 8;    // KK
    } else if ( getNDaug() == 6 && theK.contains( getDaug( 1 ) ) &&
                theK.contains( getDaug( 2 ) ) && thePis.contains( getDaug( 3 ) ) &&
                thePis.contains( getDaug( 4 ) ) &&
                thePis.contains( getDaug( 5 ) ) ) {
        out_code = 9;    // KK+3pi
    } else if ( getNDaug() == 8 && thePis.contains( getDaug( 1 ) ) &&
                thePis.contains( getDaug( 2 ) ) &&
                thePis.contains( getDaug( 3 ) ) &&
                thePis.contains( getDaug( 4 ) ) &&
                thePis.contains( getDaug( 5 ) ) &&
                thePis.contains( getDaug( 6 ) ) &&
                thePis.contains( getDaug( 7 ) ) ) {
        out_code = 10;    //7pi
    } else if ( getNDaug() == 6 && theK.contains( getDaug( 1 ) ) &&
                thePis.contains( getDaug( 2 ) ) &&
                thePis.contains( getDaug( 3 ) ) &&
                thePis.contains( getDaug( 4 ) ) &&
                thePis.contains( getDaug( 5 ) ) ) {
        out_code = 11;    // K+ pi+ pi+ pi- pi-
    } else {
        EvtGenReport( EVTGEN_ERROR, "EvtBcHad" )
            << "Init: unknown decay" << std::endl;
    };

    EvtGenReport( EVTGEN_INFO, "EvtBcHad" )
        << "out_code = " << out_code << ", whichfit = " << whichfit << std::endl;
}

//======================================================

void EvtBcVHad::initProbMax()
{
    if ( out_code == 3 ) {
        if ( idVector == EvtPDL::getId( "J/psi" ).getId() && whichfit == 1 &&
             getNDaug() == 4 )
            setProbMax( 42000. );
        else if ( idVector == EvtPDL::getId( "J/psi" ).getId() &&
                  whichfit == 2 && getNDaug() == 4 )
            setProbMax( 90000. );
        else if ( idVector == EvtPDL::getId( "psi(2S)" ).getId() &&
                  whichfit == 1 && getNDaug() == 4 )
            setProbMax( 1660. );
        else if ( idVector == EvtPDL::getId( "psi(2S)" ).getId() &&
                  whichfit == 2 && getNDaug() == 4 )
            setProbMax( 2600. );

    } else if ( out_code == 5 ) {
        if ( idVector == EvtPDL::getId( "J/psi" ).getId() && whichfit == 1 &&
             getNDaug() == 6 )
            setProbMax( 720000. );
        else if ( idVector == EvtPDL::getId( "J/psi" ).getId() &&
                  whichfit == 2 && getNDaug() == 6 )
            setProbMax( 519753. );
        else if ( idVector == EvtPDL::getId( "psi(2S)" ).getId() &&
                  whichfit == 1 && getNDaug() == 6 )
            setProbMax( 40000. );
        else if ( idVector == EvtPDL::getId( "psi(2S)" ).getId() &&
                  whichfit == 2 && getNDaug() == 6 )
            setProbMax( 30000. );
    } else if ( out_code == 6 ) {
        if ( idVector == EvtPDL::getId( "J/psi" ).getId() && whichfit == 1 )
            setProbMax( 50000. );
        else if ( idVector == EvtPDL::getId( "J/psi" ).getId() && whichfit == 2 )
            setProbMax( 22000.0 );
        else if ( idVector == EvtPDL::getId( "psi(2S)" ).getId() && whichfit == 1 )
            setProbMax( 2300.0 );
        else if ( idVector == EvtPDL::getId( "psi(2S)" ).getId() && whichfit == 2 )
            setProbMax( 1700.00 );
    } else if ( out_code == 7 ) {
        if ( idVector == EvtPDL::getId( "J/psi" ).getId() && whichfit == 1 )
            setProbMax( 2.2e+06 );
        else if ( idVector == EvtPDL::getId( "J/psi" ).getId() && whichfit == 2 )
            setProbMax( 930000 );
        else if ( idVector == EvtPDL::getId( "psi(2S)" ).getId() && whichfit == 1 )
            setProbMax( 92000.0 );
        else if ( idVector == EvtPDL::getId( "psi(2S)" ).getId() && whichfit == 2 )
            setProbMax( 93000.0 );
    } else if ( out_code == 8 ) {
        if ( idVector == EvtPDL::getId( "J/psi" ).getId() && whichfit == 1 )
            setProbMax( 2e2 );
        else if ( idVector == EvtPDL::getId( "J/psi" ).getId() && whichfit == 2 )
            setProbMax( 80 );
        else if ( idVector == EvtPDL::getId( "psi(2S)" ).getId() && whichfit == 1 )
            setProbMax( 10 );
        else if ( idVector == EvtPDL::getId( "psi(2S)" ).getId() && whichfit == 2 )
            setProbMax( 10 );
    } else if ( out_code == 9 ) {
        if ( idVector == EvtPDL::getId( "J/psi" ).getId() && whichfit == 1 )
            setProbMax( 3e4 );
        else if ( idVector == EvtPDL::getId( "J/psi" ).getId() && whichfit == 2 )
            setProbMax( 18540 );
        else if ( idVector == EvtPDL::getId( "psi(2S)" ).getId() && whichfit == 1 )
            setProbMax( 0.15 * 1e4 );
        else if ( idVector == EvtPDL::getId( "psi(2S)" ).getId() && whichfit == 2 )
            setProbMax( 2 * 500 );
    } else if ( out_code == 10 ) {
        if ( idVector == EvtPDL::getId( "J/psi" ).getId() && whichfit == 1 )
            setProbMax( 2e6 );
        else if ( idVector == EvtPDL::getId( "J/psi" ).getId() && whichfit == 2 )
            setProbMax( 5e6 );
        else if ( idVector == EvtPDL::getId( "psi(2S)" ).getId() && whichfit == 1 )
            setProbMax( 1.5e5 );
        else if ( idVector == EvtPDL::getId( "psi(2S)" ).getId() && whichfit == 2 )
            setProbMax( 1e5 );
    } else if ( out_code == 11 ) {
        if ( idVector == EvtPDL::getId( "J/psi" ).getId() && whichfit == 1 )
            setProbMax( 2.5e8 );
        else if ( idVector == EvtPDL::getId( "J/psi" ).getId() && whichfit == 2 )
            setProbMax( 1.4e7 );
        else if ( idVector == EvtPDL::getId( "psi(2S)" ).getId() && whichfit == 1 )
            setProbMax( 2e6 );
        else if ( idVector == EvtPDL::getId( "psi(2S)" ).getId() && whichfit == 2 )
            setProbMax( 8e4 );
    } else {
        EvtGenReport( EVTGEN_ERROR, "EvtBcHad" )
            << "probmax: Have not yet implemented this final state in BC_VHAD model, out_code = "
            << out_code << std::endl;
        ::abort();
    }
}

//======================================================

EvtVector4C EvtBcVHad::hardCurr( EvtParticle* root_particle ) const
{
    EvtVector4C hardCur;

    if ( out_code == 1 ) {
        // pi+
        hardCur = wcurr->WCurrent( root_particle->getDaug( 1 )->getP4() );

    } else if ( out_code == 2 ) {
        // pi+ pi0
        hardCur = wcurr->WCurrent( root_particle->getDaug( 1 )->getP4(),
                                   root_particle->getDaug( 2 )->getP4() );

    } else if ( out_code == 3 ) {
        // pi+ pi+ pi-
        hardCur = wcurr->WCurrent( root_particle->getDaug( 1 )->getP4(),
                                   root_particle->getDaug( 2 )->getP4(),
                                   root_particle->getDaug( 3 )->getP4() );

    } else if ( out_code == 5 ) {
        // Bc -> psi pi+ pi+ pi- pi- pi+ from Kuhn, Was, hep-ph/0602162
        hardCur = wcurr->WCurrent( root_particle->getDaug( 1 )->getP4(),
                                   root_particle->getDaug( 2 )->getP4(),
                                   root_particle->getDaug( 3 )->getP4(),
                                   root_particle->getDaug( 4 )->getP4(),
                                   root_particle->getDaug( 5 )->getP4() );

    } else if ( out_code == 6 ) {
        // K+ K- pi+
        hardCur = wcurr->WCurrent_KKP( root_particle->getDaug( 1 )->getP4(),
                                       root_particle->getDaug( 2 )->getP4(),
                                       root_particle->getDaug( 3 )->getP4() );

    } else if ( out_code == 7 ) {
        // K+ pi+ pi-
        hardCur = wcurr->WCurrent_KPP( root_particle->getDaug( 1 )->getP4(),
                                       root_particle->getDaug( 2 )->getP4(),
                                       root_particle->getDaug( 3 )->getP4() );

    } else if ( out_code == 8 ) {
        // K_S0 K+
        hardCur = wcurr->WCurrent_KSK( root_particle->getDaug( 1 )->getP4(),
                                       root_particle->getDaug( 2 )->getP4() );

    } else if ( out_code == 9 ) {
        // K+ K- pi+ pi+ pi-
        hardCur = wcurr->WCurrent_KKPPP(
            root_particle->getDaug( 1 )->getP4(),    // K+
            root_particle->getDaug( 2 )->getP4(),    // K-
            root_particle->getDaug( 3 )->getP4(),    // pi+
            root_particle->getDaug( 4 )->getP4(),    // pi+
            root_particle->getDaug( 5 )->getP4()     // pi-
        );
    } else if ( out_code == 10 ) {
        // 1=pi+ 2=pi+ 3=pi+ 4=pi+ 5=pi- 6=pi- 7=pi- with symmetrization of the identical particles
        hardCur =
            wcurr->WCurrent_7pi( root_particle->getDaug( 1 )->getP4(),    // pi+
                                 root_particle->getDaug( 2 )->getP4(),    // pi+
                                 root_particle->getDaug( 3 )->getP4(),    // pi+
                                 root_particle->getDaug( 4 )->getP4(),    // pi+
                                 root_particle->getDaug( 5 )->getP4(),    // pi-
                                 root_particle->getDaug( 6 )->getP4(),    // pi-
                                 root_particle->getDaug( 7 )->getP4()     // pi-
            );
    } else if ( out_code == 11 ) {
        // 1=K+ 2 = pi+ 3 = pi+ 4 = pi- 5 = pi- with symmetrizatiom
        hardCur = wcurr->WCurrent_K4pi(
            root_particle->getDaug( 1 )->getP4(),    // K+
            root_particle->getDaug( 2 )->getP4(),    // pi+
            root_particle->getDaug( 3 )->getP4(),    // pi+
            root_particle->getDaug( 4 )->getP4(),    // pi-
            root_particle->getDaug( 5 )->getP4()     // pi-
        );
    } else {
        EvtGenReport( EVTGEN_ERROR, "EvtBcHad" )
            << "hardCurr: Have not yet implemented this final state in BC_VHAD model"
            << std::endl;
        //	EvtGenReport(EVTGEN_ERROR, "EvtGen") << "Have not yet implemented this final state in BC_VHAD model" << std::endl;
        //	EvtGenReport(EVTGEN_ERROR, "EvtGen") << "Ndaug=" << getNDaug() << std::endl;
        for ( int id = 0; id < ( getNDaug() - 1 ); id++ ) {
            //	    EvtGenReport(EVTGEN_ERROR, "EvtGen") << "Daug " << id << " " << EvtPDL::name(getDaug(id)).c_str() << std::endl;
        }
        ::abort();
    }

    return hardCur;
}

//======================================================

void EvtBcVHad::decay( EvtParticle* root_particle )
{
    root_particle->initializePhaseSpace( getNDaug(), getDaugs() );

    // Calculate hadronic current
    const EvtVector4C hardCur = hardCurr( root_particle );

    EvtParticle* Jpsi = root_particle->getDaug( 0 );

    const EvtVector4R p4b( root_particle->mass(), 0., 0., 0. ),    // Bc momentum
        p4meson = Jpsi->getP4(),    // J/psi momenta
        Q = p4b - p4meson, p4Sum = p4meson + p4b;
    const double Q2 = Q.mass2();

    // Calculate Bc -> V W form-factors
    double a1f( 0.0 ), a2f( 0.0 ), vf( 0.0 ), a0f( 0.0 );

    const double m_meson = Jpsi->mass();
    const double m_b = root_particle->mass();
    const double mVar = m_b + m_meson;

    ffmodel->getvectorff( root_particle->getId(), Jpsi->getId(), Q2, m_meson,
                          &a1f, &a2f, &vf, &a0f );

    const double a3f = ( mVar / ( 2.0 * m_meson ) ) * a1f -
                       ( ( m_b - m_meson ) / ( 2.0 * m_meson ) ) * a2f;

    // Calculate Bc -> V W current
    EvtTensor4C H = a1f * mVar * EvtTensor4C::g();
    H.addDirProd( ( -a2f / mVar ) * p4b, p4Sum );
    H += EvtComplex( 0.0, vf / mVar ) *
         dual( EvtGenFunctions::directProd( p4Sum, Q ) );
    H.addDirProd( ( a0f - a3f ) * 2.0 * ( m_meson / Q2 ) * p4b, Q );
    const EvtVector4C Heps = H.cont2( hardCur );

    for ( int i = 0; i < 4; i++ ) {
        const EvtVector4C eps =
            Jpsi->epsParent( i ).conj();    // psi-meson polarization vector
        const EvtComplex amp = eps * Heps;
        vertex( i, amp );
    }
}

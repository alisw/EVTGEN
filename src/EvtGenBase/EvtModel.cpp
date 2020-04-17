#include "EvtGenBase/EvtModel.hh"

#include "EvtGenBase/EvtDecayBase.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtParser.hh"
#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtParticleDecayList.hh"
#include "EvtGenBase/EvtPatches.hh"
#include "EvtGenBase/EvtRandom.hh"
#include "EvtGenBase/EvtReport.hh"

#include <assert.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string>
using std::fstream;

EvtModel* EvtModel::_instance = 0;

EvtModel::EvtModel()
{
}

EvtDecayBase* EvtModel::getFcn( std::string model_name )
{
    EvtDecayBase* model = 0;
    if ( _modelNameHash.find( model_name ) != _modelNameHash.end() ) {
        model = _modelNameHash[model_name];
    }

    if ( model == 0 ) {
        EvtGenReport( EVTGEN_ERROR, "EvtGen" )
            << "Did not find the right model:" << model_name.c_str() << "\n";
        return 0;
    }

    return model->clone();
}

void EvtModel::registerModel( EvtDecayBase* prototype )
{
    std::string modelName = prototype->getName();

    _modelNameHash[modelName] = prototype;

    std::string commandName = prototype->commandName();

    if ( commandName != "" ) {
        _commandNameHash[commandName] = prototype;
    }
}

int EvtModel::isModel( std::string model_name )
{
    if ( _modelNameHash.find( model_name ) != _modelNameHash.end() ) {
        return 1;
    }
    return 0;
}

int EvtModel::isCommand( std::string cmd )
{
    if ( _commandNameHash.find( cmd ) != _commandNameHash.end() ) {
        return 1;
    }
    return 0;
}

void EvtModel::storeCommand( std::string cmd, std::string cnfgstr )
{
    EvtDecayBase* model = 0;
    if ( _commandNameHash.find( cmd ) != _commandNameHash.end() ) {
        model = _commandNameHash[cmd];
    }

    assert( model != 0 );

    model->command( cnfgstr );
}

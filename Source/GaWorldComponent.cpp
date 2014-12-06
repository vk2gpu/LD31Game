/**************************************************************************
*
* File:		GaWorldComponent.cpp
* Author:	Neil Richardson 
* Ver/Date:	
* Description:
*		
*		
*
*
* 
**************************************************************************/

#include "GaWorldComponent.h"

#include "System/Scene/Rendering/ScnShaderFileData.h"
#include "System/Scene/Rendering/ScnViewComponent.h"
#include "System/Scene/Rendering/ScnDebugRenderComponent.h"

#include "System/Content/CsPackage.h"
#include "System/Content/CsCore.h"

#include "Base/BcProfiler.h"
#include "Base/BcMath.h"

//////////////////////////////////////////////////////////////////////////
// Define resource internals.
DEFINE_RESOURCE( GaWorldComponent );

void GaWorldComponent::StaticRegisterClass()
{
	ReRegisterClass< GaWorldComponent, Super >()
		.addAttribute( new ScnComponentAttribute( 0 ) );
}

//////////////////////////////////////////////////////////////////////////
// initialise
void GaWorldComponent::initialise( const Json::Value& Object )
{

}

//////////////////////////////////////////////////////////////////////////
// update
//virtual
void GaWorldComponent::update( BcF32 Tick )
{
	Super::update( Tick );

	// Draw floor.
	ScnDebugRenderComponent::pImpl()->drawGrid( 
		MaVec3d( 0.0f, 0.0f, 0.0f ),
		MaVec3d( 500.0f, 0.0f, 500.0f ),
		1.0f,
		10.0f,
		0 );
}

//////////////////////////////////////////////////////////////////////////
// onAttach
//virtual
void GaWorldComponent::onAttach( ScnEntityWeakRef Parent )
{
	Super::onAttach( Parent );

	BcU32 Idx = 0;

	auto spawnRobot = [ this, &Idx ]( MaVec3d Position, MaVec3d Rotation )
	{
		ScnEntitySpawnParams EntityParams = 
		{
			"default", "RobotEntity", BcName( "ModelEntity", Idx++ ),
			MaMat4d(),
			getParentEntity()
		};

		EntityParams.Transform_.rotation( Rotation );
		EntityParams.Transform_.translation( Position );
		ScnCore::pImpl()->spawnEntity( EntityParams );
	};

	spawnRobot( MaVec3d( -32.0f, 0.0f, 0.0f ), MaVec3d( 0.0f, 0.0f, 0.0f ) );
	spawnRobot( MaVec3d( 32.0f, 0.0f, 0.0f ), MaVec3d( 0.0f, BcPI, 0.0f ) );
}

//////////////////////////////////////////////////////////////////////////
// onDetach
//virtual
void GaWorldComponent::onDetach( ScnEntityWeakRef Parent )
{
	Super::onDetach( Parent );

}

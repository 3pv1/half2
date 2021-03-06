//========= Copyright ? 1996-2001, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $Header: $
// $NoKeywords: $
//=============================================================================

#include "BaseVSShader.h"

BEGIN_VS_SHADER( VertexLitGeneric, 
				"Help for VertexLitGeneric" )
	BEGIN_SHADER_PARAMS
		SHADER_PARAM( SELFILLUMTINT, SHADER_PARAM_TYPE_COLOR, "[1 1 1]", "Self-illumination tint" )
		SHADER_PARAM( BRIGHTNESS, SHADER_PARAM_TYPE_TEXTURE, "shadertest/detail", "HDR brightness texture" )
		SHADER_PARAM( DETAIL, SHADER_PARAM_TYPE_TEXTURE, "shadertest/detail", "detail texture" )
		SHADER_PARAM( DETAILFRAME, SHADER_PARAM_TYPE_INTEGER, "0", "frame number for $detail" )
		SHADER_PARAM( DETAILSCALE, SHADER_PARAM_TYPE_FLOAT, "4", "scale of the detail texture" )
		SHADER_PARAM( ENVMAP, SHADER_PARAM_TYPE_TEXTURE, "shadertest/shadertest_env", "envmap" )
		SHADER_PARAM( ENVMAPFRAME, SHADER_PARAM_TYPE_INTEGER, "", "envmap frame number" )
		SHADER_PARAM( ENVMAPMASK, SHADER_PARAM_TYPE_TEXTURE, "shadertest/BaseTimesLightmapPlusMaskedCubicEnvMap_glass", "envmap mask" )
		SHADER_PARAM( ENVMAPMASKFRAME, SHADER_PARAM_TYPE_INTEGER, "", "" )
		SHADER_PARAM( ENVMAPMASKTRANSFORM, SHADER_PARAM_TYPE_MATRIX, "center .5 .5 scale 1 1 rotate 0 translate 0 0", "$envmapmask texcoord transform" )
		SHADER_PARAM( ENVMAPTINT, SHADER_PARAM_TYPE_COLOR, "[1 1 1]", "envmap tint" )
		SHADER_PARAM( BUMPMAP, SHADER_PARAM_TYPE_TEXTURE, "shadertest/WorldDiffuseBumpMap_bump", "bump map" )
		SHADER_PARAM( BUMPFRAME, SHADER_PARAM_TYPE_INTEGER, "0", "frame number for $bumpmap" )
		SHADER_PARAM( BUMPTRANSFORM, SHADER_PARAM_TYPE_MATRIX, "center .5 .5 scale 1 1 rotate 0 translate 0 0", "$bumpmap texcoord transform" )
		SHADER_PARAM( ENVMAPCONTRAST, SHADER_PARAM_TYPE_FLOAT, "0.0", "contrast 0 == normal 1 == color*color" )
		SHADER_PARAM( ENVMAPSATURATION, SHADER_PARAM_TYPE_FLOAT, "1.0", "saturation 0 == greyscale 1 == normal" )
	END_SHADER_PARAMS

	SHADER_INIT_PARAMS()
	{
		// hack
/*
		params[BUMPMAP]->SetUndefined();
		params[ENVMAP]->SetUndefined();
		params[ENVMAPMASK]->SetUndefined();
		CLEAR_FLAGS( MATERIAL_VAR_BASEALPHAENVMAPMASK );
		CLEAR_FLAGS( MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK );
*/

		const bool bVertexLitGeneric = true;
		InitParamsVertexLitAndUnlitGeneric_HDR( bVertexLitGeneric,
			BASETEXTURE,	FRAME,				BASETEXTURETRANSFORM,
			SELFILLUMTINT,
			BRIGHTNESS,
			DETAIL,			DETAILFRAME,		DETAILSCALE,
			ENVMAP,			ENVMAPFRAME,
			ENVMAPMASK,		ENVMAPMASKFRAME,	ENVMAPMASKTRANSFORM,
			ENVMAPTINT,
			BUMPMAP,		BUMPFRAME,			BUMPTRANSFORM,
			ENVMAPCONTRAST,	ENVMAPSATURATION );
	}

	SHADER_FALLBACK
	{	
		if( !g_pHardwareConfig->SupportsHDR() )
		{
			return "VertexLitGeneric_DX9";
		}
		return 0;
	}

	SHADER_INIT
	{
		const bool bVertexLitGeneric = true;
		InitVertexLitAndUnlitGeneric_HDR( bVertexLitGeneric,
			BASETEXTURE,	FRAME,				BASETEXTURETRANSFORM,
			SELFILLUMTINT,
			BRIGHTNESS,
			DETAIL,			DETAILFRAME,		DETAILSCALE,
			ENVMAP,			ENVMAPFRAME,
			ENVMAPMASK,		ENVMAPMASKFRAME,	ENVMAPMASKTRANSFORM,
			ENVMAPTINT,
			BUMPMAP,		BUMPFRAME,			BUMPTRANSFORM,
			ENVMAPCONTRAST,	ENVMAPSATURATION );
	}

	SHADER_DRAW
	{
		const bool bVertexLitGeneric = true;
		DrawVertexLitAndUnlitGeneric_HDR( bVertexLitGeneric,
			BASETEXTURE,	FRAME,				BASETEXTURETRANSFORM,
			SELFILLUMTINT,
			BRIGHTNESS,
			DETAIL,			DETAILFRAME,		DETAILSCALE,
			ENVMAP,			ENVMAPFRAME,
			ENVMAPMASK,		ENVMAPMASKFRAME,	ENVMAPMASKTRANSFORM,
			ENVMAPTINT,
			BUMPMAP,		BUMPFRAME,			BUMPTRANSFORM,
			ENVMAPCONTRAST,	ENVMAPSATURATION );
	}
END_SHADER

vs.1.1

#include "macros.vsh"

&AllocateRegister( \$worldPos );
&SkinPosition( $g_numBones, $worldPos );

; Transform the position from world to view space
dp4 oPos.x, $worldPos, $cViewProj0
dp4 oPos.y, $worldPos, $cViewProj1
dp4 oPos.z, $worldPos, $cViewProj2
dp4 oPos.w, $worldPos, $cViewProj3

&FreeRegister( \$worldPos );

mov oD0, $cOne



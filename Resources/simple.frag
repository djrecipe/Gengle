#version 430 core

layout(location = 4) in vec2 TexCoord;

out vec4 fColor;

uniform bool istex;      // flag: use texture?
uniform sampler2D tex0;

vec4 ComputeLight (const in vec3 direction, const in vec4 lightcolorin, const in vec3 normal, const in vec3 halfvec, const in vec4 mydiffuse, const in vec4 myspecular, const in float myshininess, const in float dist_in)
{

        vec4 lambert=vec4(0.0,0.0,0.0,0.0);
        vec4 phong=vec4(0.0,0.0,0.0,0.0);
        if(true)
        {
            float nDotL = dot(normal, direction)  ;         
            lambert = mydiffuse * lightcolorin * max (nDotL, 0.0) ;
        }
        if(true)
        {
            float nDotH = dot(normal, halfvec) ; 
            phong = myspecular * lightcolorin * pow (max(nDotH, 0.0), myshininess) ;
        }

        return (lambert + phong) * max(min(1.0-dist_in/5000.0,1.0),0.0);
} 

void main()
{
	if(istex)
	{
		fColor = texture( tex0, TexCoord );
	}
	else
	{
		fColor = vec4(0.05, 0.1, 0.9, 1.0);
	}
}
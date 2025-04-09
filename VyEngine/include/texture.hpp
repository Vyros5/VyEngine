#pragma once

#include <glad/glad.h>
#include <assimp/scene.h>
#include <string>

/*
    Texture
*/

struct MeshTexture
{
	// Texture ID
	unsigned int ID;

	// Texture Type
	aiTextureType type;

	// Texture Name
	std::string name;

	// Texture Name in Directory
	std::string path;
};



class Texture
{
    public:
    
    unsigned int ID = 0;
    
    // Texture Type
    aiTextureType Type  = aiTextureType_NONE;

    GLenum NumType      = GL_UNSIGNED_BYTE;

    GLenum Target       = GL_TEXTURE_2D;
    
    GLenum Format       = GL_RGBA;

    // Filter Methods
    GLenum FilterMin    = GL_LINEAR;
    GLenum FilterMax    = GL_LINEAR;

    // Wrapping Methods
    GLenum WrapS        = GL_REPEAT;
    GLenum WrapT        = GL_REPEAT;
    GLenum WrapR        = GL_REPEAT;

    // Mipmap
    bool Mipmapping     = true;

    Texture(GLenum target, const std::string& fileName);

    ~Texture();

    void bind(GLuint unit = -1);
    void unbind();

    void setWrapMode(GLenum wrapMode, bool bind = false);
    void setFilterMin(GLenum filter,  bool bond = false);
    void setFilterMax(GLenum filter,  bool bond = false);

};



/*
aiTextureType_NONE 	
Dummy value. No texture, but the value to be used as 'texture semantic'
(#aiMaterialProperty::mSemantic) for all material properties not related to textures.


aiTextureType_DIFFUSE 	
The texture is combined with the result of the diffuse lighting equation.

aiTextureType_SPECULAR 	
The texture is combined with the result of the specular lighting equation.

aiTextureType_AMBIENT 	
The texture is combined with the result of the ambient lighting equation.

aiTextureType_EMISSIVE 	
The texture is added to the result of the lighting calculation.
It isn't influenced by incoming light.

aiTextureType_HEIGHT 	
The texture is a height map.
By convention, higher gray-scale values stand for higher elevations from the base height.

aiTextureType_NORMALS 	
The texture is a (tangent space) normal-map.
Again, there are several conventions for tangent-space normal maps.
Assimp does (intentionally) not distinguish here.

aiTextureType_SHININESS 	
The texture defines the glossiness of the material.
The glossiness is in fact the exponent of the specular (phong) lighting equation. 
Usually there is a conversion function defined to map the linear color 
values in the texture to a suitable exponent.

aiTextureType_OPACITY 	
The texture defines per-pixel opacity.
Usually 'white' means opaque and 'black' means 'transparency'. Or quite the opposite.

aiTextureType_DISPLACEMENT 	
Displacement texture.
The exact purpose and format is application-dependent. 
Higher color values stand for higher vertex displacements.

aiTextureType_LIGHTMAP 	
Lightmap texture (aka Ambient Occlusion)
Both 'Lightmaps' and dedicated 'ambient occlusion maps' are covered by this material property. 
The texture contains a scaling value for the final color value of a pixel. 
Its intensity is not affected by incoming light.
*/
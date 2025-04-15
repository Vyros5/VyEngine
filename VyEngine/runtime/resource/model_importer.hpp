#pragma once

#include "mesh.hpp"

namespace VyEngine
{
    struct LoadedMeshData
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<MeshTexture> textures;
    };

    
    struct LoadedMeshesData
    {
        std::string name;
        SharedPtr<Mesh> root;
        std::vector<LoadedMeshData> meshes;
    };
}
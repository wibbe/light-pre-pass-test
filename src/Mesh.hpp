
#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <string>

#include "Math.hpp"

namespace mesh
{

   struct FaceRaw
   {
      FaceRaw(int _v1, int _v2, int _v3)
        : v1(_v1),
          v2(_v2),
          v3(_v3)
      { }

      int v1, v2, v3;
   };

   struct GroupRaw
   {
      GroupRaw(std::string const& _material)
        : material(material)
      { }

      std::vector<FaceRaw> faces;
      std::string material;
   };

   struct MeshRaw
   {
     std::vector<math::Vector3> positions;
     std::vector<math::Vector3> normals;
     std::vector<GroupRaw> groups;
   };

   /// Load an obj mesh from disk
   MeshRaw * load(std::string const& filename);

}

#endif


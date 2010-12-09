
#include "Mesh.hpp"

#include <fstream>
#include <iostream>

#include <boost/spirit/core.hpp>
#include <boost/spirit/actor/push_back_actor.hpp>
#include <boost/spirit/actor/insert_at_actor.hpp>

namespace mesh
{

   MeshRaw * load(std::string const& filename)
   {
     MeshRaw * mesh = new MeshRaw();

     using namespace boost::spirit;

     std::ifstream file(filename.c_str());

     while (file.good())
     {
       std::string line;
       getline(file, line);
       std::vector<int> indices;

       if (line.length() > 1)
       {
         double x, y, z;
         char groupName[2048];

         bool vertexParsed = parse(line.c_str(),
                                   ('v' >> real_p[assign_a(x)] >> real_p[assign_a(y)] >> real_p[assign_a(z)] >> *space_p),
                                   space_p).full;

         bool groupParsed = parse(line.c_str(),
                                  ('g' >> (ch_p >> *(ch_p|space_p))[assign_a(groupName)]),
                                  space_p).full;

        // discard return value - some sort of junk at end in some lines, can't be bothered with it now though
         parse(
             line.c_str(),
             (
             ('f' >> *(int_p[push_back_a(indices)] >> *(+ch_p('/') >> int_p)))
             ),
             space_p).full;

         if (vertexParsed)
         {
           mesh->positions.push_back(math::Vector3(x, y, z));
         }
         else if (indices.size() >= 3)
         {
           // Triangulate everything
           for (size_t i = 1; i + 1 < indices.size(); ++i)
           {
             //            std::cout << "  Triangulating " << indices[0] - 1 << ", " << indices[i] - 1 << ", " << indices[i + 1] - 1 << std::endl;
             //m_faces.push_back(ObjFace(indices[0] - 1, indices[i] - 1, indices[i + 1] - 1));
           }
         }
       }
     }

     return mesh;
   }

}


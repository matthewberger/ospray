// ======================================================================== //
// Copyright 2009-2017 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#include <ospray/ospray.h>
#include "CommandLine.h"
#include "Patch.h"

/*! _everything_ in the ospray core universe should _always_ be in the
  'ospray' namespace. */
namespace ospray {

  /*! though not required, it is good practice to put any module into
    its own namespace (isnide of ospray:: ). Unlike for the naming of
    library and init function, the naming for this namespace doesn't
    particularlly matter. E.g., 'bilinearPatch', 'module_blp',
    'bilinar_patch' etc would all work equally well. */
  namespace bilinearPatch {

    // use ospcommon for vec3f etc
    using namespace ospcommon;
    
    extern "C" int main(int ac, const char **av)
    {
      // initialize ospray (this also takes all ospray-related args
      // off the command-line)
      ospInit(&ac,av);
      
      // parse the commandline; complain about anything we do not
      // recognize
      CommandLine args(ac,av);
      if (args.inputFiles.empty())
        throw std::runtime_error("no input files specified");

      // import the patches from the sample files
      std::vector<Patch> patches;
      for (auto fileName : args.inputFiles)
        readPatchesFromFile(patches,fileName);

      box3f bounds = empty;
      for (auto patch : patches) {
        bounds.extend(patch.v00);
        bounds.extend(patch.v01);
        bounds.extend(patch.v10);
        bounds.extend(patch.v11);
      }
      std::cout << "##################################################################" << std::endl;
      std::cout << "#osp:blp: done parsing input files" << std::endl;
      std::cout << "#osp:blp: found a total of  " << patches.size() << " patches ..." << std::endl;
      std::cout << "#osp:blp: ... with world bounds of " << bounds << std::endl;
      std::cout << "##################################################################" << std::endl;

      // create the actual viewer ....
      throw std::runtime_error("creating actual viewer not implemented yet ...");
    }
        
  } // ::ospray::bilinearPatch
} // ::ospray

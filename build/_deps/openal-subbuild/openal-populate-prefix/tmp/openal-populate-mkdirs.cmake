# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/jaakk/Desktop/OhjProjektiTITE23/build/_deps/openal-src")
  file(MAKE_DIRECTORY "C:/Users/jaakk/Desktop/OhjProjektiTITE23/build/_deps/openal-src")
endif()
file(MAKE_DIRECTORY
  "C:/Users/jaakk/Desktop/OhjProjektiTITE23/build/_deps/openal-build"
  "C:/Users/jaakk/Desktop/OhjProjektiTITE23/build/_deps/openal-subbuild/openal-populate-prefix"
  "C:/Users/jaakk/Desktop/OhjProjektiTITE23/build/_deps/openal-subbuild/openal-populate-prefix/tmp"
  "C:/Users/jaakk/Desktop/OhjProjektiTITE23/build/_deps/openal-subbuild/openal-populate-prefix/src/openal-populate-stamp"
  "C:/Users/jaakk/Desktop/OhjProjektiTITE23/build/_deps/openal-subbuild/openal-populate-prefix/src"
  "C:/Users/jaakk/Desktop/OhjProjektiTITE23/build/_deps/openal-subbuild/openal-populate-prefix/src/openal-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/jaakk/Desktop/OhjProjektiTITE23/build/_deps/openal-subbuild/openal-populate-prefix/src/openal-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/jaakk/Desktop/OhjProjektiTITE23/build/_deps/openal-subbuild/openal-populate-prefix/src/openal-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()

# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/onyxnode/anero/translations"
  "/home/onyxnode/anero/translations"
  "/home/onyxnode/anero/generate_translations_header-prefix"
  "/home/onyxnode/anero/generate_translations_header-prefix/tmp"
  "/home/onyxnode/anero/generate_translations_header-prefix/src/generate_translations_header-stamp"
  "/home/onyxnode/anero/generate_translations_header-prefix/src"
  "/home/onyxnode/anero/generate_translations_header-prefix/src/generate_translations_header-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/onyxnode/anero/generate_translations_header-prefix/src/generate_translations_header-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/onyxnode/anero/generate_translations_header-prefix/src/generate_translations_header-stamp${cfgdir}") # cfgdir has leading slash
endif()

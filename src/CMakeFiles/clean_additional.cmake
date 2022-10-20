# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "3dviewer.app"
  "3dviewer_autogen"
  "CMakeFiles\\3dviewer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\3dviewer_autogen.dir\\ParseCache.txt"
  "QtGifImage\\CMakeFiles\\qtgif_autogen.dir\\AutogenUsed.txt"
  "QtGifImage\\CMakeFiles\\qtgif_autogen.dir\\ParseCache.txt"
  "QtGifImage\\qtgif_autogen"
  "coverage"
  "dist.tar.gz"
  "doc\\documentation.html"
  "install_manifest.txt"
  "s21_matrixplus\\TAG"
  "s21_matrixplus\\Temporary"
  "s21_matrixplus\\Testing"
  "s21_matrixplus\\coverage"
  "s21_matrixplus\\install_manifest.txt"
  "tests\\DartConfiguration.tcl"
  "tests\\TAG"
  "tests\\Temporary"
  "tests\\Testing"
  )
endif()

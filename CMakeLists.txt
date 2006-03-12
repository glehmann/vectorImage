#Change PROJECT_NAME to the name of your project
PROJECT(vectorImage)

#include some macros from another file...
INCLUDE(IJMacros.txt)

#The following lines are required to use Dart
ENABLE_TESTING()
INCLUDE(Dart)
FIND_PROGRAM(IMAGE_COMPARE ImageCompare)

#Declare any external dependencies that your project may have here.
#examples include: ITK, VTK, JPEG, PNG, OpenGL, ZLIB, Perl, Java
#If you're not sure what name to use, look in the Modules directory of your
#cmake install and check that a file named Find(Package).cmake exists
SET(Required_Packages
  ITK
)

#this foreach loads all of the packages that you specified as required.
#It shouldn't need to be modified.
FOREACH(Package ${Required_Packages})
  LOADPACKAGE(${Package})
ENDFOREACH(Package)

#Set any libraries that your project depends on.
#examples: ITKCommon, VTKRendering, etc
SET(Libraries
  ITKCommon
  ITKBasicFilters
  ITKIO
)


# install devel files
FILE(GLOB develFiles *.h *.txx) 
FOREACH(f ${develFiles})
  INSTALL_FILES(/include/InsightToolkit/BasicFilters FILES ${f})
ENDFOREACH(f)



# option for wrapping
OPTION(BUILD_WRAPPERS "Wrap library" OFF)
IF(BUILD_WRAPPERS)
   SUBDIRS(Wrapping)
ENDIF(BUILD_WRAPPERS)
   
   

#the following block of code is an example of how to build an executable in
#cmake.  Unmodified, it will add an executable called "MyExe" to the project.
#MyExe will be built using the files MyClass.h and MyClass.cxx, and it will
#be linked to all the libraries you specified above. 
#You can build more than one executable per project

SET(CurrentExe "vector2image")
ADD_EXECUTABLE(${CurrentExe} ${CurrentExe}.cxx)
TARGET_LINK_LIBRARIES(${CurrentExe} ${Libraries})

SET(CurrentExe "image2vector")
ADD_EXECUTABLE(${CurrentExe} ${CurrentExe}.cxx)
TARGET_LINK_LIBRARIES(${CurrentExe} ${Libraries})

#the following line is an example of how to add a test to your project.
#Testname is the title for this particular test.  ExecutableToRun is the
#program which will be running this test.  It can either be a part of this
#project or an external executable.  After that list any args that are needed
#for this test.  Include as many tests as you like.  If your project doesn't have
#any tests you can comment out or delete the following line.
# ADD_TEST(Testname ExecutableToRun arg1 arg2 arg3)

ADD_TEST(ImageToVectorImage image2vector ${CMAKE_SOURCE_DIR}/images/cthead0.png ${CMAKE_SOURCE_DIR}/images/cthead1.png ${CMAKE_SOURCE_DIR}/images/cthead2.png ${CMAKE_SOURCE_DIR}/images/cthead3.png ${CMAKE_SOURCE_DIR}/images/cthead4.png ${CMAKE_SOURCE_DIR}/images/cthead5.png ctheadx.nrrd)
ADD_TEST(ImageToVectorImageCompare ${IMAGE_COMPARE} ctheadx.nrrd ${CMAKE_SOURCE_DIR}/images/ctheadx.nrrd)

FOREACH(i 0 1 2 3 4 5)
  ADD_TEST(VectorToImage-${i} vector2image ${CMAKE_SOURCE_DIR}/images/ctheadx.nrrd cthead${i}.png ${i})
  ADD_TEST(VectorToImageCompare-${i} ${IMAGE_COMPARE} cthead${i}.png ${CMAKE_SOURCE_DIR}/images/cthead${i}.png)
ENDFOREACH(i)

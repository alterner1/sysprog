project(Libs)

#-------------------- Create a library -----------------------------------------
#Generate the shared library from the library sources
#-------------------------------------------------------------------------------

add_library(md5 SHARED 
            ../src/md5.c
          )
target_include_directories(md5
    PRIVATE 
         ../lib
)
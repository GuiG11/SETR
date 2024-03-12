# Set the source files that make up the library
set(DLL_SRCS
   dll.h dll.c
)

# Set the library type (can be static or dynamic )
set(LIB_TYPE STATIC)

# Create the library
add_library(dllLib ${LIB_TYPE} ${DLL_SRCS})

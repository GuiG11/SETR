# Set the source files that make up the library
set(sensor_SRCS
   sensor.h sensor.c unity_internals.h unity.h unity.c
)

# Set the library type (can be static or dynamic )
set(LIB_TYPE STATIC)

# Create the library
add_library(sensorLib ${LIB_TYPE} ${sensor_SRCS})

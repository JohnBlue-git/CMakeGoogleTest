# Set variables
set(INCLUDE
    ${PROJECT_SOURCE_DIR}/include
)
set(SOURCE
    main.cpp
    caculate.cpp
)

# Add include directories
include_directories(${INCLUDE})

# Add the executable
add_executable(my_app ${SOURCE})

# Link any libraries if needed
# target_link_libraries(my_app ${LIBRARIES})

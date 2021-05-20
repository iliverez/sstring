add_library(sstring SHARED sstring.cpp sstring.h)

install(TARGETS sstring
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


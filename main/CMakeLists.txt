# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

set(srcs main.c
    	 src/HTTPPrintCustom.c
    	 src/HTTPPostCustom.c        
  		 src/MQTTCustom.c
		 src/AppConfiguration.c
		 )
set(include "include")

idf_component_register(
    SRCS "${srcs}"
    INCLUDE_DIRS ${include}
)
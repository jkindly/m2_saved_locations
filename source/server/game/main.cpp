//add as the last #include at the top of the file:
#ifdef ENABLE_SAVED_LOCATIONS
#include "saved_locations_manager.h"
#endif

//find:
if (!start(argc, argv)) {
	
//add above:
#ifdef ENABLE_SAVED_LOCATIONS
	SavedLocationsManager saved_locations;
#endif
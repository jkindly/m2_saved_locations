#find:
onClickKeyDict[app.DIK_LSHIFT] = lambda: self.__SetQuickSlotMode()

#add below:
if app.ENABLE_SAVED_LOCATIONS:
    onClickKeyDict[app.DIK_X] = lambda: self.__OpenSavedLocations()
    
#find:
self.serverCommander=stringCommander.Analyzer()

#add above:
if app.ENABLE_SAVED_LOCATIONS:
    serverCommandList.update({
        "open_locations": self.__OpenSavedLocationsWindowAfterLoad,
    })
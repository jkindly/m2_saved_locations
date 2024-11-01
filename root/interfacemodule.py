# add to imports at the top of the file

if app.ENABLE_SAVED_LOCATIONS:
	import uiSavedLocations
    
#find:
self.equipmentDialogDict = {}

#add below:
if app.ENABLE_SAVED_LOCATIONS:
    self.wndSavedLocations = None
    
#find:
self.wndChatLog = wndChatLog

#add below:
if app.ENABLE_SAVED_LOCATIONS:
    self.wndSavedLocations = uiSavedLocations.SavedLocationsWindow()
    
#find:
if self.wndChatLog:
    self.wndChatLog.Destroy()
    
#add below:
if app.ENABLE_SAVED_LOCATIONS:
    if self.wndSavedLocations:
        self.wndSavedLocations.Destroy()
        
#find:
del self.wndItemSelect

#add below:
if app.ENABLE_SAVED_LOCATIONS:
    if self.wndSavedLocations:
        del self.wndSavedLocations
        
#find:
if self.wndGuild:
    self.wndGuild.Hide()

#add below:            
if app.ENABLE_SAVED_LOCATIONS:
    if self.wndSavedLocations:
        self.wndSavedLocations.Hide()
        
#find:
if self.wndExpandedTaskBar:
    hideWindows += self.wndExpandedTaskBar,
            
#add below:
if app.ENABLE_SAVED_LOCATIONS:
    if self.wndSavedLocations:
        hideWindows += self.wndSavedLocations,
        
#find:
def BULID_ExitGuildArea(self, areaID):
    self.wndGameButton.HideBuildButton()
        
#add below:
if app.ENABLE_SAVED_LOCATIONS:
    def ToggleSavedLocationsWindow(self):
        if self.wndSavedLocations:
            self.wndSavedLocations.Open()

    def AppendLocation(self, idx, globalX, globalY, localX, localY, name):
        if self.wndSavedLocations:
            self.wndSavedLocations.AppendLocation(idx, globalX, globalY, localX, localY, name)
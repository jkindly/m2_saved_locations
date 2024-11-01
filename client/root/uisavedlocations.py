import ui
import chat
import net
import uiCommon
import localeInfo

LOCATIONS_PER_PAGE  = 10


class SavedLocationsWindow(ui.ScriptWindow):
    def __init__(self):
        self.isLoaded = False
        self.inputDialog = None
        self.currentPage = 1
        self.UI = {}
        self.locationDict = {}
        ui.ScriptWindow.__init__(self)

    def __del__(self):
        ui.ScriptWindow.__del__(self)

    def __LoadWindow(self):
        if self.isLoaded:
            return

        self.isLoaded = True

        try:
            pyScrLoader = ui.PythonScriptLoader()
            pyScrLoader.LoadScriptFile(self, "UIScript/savedlocations.py")
        except:
            import exception
            exception.Abort("SavedLocationsWindow.LoadDialog.LoadScript")

        try:
            self.GetChild("SavedLocationsTitleBar").SetCloseEvent(self.Close)
            self.LocationWindows = {
                1: self.GetChild("I_Window"),
                2: self.GetChild("II_Window"),
                3: self.GetChild("III_Window"),
                4: self.GetChild("IV_Window"),
                5: self.GetChild("V_Window"),
            }
            self.tabButtons = {
                1: self.GetChild("I_Button"),
                2: self.GetChild("II_Button"),
                3: self.GetChild("III_Button"),
                4: self.GetChild("IV_Button"),
                5: self.GetChild("V_Button"),
            }
        except:
            import exception
            exception.Abort("SavedLocationsWindow.LoadDialog.GetChild")

        self.InitializeSavedLocationList()
        self.OnClickTabButton(1)
        self.ShowCurrentWindow()

        for key, btn in self.tabButtons.items():
            btn.SetEvent(ui.__mem_func__(self.OnClickTabButton), key)

    def InitializeSavedLocationList(self):
        y_step = 27
        idx = 0
        for key, window in self.LocationWindows.items():
            self.UI[key] = {}
            for x in xrange(LOCATIONS_PER_PAGE ):
                self.UI[key][idx] = {}
                locationBg = ui.MakeImageBox(window, "d:/ymir work/ui/game/saved_locations/input.png", 0, x * y_step)
                locationName = ui.MakeText(locationBg, localeInfo.SAVED_LOCATION_EMPTY, 5, 0, None)
                locationName.SetWindowVerticalAlignCenter()
                locationName.SetVerticalAlignCenter()
                locationCoords = ui.MakeText(locationBg, "X: 0, Y: 0", 198, 0, None)
                locationCoords.SetWindowVerticalAlignCenter()
                locationCoords.SetVerticalAlignCenter()
                locationTPButton = ui.MakeButton(window, 305, x * y_step, None, "d:/ymir work/ui/public/", "Large_Button_01.sub", "Large_Button_02.sub", "Large_Button_03.sub")
                locationTPButton.SetText(localeInfo.SAVED_LOCATION_TELEPORT)
                locationTPButton.SetEvent(lambda arg=idx: net.SendChatPacket("/teleport_to_location %d" % arg))
                locationSaveButton = ui.MakeButton(window, 395, x * y_step, None, "d:/ymir work/ui/public/", "Large_Button_01.sub", "Large_Button_02.sub", "Large_Button_03.sub")
                locationSaveButton.SetText(localeInfo.SAVED_LOCATION_SAVE)
                locationSaveButton.SetEvent(ui.__mem_func__(self.SaveLocation), idx)
                locationEditNameButton = ui.MakeButton(locationBg, 165, 0, None, "d:/ymir work/ui/game/saved_locations/", "btn_edit_01.tga", "btn_edit_02.tga", "btn_edit_03.tga")
                locationEditNameButton.SetEvent(ui.__mem_func__(self.EditLocationName), idx)
                self.UI[key][idx]["bg"] = locationBg
                self.UI[key][idx]["name"] = locationName
                self.UI[key][idx]["coords"] = locationCoords
                self.UI[key][idx]["tp"] = locationTPButton
                self.UI[key][idx]["save"] = locationSaveButton
                self.UI[key][idx]["editName"] = locationEditNameButton

                idx += 1

        net.SendChatPacket("/load_Locations")

    def EditLocationName(self, idx):
        self.inputDialog = uiCommon.EditLineLocation()
        self.inputDialog.SetMaxLength(26)
        self.inputDialog.SetAcceptEvent(ui.__mem_func__(self.AcceptRenameLocation))
        self.inputDialog.SetCancelEvent(ui.__mem_func__(self.CloseDialog))
        self.inputDialog.SetAcceptText(localeInfo.SAVED_LOCATION_EDIT)
        self.inputDialog.SetCancelText(localeInfo.SAVED_LOCATION_CANCEL)
        self.inputDialog.SetTitle(localeInfo.SAVED_LOCATION_CHANGE_NAME)
        self.inputDialog.idx = idx

        self.inputDialog.SetDescription(localeInfo.SAVED_LOCATION_CURRENT_NAME + ": " + self.GetLocationName(idx))
        self.inputDialog.Open()

    def GetLocationName(self, idx):
        for key, location in self.locationDict.items():
            if key == idx:
                return location.GetName()

        return "-"

    def AcceptRenameLocation(self):
        if not self.inputDialog:
            return

        idx = self.inputDialog.idx

        textLine = self.inputDialog.GetText()
        if len(textLine) > 26:
            chat.AppendChat(1, localeInfo.SAVED_LOCATION_NAME_TOO_LONG)
            return

        net.SendRenameLocationPacket(idx, textLine)
        self.CloseDialog()

    def SaveLocation(self, idx):
        self.inputDialog = uiCommon.EditLineLocation()
        self.inputDialog.SetMaxLength(26)
        self.inputDialog.SetAcceptEvent(ui.__mem_func__(self.AcceptSaveLocation))
        self.inputDialog.SetCancelEvent(ui.__mem_func__(self.CloseDialog))
        self.inputDialog.SetAcceptText(localeInfo.SAVED_LOCATION_SAVE)
        self.inputDialog.SetCancelText(localeInfo.SAVED_LOCATION_CANCEL)
        self.inputDialog.SetTitle(localeInfo.SAVED_LOCATION_CHANGE_NAME)
        self.inputDialog.idx = idx
        self.inputDialog.SetDescription(localeInfo.SAVED_LOCATION_CURRENT_NAME + ": " + self.GetLocationName(idx))
        self.inputDialog.Open()

    def AcceptSaveLocation(self):
        if not self.inputDialog:
            return

        idx = self.inputDialog.idx

        textLine = self.inputDialog.GetText()
        if len(textLine) > 26:
            chat.AppendChat(1, localeInfo.SAVED_LOCATION_NAME_TOO_LONG)
            return

        net.SendSaveLocationPacket(idx, textLine)
        self.CloseDialog()

    def CloseDialog(self):
        if self.inputDialog:
            self.inputDialog.Hide()
            self.inputDialog = None

        return True

    def AppendLocation(self, idx, globalX, globalY, localX, localY, name):
        if name == "":
            name = "-"
        location = Location(idx, globalX, globalY, localX, localY, name)
        self.locationDict[idx] = location

        page = 1
        if 9 < idx < 20:
            page = 2
        elif 20 <= idx < 30:
            page = 3
        elif 30 <= idx < 40:
            page = 4
        elif 40 <= idx < 50:
            page = 5

        self.UI[page][idx]["name"].SetText(name)
        self.UI[page][idx]["coords"].SetText("X: %d Y: %d" % (localX, localY))

    def OnClickTabButton(self, page):
        self.currentPage = page

        for idx, btn in self.tabButtons.items():
            if idx == page:
                btn.Down()
                btn.Disable()
            else:
                btn.SetUp()
                btn.Enable()

        self.ShowCurrentWindow()

    def ShowCurrentWindow(self):
        for key, window in self.LocationWindows.items():
            if key == self.currentPage:
                window.Show()
            else:
                window.Hide()

    def Open(self):
        if not self.IsShow():
            if self.isLoaded:
                self.Show()
            else:
                self.__LoadWindow()
        else:
            self.Close()

    def Close(self):
        self.CloseDialog()
        self.Hide()

    def OnPressEscapeKey(self):
        self.Close()
        return True


class Location:
    def __init__(self, idx, globalX, globalY, localX, localY, name):
        self.idx = idx
        self.globalX = globalX
        self.globalY = globalY
        self.localX = localX
        self.localY = localY
        self.name = name

    def GetIdx(self):
        return self.idx

    def GetGlobalX(self):
        return self.globalX

    def GetGlobalY(self):
        return self.globalY

    def GetLocalX(self):
        return self.localX

    def GetLocalY(self):
        return self.localY

    def GetName(self):
        return self.name

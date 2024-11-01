#add at the bottom of the file

if app.ENABLE_SAVED_LOCATIONS:
	class EditLineLocation(InputDialog):
		def __init__(self):
			ui.ScriptWindow.__init__(self)
			self.LoadDialog()

		def __del__(self):
			InputDialog.__del__(self)

		def LoadDialog(self):
			pyScrLoader = ui.PythonScriptLoader()
			if localeInfo.IsARABIC():
				pyScrLoader.LoadScriptFile(self, uiScriptLocale.LOCALE_UISCRIPT_PATH + "inputdialogwithdescription.py")
			else:
				pyScrLoader.LoadScriptFile(self, "uiscript/inputdialogwithdescription.py")
			try:
				getObject = self.GetChild
				self.board = getObject("Board")
				self.acceptButton = getObject("AcceptButton")
				self.cancelButton = getObject("CancelButton")
				self.inputSlot = getObject("InputSlot")
				self.inputValue = getObject("InputValue")
				self.description = getObject("Description")
			except:
				import exception
				exception.Abort("EditLineLocalization.LoadDialog.BindObject")

		def SetText(self, text):
			self.inputValue.SetText(str(text))

		def SetDescription(self, text):
			self.description.SetText(text)

		def SetAcceptText(self, text):
			self.acceptButton.SetText(text)

		def SetCancelText(self, text):
			self.cancelButton.SetText(text)
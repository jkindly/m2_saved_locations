import uiScriptLocale

BOARD_WIDTH = 520
BOARD_HEIGHT = 357
X_RADIO_START = 35
X_RADIO_STEP = 90

PATTERN_PATH = "d:/ymir work/ui/pattern/"
MAIN_PATTERN_WIDTH = 500
MAIN_PATTERN_HEIGHT = 316
MAIN_PATTERN_X_COUNT = (MAIN_PATTERN_WIDTH - 32) / 16
MAIN_PATTERN_Y_COUNT = (MAIN_PATTERN_HEIGHT - 32) / 16

window = {
    "name": "SavedLocationsWindow",

    "x": SCREEN_WIDTH / 2 - BOARD_WIDTH / 2,
    "y": SCREEN_HEIGHT / 2 - BOARD_HEIGHT / 2,

    "style": ("movable", "float",),

    "width": BOARD_WIDTH,
    "height": BOARD_HEIGHT,

    "children":
        (
            {
                "name": "SavedLocationsBoard",
                "type": "board",
                "style": ("attach", "ltr"),

                "x": 0,
                "y": 0,

                "width": BOARD_WIDTH,
                "height": BOARD_HEIGHT,

                "children":
                    (
                        {
                            "name": "SavedLocationsTitleBar",
                            "type": "titlebar",
                            "style": ("attach",),

                            "x": 6,
                            "y": 7,

                            "width": BOARD_WIDTH - 13,

                            "children":
                                (
                                    {
                                        "name": "TitleName",
                                        "type": "text",

                                        "x": 0,
                                        "y": -2,

                                        "text": uiScriptLocale.SAVED_LOCATIONS_TITLE,
                                        "all_align": "center"
                                    },
                                ),
                        },
                        {
                            "name": "Section",
                            "type": "section_without_title",

                            "x": 10,
                            "y": 32,

                            "width": MAIN_PATTERN_WIDTH,
                            "height": MAIN_PATTERN_HEIGHT,

                            "children":
                                (
                                    {
                                        "name": "I_Window",
                                        "type": "window",
                                        "x": 10,
                                        "y": 10,
                                        "width": BOARD_WIDTH - 20,
                                        "height": BOARD_HEIGHT - 50,
                                    },
                                    {
                                        "name": "II_Window",
                                        "type": "window",
                                        "x": 10,
                                        "y": 10,
                                        "width": BOARD_WIDTH - 20,
                                        "height": BOARD_HEIGHT - 50,
                                    },
                                    {
                                        "name": "III_Window",
                                        "type": "window",
                                        "x": 10,
                                        "y": 10,
                                        "width": BOARD_WIDTH - 20,
                                        "height": BOARD_HEIGHT - 50,
                                    },
                                    {
                                        "name": "IV_Window",
                                        "type": "window",
                                        "x": 10,
                                        "y": 10,
                                        "width": BOARD_WIDTH - 20,
                                        "height": BOARD_HEIGHT - 50,
                                    },
                                    {
                                        "name": "V_Window",
                                        "type": "window",
                                        "x": 10,
                                        "y": 10,
                                        "width": BOARD_WIDTH - 20,
                                        "height": BOARD_HEIGHT - 50,
                                    },
                                ),
                        },
                        {
                            "name": "I_Button",
                            "type": "radio_button",

                            "x": X_RADIO_START,
                            "y": BOARD_HEIGHT - 38,

                            "default_image": "d:/ymir work/ui/public/Large_Button_01.sub",
                            "over_image": "d:/ymir work/ui/public/Large_Button_02.sub",
                            "down_image": "d:/ymir work/ui/public/Large_Button_03.sub",
                            "children":
                                (
                                    {
                                        "name": "I_Button_Print",
                                        "type": "text",

                                        "x": 0,
                                        "y": 0,

                                        "all_align": "center",

                                        "text": "I",
                                    },
                                ),
                        },
                        {
                            "name": "II_Button",
                            "type": "radio_button",

                            "x": X_RADIO_START + X_RADIO_STEP,
                            "y": BOARD_HEIGHT - 38,

                            "default_image": "d:/ymir work/ui/public/Large_Button_01.sub",
                            "over_image": "d:/ymir work/ui/public/Large_Button_02.sub",
                            "down_image": "d:/ymir work/ui/public/Large_Button_03.sub",

                            "children":
                                (
                                    {
                                        "name": "II_Button_Print",
                                        "type": "text",

                                        "x": 0,
                                        "y": 0,

                                        "all_align": "center",

                                        "text": "II",
                                    },
                                ),
                        },
                        {
                            "name": "III_Button",
                            "type": "radio_button",

                            "x": X_RADIO_START + X_RADIO_STEP * 2,
                            "y": BOARD_HEIGHT - 38,

                            "default_image": "d:/ymir work/ui/public/Large_Button_01.sub",
                            "over_image": "d:/ymir work/ui/public/Large_Button_02.sub",
                            "down_image": "d:/ymir work/ui/public/Large_Button_03.sub",

                            "children":
                                (
                                    {
                                        "name": "III_Button_Print",
                                        "type": "text",

                                        "x": 0,
                                        "y": 0,

                                        "all_align": "center",

                                        "text": "III",
                                    },
                                ),
                        },
                        {
                            "name": "IV_Button",
                            "type": "radio_button",

                            "x": X_RADIO_START + X_RADIO_STEP * 3,
                            "y": BOARD_HEIGHT - 38,

                            "default_image": "d:/ymir work/ui/public/Large_Button_01.sub",
                            "over_image": "d:/ymir work/ui/public/Large_Button_02.sub",
                            "down_image": "d:/ymir work/ui/public/Large_Button_03.sub",

                            "children":
                                (
                                    {
                                        "name": "IV_Button_Print",
                                        "type": "text",

                                        "x": 0,
                                        "y": 0,

                                        "all_align": "center",

                                        "text": "IV",
                                    },
                                ),
                        },
                        {
                            "name": "V_Button",
                            "type": "radio_button",

                            "x": X_RADIO_START + X_RADIO_STEP * 4,
                            "y": BOARD_HEIGHT - 38,

                            "default_image": "d:/ymir work/ui/public/Large_Button_01.sub",
                            "over_image": "d:/ymir work/ui/public/Large_Button_02.sub",
                            "down_image": "d:/ymir work/ui/public/Large_Button_03.sub",

                            "children":
                                (
                                    {
                                        "name": "IV_Button_Print",
                                        "type": "text",

                                        "x": 0,
                                        "y": 0,

                                        "all_align": "center",

                                        "text": "V",
                                    },
                                ),
                        },
                    ),
            },
        ),
}

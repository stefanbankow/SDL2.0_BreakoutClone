
#ifndef MENU_OPTIONS_ENUMS_HPP
#define MENU_OPTIONS_ENUMS_HPP
enum MainMenuOption
{
    MENUOPT_START_PLAYING, //Start the game from the main menu
    MENUOPT_EXIT,          //Exit to desktop
};

enum ChooseLevelMenuOption
{
    LEVELOPT_1,
    LEVELOPT_2,
    LEVELOPT_3,
    LEVELOPT_EXIT,
};
enum LevelMenuOption //Since all "ingame" menus will have 2 options that do similar things, we don't need enums for each one
{
    PAUSEOPT_CONTINUE_OR_RETRY, //Continues the game or resets the level depending on the menu
    PAUSEOPT_EXIT_TO_MAIN_MENU, //Exit to the main
};
#endif
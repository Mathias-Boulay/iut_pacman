#include "MenuUtils.h"
#include "Game.h"

using namespace std;

void MainMenu(){
    char input;

    while (true) {
        ClearDisplay();
        DisplayPacmanHeader();
        cout << "		[1] Play" << endl
             << "		[2] Settings" << endl
             << "		[3] Game Mode" << endl
             << "		[4] Leaderboard" << endl
             << "		[5] Quit" << endl
             << endl
             << "____________________________________________________" << endl;

        input = ReadSpecificKeyboardInput({'1','2','3','4','5'});

        switch (input) {
        case '1':
            PlayMenu();
            break;
        case '2':
            SettingMenu();
            break;
        case '3':
            SelectGamemodeMenu();
            break;
        case '4':
            LeaderdoardMenu();
            break;
        case '5':
            return;
            break;
        }
    }
}

void PlayMenu(){
    Settings st = LoadSettings();
    char input;

    while (true) {
        ClearDisplay();
        if(st.MiscSetting["Gamemode"] == "Classic"){
            DisplayClassicInstruction();
        }else{
            DisplayInfiniteInstruction();
        }

        input = ReadSpecificKeyboardInput({'1','2'});

        switch (input){
        case '2':
            // TODO Lancer le jeu
            if(st.MiscSetting["Gamemode"] == "Classic"){
                ClassicGame();
            }else{
                InfiniteGame();
            }
            break;
        case '1':
            return;
            break;
        }
    }
}

void SettingMenu(){
    char input;

    while (true) {
        ClearDisplay();
        DisplayPacmanHeader();
        cout << "		Settings" << endl
             << endl
             << "	[1] Reset leaderboard" << endl
             << "	[2] Change controls" << endl
             << endl
             << "[3] Main Menu" << endl
             << "____________________________________________________" << endl;

        input = ReadSpecificKeyboardInput({'1','2','3'});

        switch (input){
        case '1':
            ResetLeaderbordMenu();
            break;

        case '2':
            ChangeBindingsMenu();
            break;
        case '3':
            return;
            break;
        }
    }

}

void LeaderdoardMenu(){
    Settings st = LoadSettings();
    char input;
    static unsigned selectedLeaderboard = 1;

    while (true){
        ClearDisplay();
        DisplayPacmanHeader();
        cout << "		Leaderboards:" << endl;

        if(selectedLeaderboard == 1){
            cout << "	-> 	[1] Classic" << endl
                 << "		[2] Infinite" << endl
                 << endl
                 << "	Leaderboard of \"Classic\" " << endl;
            for(const auto &x : st.ClassicModeHighScore){
                cout << "	" << x.first << ". " << x.second << endl;
            }
        }else{
            cout << "	   	[1] Classic" << endl
                 << "	->	[2] Infinite" << endl
                 << endl
                 << "	Leaderboard of \"Infinite\" " << endl;
            for(const auto &x : st.InfiniteModeHighScore){
                cout << "	" << x.first << ". " << x.second << endl;
            }
        }
        cout << "[3] Main Menu" << endl
             << "____________________________________________________" << endl;

        input = ReadSpecificKeyboardInput({'1','2','3'});

        switch (input) {
        case '1':
            selectedLeaderboard = 1;
            break;
        case '2':
            selectedLeaderboard = 2;
            break;
        case '3':
            return;
            break;
        }
    }

}

void ResetLeaderbordMenu(){
    Settings st;
    char input;

    while (true) {
        ClearDisplay();
        DisplayPacmanHeader();
        cout << "		Are you sur you want to" << endl
             << "		reset the leaderboards ?" << endl
             << endl
             << "		[1] Yes" << endl
             << "		[2] No" << endl
             << endl
             << "____________________________________________________" << endl;

        input = ReadSpecificKeyboardInput({'1','2'});

        switch (input){
        case '1':
            remove("Classic_Highscores.yaml");
            remove("Infinite_Highscores.yaml");
            st = LoadSettings();
            ApplySettings(st);
            return;
            break;

        case '2':
            return;
            break;
        }
    }
}

void ChangeBindingsMenu(){
    Settings st = LoadSettings();
    char input;

    cout << "    Press the KeyUp: "  << endl;
    input = ReadKeyboardInput();
    st.MovementChar["KeyUp"] = input;
    cout << input << endl;

    cout << "    Press the KeyDown: "  << endl;
    input = ReadKeyboardInput();
    st.MovementChar["KeyDown"] = input;
    cout << input << endl;

    cout << "    Press the KeyLeft: "  << endl;
    input = ReadKeyboardInput();
    st.MovementChar["KeyLeft"] = input;
    cout << input << endl;

    cout << "    Press the KeyRight: "  << endl;
    input = ReadKeyboardInput();
    st.MovementChar["KeyRight"] = input;
    cout << input << endl;

    ApplySettings(st);

    return;
}

void SelectGamemodeMenu(){
    Settings st = LoadSettings();
    string gamemode;
    char input;

    while (true) {
        gamemode = st.MiscSetting["Gamemode"];
        ClearDisplay();
        DisplayPacmanHeader();

        if(gamemode == "Classic"){
            cout << "	Selected game mode :	[1] Classic" << endl
                 << "				[2] Infinite" << endl;
        }else{
            cout << "				[1] Classic" << endl
                 << "	Selected game mode :	[2] Infinite" << endl;
        }

        cout << endl
             << "	[3] Main Menu" << endl
             << "____________________________________________________" << endl;

        input = ReadSpecificKeyboardInput({'1','2','3'});


        switch (input){
        case '1':
            st.MiscSetting["Gamemode"] = "Classic";
            break;

        case '2':
            st.MiscSetting["Gamemode"] = "Infinite";
            break;

        case '3':
            ApplySettings(st);
            return;
            break;
        }
    }
}

void YouLostMenu(const unsigned &Score, const bool isClassicMode){
    Settings st = LoadSettings();
    InsertHighScore(st,Score,isClassicMode);
    ClearDisplay();
    DisplayPacmanHeader();
    cout << "____________________________________________________" << endl
         << "Well, you lost despite the AI being quite dumb." << endl
         << "How did you even lose the game ?!" << endl
         << endl
         << "Did you try to kill yourself or something ?" << endl;
    exit(EXIT_SUCCESS);

}

void YouWonMenu(const unsigned &Score, const bool isClassicMode){
    Settings st = LoadSettings();
    InsertHighScore(st,Score,isClassicMode);
    ClearDisplay();
    DisplayPacmanHeader();
    cout << "____________________________________________________" << endl
         << "Well, you won but the AI is and will stay quite dumb." << endl
         << "It wasn't that hard you know, even I can do it" << endl
         << endl
         << "But for now, take some rest" << endl;
    exit(EXIT_SUCCESS);

}

void DisplayPacmanHeader(){
    cout << "____________________________________________________" << endl
         << "	 ____  ____  ____        ____" << endl
         << "	|    ||    ||     |\\  /||    ||\\   |" << endl
         << "	|____||____||     | \\/ ||____|| \\  |" << endl
         << "	|     |    ||     |    ||    ||  \\ |" << endl
         << "	|     |    ||____ |    ||    ||   \\|" << endl
         << endl
         << endl;
}

void DisplayClassicInstruction(){
    cout << "____________________________________________________" << endl
         << endl
         << "		Classic" << endl
         << endl
         << "In this game mode, you will have \nto collect Pacgum in order to \ngain points. But you'll have to \ndodge the phantoms ! Move wisely\nall around the map, and be careful\nof what you eat... " << endl
         << endl
         << "20 levels, you won't beat them." << endl
         << endl
         << "[1] Main Menu 				[2] Start !" << endl
         << "____________________________________________________" << endl;
}

void DisplayInfiniteInstruction(){
    cout << "____________________________________________________" << endl
         << endl
         << "		Infinite" << endl
         << endl
         << "In this game mode, you will have \nto collect Pacgum in order to \ngain points. But you'll have to \ndodge the phantoms ! Move wisely\nall around the map, and be careful\nof what you eat... " << endl
         << endl
         << "Infinite number of levels, you can't escape." << endl
         << endl
         << "[1] Main Menu 				[2] Start !" << endl
         << "____________________________________________________" << endl;
}




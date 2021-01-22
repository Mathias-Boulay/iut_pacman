#include "types.h"
#include "SettingUtils.h"

using namespace std;

Settings LoadDefaultSettings(){
    Settings st;
    //Movements
    st.MovementChar["KeyUp"] = 'z';
    st.MovementChar["KeyDown"] = 's';
    st.MovementChar["KeyLeft"] = 'q';
    st.MovementChar["KeyRight"] = 'd';

    //Highscores
    st.ClassicModeHighScore["1"] = 0;
    st.ClassicModeHighScore["2"] = 0;
    st.ClassicModeHighScore["3"] = 0;
    st.ClassicModeHighScore["4"] = 0;
    st.ClassicModeHighScore["5"] = 0;
    st.ClassicModeHighScore["6"] = 0;
    st.ClassicModeHighScore["7"] = 0;
    st.ClassicModeHighScore["8"] = 0;
    st.ClassicModeHighScore["9"] = 0;
    //Infinite mode
    st.InfiniteModeHighScore["1"] = 0;
    st.InfiniteModeHighScore["2"] = 0;
    st.InfiniteModeHighScore["3"] = 0;
    st.InfiniteModeHighScore["4"] = 0;
    st.InfiniteModeHighScore["5"] = 0;
    st.InfiniteModeHighScore["6"] = 0;
    st.InfiniteModeHighScore["7"] = 0;
    st.InfiniteModeHighScore["8"] = 0;
    st.InfiniteModeHighScore["9"] = 0;

    //Misc settings
    st.MiscSetting["Gamemode"] = "Classic";

    return st;
}

Settings LoadSettings(){
    Settings st = LoadDefaultSettings();
    ifstream ifs;
    string Key;
    char tmp;

    //Try to load various config files
    ifs.open("Bindings.yaml");
    if (ifs.is_open()){
        while(ifs >> Key){
            ifs >> tmp;
            if(find(AuthorizedKey.MovementKey.begin(), AuthorizedKey.MovementKey.end(), Key) != AuthorizedKey.MovementKey.end()){
                ifs >> st.MovementChar[Key];
            }
        }
    }
    ifs.close();

    ifs.open("Classic_Highscores.yaml");
    if (ifs.is_open()){
        while(ifs >> Key){
            ifs >> tmp;
            if(find(AuthorizedKey.HighScoreKey.begin(), AuthorizedKey.HighScoreKey.end(), Key) != AuthorizedKey.HighScoreKey.end()){
                ifs >> st.ClassicModeHighScore[Key];
            }
        }
    }
    ifs.close();

    ifs.open("Infinite_Highscores.yaml");
    if (ifs.is_open()){
        while(ifs >> Key){
            ifs >> tmp;
            if(find(AuthorizedKey.HighScoreKey.begin(), AuthorizedKey.HighScoreKey.end(), Key) != AuthorizedKey.HighScoreKey.end()){
                ifs >> st.InfiniteModeHighScore[Key];
            }
        }
    }
    ifs.close();

    ifs.open("Misc.yaml");
    if (ifs.is_open()){
        while(ifs >> Key){
            ifs >> tmp;
            if(find(AuthorizedKey.MiscellaneousKey.begin(), AuthorizedKey.MiscellaneousKey.end(), Key) != AuthorizedKey.MiscellaneousKey.end()){
                ifs >> st.MiscSetting[Key];
            }
        }
    }
    ifs.close();

    return st;
}

void ApplySettings(const Settings &St){
    ofstream ofs;

    ofs.open("Bindings.yaml", ios_base::out | ios_base::trunc);
    for (auto const& x : St.MovementChar){
        //Write down settings
        ofs << x.first << " : " << x.second << endl;
    }
    ofs.close();

    ofs.open("Classic_Highscores.yaml", ios_base::out | ios_base::trunc);
    for (auto const& x : St.ClassicModeHighScore){
        //Write down settings
        ofs << x.first << " : " << x.second << endl;
    }
    ofs.close();

    ofs.open("Infinite_Highscores.yaml", ios_base::out | ios_base::trunc);
    for (auto const& x : St.InfiniteModeHighScore){
        //Write down settings
        ofs << x.first << " : " << x.second << endl;
    }
    ofs.close();

    ofs.open("Misc.yaml", ios_base::out | ios_base::trunc);
    for (auto const& x : St.MiscSetting){
        //Write down settings
        ofs << x.first << " : " << x.second << endl;
    }
    ofs.close();
}


void InsertHighScore(Settings &St,const unsigned &Highscore, const bool ClassicGamemode){
    if(ClassicGamemode){
        for(unsigned i(1); i < 10; i+=1){
            if(Highscore >= St.ClassicModeHighScore.find(to_string(i))->second){
                for(unsigned j (8); j >= i; j-=1){
                    St.ClassicModeHighScore.find(to_string(j+1))->second = St.ClassicModeHighScore.find(to_string(j))->second;
                }
                St.ClassicModeHighScore.find(to_string(i))->second = Highscore;
                break;
            }
        }
    }else{
        for(unsigned i(1); i < 10; i+=1){
            if(Highscore >= St.InfiniteModeHighScore.find(to_string(i))->second){
                for(unsigned j (8); j >= i; j-=1){
                    St.InfiniteModeHighScore.find(to_string(j+1))->second = St.InfiniteModeHighScore.find(to_string(j))->second;
                }
                St.InfiniteModeHighScore[to_string(i)] = Highscore;
                break;
            }
        }
    }
    ApplySettings(St);
}

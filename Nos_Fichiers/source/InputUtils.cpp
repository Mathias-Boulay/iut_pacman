#include "InputUtils.h"

/* Use this variable to remember original terminal attributes. */
struct termios saved_attributes;

void ResetRawInput(){
    tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void SetRawInput(const unsigned TimePressure){
    struct termios tattr;

    /* Make sure stdin is a terminal. */
    if (!isatty (STDIN_FILENO)){
        fprintf (stderr, "Not a terminal.\n");
        exit (EXIT_FAILURE);
      }

    /* Save the terminal attributes so we can restore them later. */
    tcgetattr (STDIN_FILENO, &saved_attributes);
    atexit (ResetRawInput);

    /* Set the funny terminal modes. */
    tcgetattr (STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
    tattr.c_cc[VMIN] = TimePressure == 0 ? 1 : 0; //No inputs can be sent during a specific time frame
    tattr.c_cc[VTIME] = TimePressure; //0 represents no pressure.
    tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

char ReadKeyboardInput(const unsigned TimePressure){
    char input;

    SetRawInput(TimePressure);
    while(true){
        read(STDIN_FILENO, &input, 1);
        if(isprint(input) || input == '\0'){
            ResetRawInput();
            return input;
        }
    }
}

char ReadSpecificKeyboardInput(std::vector<char> Keys,  const unsigned TimePressure){
    char input;

    if(TimePressure != 0) Keys.push_back('\0');

    SetRawInput(TimePressure);
    while (true) {
         read(STDIN_FILENO, &input, 1);
         for(const char &validInput : Keys){
             if(input == validInput){
                 ResetRawInput();
                 return input;
             }
         }
    }
}

#include "InputUtils.h"

/* Use this variable to remember original terminal attributes. */
struct termios saved_attributes;

void ResetRawInput(){
    tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void SetRawInput(){
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
    tattr.c_cc[VMIN] = 1;
    tattr.c_cc[VTIME] = 0;
    tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}

char ReadKeyboardInput(){
    char input;

    SetRawInput();
    while(true){
        read(STDIN_FILENO, &input, 1);
        if(isprint(input)){
            ResetRawInput();
            return input;
        }
    }
}

char ReadSpecificKeyboardInput(const std::vector<char> Keys){
    char input;

    SetRawInput();
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

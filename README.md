
# IUT_PACMAN [M1103]
Main repository for a little project that me and my unfortunate teammates have been tasked to deal with.

Due to the constraints of the project, all generated documentation is in French, however the whole codebase bein in English, it should be pretty straightforward to understand it.

## Features
- Colored Unicode characters
- 14 maps
- Leaderboard system
- Changeable controls
- Might be playable over SSH terminal.
- Input buffering   &sup1;
- Elegant input system.  &sup1;

  
&sup1; Only since the Day 1 patch.


## Config files
Configuration files are generated near the executable when a setting is changed. They do not share a common path like maps, it allows configs on a per profile basis (Debug, Release);

## Building
The project was realized QTCreator 5.12.X in Lubuntu 20.04.
When building the project, make sure your build path isn't fucked up, otherwise the game won't be able to access map files.


License
----

See the LICENSE file at the root of the repository

# chess

A tool I created that allows me to play chess with myself.

This is cross-platform except for the console clear method in [this file](src/view/console_view/ConsoleSession.cpp). Just implement your own and you're good to go.

TODO: There might be undefined behavior that causes segfaults occasionally, but I'm not sure. It didn't happen in a while so I guess it's ok.
Update: Turns out the segfault happens when entering the next command while the program is not ready yet.
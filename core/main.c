#include <stdio.h>
#include "../command/parser.h"
#include "../network/client.h"
#include "../network/protocol.h"

#define VERSION "0.0.1"


int main() {
    printf("      ___           ___           ___           ___           ___           ___     \n"
           "     /\\  \\         /\\  \\         /\\  \\         /\\__\\         /\\  \\         /\\__\\    \n"
           "    /::\\  \\       /::\\  \\        \\:\\  \\       /:/  /        /::\\  \\       /:/  /    \n"
           "   /:/\\:\\  \\     /:/\\:\\  \\        \\:\\  \\     /:/  /        /:/\\:\\  \\     /:/__/     \n"
           "  /:/  \\:\\__\\   /::\\~\\:\\  \\       /::\\  \\   /:/  /  ___   /::\\~\\:\\  \\   /::\\__\\____ \n"
           " /:/__/ \\:|__| /:/\\:\\ \\:\\__\\     /:/\\:\\__\\ /:/__/  /\\__\\ /:/\\:\\ \\:\\__\\ /:/\\:::::\\__\\\n"
           " \\:\\  \\ /:/  / \\/__\\:\\/:/  /    /:/  \\/__/ \\:\\  \\ /:/  / \\/__\\:\\/:/  / \\/_|:|~~|~   \n"
           "  \\:\\  /:/  /       \\::/  /    /:/  /       \\:\\  /:/  /       \\::/  /     |:|  |    \n"
           "   \\:\\/:/  /        /:/  /     \\/__/         \\:\\/:/  /        /:/  /      |:|  |    \n"
           "    \\::/__/        /:/  /                     \\::/  /        /:/  /       |:|  |    \n"
           "     ~~            \\/__/                       \\/__/         \\/__/         \\|__|    \n\nClient v %s\n\n",
           VERSION);

    //  printf("Welcome to Dati client, use the command 'help' for further information \n\n");

    begin_connection();


    /**for (;;) {
        printf("Dati > ");

        char line[256];
        fgets(line, 256, stdin);
        parse(line);
    } **/

}



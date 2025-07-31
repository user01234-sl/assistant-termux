#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//values
#define MAX_INPUT 150
#define MAX_CMD 50
#define MAX_ARG 100
//welcom_screen
void welcome_screen() {
    FILE *file;
    char text[500];
    file = fopen("./.data/screen.txt", "r");

    if (file == NULL) {
        printf("\033[41m (Error opening file) \n\033[0m\n");
        return;
    } else {
        while (fgets(text, 100, file) != NULL) {
            printf("\033[1m %s\033[0m", text);
        }
        fclose(file);
        printf("\n");
    }
}
//colors
void colors() {
    const char* names[] = {
        "Reset", "Black", "Red", "Green", "Yellow", "Blue", "Magenta", "Cyan", "White",
        "Bright Black", "Bright Red", "Bright Green", "Bright Yellow", "Bright Blue",
        "Bright Magenta", "Bright Cyan", "Bright White"
    };
    const char* codes[] = {
        "\\033[0m",  "\\033[30m", "\\033[31m", "\\033[32m", "\\033[33m",
        "\\033[34m", "\\033[35m", "\\033[36m", "\\033[37m",
        "\\033[90m", "\\033[91m", "\\033[92m", "\\033[93m",
        "\\033[94m", "\\033[95m", "\\033[96m", "\\033[97m"
    };
    printf("Text Color Escape Codes:\n\n");
    for (int i = 0; i < 17; i++) {
        printf("%-16s : %s\n", names[i], codes[i]);
    }
    printf("\nOther:\n");
    printf("Bold               : \\033[1m\n");
    printf("Underline          : \\033[4m\n");
    printf("Reverse/Invert     : \\033[7m\n");
    printf("Background Red     : \\033[41m\n");
    return;
}
//execute
void execute(char *cmd, char *arg) {
    char open_url[150], run_c[150], run_kt[150], run_py[150], run_sh[150], run_else[150];
    char name_c[40], name_kt[40];
    char pkg_s[100], pkg_i[100], pkg_r[100], pkg_v[50];
    //process
    if (strcmp(cmd, "web") == 0) {
        sprintf(open_url, "w3m %s", arg);
        system(open_url);
        exit (0);
    } else if (strcmp(cmd, "c") == 0) {
        printf("\n Output programme name: ");
        scanf(" %s", name_c);
        sprintf(run_c, "clang %s -o %s", arg, name_c);
        if (system(run_c) != 0) {
            printf(" [Error]\n");
            return;
        }
        printf(" [Finish]\n");
    } else if (strcmp(cmd, "kt") == 0) {
        printf("\n Output file name(with '.jar'): ");
        scanf(" %s", name_kt);
        sprintf(run_kt, "kotlinc %s -include-runtime -d %s", arg, name_kt);
        if (system(run_kt) != 0) {
            printf(" [Error]\n");
            return;
        }
        printf(" [Finish]\n");
    } else if (strcmp(cmd, "py") == 0) {
        sprintf(run_py, "chmod +x %s && python %s", arg, arg);
        if (system(run_py) != 0) {
            printf(" [Error]\n");
            return;
        }
        printf(" [Finish]\n");
        exit (0);
    } else if (strcmp(cmd, "sh") == 0) {
        sprintf(run_sh, "chmod +x %s && %s", arg, arg);
        if (system(run_sh) != 0) {
            printf(" [Error]\n");
            return;
        }
        printf(" [Finish]\n");
        exit (0);
    } else if (strcmp(cmd, "pkg-search") == 0) {
        sprintf(pkg_s, "pkg search %s", arg);
        system(pkg_s);
    } else if (strcmp(cmd, "install") == 0) {
        sprintf(pkg_i, "pkg install %s", arg);
        system(pkg_i);
        sprintf(pkg_v, " %s --version", arg);
        system(pkg_v);
    } else if (strcmp(cmd, "uninstall") == 0) {
        sprintf(pkg_r, "pkg uninstall %s", arg);
    } else if (strcmp(cmd, "pkg-list") == 0) {
        system("clear");
        system("pkg list-installed");
    } else if (strcmp(cmd, "update") == 0) {
        printf("\n Upgrading... \n");
        system("pkg update && upgrade");
        exit (0);
    } else if (strcmp(cmd, "systeminfo") == 0) {
        system("neofetch --off");
    } else if (strcmp(cmd, "hi") == 0 || strcmp(cmd,  "hello") == 0) {
        printf("> Hi 👋\n");
    } else if (strcmp(cmd, "colors") == 0) {
        colors();
    } else if (strcmp(cmd, "time") == 0) {
        system("date '+%A, %d %B %Y - %I:%M %p'");
    } else if (strcmp(cmd, "clear") == 0) {
        system("clear");
    } else {
        printf("\n\033[41m [?] cannot understand.");
        printf(" %s ", cmd);
        printf("\033[0m\n");
    }
}
//help
void help() {
    printf("\n\033[1;33m");
    printf("\n =====[ Help ]===== \n");
    printf("\n exit = exit the programe.");
    printf("\n help = print this message.");
    printf("\n time = print date and time.");
    printf("\n clear = clear the screen.");
    printf("\n pkg-search <name> = search termux packages.");
    printf("\n install <name> = install package on termux.");
    printf("\n uninstall <name> = uninstall package on termux.");
    printf("\n pkg-list = list all installed packages.");
    printf("\n update = update & upgrade installed packages on termux.");
    printf("\n systeminfo = print device information.");
    printf("\n colors = print ANCII escape color codes.");
    printf("\n web <url> = open url in browser(w3m).");
    printf("\n c <file path> = compile the given c file.");
    printf("\n kt <file path> = compile the given kotlin file.");
    printf("\n py <file path> = execute the given python file.");
    printf("\n sh <file path> = execute the given shell script file.");
    printf("\n ----- ");
    printf("\n * PATH: ");
    printf("\n  '~/' or 'HOME/' - this is your home folder.\n  you can enter the path from here");
    printf("\n * if you dont know were your file,\n  run 'pwd' on terminal to display the full path.");
    printf("\n * you can't run Termux commands.");
    printf("\n\033[0;31m (end) \033[0m\n");
    return;
}
//main
int main() {
    char input[MAX_INPUT];
    char cmd[MAX_CMD];
    char arg[MAX_ARG];
    //disply
    system("clear");
    welcome_screen();
    while(1) {
        printf("\n\033[1;34m");
        printf("[|]>\033[0m ");
        fgets(input, MAX_INPUT, stdin);
        input[strcspn(input, "\n")] = 0;
        //execute
        if (strcmp(input, "exit") == 0) {
            printf("\n\033[30;42m logout...\033[0m\n");
            break;
        } else if (strcmp(input, "help") == 0) {
            help();
        }
        sscanf(input, "%49s %99s", cmd, arg);
        if (strlen(cmd) > 0 && strlen(arg) > 0) {
            if (strcmp(cmd, "exit") != 0 && strcmp(cmd, "help") != 0) {
                execute(cmd, arg);
            } else {
                continue;
            }
        }
    }
    return 0;
}
//assistant.exe
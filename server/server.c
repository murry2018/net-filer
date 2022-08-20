#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

typedef int bool;
const int _t = 1;
const int _f = 0;

#define STR_EQ(x, y) !strcmp(x, y)
#define STR_EQN(x, y, n) !strncmp(x, y, n)

const int default_port = 5000;

static const int __help_wanted = -2;
static const int __parse_error = -1;
static const int __not_designated = 0;

static int parse_port(char* s) {
    if (!s)
        return __parse_error;
    int res=0;
    for (int i = 0; i < 6; i++) {
        int c = s[i];
        if (!c)
            break;
        if (!isnumber(c))
            return __parse_error;
        res = res*10 + c - '0';
    }
    if (res > 65535)
        return __parse_error;
    return res;
}

int get_port(int argc, char* argv[]) {
    bool is_pending = _f;
    for (int i = 1; i < argc; i++) {
        if (is_pending) {
            return parse_port(argv[i]);
        }

        if (STR_EQ(argv[i], "-p")) {
            is_pending = _t;
        } else if (STR_EQN(argv[i], "--port=", 7)) {
            return parse_port(argv[i]+7);
        } else { // invalid option: User doesn't know how to use
            return __help_wanted;
        }
    }
    return __not_designated;
}

void show_usage(char* prog_name) {
    char* usage = "\
usage:\n\
  %s -p <port number>\n\
  %s --port=<port number>\n";
    printf(usage, prog_name, prog_name);
}

void handle_arg_error(char* prog_name, int port) {
    switch(port) {
    case __help_wanted:
        show_usage(prog_name);
        exit(0);
    case __parse_error:
        printf("Could not understand port number:\n\
  port number should be a number(1-65535).\n");
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    int port = get_port(argc, argv);
    handle_arg_error(argv[0], port);
    if (port == 0)
        port = default_port;
    printf("port number is %d\n", port);
    return 0;
}


static int enableRawMode(void) {
#ifdef _WIN32
    if (!console_in) {
        console_in = GetStdHandle(STD_INPUT_HANDLE);
        console_out = GetStdHandle(STD_OUTPUT_HANDLE);

        GetConsoleMode(console_in, &oldMode);
        SetConsoleMode(console_in,
                       oldMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT));
    }
    return 0;
#else
    struct termios raw;

    if (!isatty(0))
        goto fatal;
    if (!atexit_registered) {
        atexit(linenoiseAtExit);
        atexit_registered = 1;
    }
    if (tcgetattr(0, &orig_termios) == -1)
        goto fatal;

    raw = orig_termios;


    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);


    raw.c_cflag |= (CS8);


    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);


    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;


    if (tcsetattr(0, TCSADRAIN, &raw) < 0)
        goto fatal;
    rawmode = 1;
    return 0;

fatal:
    errno = ENOTTY;
    return -1;
#endif
}

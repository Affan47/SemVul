screen_filter_match(char *s) {
    int r;
    if(options.screenfilter == NULL) {
        return 1;
    }

    r = regexec(&preg, s, 0, NULL, 0);
    if(r == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

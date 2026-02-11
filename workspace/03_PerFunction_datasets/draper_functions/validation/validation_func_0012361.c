str2pattern(char *s) {
    char *a = s;
    char *n = s;

    while (1) {
        char c = *a++;

        if (c==ESC) {
            c = *a++;
            if (c==ESC) {
                *n++ = ESC;
            }
            else if (c=='n') {
                *n++ = '\n';
            }
            else {
                *n++ = ESC;
                *n++ = c;
            }
        }
        else {
            *n++ = c;
            if (!c) {
                break;
            }
        }
    }
}

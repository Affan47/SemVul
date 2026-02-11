indent(int n) {
    static const char *buf = "                                            ";
    static int len = strlen(buf);
    return buf + len - n*3;
}

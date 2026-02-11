open_script_file(const char * script_name) {
    if (script_name == NULL || (infile = fopen(script_name, "r")) == NULL) {
        if (script_name == NULL) script_name = "<null>";
        fprintf(stderr, "Error: Cannot open script file %s\n", script_name);
        exit(1);
    }
}

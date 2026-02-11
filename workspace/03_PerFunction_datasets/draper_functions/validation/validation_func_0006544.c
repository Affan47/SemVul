myyylex (void) {
    int rv = myyylex ();

    fprintf (stderr, "returning %d\n", rv);
    if (rv == T_id)
        fprintf (stderr, "string val is %s\n", yylval.s);
    return rv;
}

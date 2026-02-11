yyerror (char *fmt, char *s) {
    if (syntax_errors++)
        return;
    fprintf (stderr, "graph parser: ");
    fprintf (stderr, fmt, s);
    fprintf (stderr, " near line %d\n", line_number);
    error_context ();
}

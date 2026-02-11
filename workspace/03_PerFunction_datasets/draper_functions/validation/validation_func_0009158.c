append_output(STRPTR text)
{
    EXPSTR *outstr = (EXPSTR *) dln_data(dll_last(outlist));


    if ((estrlen(outstr) + strlen(text) + 1) > OUTPUT_STEPSIZE) {


#if DEBUG_HSC_OUTPUT
        fprintf(stderr, DHSC "new string after %lu/%lu chars\n",
                estrlen(outstr), OUTPUT_STEPSIZE);
#endif
        outstr = init_estr(OUTPUT_STEPSIZE);
        app_dlnode(outlist, (APTR) outstr);

    }

    app_estr(outstr, text);
}

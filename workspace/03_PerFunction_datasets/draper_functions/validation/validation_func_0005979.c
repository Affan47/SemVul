arg_print_option(FILE *fp, const char *shortopts, const char *longopts, const char *datatype, const char *suffix)
    {
    char syntax[200]="";
    suffix = suffix ? suffix : "";


    arg_cat_optionv(syntax,sizeof(syntax),shortopts,longopts,datatype,0,"|");

    fputs(syntax,fp);
    fputs(suffix,fp);
    }

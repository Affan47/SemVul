verify_server_name(char *given, char **expanded, char **error, BUILDER_ARG *fcc, int *mangled)
{
    char *tmp;

    tmp = cpystr(given ? given : "");
    removing_leading_and_trailing_white_space(tmp);

    if(*tmp){


    }

    if(expanded)
      *expanded = tmp;
    else
      fs_give((void **)&tmp);

    if(error)
      *error = cpystr("");

    return 0;
}

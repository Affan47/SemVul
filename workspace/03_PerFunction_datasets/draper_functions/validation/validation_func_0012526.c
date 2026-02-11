irplib_dfs_table_convert(cpl_table               * self,
                         cpl_frameset            * allframes,
                         const cpl_frameset      * useframes,
                         int                       maxlinelen,
                         char                      commentchar,
                         const char              * product_name,
                         const char              * procatg,
                         const cpl_parameterlist * parlist,
                         const char              * recipe_name,
                         const cpl_propertylist  * mainlist,
                         const cpl_propertylist  * extlist,
                         const char              * remregexp,
                         const char              * instrume,
                         const char              * pipe_id,
                         cpl_boolean (*table_set_row)
                         (cpl_table *, const char *, int,
                          const cpl_frame *,
                          const cpl_parameterlist *),
                         cpl_error_code (*table_check)
                         (cpl_table *,
                          const cpl_frameset *,
                          const cpl_parameterlist *))
{

    const char       * filename;
    cpl_propertylist * applist    = NULL;
    cpl_errorstate     prestate   = cpl_errorstate_get();
    cpl_error_code     error;

    cpl_ensure_code(self         != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(allframes    != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(useframes    != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(procatg      != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(parlist      != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(recipe_name  != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(instrume     != NULL, CPL_ERROR_NULL_INPUT);
    cpl_ensure_code(pipe_id      != NULL, CPL_ERROR_NULL_INPUT);

    cpl_ensure_code(!irplib_table_read_from_frameset(self, useframes,
                                                     maxlinelen,
                                                     commentchar,
                                                     parlist,
                                                     table_set_row),
                    cpl_error_get_code());

    if (table_check != NULL && (table_check(self, useframes, parlist) ||
                                !cpl_errorstate_is_equal(prestate))) {
        return cpl_error_set_message(cpl_func, cpl_error_get_code(),
                                     "Consistency check of table failed");
    }

    filename = product_name != NULL
        ? product_name : cpl_sprintf("%s" CPL_DFS_FITS, recipe_name);

    applist = mainlist == NULL
        ? cpl_propertylist_new() : cpl_propertylist_duplicate(mainlist);

    error = cpl_propertylist_append_string(applist, "INSTRUME", instrume);

    if (!error)
        error = irplib_dfs_save_table(allframes, parlist, useframes, self,
                                      extlist, recipe_name, procatg, applist,
                                      remregexp, pipe_id, filename);

    cpl_propertylist_delete(applist);
    if (filename != product_name) cpl_free((char*)filename);


    cpl_ensure_code(!error, error);

    return CPL_ERROR_NONE;

}

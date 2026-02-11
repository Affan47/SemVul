kmo_dfs_get_parameter_double(cpl_parameterlist *parlist,
                                    const char *name)
{
    cpl_parameter   *param      = NULL;
    double          ret_val     = -DBL_MAX;

    KMO_TRY
    {
        KMO_TRY_ASSURE((parlist != NULL) && (name != NULL),
                       CPL_ERROR_NULL_INPUT,
                       "Not all input data provided!");

        KMO_TRY_EXIT_IF_NULL(
            param = cpl_parameterlist_find(parlist, name));

        KMO_TRY_ASSURE(cpl_parameter_get_type(param) == CPL_TYPE_DOUBLE,
                       CPL_ERROR_INVALID_TYPE,
                       "Unexpected type for parameter %s: it should be double",
                       name);

        KMO_TRY_EXIT_IF_ERROR(
            ret_val = cpl_parameter_get_double(param));
    }
    KMO_CATCH
    {
        KMO_CATCH_MSG();

        ret_val = -DBL_MAX;
    }

    return ret_val;
}

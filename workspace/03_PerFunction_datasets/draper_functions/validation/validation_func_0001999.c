epr_free_param_elem(EPR_SParamElem* param_elem)
{

    if (param_elem == NULL)
        return;
    epr_free_string(param_elem->param_name);
    param_elem->param_name = NULL;
    param_elem->param_value = 0;

    free(param_elem);
    return;
}

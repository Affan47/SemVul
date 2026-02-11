zparse_dsc_comments(i_ctx_t *i_ctx_p)
{
#define MAX_DSC_MSG_SIZE (DSC_LINE_LENGTH + 4)
    os_ptr const opString = osp;
    os_ptr const opDict = opString - 1;
    uint ssize;
    int comment_code, code;
    char dsc_buffer[MAX_DSC_MSG_SIZE + 2];
    const cmdlist_t *pCmdList = DSCcmdlist;
    const char * const *pBadList = BadCmdlist;
    ref * pvalue;
    dsc_data_t * dsc_state = NULL;
    dict_param_list list;


    check_type(*opString, t_string);
    check_dict_write(*opDict);
    ssize = r_size(opString);
    if (ssize > MAX_DSC_MSG_SIZE)
        ssize = MAX_DSC_MSG_SIZE;


    code = dict_find_string(opDict, dsc_dict_name, &pvalue);
    if (code < 0)
        return code;
    dsc_state = r_ptr(pvalue, dsc_data_t);


    memcpy(dsc_buffer, opString->value.bytes, ssize);
    dsc_buffer[ssize] = 0x0d;
    dsc_buffer[ssize + 1] = 0;


    while (*pBadList && strncmp(*pBadList, dsc_buffer, strlen(*pBadList)))
        pBadList++;
    if (*pBadList) {
        comment_code = 0;
        if (dsc_buffer[2] == 'B') {
            dsc_state->document_level++;
        } else if (dsc_state->document_level > 0) {
            dsc_state->document_level--;
        }
    }
    else if (dsc_state->document_level > 0) {
       comment_code = 0;
    } else {


        comment_code = dsc_scan_data(dsc_state->dsc_data_ptr, dsc_buffer, ssize + 1);
        if_debug1m('%', imemory, "[%%].parse_dsc_comments: code = %d\n", comment_code);


        if (comment_code < 0)
            comment_code = 0;
    }


    while (pCmdList->code && pCmdList->code != comment_code )
        pCmdList++;
    if (pCmdList->dsc_proc) {
        code = dict_param_list_write(&list, opDict, NULL, iimemory);
        if (code < 0)
            return code;
        code = (pCmdList->dsc_proc)((gs_param_list *)&list, dsc_state->dsc_data_ptr);
        iparam_list_release(&list);
        if (code < 0)
            return code;
    }


    return name_enter_string(imemory, pCmdList->comment_name, opString);
}

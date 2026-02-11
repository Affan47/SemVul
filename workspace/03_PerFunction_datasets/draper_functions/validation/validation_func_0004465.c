compile_and_search(
    const char *patstr, size_t patlen,
    const char *entirestr, const char *searchstr, size_t searchlen,
    int *result_len)
{
    re_compiled_pattern_base pat;


    group_cnt_ = 0;


    clear_group_regs(regs_);


    if (parser_->compile(patstr, patlen, &pat) != RE_STATUS_SUCCESS)
        return -1;


    group_cnt_ = pat.group_cnt;


    return search(entirestr, searchstr, searchlen,
                  &pat, parser_->tuple_arr_, &pat.machine,
                  regs_, result_len);
}

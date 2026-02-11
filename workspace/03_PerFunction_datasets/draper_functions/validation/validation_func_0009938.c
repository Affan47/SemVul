add_result(char* result_name) {
    SCHED_RESULT_ITEM result;
    result.id = 0;
    strcpy2(result.queried_name, result_name);
    results.push_back(result);
    return 0;
}

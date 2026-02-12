parse_int(const char *val_str, int64_t min, int64_t max, int base, int64_t *ret, struct lyd_node *node)
{
    char *strptr;

    assert(node);

    if (!val_str || !val_str[0]) {
        goto error;
    }


    errno = 0;
    strptr = NULL;


    *ret = strtoll(val_str, &strptr, base);
    if (errno || (*ret < min) || (*ret > max)) {
        goto error;
    } else if (strptr && *strptr) {
        while (isspace(*strptr)) {
            ++strptr;
        }
        if (*strptr) {
            goto error;
        }
    }

    return EXIT_SUCCESS;

error:
    LOGVAL(node->schema->module->ctx, LYE_INVAL, LY_VLOG_LYD, node, val_str ? val_str : "", node->schema->name);
    return EXIT_FAILURE;
}

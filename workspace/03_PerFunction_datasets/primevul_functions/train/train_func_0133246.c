sds sdstemplate(const char *template, sdstemplate_callback_t cb_func, void *cb_arg)
{
    sds res = sdsempty();
    const char *p = template;

    while (*p) {

        const char *sv = strchr(p, '{');
        if (!sv) {

            res = sdscat(res, p);
            break;
        } else if (sv > p) {

            res = sdscatlen(res, p, sv - p);
        }

        sv++;
        if (!*sv) goto error;
        if (*sv == '{') {

            p = sv + 1;
            res = sdscat(res, "{");
            continue;
        }

        const char *ev = strchr(sv, '}');
        if (!ev) goto error;

        sds varname = sdsnewlen(sv, ev - sv);
        sds value = cb_func(varname, cb_arg);
        sdsfree(varname);
        if (!value) goto error;

        res = sdscat(res, value);
        sdsfree(value);
        p = ev + 1;
    }

    return res;

error:
    sdsfree(res);
    return NULL;
}
}
}

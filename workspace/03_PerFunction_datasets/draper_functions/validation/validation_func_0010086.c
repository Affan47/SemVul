xlator_option_validate_double (xlator_t *xl, const char *key, const char *value,
                               volume_option_t *opt, char **op_errstr)
{
        int          ret = -1;
        char         errstr[256];
        double       val = 0.0;


        if (gf_string2double (value, &val) != 0) {
                snprintf (errstr, 256,
                          "invalid double \"%s\" in \"option %s\"",
                          value, key);
                gf_log (xl->name, GF_LOG_ERROR, "%s", errstr);
                goto out;
        }

        if (val < 0.0) {
                snprintf (errstr, 256,
                          "invalid double \"%s\" in \"option %s\"",
                          value, key);
                gf_log (xl->name, GF_LOG_ERROR, "%s", errstr);
                goto out;
        }

        if ((opt->min == 0) && (opt->max == 0)) {
                gf_log (xl->name, GF_LOG_DEBUG,
                        "no range check required for 'option %s %s'",
                        key, value);
                ret = 0;
                goto out;
        }

        ret = 0;
out:
        if (ret && op_errstr)
                *op_errstr = gf_strdup (errstr);
        return ret;
}

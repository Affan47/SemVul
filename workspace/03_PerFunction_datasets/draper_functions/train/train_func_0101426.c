xlator_set_type_virtual (xlator_t *xl, const char *type)
{
        GF_VALIDATE_OR_GOTO ("xlator", xl, out);
        GF_VALIDATE_OR_GOTO ("xlator", type, out);

        xl->type = gf_strdup (type);

        if (xl->type)
                return 0;

out:
        return -1;
}

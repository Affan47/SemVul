mq_dict_set_contribution (xlator_t *this, dict_t *dict,
                          loc_t *loc)
{
        int32_t ret              = -1;
        char    contri_key [512] = {0, };

        GF_VALIDATE_OR_GOTO ("marker", this, out);
        GF_VALIDATE_OR_GOTO ("marker", dict, out);
        GF_VALIDATE_OR_GOTO ("marker", loc, out);
        GF_VALIDATE_OR_GOTO ("marker", loc->parent, out);

        GET_CONTRI_KEY (contri_key, loc->parent->gfid, ret);
        if (ret < 0) {
                ret = -1;
                goto out;
        }

        ret = dict_set_int64 (dict, contri_key, 0);
        if (ret < 0) {
                gf_log (this->name, GF_LOG_WARNING,
                        "unable to set dict value on %s.",
                        loc->path);
                goto out;
        }

        ret = 0;
out:
        return ret;
}

json_append_number(lua_State *l, strbuf_t *json, int index,
                               json_config_t *cfg)
{
    double num = lua_tonumber(l, index);

    if (cfg->encode_refuse_badnum && (isinf(num) || isnan(num)))
        json_encode_exception(l, cfg, index, "must not be NaN or Inf");


    strbuf_append_fmt(json, 32, cfg->number_fmt, num);
}

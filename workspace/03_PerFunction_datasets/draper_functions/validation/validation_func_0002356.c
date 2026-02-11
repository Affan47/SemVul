evaluate(string_ty *path_unres, string_ty *path,
    string_ty *path_res, struct stat *st) const
{
    rpt_value::pointer v1 =
        get_left()->evaluate(path_unres, path, path_res, st);
    rpt_value::pointer v1s = rpt_value::stringize(v1);
    rpt_value_string *v1sp = dynamic_cast<rpt_value_string *>(v1s.get());

    rpt_value::pointer v2 =
        get_right()->evaluate(path_unres, path, path_res, st);
    rpt_value::pointer v2s = rpt_value::stringize(v2);
    rpt_value_string *v2sp = dynamic_cast<rpt_value_string *>(v2s.get());

    if (!v1sp || !v2sp)
    {
	sub_context_ty sc;
	sc.var_set_charstar("Name1", v1->name());
	sc.var_set_charstar("Name2", v2->name());
	nstring s(sc.subst_intl(i18n("illegal match ($name1 ~ $name2)")));
	return rpt_value_error::create(s);
    }
    return
        rpt_value_boolean::create
        (
            gmatch(v1sp->query().c_str(), v2sp->query().c_str())
        );
}

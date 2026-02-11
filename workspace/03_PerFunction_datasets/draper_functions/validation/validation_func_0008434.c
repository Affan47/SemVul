subs(const map_basic_basic &subs_dict) const
{
    RCP<const Mul> self = rcp_const_cast<Mul>(rcp(this));
    auto it = subs_dict.find(self);
    if (it != subs_dict.end())
        return it->second;

    RCP<const Number> coef = coef_;
    map_basic_basic d;
    for (auto &p: dict_) {
        RCP<const Basic> factor_old = pow(p.first, p.second);
        RCP<const Basic> factor = factor_old->subs(subs_dict);
        if (factor == factor_old) {
            Mul::dict_add_term(d, p.second, p.first);
        } else if (is_a<Integer>(*factor) &&
                rcp_static_cast<const Integer>(factor)->is_zero()) {
            return zero;
        } else if (is_a_Number(*factor)) {
            imulnum(outArg(coef), rcp_static_cast<const Number>(factor));
        } else if (is_a<Mul>(*factor)) {
            RCP<const Mul> tmp = rcp_static_cast<const Mul>(factor);
            imulnum(outArg(coef), tmp->coef_);
            for (auto &q: tmp->dict_) {
                Mul::dict_add_term(d, q.second, q.first);
            }
        } else {
            RCP<const Basic> exp, t;
            Mul::as_base_exp(factor, outArg(exp), outArg(t));
            Mul::dict_add_term(d, exp, t);
        }
    }
    return Mul::from_dict(coef, d);
}

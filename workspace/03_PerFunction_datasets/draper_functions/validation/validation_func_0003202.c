parse_saturating(const String &str, uint32_t &result, const ArgContext &)
{
    int power, factor;
    const char *unit_end = UnitArg(seconds_units, seconds_prefixes).parse(str.begin(), str.end(), power, factor);

    value_type ix;
    uint32_t fx;
    const char *xend = parse_fraction(str.begin(), unit_end,
				      false, power + fraction_digits, ix, fx, status);
    if (status == status_inval || xend != unit_end) {
	status = status_inval;
	return false;
    }
    if (uint32_t(ix) != ix)
	status = status_range;
    ix = multiply_factor(ix, fx, factor, status);
    if (status == status_range)
	ix = integer_traits<uint32_t>::const_max;
    result = ix;
    return true;
}

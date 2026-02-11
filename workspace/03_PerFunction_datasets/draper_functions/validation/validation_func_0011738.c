wi_number_string(wi_number_t *number) {
	if(_wi_number_is_float(number))
		return wi_string_with_format(WI_STR("%f"), wi_number_double(number));
	else
		return wi_string_with_format(WI_STR("%lld"), wi_number_int64(number));
}

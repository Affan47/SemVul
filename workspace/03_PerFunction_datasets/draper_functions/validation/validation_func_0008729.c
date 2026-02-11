check_type_number(object *p)
{
	enum type t;

	while ((t = type_of(*p)) != t_fixnum && t != t_bignum &&
	       t != t_ratio && t != t_shortfloat && t != t_longfloat &&
	       t != t_complex)
		*p = wrong_type_argument(sLnumber, *p);
}

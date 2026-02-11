cl_F_extendsqrtx (const cl_F& x)
{


	floatcase(x
	,	return cl_SF_to_DF(x);
	,	return cl_FF_to_DF(x);
	,	return cl_DF_to_LF(x,ceiling(73,intDsize));
	,	return extend(x,cl_LF_len_incsqrtx(TheLfloat(x)->len));
	);
}

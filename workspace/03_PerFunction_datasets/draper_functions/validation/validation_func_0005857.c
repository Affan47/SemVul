gamma_function (double x)
{
    double ret = cephes_gamma(x);

    if (get_cephes_errno()) {
	ret = NADBL;
    }

    return ret;
}

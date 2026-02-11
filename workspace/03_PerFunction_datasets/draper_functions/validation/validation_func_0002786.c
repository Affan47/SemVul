gretl_is_simple_OLS (const MODEL *pmod)
{
    if (pmod->ci == OLS &&
	pmod->list != NULL &&
	pmod->list[0] == 3 &&
	pmod->list[2] == 0) {
	return 1;
    } else {
	return 0;
    }
}

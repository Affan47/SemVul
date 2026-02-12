static inline pte_t native_ptep_get_and_clear(pte_t *ptep)
{
	pte_t res;


	res.pte_low = xchg(&ptep->pte_low, 0);
	res.pte_high = ptep->pte_high;
	ptep->pte_high = 0;

	return res;
}

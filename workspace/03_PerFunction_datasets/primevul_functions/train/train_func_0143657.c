static inline void sdma_update_tail(struct sdma_engine *sde, u16 tail)
{

	smp_wmb();
	writeq(tail, sde->tail_csr);
}

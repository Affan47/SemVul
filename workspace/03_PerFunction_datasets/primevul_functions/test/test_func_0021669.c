static inline void xt_write_recseq_end(unsigned int addend)
{

	smp_wmb();
	__this_cpu_add(xt_recseq.sequence, addend);
}

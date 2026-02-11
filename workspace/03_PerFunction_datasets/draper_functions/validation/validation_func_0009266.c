setup_vector_irq(int cpu)
{
	int irq;

	lockdep_assert_held(&vector_lock);


	for (irq = 0; irq < nr_legacy_irqs(); irq++)
		per_cpu(vector_irq, cpu)[ISA_IRQ_VECTOR(irq)] = irq_to_desc(irq);

	__setup_vector_irq(cpu);
}

i40e_clear_interrupt_scheme(struct i40e_pf *pf)
{
	int i;

	i40e_stop_misc_vector(pf);
	if (pf->flags & I40E_FLAG_MSIX_ENABLED) {
		synchronize_irq(pf->msix_entries[0].vector);
		free_irq(pf->msix_entries[0].vector, pf);
	}

	i40e_put_lump(pf->irq_pile, 0, I40E_PILE_VALID_BIT-1);
	for (i = 0; i < pf->num_alloc_vsi; i++)
		if (pf->vsi[i])
			i40e_vsi_free_q_vectors(pf->vsi[i]);
	i40e_reset_interrupt_capability(pf);
}

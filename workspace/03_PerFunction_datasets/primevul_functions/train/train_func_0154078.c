static int i40e_init_msix(struct i40e_pf *pf)
{
	struct i40e_hw *hw = &pf->hw;
	int cpus, extra_vectors;
	int vectors_left;
	int v_budget, i;
	int v_actual;
	int iwarp_requested = 0;

	if (!(pf->flags & I40E_FLAG_MSIX_ENABLED))
		return -ENODEV;


	vectors_left = hw->func_caps.num_msix_vectors;
	v_budget = 0;


	if (vectors_left) {
		v_budget++;
		vectors_left--;
	}


	cpus = num_online_cpus();
	pf->num_lan_msix = min_t(int, cpus, vectors_left / 2);
	vectors_left -= pf->num_lan_msix;


	if (pf->flags & I40E_FLAG_FD_SB_ENABLED) {
		if (vectors_left) {
			pf->num_fdsb_msix = 1;
			v_budget++;
			vectors_left--;
		} else {
			pf->num_fdsb_msix = 0;
		}
	}


	if (pf->flags & I40E_FLAG_IWARP_ENABLED) {
		iwarp_requested = pf->num_iwarp_msix;

		if (!vectors_left)
			pf->num_iwarp_msix = 0;
		else if (vectors_left < pf->num_iwarp_msix)
			pf->num_iwarp_msix = 1;
		v_budget += pf->num_iwarp_msix;
		vectors_left -= pf->num_iwarp_msix;
	}


	if (pf->flags & I40E_FLAG_VMDQ_ENABLED) {
		if (!vectors_left) {
			pf->num_vmdq_msix = 0;
			pf->num_vmdq_qps = 0;
		} else {
			int vmdq_vecs_wanted =
				pf->num_vmdq_vsis * pf->num_vmdq_qps;
			int vmdq_vecs =
				min_t(int, vectors_left, vmdq_vecs_wanted);


			if (vectors_left < vmdq_vecs_wanted) {
				pf->num_vmdq_qps = 1;
				vmdq_vecs_wanted = pf->num_vmdq_vsis;
				vmdq_vecs = min_t(int,
						  vectors_left,
						  vmdq_vecs_wanted);
			}
			pf->num_vmdq_msix = pf->num_vmdq_qps;

			v_budget += vmdq_vecs;
			vectors_left -= vmdq_vecs;
		}
	}


	extra_vectors = min_t(int, cpus - pf->num_lan_msix, vectors_left);
	pf->num_lan_msix += extra_vectors;
	vectors_left -= extra_vectors;

	WARN(vectors_left < 0,
	     "Calculation of remaining vectors underflowed. This is an accounting bug when determining total MSI-X vectors.\n");

	v_budget += pf->num_lan_msix;
	pf->msix_entries = kcalloc(v_budget, sizeof(struct msix_entry),
				   GFP_KERNEL);
	if (!pf->msix_entries)
		return -ENOMEM;

	for (i = 0; i < v_budget; i++)
		pf->msix_entries[i].entry = i;
	v_actual = i40e_reserve_msix_vectors(pf, v_budget);

	if (v_actual < I40E_MIN_MSIX) {
		pf->flags &= ~I40E_FLAG_MSIX_ENABLED;
		kfree(pf->msix_entries);
		pf->msix_entries = NULL;
		pci_disable_msix(pf->pdev);
		return -ENODEV;

	} else if (v_actual == I40E_MIN_MSIX) {

		pf->num_vmdq_vsis = 0;
		pf->num_vmdq_qps = 0;
		pf->num_lan_qps = 1;
		pf->num_lan_msix = 1;

	} else if (v_actual != v_budget) {


		int vec;

		dev_info(&pf->pdev->dev,
			 "MSI-X vector limit reached with %d, wanted %d, attempting to redistribute vectors\n",
			 v_actual, v_budget);

		vec = v_actual - 1;


		pf->num_vmdq_msix = 1;
		pf->num_vmdq_vsis = 1;
		pf->num_vmdq_qps = 1;


		switch (vec) {
		case 2:
			pf->num_lan_msix = 1;
			break;
		case 3:
			if (pf->flags & I40E_FLAG_IWARP_ENABLED) {
				pf->num_lan_msix = 1;
				pf->num_iwarp_msix = 1;
			} else {
				pf->num_lan_msix = 2;
			}
			break;
		default:
			if (pf->flags & I40E_FLAG_IWARP_ENABLED) {
				pf->num_iwarp_msix = min_t(int, (vec / 3),
						 iwarp_requested);
				pf->num_vmdq_vsis = min_t(int, (vec / 3),
						  I40E_DEFAULT_NUM_VMDQ_VSI);
			} else {
				pf->num_vmdq_vsis = min_t(int, (vec / 2),
						  I40E_DEFAULT_NUM_VMDQ_VSI);
			}
			if (pf->flags & I40E_FLAG_FD_SB_ENABLED) {
				pf->num_fdsb_msix = 1;
				vec--;
			}
			pf->num_lan_msix = min_t(int,
			       (vec - (pf->num_iwarp_msix + pf->num_vmdq_vsis)),
							      pf->num_lan_msix);
			pf->num_lan_qps = pf->num_lan_msix;
			break;
		}
	}

	if ((pf->flags & I40E_FLAG_FD_SB_ENABLED) &&
	    (pf->num_fdsb_msix == 0)) {
		dev_info(&pf->pdev->dev, "Sideband Flowdir disabled, not enough MSI-X vectors\n");
		pf->flags &= ~I40E_FLAG_FD_SB_ENABLED;
		pf->flags |= I40E_FLAG_FD_SB_INACTIVE;
	}
	if ((pf->flags & I40E_FLAG_VMDQ_ENABLED) &&
	    (pf->num_vmdq_msix == 0)) {
		dev_info(&pf->pdev->dev, "VMDq disabled, not enough MSI-X vectors\n");
		pf->flags &= ~I40E_FLAG_VMDQ_ENABLED;
	}

	if ((pf->flags & I40E_FLAG_IWARP_ENABLED) &&
	    (pf->num_iwarp_msix == 0)) {
		dev_info(&pf->pdev->dev, "IWARP disabled, not enough MSI-X vectors\n");
		pf->flags &= ~I40E_FLAG_IWARP_ENABLED;
	}
	i40e_debug(&pf->hw, I40E_DEBUG_INIT,
		   "MSI-X vector distribution: PF %d, VMDq %d, FDSB %d, iWARP %d\n",
		   pf->num_lan_msix,
		   pf->num_vmdq_msix * pf->num_vmdq_vsis,
		   pf->num_fdsb_msix,
		   pf->num_iwarp_msix);

	return v_actual;
}

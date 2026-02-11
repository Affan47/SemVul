setup_minimal(int flag)
{
  update->setupflag = 1;


  if (flag) {
    modify->setup_pre_exchange();
    if (triclinic) domain->x2lamda(atom->nlocal);
    domain->pbc();
    domain->reset_box();
    comm->setup();
    if (neighbor->style) neighbor->setup_bins();
    comm->exchange();
    comm->borders();
    if (triclinic) domain->lamda2x(atom->nlocal+atom->nghost);
    domain->image_check();
    domain->box_too_small_check();
    modify->setup_pre_neighbor();
    neighbor->build();
    neighbor->ncalls = 0;
  }


  ev_set(update->ntimestep);

  for (int ilevel = 0; ilevel < nlevels; ilevel++) {
    force_clear(newton[ilevel]);
    modify->setup_pre_force_respa(vflag,ilevel);
    if (level_bond == ilevel && force->bond)
      force->bond->compute(eflag,vflag);
    if (level_angle == ilevel && force->angle)
      force->angle->compute(eflag,vflag);
    if (level_dihedral == ilevel && force->dihedral)
      force->dihedral->compute(eflag,vflag);
    if (level_improper == ilevel && force->improper)
      force->improper->compute(eflag,vflag);
    if (level_pair == ilevel && pair_compute_flag)
      force->pair->compute(eflag,vflag);
    if (level_inner == ilevel && pair_compute_flag)
      force->pair->compute_inner();
    if (level_middle == ilevel && pair_compute_flag)
      force->pair->compute_middle();
    if (level_outer == ilevel && pair_compute_flag)
      force->pair->compute_outer(eflag,vflag);
    if (level_kspace == ilevel && force->kspace) {
      force->kspace->setup();
      if (kspace_compute_flag) force->kspace->compute(eflag,vflag);
    }


    if (!fix->get_reduced()) {
      const int nall = atom->nlocal + atom->nghost;
      const int nthreads = comm->nthreads;
#if defined(_OPENMP)
#pragma omp parallel default(none)
#endif
      {
#if defined(_OPENMP)
	int tid = omp_get_thread_num();
#else
	int tid = 0;
#endif
	data_reduce_thr(atom->f[0], nall, nthreads, 3, tid);
      }
      fix->did_reduce();
    }

    if (newton[ilevel]) comm->reverse_comm();
    copy_f_flevel(ilevel);
  }

  modify->setup(vflag);
  sum_flevel_f();
  update->setupflag = 0;
}

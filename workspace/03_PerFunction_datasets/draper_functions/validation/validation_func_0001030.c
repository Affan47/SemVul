ellipt_est_fct(const EL_INFO *el_info, void *data)
{
  EL           *el = el_info->el;
  REAL          det = 0.0, est_el;
  REAL_D        Lambda[N_LAMBDA];
  int           face;
  int           dim = el_info->mesh->dim;
  const S_CHAR *bound =
    ((dim == 3) ? el_info->face_bound : el_info->edge_bound);
  EL           *neigh;


  est_el = DATA->rw_est ? *(DATA->rw_est(el)) : 0.0;

  DATA->bas_fcts->get_real_d_vec(el, DATA->uh, DATA->uh_el);

  switch(dim) {
  case 1:
    det = el_grd_lambda_1d(el_info, Lambda);
    break;
#if DIM_OF_WORLD > 1
  case 2:
    det = el_grd_lambda_2d(el_info, Lambda);
    break;
#if DIM_OF_WORLD > 2
  case 3:
    det = el_grd_lambda_3d(el_info, Lambda);
#endif
#endif
  }


  if (DATA->C0)
    est_el += el_res2(el_info, (const REAL_D *)Lambda, det, DATA);


  if (dim > 1 && DATA->C1)
  {
    for (face = 0; face < N_NEIGH(dim); face++)
    {
      if ((neigh = el_info->neigh[face]))
      {


	if (!DATA->rw_est  ||  neigh->mark)
	{
	  REAL est = jump_res2(el_info, face,
			       (const REAL_D *)Lambda, det, DATA);

	  est_el += est;

	  if (DATA->rw_est) *(DATA->rw_est(neigh)) += est;
	}
      }
      else if (IS_NEUMANN(bound[face]))
      {
	est_el += neumann_res2(el_info, face,
			       (const REAL_D *)Lambda, det, DATA);
      }
    }
  }


  if (DATA->rw_est) *(DATA->rw_est(el)) = est_el;

  DATA->est_sum += est_el;
  DATA->est_max = MAX(DATA->est_max, est_el);

  el_info->el->mark = 0;
  return;
}

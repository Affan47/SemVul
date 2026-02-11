ap_linexpr0_alloc(ap_linexpr_discr_t lin_discr, size_t size)
{
  ap_linexpr0_t* e;
  size_t i;

  e = (ap_linexpr0_t*)malloc(sizeof(ap_linexpr0_t));
  ap_coeff_init(&e->cst,AP_COEFF_SCALAR);
  e->discr = lin_discr;
  e->size = size;
  switch (lin_discr){
  case AP_LINEXPR_DENSE:
    e->p.coeff = size==0 ? NULL : (ap_coeff_t*)malloc(size*sizeof(ap_coeff_t));
    for (i=0; i<size; i++) ap_coeff_init(&e->p.coeff[i],AP_COEFF_SCALAR);
    break;
  case AP_LINEXPR_SPARSE:
    e->p.linterm = size==0 ? NULL : (ap_linterm_t*)malloc(size*sizeof(ap_linterm_t));
    for (i=0; i<size; i++){
      ap_coeff_init(&e->p.linterm[i].coeff,AP_COEFF_SCALAR);
      e->p.linterm[i].dim = AP_DIM_MAX;
    }
    break;
  }
  return e;
}

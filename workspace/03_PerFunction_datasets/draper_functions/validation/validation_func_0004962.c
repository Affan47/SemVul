free_prep_desc(PREPdesc *P)
{
   if (P){
      if (P->sr){
	 free_sr_desc(P->sr);
      }
      if (P->d_sr){
	 free_sr_desc(P->d_sr);
      }

      if (P->mip){
	 free_mip_desc(P->mip);
      }

      FREE(P->impl_vars);
      FREE(P->impl_ub);
      FREE(P->impl_lb);
      FREE(P->ulist_checked);
      FREE(P->llist_checked);
      FREE(P->rows_checked);


      FREE(P->impl_cols);
      FREE(P->impl_rows);
      FREE(P->user_col_ind);
      FREE(P->user_row_ind);
      FREE(P->stats.nz_coeff_changed);
      FREE(P->tmpi);
      FREE(P->tmpd);
      FREE(P->tmpc);

      FREE(P->xind);
      FREE(P->xval);

      FREE(P);
   }
}

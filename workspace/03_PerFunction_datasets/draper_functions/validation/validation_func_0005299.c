mpc860_fec_unset_nio(struct mpc860_data *d)
{
   if (!d)
      return(-1);

   if (d->fec_nio != NULL) {
      netio_rxl_remove(d->fec_nio);
      d->fec_nio = NULL;
   }

   return(0);
}

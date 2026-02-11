mpc860_fec_set_nio(struct mpc860_data *d,netio_desc_t *nio)
{

   if (!d || (d->fec_nio != NULL))
      return(-1);

   d->fec_nio = nio;
   netio_rxl_add(nio,(netio_rx_handler_t)mpc860_fec_handle_rx_pkt,d,NULL);
   return(0);
}

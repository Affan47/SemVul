ti1570_update_rx_cring(struct pa_a1_data *d,
                                   ti1570_rx_dma_entry_t *rde,
                                   m_uint32_t atm_hdr,
                                   m_uint32_t aal5_trailer,
                                   m_uint32_t err_ind,
                                   m_uint32_t fbuf_valid)
{
   m_uint32_t rcr_addr,rcr_end,aal_type,ptr,val;
   ti1570_rcr_entry_t rcre;

   if (rde->ctrl & TI1570_RX_DMA_RCR_SELECT) {

      rcr_addr = d->iregs[TI1570_REG_RCR_WI_ADDR];
      rcr_addr += (d->rcr_wi_pos * sizeof(rcre));
   } else {

      rcr_addr = d->iregs[TI1570_REG_RCR_WOI_ADDR];
      rcr_addr += (d->rcr_woi_pos * sizeof(rcre));
   }

#if DEBUG_RECEIVE
   TI1570_LOG(d,"ti1570_update_rx_cring: posting 0x%x at address 0x%x\n",
              (rde->sp_ptr << 2),rcr_addr);

   physmem_dump_vm(d->vm,rde->sp_ptr<<2,sizeof(ti1570_rx_buffer_t) >> 2);
#endif


   ptr = rcr_addr + OFFSET(ti1570_rcr_entry_t,fbr_entry);
   val = physmem_copy_u32_from_vm(d->vm,ptr);

   if (!(val & TI1570_RCR_OWN)) {
      TI1570_LOG(d,"ti1570_update_rx_cring: RX freeze...\n");
      d->iregs[TI1570_REG_STATUS] |= TI1570_STAT_RX_FRZ;
      return;
   }


   memset(&rcre,0,sizeof(rcre));


   rcre.atm_hdr = atm_hdr;


   aal_type = rde->ctrl & TI1570_RX_DMA_AAL_TYPE_MASK;
   if (aal_type == TI1570_RX_DMA_AAL_AAL5)
      rcre.error |= TI1570_RCR_AAL5;

   rcre.error |= err_ind;


   if (fbuf_valid)
      rcre.sp_addr = TI1570_RCR_VALID | rde->sp_ptr;


   rcre.aal5_trailer = aal5_trailer;


   rcre.fbr_entry = rde->fbr_entry & TI1570_RX_DMA_FB_PTR_MASK;
   if (err_ind) rcre.fbr_entry |= TI1570_RCR_ERROR;


   rcre.atm_hdr      = htonl(rcre.atm_hdr);
   rcre.error        = htonl(rcre.error);
   rcre.sp_addr      = htonl(rcre.sp_addr);
   rcre.aal5_trailer = htonl(rcre.aal5_trailer);
   rcre.fbr_entry    = htonl(rcre.fbr_entry);
   physmem_copy_to_vm(d->vm,&rcre,rcr_addr,sizeof(rcre));


   rde->ctrl &= ~TI1570_RX_DMA_ACT;


   if (rde->ctrl & TI1570_RX_DMA_RCR_SELECT) {
      rcr_end = d->iregs[TI1570_REG_RX_CRING_SIZE] & TI1570_RCR_SIZE_MASK;

      if ((d->rcr_wi_pos++) == rcr_end)
         d->rcr_wi_pos = 0;


      d->iregs[TI1570_REG_STATUS] |= TI1570_STAT_CP_RX;
      dev_pa_a1_update_irq_status(d);
   } else  {
      rcr_end = (d->iregs[TI1570_REG_RX_CRING_SIZE] >> 16);
      rcr_end &= TI1570_RCR_SIZE_MASK;

      if ((d->rcr_woi_pos++) == rcr_end)
         d->rcr_woi_pos = 0;
   }
}

ibsm_send_mad_by_lid (
  ibsm_t   *p_ibsm,
  uint8_t  *p_data,
  size_t    data_size,
  uint16_t  lid,
  uint16_t  attr,
  uint32_t  mod,
  uint16_t  meth)
{
  osm_mad_addr_t        mad_addr;
  osm_madw_t           *p_madw;
  ib_smp_t              response_mad = {0};
  ib_api_status_t       status;
  int debug_mode = 0;

  OSM_LOG_ENTER(&(IbisObj.log));

  osm_log(&(IbisObj.log), OSM_LOG_DEBUG,
          "ibsm_send_mad_by_lid: "
          " Sending to lid:0x%04X method:0x%02X attr:0x%04X mod:0x%08x\n",
          lid, meth, attr, mod);

  mad_addr.dest_lid = cl_hton16(lid);
  mad_addr.path_bits = 0;
  mad_addr.static_rate = 0;

  p_madw = osm_mad_pool_get(
    &(IbisObj.mad_pool), p_ibsm->lid_route_bind, MAD_BLOCK_SIZE, &mad_addr);
  p_madw->resp_expected = TRUE;

  memset((char*)p_madw->p_mad, 0, MAD_BLOCK_SIZE);
  ((ib_mad_t *)p_madw->p_mad)->method = meth;
  ((ib_mad_t *)p_madw->p_mad)->class_ver = 1;
  ((ib_mad_t *)p_madw->p_mad)->mgmt_class = IB_MCLASS_SUBN_LID;
  ((ib_mad_t *)p_madw->p_mad)->base_ver = 1;
  ((ib_smp_t *)p_madw->p_mad)->m_key = cl_hton64(IbisObj.p_opt->m_key);
  ((ib_mad_t *)p_madw->p_mad)->attr_id = cl_hton16(attr);
  ((ib_mad_t *)p_madw->p_mad)->attr_mod = cl_hton32(mod);
  ((ib_mad_t *)p_madw->p_mad)->trans_id = ibis_get_tid();


  memcpy(&((ib_smp_t*)p_madw->p_mad)->data, p_data, data_size);

  if (debug_mode == 1)
  {

      printf("\n\n>>> Sending MAD:\n\n" );
      __ibsm_dump_raw_mad_by_lid((ib_smp_t *)(p_madw->p_mad));
  }

  status = ibis_gsi_send_sync_mad_batch(
    &(IbisObj.mad_ctrl),
    p_ibsm->lid_route_bind,
    1,
    &p_madw,
    sizeof(ib_smp_t),
    (uint8_t*)&response_mad);

  if (!response_mad.method)
    status = IB_TIMEOUT;

  if (status == IB_SUCCESS)
  {
       if (debug_mode == 1)
       {

           printf("\n\n>>> Response MAD:\n\n" );
           __ibsm_dump_raw_mad_by_lid((ib_smp_t *)&response_mad);
       }
    memcpy(p_data, &response_mad.data, data_size);

    if (cl_ntoh16(response_mad.status) & 0x7fff)
    {
      status = cl_ntoh16(response_mad.status);
    }
  }

  OSM_LOG_EXIT(&(IbisObj.log));
  return (status);
}

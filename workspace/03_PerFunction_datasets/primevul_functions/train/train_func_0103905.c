ospf_db_desc_resend (struct ospf_neighbor *nbr)
{
  struct ospf_interface *oi;

  oi = nbr->oi;


  ospf_packet_add (oi, ospf_packet_dup (nbr->last_send));


  OSPF_ISM_WRITE_ON (oi->ospf);
}

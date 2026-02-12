ospf_check_area_id (struct ospf_interface *oi, struct ospf_header *ospfh)
{

  if (OSPF_AREA_SAME (&oi->area, &ospfh))
    return 1;

  return 0;
}

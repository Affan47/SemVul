gpx_write_common_description(const waypoint* waypointp, const char* indent,
                             const char* oname)
{
  write_optional_xml_entity(ofd, indent, "name", oname);
  write_optional_xml_entity(ofd, indent, "cmt", waypointp->description);
  if (waypointp->notes && waypointp->notes[0]) {
    write_xml_entity(ofd, indent, "desc", waypointp->notes);
  } else {
    write_optional_xml_entity(ofd, indent, "desc", waypointp->description);
  }
  write_gpx_url(waypointp);
  write_optional_xml_entity(ofd, indent , "sym", waypointp->icon_descr);
}

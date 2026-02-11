ozi_track_hdr(const route_head * rte)
{
  static char *ozi_trk_header =
    "OziExplorer Track Point File Version 2.1\r\n"
    "WGS 84\r\n"
    "Altitude is in %s\r\n"
    "Reserved 3\r\n"
    "0,2,255,%s,0,0,2,8421376\r\n"
    "0\r\n";

  if ((! pack_opt) || (track_out_count == 0)) {
    ozi_openfile(ozi_ofname);
    gbfprintf(file_out, ozi_trk_header,
              altunit == 'f' ? "Feet" : "Meters",
              rte->rte_name ? rte->rte_name : "ComplimentsOfGPSBabel");
  }

  track_out_count++;
  new_track = 1;
}

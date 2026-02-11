wfff_xml_rd_deinit(void)
{


  xfreez(ap_mac);
  xfreez(ap_ssid);
  xfreez(ap_type);
  xfreez(ap_wep);
  xfreez(ap_last);

  xml_deinit();

  if (tosscount) {
    warning("Warning: %s reading file. Threw away %ld invalid entries.\n",
            MYNAME, tosscount);
  }

}

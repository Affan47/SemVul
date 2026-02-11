syn_ps2_translate_wmode_data (unsigned char *data,
					    report_type *report)
{

  if (((data[0] & 0xc8) == 0x80) && ((data[3] & 0xc8) == 0xc0)) {

    report->left        = check_bits (data[0], 0x01);
    report->middle      = check_bits (data[0] ^ data[3], 0x01);
    report->right       = check_bits (data[0], 0x02);
    report->fourth      = check_bits (data[0] ^ data[3], 0x02);
    report->up          = 0;
    report->down        = 0;
    report->x           = (((data[1] & 0x0F) << 8) |
			   ((data[3] & 0x10) << 8) |
			   ((data[4])));
    report->y           = (((data[1] & 0xF0) << 4) |
			   ((data[3] & 0x20) << 7) |
			   ((data[5])));
    report->pressure    = data[2];
    report->fingers     = 0;
    report->fingerwidth = 0;
    report->gesture     = 0;
    report->w = (((data[3] & 0x04) >> 2) |
		 ((data[0] & 0x04) >> 1) |
		 ((data[0] & 0x30) >> 2));


  } else {
    syn_ps2_translate_error(data,report);
  }
}

gl646_send_gamma_table (Genesys_Device * dev)
{
  int size;
  int address;
  SANE_Status status;
  uint8_t *gamma;
  int bits;

  DBGSTART;


  if (dev->reg[reg_0x05].value & REG05_GMMTYPE)
    {
      size = 16384;
      bits = 14;
    }
  else
    {
      size = 4096;
      bits = 12;
    }


  gamma = (uint8_t *) malloc (size * 2 * 3);
  if (gamma==NULL)
    {
      return SANE_STATUS_NO_MEM;
    }

  RIE(sanei_genesys_generate_gamma_buffer(dev, bits, size-1, size, gamma));


  switch (dev->reg[reg_0x05].value >> 6)
    {
    case 0:
      address = 0x09000;
      break;
    case 1:
      address = 0x11000;
      break;
    case 2:
      address = 0x20000;
      break;
    default:
      free (gamma);
      return SANE_STATUS_INVAL;
    }


  status = sanei_genesys_set_buffer_address (dev, address);
  if (status != SANE_STATUS_GOOD)
    {
      free (gamma);
      DBG (DBG_error,
	   "gl646_send_gamma_table: failed to set buffer address: %s\n",
	   sane_strstatus (status));
      return status;
    }


  status = gl646_bulk_write_data (dev, 0x3c, (uint8_t *) gamma, size * 2 * 3);
  if (status != SANE_STATUS_GOOD)
    {
      free (gamma);
      DBG (DBG_error,
	   "gl646_send_gamma_table: failed to send gamma table: %s\n",
	   sane_strstatus (status));
      return status;
    }
  free (gamma);

  DBGCOMPLETED;
  return SANE_STATUS_GOOD;
}

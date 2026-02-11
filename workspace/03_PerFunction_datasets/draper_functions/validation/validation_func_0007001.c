create_sfr_map()
{
  if(verbose)
    cout << "creating c55 registers\n";

  P16C54::create_sfr_map();

  delete_file_registers(0x07, 0x07);
  add_sfr_register(m_portc, 0x07);
  add_sfr_register(m_trisc,  0xffffffff, RegisterValue(0xff,0));

}

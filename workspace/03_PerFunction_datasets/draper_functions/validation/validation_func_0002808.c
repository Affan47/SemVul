create_sfr_map()
{
  if(verbose)
    cout << "creating c54 registers\n";

  add_file_registers(0x07, 0x1f, 0x00);


  add_sfr_register(indf,   0x00);

  add_sfr_register(&tmr0,  0x01);

  add_sfr_register(pcl,    0x02, RegisterValue(0,0));
  add_sfr_register(status, 0x03, RegisterValue(0x18,0));
  add_sfr_register(fsr,    0x04);

  add_sfr_register(m_porta, 0x05);
  add_sfr_register(m_portb, 0x06);

  add_sfr_register(option_reg,  0xffffffff, RegisterValue(0xff,0));
  add_sfr_register(m_trisa,  0xffffffff, RegisterValue(0x1f,0));
  add_sfr_register(m_trisb,  0xffffffff, RegisterValue(0xff,0));
#ifndef USE_PIN_MODULE_FOR_TOCKI
  add_sfr_register(m_tocki,  0xffffffff, RegisterValue(0x01,0));
  add_sfr_register(m_trist0, 0xffffffff, RegisterValue(0x01,0));
#endif

}

set_config_word(unsigned int address,unsigned int cfg_word)
{
  enum {
    FOSC0  = 1<<0,
    FOSC1  = 1<<1,
    FOSC2  = 1<<2,
    WDTEN  = 1<<3,
    PWRTEN = 1<<4,
    MCLRE  = 1<<5,
    BOREN  = 1<<6,
    CP     = 1<<7,
    CPD    = 1<<8,

    BG0    = 1<<12,
    BG1    = 1<<13
  };


    if(address == config_word_address())
    {
        if ((cfg_word & MCLRE) == MCLRE)
	    assignMCLRPin(4);
        else
	    unassignMCLRPin();

 	wdt.initialize((cfg_word & WDTEN) == WDTEN);
        if ((cfg_word & (FOSC2 | FOSC1 )) == 0x04)
	  osccal.set_freq(4e6);


	return(_14bit_processor::set_config_word(address, cfg_word));

    }
    return false;
}

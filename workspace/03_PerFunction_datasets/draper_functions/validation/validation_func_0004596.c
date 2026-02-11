nrf_set_strength(unsigned char strength){
    if(strength>3)
        strength=3;
    nrf_write_reg(R_RF_SETUP,DEFAULT_SPEED|(strength<<1));
}

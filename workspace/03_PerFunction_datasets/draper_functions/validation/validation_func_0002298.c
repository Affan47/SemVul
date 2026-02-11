water_setphysics(double physics) {
  if(physics<0.25) {

    mode |= 0x4000;
    density=4;
    pheight=600;
  } else if(physics<0.50) {

    mode &= 0xBFFF;
    density=3;
    pheight=400;
  } else if(physics<0.75) {

    mode &= 0xBFFF;
    density=6;
    pheight=400;
  } else {

    mode &=0xBFFF;
    density=8;
    pheight=400;
  }
}

put_value(unsigned int new_value)
{
  Dprintf(("PortRegister::put_value old=0x%x:new=0x%x\n",value.data,new_value));

  unsigned int diff = mEnableMask & (new_value ^ value.data);
  drivingValue = new_value & mEnableMask;
  value.data = drivingValue;

  if(diff) {


    updatePort();
  }
}

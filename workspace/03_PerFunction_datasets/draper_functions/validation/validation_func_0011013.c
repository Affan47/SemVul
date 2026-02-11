rix_C0_pro(unsigned short ctrl_l,unsigned short index)
{
  register unsigned short i = index>=12?index-12:0;
  if(ctrl_l < 6 || rhythm == 0)
    {
      ad_a0b0l_reg(ctrl_l,i,1);
      return;
    }
  else
    {
      if(ctrl_l != 6)
	{
	  if(ctrl_l == 8)
	    {
	      ad_a0b0l_reg(ctrl_l,i,0);
	      ad_a0b0l_reg(7,i+7,0);
	    }
	}
      else ad_a0b0l_reg(ctrl_l,i,0);
      bd_modify |= bd_reg_data[ctrl_l];
      ad_bd_reg();
      return;
    }
}

test_old_growth_bits(struct pine *ps, int index)
{


    static unsigned long old_growth_bits = ((1 << F_ENABLE_FULL_HDR)     |
					    (1 << F_ENABLE_PIPE)         |
					    (1 << F_ENABLE_TAB_COMPLETE) |
					    (1 << F_QUIT_WO_CONFIRM)     |
					    (1 << F_ENABLE_JUMP)         |
					    (1 << F_ENABLE_ALT_ED)       |
					    (1 << F_ENABLE_BOUNCE)       |
					    (1 << F_ENABLE_AGG_OPS)	 |
					    (1 << F_ENABLE_FLAG)         |
					    (1 << F_CAN_SUSPEND));
    if(index >= 32)
	return(0);

    if(index == F_OLD_GROWTH){
	for(index = 1; index <= F_FEATURE_LIST_COUNT; index++)
	  if(((1 << index) & old_growth_bits) && F_OFF(index, ps))
	    return(0);

	return(1);
    }
    else
      return((1 << index) & old_growth_bits);
}

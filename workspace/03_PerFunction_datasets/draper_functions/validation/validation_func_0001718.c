TkWaitForMultipleEvents (int width,
                                        ACE_Select_Reactor_Handle_Set &wait_set,
                                        ACE_Time_Value *)
{

  ACE_Select_Reactor_Handle_Set temp_set = wait_set;

  if (ACE_OS::select (width,
                      temp_set.rd_mask_,
                      temp_set.wr_mask_,
                      temp_set.ex_mask_,
                      (ACE_Time_Value *) &ACE_Time_Value::zero) == -1)
    return -1;


  ::Tcl_DoOneEvent (0);


  width = this->handler_rep_.max_handlep1 ();


  return ACE_OS::select (width,
                         wait_set.rd_mask_,
                         wait_set.wr_mask_,
                         wait_set.ex_mask_,
                         (ACE_Time_Value *) &ACE_Time_Value::zero);
}

UpdateHessian()
  {
    DBG_START_METH("ExactHessianUpdater::UpdateHessian",
                   dbg_verbosity);

    IpData().Set_W(IpCq().curr_exact_hessian());
  }

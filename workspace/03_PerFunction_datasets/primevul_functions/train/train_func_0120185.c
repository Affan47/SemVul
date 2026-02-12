Statement_Ptr Expand::operator()(Warning_Ptr w)
  {

    w->perform(&eval);
    return 0;
  }

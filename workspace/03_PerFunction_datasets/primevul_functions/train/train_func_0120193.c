Statement_Ptr Expand::operator()(Error_Ptr e)
  {

    e->perform(&eval);
    return 0;
  }

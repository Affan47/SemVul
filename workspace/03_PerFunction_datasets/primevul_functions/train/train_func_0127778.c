inline void reconstruct_base()
  {


    (LibRaw_buffer_datastream &)*this =
        LibRaw_buffer_datastream(pView_, (size_t)cbView_);
  }

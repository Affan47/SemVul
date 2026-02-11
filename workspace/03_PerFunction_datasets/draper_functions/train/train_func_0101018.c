align_pos( const int alignment )
  {
  if( alignment > 1 )
    {
    const int disp = alignment - ( pos_ % alignment );
    if( disp < alignment && disp < size_ )
      { pos_ += disp; size_ -= disp; }
    }
  }

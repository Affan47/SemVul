operator[]( Int offset )
      throw( BoundsException )
   {
      theCurrentPointer = theBasePointer;
      (*this) + offset;
      return (*this);
   }

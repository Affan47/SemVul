remove_ref (void)
    {
      const long new_count = this->decrement ();

      if (new_count == 0)
        {
          delete this;
        }
    }

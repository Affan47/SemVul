bool convert_if_needed(THD *thd, String *str)
    {


      if (needs_conversion())
        return convert(thd, str);
      str->set_charset(final_character_set_of_str_value);
      return false;
    }

bool check_vcol_func_processor(void *arg)
  {
    context= 0;
    if (field && (field->unireg_check == Field::NEXT_NUMBER))
    {

      return mark_unsupported_function(field_name, arg, VCOL_FIELD_REF | VCOL_AUTO_INC);
    }
    return mark_unsupported_function(field_name, arg, VCOL_FIELD_REF);
  }

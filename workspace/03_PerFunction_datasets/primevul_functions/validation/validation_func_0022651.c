merge_key_fields(KEY_FIELD *start,KEY_FIELD *new_fields,KEY_FIELD *end,
		 uint and_level)
{
  if (start == new_fields)
    return start;
  if (new_fields == end)
    return start;

  KEY_FIELD *first_free=new_fields;


  for (; new_fields != end ; new_fields++)
  {
    for (KEY_FIELD *old=start ; old != first_free ; old++)
    {
      if (old->field == new_fields->field)
      {


	if (!new_fields->val->const_item())
	{


	  if (old->val->eq(new_fields->val, old->field->binary()))
	  {
	    old->level= and_level;
	    old->optimize= ((old->optimize & new_fields->optimize &
			     KEY_OPTIMIZE_EXISTS) |
			    ((old->optimize | new_fields->optimize) &
			     KEY_OPTIMIZE_REF_OR_NULL));
            old->null_rejecting= (old->null_rejecting &&
                                  new_fields->null_rejecting);
	  }
	}
	else if (old->eq_func && new_fields->eq_func &&
                 old->val->eq_by_collation(new_fields->val,
                                           old->field->binary(),
                                           old->field->charset()))

	{
	  old->level= and_level;
	  old->optimize= ((old->optimize & new_fields->optimize &
			   KEY_OPTIMIZE_EXISTS) |
			  ((old->optimize | new_fields->optimize) &
			   KEY_OPTIMIZE_REF_OR_NULL));
          old->null_rejecting= (old->null_rejecting &&
                                new_fields->null_rejecting);
	}
	else if (old->eq_func && new_fields->eq_func &&
		 ((old->val->const_item() && !old->val->is_expensive() &&
                   old->val->is_null()) ||
                  (!new_fields->val->is_expensive() &&
                   new_fields->val->is_null())))
	{

	  old->level= and_level;
          if (old->field->maybe_null())
	  {
	    old->optimize= KEY_OPTIMIZE_REF_OR_NULL;

            old->null_rejecting= 0;
	  }


	  if (!old->val->used_tables() && !old->val->is_expensive() &&
              old->val->is_null())
	    old->val= new_fields->val;
	}
	else
	{


	  if (old == --first_free)
	    break;
	  *old= *first_free;
	  old--;
	}
      }
    }
  }

  for (KEY_FIELD *old=start ; old != first_free ;)
  {
    if (old->level != and_level)
    {
      if (old == --first_free)
	break;
      *old= *first_free;
      continue;
    }
    old++;
  }
  return first_free;
}

prFieldHasValue (PR *pr, FieldIndex field)
{
  if (field == InvalidFieldIndex)
    {
      abort ();
    }

  return (pr->private != NULL && pr->private->value != NULL
	  && pr->private->value[fieldNumber (field)].data.string != NULL);

}

scm_i_dowinds (SCM to, long delta, void (*turn_func) (void *), void *data)
{
 tail:
  if (scm_is_eq (to, scm_i_dynwinds ()))
    {
      if (turn_func)
	turn_func (data);
    }
  else if (delta < 0)
    {
      SCM wind_elt;
      SCM wind_key;

      scm_i_dowinds (SCM_CDR (to), 1 + delta, turn_func, data);
      wind_elt = SCM_CAR (to);

      if (FRAME_P (wind_elt))
	{
	  if (!FRAME_REWINDABLE_P (wind_elt))
	    scm_misc_error ("dowinds",
			    "cannot invoke continuation from this context",
			    SCM_EOL);
	}
      else if (WINDER_P (wind_elt))
	{
	  if (WINDER_REWIND_P (wind_elt))
	    WINDER_PROC (wind_elt) (WINDER_DATA (wind_elt));
	}
      else
	{
	  wind_key = SCM_CAR (wind_elt);

	  if (SCM_NIMP (wind_key))
	    {
	      if (scm_is_pair (wind_key))
		{
		  if (SCM_VARIABLEP (SCM_CAR (wind_key)))
		    scm_swap_bindings (wind_key, SCM_CDR (wind_elt));
		}
	      else if (SCM_TYP3 (wind_key) == scm_tc3_closure)
		scm_call_0 (wind_key);
	    }
	}

      scm_i_set_dynwinds (to);
    }
  else
    {
      SCM wind;
      SCM wind_elt;
      SCM wind_key;

      wind = scm_i_dynwinds ();
      wind_elt = SCM_CAR (wind);
      scm_i_set_dynwinds (SCM_CDR (wind));

      if (FRAME_P (wind_elt))
	{

	}
      else if (WINDER_P (wind_elt))
	{
	  if (!WINDER_REWIND_P (wind_elt))
	    WINDER_PROC (wind_elt) (WINDER_DATA (wind_elt));
	}
      else
	{
	  wind_key = SCM_CAR (wind_elt);
	  if (SCM_NIMP (wind_key))
	    {
	      if (scm_is_pair (wind_key))
		{
		  if (SCM_VARIABLEP (SCM_CAR (wind_key)))
		    scm_swap_bindings (wind_key, SCM_CDR (wind_elt));
		}
	      else if (SCM_TYP3 (wind_key) == scm_tc3_closure)
		scm_call_0 (SCM_CDR (wind_elt));
	    }
	}

      delta--;
      goto tail;
    }
}

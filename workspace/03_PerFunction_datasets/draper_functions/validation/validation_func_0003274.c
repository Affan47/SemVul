_e_smart_value_limit(E_Smart_Data *sd)
{
   if (sd->val < sd->val_min) sd->val = sd->val_min;
   if (sd->val > sd->val_max) sd->val = sd->val_max;
   if (sd->val_range > 0.0)
     {
	if (sd->step_count > 0)
	  {
	     double p, s;

	     s = sd->val_range / sd->step_count;
	     p = sd->val / s;
	     if (sd->direction == 1)
	       p = ceil(p);
	     else if (sd->direction == -1)
	       p = floor(p);
	     else
	       p = round(p);
	     sd->val = p * s;
	  }
	else if (sd->step_size > 0.0)
	  {
	     double p;

	     p = sd->val / sd->step_size;
	     if (sd->direction == 1)
	       p = ceil(p);
	     else if (sd->direction == -1)
	       p = floor(p);
	     else
	       p = round(p);
	     sd->val = p * sd->step_size;
	  }
     }
   sd->direction = 0;
}

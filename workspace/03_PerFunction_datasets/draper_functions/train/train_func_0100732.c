build_sn_cm_priors( database_DS data_base, att_DS att)
{
   int n;
   float range, sigma_min, sigma_max;
   priors_DS priors;
   real_stats_DS statistics = att->r_statistics;

   range = statistics->mx - statistics->mn;
   sigma_min = SN_CM_SIGMA_SAFETY_FACTOR * att->error;

   sigma_max = max(sigma_min, range / 2.0);
   if (sigma_min == sigma_max) {
      if ( (n = att->warnings_and_errors->num_expander_errors ++) == 0)
	 att->warnings_and_errors->model_expander_errors =
	    (fxlstr *) malloc(sizeof(fxlstr));
      else
	 att->warnings_and_errors->model_expander_errors =
	    (fxlstr *) realloc(att->warnings_and_errors->model_expander_errors,
			    (n+1) * sizeof(fxlstr));
      strcpy(att->warnings_and_errors->model_expander_errors[n],
	     "          single_normal_cm is faulty due to large error-to-range\n"
             "          ratio on sigma priors.\n");
   }
   priors = (priors_DS) malloc(sizeof(struct priors));
   priors->known_prior = (0.5 + statistics->count) / (1.0 + data_base->n_data);
   priors->sigma_min = sigma_min;
   priors->sigma_max = sigma_max;
   priors->mean_mean = statistics->mean;
   priors->mean_sigma =
      max((range / 2.0),
           (SN_CM_SIGMA_SAFETY_FACTOR /
                (float) sqrt( ABSOLUTE_MIN_CLASS_WT)) * sigma_min);
   priors->mean_var = square(priors->mean_sigma);
   priors->minus_log_log_sigmas_ratio =
     - (float) safe_log( max( safe_log( 1.0 / (1.0 - SINGLE_FLOAT_EPSILON)),
                        max( safe_log( (double) (priors->sigma_max / priors->sigma_min)),
                            LEAST_POSITIVE_SHORT_FLOAT)));
   priors->minus_log_mean_sigma = - (float) safe_log( (double) priors->mean_sigma);

   return(priors);
}

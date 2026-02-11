png_set_filter_heuristics_fixed(png_structrp png_ptr, int heuristic_method,
    int num_weights, png_const_fixed_point_p filter_weights,
    png_const_fixed_point_p filter_costs)
{
   png_debug(1, "in png_set_filter_heuristics_fixed");


   if (!png_init_filter_heuristics(png_ptr, heuristic_method, num_weights))
      return;


   if (heuristic_method == PNG_FILTER_HEURISTIC_WEIGHTED)
   {
      int i;
      for (i = 0; i < num_weights; i++)
      {
         if (filter_weights[i] <= 0)
         {
            png_ptr->inv_filter_weights[i] =
            png_ptr->filter_weights[i] = PNG_WEIGHT_FACTOR;
         }

         else
         {
            png_ptr->inv_filter_weights[i] = (png_uint_16)
               ((PNG_WEIGHT_FACTOR*filter_weights[i]+PNG_FP_HALF)/PNG_FP_1);

            png_ptr->filter_weights[i] = (png_uint_16)((PNG_WEIGHT_FACTOR*
               PNG_FP_1+(filter_weights[i]/2))/filter_weights[i]);
         }
      }


      for (i = 0; i < PNG_FILTER_VALUE_LAST; i++)
         if (filter_costs[i] >= PNG_FP_1)
      {
         png_uint_32 tmp;


         tmp = PNG_COST_FACTOR*PNG_FP_1 + (filter_costs[i]/2);
         tmp /= filter_costs[i];

         png_ptr->inv_filter_costs[i] = (png_uint_16)tmp;

         tmp = PNG_COST_FACTOR * filter_costs[i] + PNG_FP_HALF;
         tmp /= PNG_FP_1;

         png_ptr->filter_costs[i] = (png_uint_16)tmp;
      }
   }
}

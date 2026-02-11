couron (model, verbose)
     rdsfig_list *model;
     int verbose;
{
   int layer_num;

   for (layer_num = 0; layer_num < RDS_MAX_LAYER; layer_num++)
   {
      if ((GET_S2R_POST_Y_OR_N (layer_num) == S2R_TREAT) && (GET_S2R_RING_WIDTH (layer_num) != 0))
      {
         couron_layer (model, layer_num, verbose);
      }
   }
}

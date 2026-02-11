create_clsf_DS( void)
{
   clsf_DS temp;
   chkpt_DS temp_chkpt;

   temp = (clsf_DS) malloc(sizeof(struct classification));
   if (G_clsf_storage_log_p == TRUE) {
     fprintf(stdout, "\ncreate_clsf_DS: %p\n", (void *) temp);
   }
   temp->log_p_x_h_pi_theta = 0.0;
   temp->log_a_x_h = 0.0;
   temp->database = NULL;
   temp->models = NULL;
   temp->num_models = 0;
   temp->n_classes = 0;
   temp->classes = NULL;
   temp->min_class_wt = 0.0;

   temp_chkpt = (chkpt_DS) malloc( sizeof( struct checkpoint));
   temp_chkpt->accumulated_try_time = 0;
   temp_chkpt->current_try_j_in = 0;
   temp_chkpt->current_cycle =0;
   temp->checkpoint = temp_chkpt;
   temp->reports = NULL;
   temp->next = NULL;
   return(temp);
}

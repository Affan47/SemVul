prtpccall(outer)
int outer;
   {
   int first_arg;
   int optim;

   first_arg = cur_proc->tnd_loc + num_tmp;
   optim = glookup(cur_proc->name)->flag & F_SmplInv;


   if (cur_proc->nargs != 0 && optim && !outer) {
      fprintf(codefile, "   {\n");
      fprintf(codefile, "   dptr r_argp_sav;\n");
      fprintf(codefile, "\n");
      fprintf(codefile, "   r_argp_sav = glbl_argp;\n");
      }
   if (debug_info) {
      fprintf(codefile, "   --k_level;\n");
      fprintf(codefile, "   if (k_trace) strace();\n");
      }
   fprintf(codefile, "   pfp = ");
   frame(outer);
   fprintf(codefile, ".old_pfp;\n");
   fprintf(codefile, "   glbl_argp = ");
   frame(outer);
   fprintf(codefile, ".old_argp;\n");
   if (line_info) {
      fprintf(codefile, "   line_num = ");
      frame(outer);
      fprintf(codefile, ".debug.old_line;\n");
      fprintf(codefile, "   file_name = ");
      frame(outer);
      fprintf(codefile , ".debug.old_fname;\n");
      }
   fprintf(codefile, "   r_signal = (*");
   if (outer)
      fprintf(codefile, "r_s_cont)();\n");
   else
      fprintf(codefile, "r_pfp->succ_cont)();\n");
   fprintf(codefile, "   if (r_signal != A_Resume) {\n");
   if (outer)
      fprintf(codefile, "      tend = r_frame.tend.previous;\n");
   fprintf(codefile, "      return r_signal;\n");
   fprintf(codefile, "      }\n");
   fprintf(codefile, "   pfp = (struct p_frame *)&");
   frame(outer);
   fprintf(codefile, ";\n");
   if (cur_proc->nargs == 0)
      fprintf(codefile, "   glbl_argp = NULL;\n");
   else {
      if (optim) {
         if (outer)
            fprintf(codefile, "   glbl_argp = r_args;\n");
         else
            fprintf(codefile, "   glbl_argp = r_argp_sav;\n");
         }
      else {
         fprintf(codefile, "   glbl_argp = &");
         if (outer)
            fprintf(codefile, "r_frame.");
         else
            fprintf(codefile, "r_pfp->");
         fprintf(codefile, "tend.d[%d];\n", first_arg);
         }
      }
   if (debug_info) {
      fprintf(codefile, "   if (k_trace) atrace();\n");
      fprintf(codefile, "   ++k_level;\n");
      }
   if (cur_proc->nargs != 0 && optim && !outer)
      fprintf(codefile, "   }\n");
   }

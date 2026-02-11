run_optim(file)
struct file_list * file;
{
   char buf[32];
   if (opt_arch<5) command.cmd = OPTIM;
   else            command.cmd = OPT;
   command_reset();
   newfilename(file, !do_as, 's', 1);
   command_opt("-c!");
   if (opt_O && opt_arch == 0)
   {
      sprintf(buf, "-huse16 %c86", opt_O);
      command_opt(buf);
   }
   command_opt(optim_rules);

   command_opt("rules.start");
   command_opts('o');

   if (opt_O) {
      if (opt_arch == 0)
	 sprintf(buf, "rules.%c86", opt_O);
      else
	 sprintf(buf, "rules.lv_%c", opt_O);
      command_opt(buf);
   }

   switch(opt_arch) {
   case 0: command_opt("rules.86"); break;
   case 1:
   case 2: command_opt("rules.i386"); break;
   case 4: command_opt("rules.6809"); break;
   default:command_opt("rules.mid"); break;
   }

   command_opt("rules.end");

   run_command(file);
}

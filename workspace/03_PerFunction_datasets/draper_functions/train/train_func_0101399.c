share_start(Function *global_funcs)
{

  global = global_funcs;

  module_register(MODULE_NAME, share_table, 2, 3);
  if (!module_depend(MODULE_NAME, "eggdrop", 106, 0)) {
    module_undepend(MODULE_NAME);
    return "This module requires Eggdrop 1.6.0 or later.";
  }
  if (!(transfer_funcs = module_depend(MODULE_NAME, "transfer", 2, 0))) {
    module_undepend(MODULE_NAME);
    return "This module requires transfer module 2.0 or later.";
  }
  if (!(channels_funcs = module_depend(MODULE_NAME, "channels", 1, 0))) {
    module_undepend(MODULE_NAME);
    return "This module requires channels module 1.0 or later.";
  }
  add_hook(HOOK_SHAREOUT, (Function) shareout_mod);
  add_hook(HOOK_SHAREIN, (Function) sharein_mod);
  add_hook(HOOK_MINUTELY, (Function) check_expired_tbufs);
  add_hook(HOOK_READ_USERFILE, (Function) hook_read_userfile);
  add_hook(HOOK_SECONDLY, (Function) check_delay);
  add_help_reference("share.help");
  def_dcc_bot_kill = DCC_BOT.kill;
  DCC_BOT.kill = cancel_user_xfer;
  add_tcl_ints(my_ints);
  add_tcl_strings(my_strings);
  add_builtins(H_dcc, my_cmds);
  uff_init();
  uff_addtable(internal_uff_table);
  return NULL;
}

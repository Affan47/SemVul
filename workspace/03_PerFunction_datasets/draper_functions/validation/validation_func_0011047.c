hypervisor_exec_cmd(hypervisor_conn_t *conn,
                               char *mod_name,char *cmd_name,
                               int argc,char *argv[])
{
   hypervisor_module_t *module;
   hypervisor_cmd_t *cmd;

   if (!(module = hypervisor_find_module(mod_name))) {
      hypervisor_send_reply(conn,HSC_ERR_UNK_MODULE,1,"Unknown module '%s'",
                            mod_name);
      return(-1);
   }

   if (!(cmd = hypervisor_find_cmd(module,cmd_name))) {
      hypervisor_send_reply(conn,HSC_ERR_UNK_CMD,1,"Unknown command '%s'",
                            cmd_name);
      return(-1);
   }

   if ((argc < cmd->min_param) || (argc > cmd->max_param))  {
      hypervisor_send_reply(conn,HSC_ERR_BAD_PARAM,1,
                            "Bad number of parameters (%d with min/max=%d/%d)",
                            argc,cmd->min_param,cmd->max_param);
      return(-1);
   }

   conn->cur_module = module;

   return(cmd->handler(conn,argc,argv));
}

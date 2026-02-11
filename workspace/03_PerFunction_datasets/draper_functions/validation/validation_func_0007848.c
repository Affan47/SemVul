module(cmd_options *opt)
{
  if(!opt)
    return;

  switch(opt->value)
    {

    case CMD_MOD_LIST:
#ifdef OLD_MODULE_LIBRARY
      cout << ModuleLibrary::DisplayFileList();
#else
      ModuleLibrary::ListLoadableModules();
#endif
      break;

    default:
      cout << "cmd_module error:";
      if(opt->name)
        cout << " no parameters with option: " << opt->name;
      cout << endl;
    }

}

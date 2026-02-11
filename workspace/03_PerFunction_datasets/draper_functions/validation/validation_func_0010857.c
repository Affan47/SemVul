cli_create_instance(char *name,char *platform_name,
                                          int instance_id)
{
   vm_instance_t *vm;

   vm = vm_create_instance(name,instance_id,platform_name);

   if (vm == NULL) {
      fprintf(stderr,"%s: unable to create instance %s!\n",platform_name,name);
      return NULL;
   }

   return vm;
}

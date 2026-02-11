free_runscript(RUNSCRIPT *script)
{
   Dmsg0(500, "runscript: freeing RUNSCRIPT object\n");

   if (script->command) {
      free_pool_memory(script->command);
   }
   if (script->target) {
      free_pool_memory(script->target);
   }
   free(script);
}

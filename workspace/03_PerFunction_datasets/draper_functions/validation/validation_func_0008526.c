_ecore_exe_make_sure_its_really_dead(void *data)
{
   struct _ecore_exe_dead_exe *dead;

   dead = data;
   if (dead)
   {
      Ecore_Exe *exe = NULL;

      if ((exe = _ecore_exe_is_it_alive(dead->pid)))
      {
         ERR("RUN!  The zombie wants to eat your brains!  And your CPU!");
         if (dead->cmd)
           INF("%s (%d) is not really dead.", dead->cmd, dead->pid);
         else
           INF("PID %d is not really dead.", dead->pid);
         exe->doomsday_clock = NULL;
      }
      IF_FREE(dead->cmd);
      free(dead);
   }
   return ECORE_CALLBACK_CANCEL;
}

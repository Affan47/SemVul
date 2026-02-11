get_cmd(const char *prompt)
{
   static char cmd[1000];

   printf("%s", prompt);
   if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
      printf("\n");
      quit = true;
      return NULL;
   }
   strip_trailing_junk(cmd);
   return cmd;
}

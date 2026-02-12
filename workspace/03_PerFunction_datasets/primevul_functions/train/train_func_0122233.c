static void stbi__stdio_skip(void *user, int n)
{
   int ch;
   fseek((FILE*) user, n, SEEK_CUR);
   ch = fgetc((FILE*) user);
   if (ch != EOF) {
      ungetc(ch, (FILE *) user);
   }
}

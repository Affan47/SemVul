print_filename (char const *file)
{


  while (*file)
    {
      switch (*file)
        {
        case '\n':
          fputs ("\\n", stdout);
          break;

        case '\\':
          fputs ("\\\\", stdout);
          break;

        default:
          putchar (*file);
          break;
        }
      file++;
    }
}

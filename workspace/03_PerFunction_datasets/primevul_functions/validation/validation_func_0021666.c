context_length_arg (char const *str, intmax_t *out)
{
  switch (xstrtoimax (str, 0, 10, out, ""))
    {
    case LONGINT_OK:
    case LONGINT_OVERFLOW:
      if (0 <= *out)
        break;

    default:
      error (EXIT_TROUBLE, 0, "%s: %s", str,
             _("invalid context length argument"));
    }
}

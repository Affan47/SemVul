diagnostic_set_caret_max_width (diagnostic_context *context, int value)
{

  value = value ? value - 1
    : (isatty (fileno (context->printer->buffer->stream))
       ? getenv_columns () - 1: INT_MAX);

  if (value <= 0)
    value = INT_MAX;

  context->caret_max_width = value;
}

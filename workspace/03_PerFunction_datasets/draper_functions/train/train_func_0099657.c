print_semantic_function_header (lf *file,
				const char *basename,
				const char *format_name,
				opcode_bits *expanded_bits,
				int is_function_definition,
				int nr_prefetched_words)
{
  int indent;
  lf_printf (file, "\n");
  lf_print__function_type_function (file, print_semantic_function_type,
				    "EXTERN_SEMANTICS",
				    (is_function_definition ? "\n" : " "));
  indent = print_function_name (file,
				basename,
				format_name,
				NULL,
				expanded_bits,
				function_name_prefix_semantics);
  if (is_function_definition)
    {
      indent += lf_printf (file, " ");
      lf_indent (file, +indent);
    }
  else
    {
      lf_printf (file, "\n");
    }
  lf_printf (file, "(");
  lf_indent (file, +1);
  print_semantic_function_formal (file, nr_prefetched_words);
  lf_indent (file, -1);
  lf_printf (file, ")");
  if (is_function_definition)
    {
      lf_indent (file, -indent);
    }
  else
    {
      lf_printf (file, ";");
    }
  lf_printf (file, "\n");
}

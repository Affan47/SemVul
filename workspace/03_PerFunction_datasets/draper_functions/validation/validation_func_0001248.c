cdfg_get_subprogram_identifier_string(pIIR_SubprogramDeclaration sd)
{
  const char *separator = "";
  string result = "\"" + get_escaped_string(get_long_name(sd))+ "(";
  for (pIIR_InterfaceList al = sd->interface_declarations; al; al = al->rest) {
    result += separator + get_escaped_string(get_long_name(get_declaration(al->first->subtype)));
    separator = ",";
  }
  result += ")";
  if (sd->is(IR_FUNCTION_DECLARATION))
    result += get_escaped_string(get_long_name(get_declaration(pIIR_FunctionDeclaration(sd)->return_type)));

  result += "\"";

  return result;
}

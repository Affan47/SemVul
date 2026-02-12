string t_go_generator::function_signature(t_function* tfunction, string prefix) {

  return publicize(prefix + tfunction->get_name()) + "(" + argument_list(tfunction->get_arglist())
         + ")";
}

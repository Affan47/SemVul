void t_cpp_generator::close_generator() {

  f_types_ << ns_close_ << endl << endl;
  f_types_impl_ << ns_close_ << endl;
  f_types_tcc_ << ns_close_ << endl << endl;


  if (gen_templates_) {
    f_types_ << "#include \"" << get_include_prefix(*get_program()) << program_name_
             << "_types.tcc\"" << endl << endl;
  }


  f_types_ << "#endif" << endl;
  f_types_tcc_ << "#endif" << endl;


  f_types_.close();
  f_types_impl_.close();
  f_types_tcc_.close();
}

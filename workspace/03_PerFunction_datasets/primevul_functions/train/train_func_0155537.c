void t_cpp_generator::generate_struct_declaration(ofstream& out,
                                                  t_struct* tstruct,
                                                  bool is_exception,
                                                  bool pointers,
                                                  bool read,
                                                  bool write,
                                                  bool swap) {
  string extends = "";
  if (is_exception) {
    extends = " : public ::apache::thrift::TException";
  }

  vector<t_field*>::const_iterator m_iter;
  const vector<t_field*>& members = tstruct->get_members();

  bool has_nonrequired_fields = false;
  for (m_iter = members.begin(); m_iter != members.end(); ++m_iter) {
    if ((*m_iter)->get_req() != t_field::T_REQUIRED)
      has_nonrequired_fields = true;
  }

  if (has_nonrequired_fields && (!pointers || read)) {

    out << indent() << "typedef struct _" << tstruct->get_name() << "__isset {" << endl;
    indent_up();

    indent(out) << "_" << tstruct->get_name() << "__isset() ";
    bool first = true;
    for (m_iter = members.begin(); m_iter != members.end(); ++m_iter) {
      if ((*m_iter)->get_req() == t_field::T_REQUIRED) {
        continue;
      }
      string isSet = ((*m_iter)->get_value() != NULL) ? "true" : "false";
      if (first) {
        first = false;
        out << ": " << (*m_iter)->get_name() << "(" << isSet << ")";
      } else {
        out << ", " << (*m_iter)->get_name() << "(" << isSet << ")";
      }
    }
    out << " {}" << endl;

    for (m_iter = members.begin(); m_iter != members.end(); ++m_iter) {
      if ((*m_iter)->get_req() != t_field::T_REQUIRED) {
        indent(out) << "bool " << (*m_iter)->get_name() << " :1;" << endl;
      }
    }

    indent_down();
    indent(out) << "} _" << tstruct->get_name() << "__isset;" << endl;
  }

  out << endl;

  out << indent() << "class " << tstruct->get_name() << extends << " {" << endl << indent()
      << " public:" << endl << endl;
  indent_up();

  generate_struct_fingerprint(out, tstruct, false);

  if (!pointers) {

    indent(out) << tstruct->get_name() << "(const " << tstruct->get_name() << "&);" << endl;

    if (gen_moveable_) {
      indent(out) << tstruct->get_name() << "(" << tstruct->get_name() << "&&);" << endl;
    }

    indent(out) << tstruct->get_name() << "& operator=(const " << tstruct->get_name() << "&);"
                << endl;

    if (gen_moveable_) {
      indent(out) << tstruct->get_name() << "& operator=(" << tstruct->get_name() << "&&);" << endl;
    }

    indent(out) << tstruct->get_name() << "()";

    bool init_ctor = false;

    for (m_iter = members.begin(); m_iter != members.end(); ++m_iter) {
      t_type* t = get_true_type((*m_iter)->get_type());
      if (t->is_base_type() || t->is_enum() || is_reference(*m_iter)) {
        string dval;
        if (t->is_enum()) {
          dval += "(" + type_name(t) + ")";
        }
        dval += (t->is_string() || is_reference(*m_iter)) ? "" : "0";
        t_const_value* cv = (*m_iter)->get_value();
        if (cv != NULL) {
          dval = render_const_value(out, (*m_iter)->get_name(), t, cv);
        }
        if (!init_ctor) {
          init_ctor = true;
          out << " : ";
          out << (*m_iter)->get_name() << "(" << dval << ")";
        } else {
          out << ", " << (*m_iter)->get_name() << "(" << dval << ")";
        }
      }
    }
    out << " {" << endl;
    indent_up();

    for (m_iter = members.begin(); m_iter != members.end(); ++m_iter) {
      t_type* t = get_true_type((*m_iter)->get_type());

      if (!t->is_base_type()) {
        t_const_value* cv = (*m_iter)->get_value();
        if (cv != NULL) {
          print_const_value(out, (*m_iter)->get_name(), t, cv);
        }
      }
    }
    scope_down(out);
  }

  if (tstruct->annotations_.find("final") == tstruct->annotations_.end()) {
    out << endl << indent() << "virtual ~" << tstruct->get_name() << "() throw();" << endl;
  }

  if (gen_dense_) {
    indent(out) << "static ::apache::thrift::reflection::local::TypeSpec* local_reflection;" << endl
                << endl;
  }

  for (m_iter = members.begin(); m_iter != members.end(); ++m_iter) {
    indent(out) << declare_field(*m_iter,
                                 false,
                                 (pointers && !(*m_iter)->get_type()->is_xception()),
                                 !read) << endl;
  }

  if (has_nonrequired_fields && (!pointers || read)) {
    out << endl << indent() << "_" << tstruct->get_name() << "__isset __isset;" << endl;
  }

  for (m_iter = members.begin(); m_iter != members.end(); ++m_iter) {
    if (pointers) {
      continue;
    }
    if (is_reference((*m_iter))) {
      out << endl << indent() << "void __set_" << (*m_iter)->get_name() << "(boost::shared_ptr<"
          << type_name((*m_iter)->get_type(), false, false) << ">";
      out << " val);" << endl;
    } else {
      out << endl << indent() << "void __set_" << (*m_iter)->get_name() << "("
          << type_name((*m_iter)->get_type(), false, true);
      out << " val);" << endl;
    }
  }
  out << endl;

  if (!pointers) {

    if (!gen_no_default_operators_) {

      out << indent() << "bool operator == (const " << tstruct->get_name() << " & "
          << (members.size() > 0 ? "rhs" : "/* rhs */") << ") const" << endl;
      scope_up(out);
      for (m_iter = members.begin(); m_iter != members.end(); ++m_iter) {

        if ((*m_iter)->get_req() != t_field::T_OPTIONAL) {
          out << indent() << "if (!(" << (*m_iter)->get_name() << " == rhs."
              << (*m_iter)->get_name() << "))" << endl << indent() << "  return false;" << endl;
        } else {
          out << indent() << "if (__isset." << (*m_iter)->get_name() << " != rhs.__isset."
              << (*m_iter)->get_name() << ")" << endl << indent() << "  return false;" << endl
              << indent() << "else if (__isset." << (*m_iter)->get_name() << " && !("
              << (*m_iter)->get_name() << " == rhs." << (*m_iter)->get_name() << "))" << endl
              << indent() << "  return false;" << endl;
        }
      }
      indent(out) << "return true;" << endl;
      scope_down(out);
      out << indent() << "bool operator != (const " << tstruct->get_name() << " &rhs) const {"
          << endl << indent() << "  return !(*this == rhs);" << endl << indent() << "}" << endl
          << endl;

      out << indent() << "bool operator < (const " << tstruct->get_name() << " & ) const;" << endl
          << endl;
    }
  }

  if (read) {
    if (gen_templates_) {
      out << indent() << "template <class Protocol_>" << endl << indent()
          << "uint32_t read(Protocol_* iprot);" << endl;
    } else {
      out << indent() << "uint32_t read("
          << "::apache::thrift::protocol::TProtocol* iprot);" << endl;
    }
  }
  if (write) {
    if (gen_templates_) {
      out << indent() << "template <class Protocol_>" << endl << indent()
          << "uint32_t write(Protocol_* oprot) const;" << endl;
    } else {
      out << indent() << "uint32_t write("
          << "::apache::thrift::protocol::TProtocol* oprot) const;" << endl;
    }
  }
  out << endl;

  out << indent() << "friend ";
  generate_struct_ostream_operator_decl(out, tstruct);
  out << ";" << endl << endl;

  if (is_exception) {
    out << indent() << "mutable std::string thriftTExceptionMessageHolder_;" << endl;
    out << indent();
    generate_exception_what_method_decl(out, tstruct, false);
    out << ";" << endl;
  }

  indent_down();
  indent(out) << "};" << endl << endl;

  if (swap) {

    out << indent() << "void swap(" << tstruct->get_name() << " &a, " << tstruct->get_name()
        << " &b);" << endl << endl;
  }
}
}

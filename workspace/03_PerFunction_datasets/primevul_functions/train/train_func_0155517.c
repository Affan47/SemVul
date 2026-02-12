void t_cpp_generator::generate_process_function(t_service* tservice,
                                                t_function* tfunction,
                                                string style,
                                                bool specialized) {
  t_struct* arg_struct = tfunction->get_arglist();
  const std::vector<t_field*>& fields = arg_struct->get_members();
  vector<t_field*>::const_iterator f_iter;

  t_struct* xs = tfunction->get_xceptions();
  const std::vector<t_field*>& xceptions = xs->get_members();
  vector<t_field*>::const_iterator x_iter;
  string service_func_name = "\"" + tservice->get_name() + "." + tfunction->get_name() + "\"";

  std::ofstream& out = (gen_templates_ ? f_service_tcc_ : f_service_);

  string prot_type = (specialized ? "Protocol_" : "::apache::thrift::protocol::TProtocol");
  string class_suffix;
  if (gen_templates_) {
    class_suffix = "T<Protocol_>";
  }

  if (style != "Cob") {

    if (gen_templates_) {
      out << indent() << "template <class Protocol_>" << endl;
    }
    const bool unnamed_oprot_seqid = tfunction->is_oneway() && !(gen_templates_ && !specialized);
    out << "void " << tservice->get_name() << "Processor" << class_suffix << "::"
        << "process_" << tfunction->get_name() << "("
        << "int32_t" << (unnamed_oprot_seqid ? ", " : " seqid, ") << prot_type << "* iprot, "
        << prot_type << "*" << (unnamed_oprot_seqid ? ", " : " oprot, ") << "void* callContext)"
        << endl;
    scope_up(out);

    string argsname = tservice->get_name() + "_" + tfunction->get_name() + "_args";
    string resultname = tservice->get_name() + "_" + tfunction->get_name() + "_result";

    if (tfunction->is_oneway() && !unnamed_oprot_seqid) {
      out << indent() << "(void) seqid;" << endl << indent() << "(void) oprot;" << endl;
    }

    out << indent() << "void* ctx = NULL;" << endl << indent()
        << "if (this->eventHandler_.get() != NULL) {" << endl << indent()
        << "  ctx = this->eventHandler_->getContext(" << service_func_name << ", callContext);"
        << endl << indent() << "}" << endl << indent()
        << "::apache::thrift::TProcessorContextFreer freer("
        << "this->eventHandler_.get(), ctx, " << service_func_name << ");" << endl << endl
        << indent() << "if (this->eventHandler_.get() != NULL) {" << endl << indent()
        << "  this->eventHandler_->preRead(ctx, " << service_func_name << ");" << endl << indent()
        << "}" << endl << endl << indent() << argsname << " args;" << endl << indent()
        << "args.read(iprot);" << endl << indent() << "iprot->readMessageEnd();" << endl << indent()
        << "uint32_t bytes = iprot->getTransport()->readEnd();" << endl << endl << indent()
        << "if (this->eventHandler_.get() != NULL) {" << endl << indent()
        << "  this->eventHandler_->postRead(ctx, " << service_func_name << ", bytes);" << endl
        << indent() << "}" << endl << endl;

    if (!tfunction->is_oneway()) {
      out << indent() << resultname << " result;" << endl;
    }

    out << indent() << "try {" << endl;
    indent_up();

    bool first = true;
    out << indent();
    if (!tfunction->is_oneway() && !tfunction->get_returntype()->is_void()) {
      if (is_complex_type(tfunction->get_returntype())) {
        first = false;
        out << "iface_->" << tfunction->get_name() << "(result.success";
      } else {
        out << "result.success = iface_->" << tfunction->get_name() << "(";
      }
    } else {
      out << "iface_->" << tfunction->get_name() << "(";
    }
    for (f_iter = fields.begin(); f_iter != fields.end(); ++f_iter) {
      if (first) {
        first = false;
      } else {
        out << ", ";
      }
      out << "args." << (*f_iter)->get_name();
    }
    out << ");" << endl;

    if (!tfunction->is_oneway() && !tfunction->get_returntype()->is_void()) {
      out << indent() << "result.__isset.success = true;" << endl;
    }

    indent_down();
    out << indent() << "}";

    if (!tfunction->is_oneway()) {
      for (x_iter = xceptions.begin(); x_iter != xceptions.end(); ++x_iter) {
        out << " catch (" << type_name((*x_iter)->get_type()) << " &" << (*x_iter)->get_name()
            << ") {" << endl;
        if (!tfunction->is_oneway()) {
          indent_up();
          out << indent() << "result." << (*x_iter)->get_name() << " = " << (*x_iter)->get_name()
              << ";" << endl << indent() << "result.__isset." << (*x_iter)->get_name() << " = true;"
              << endl;
          indent_down();
          out << indent() << "}";
        } else {
          out << "}";
        }
      }
    }

    if (!tfunction->is_oneway()) {
      out << " catch (const std::exception& e) {" << endl;
    } else {
      out << " catch (const std::exception&) {" << endl;
    }

    indent_up();
    out << indent() << "if (this->eventHandler_.get() != NULL) {" << endl << indent()
        << "  this->eventHandler_->handlerError(ctx, " << service_func_name << ");" << endl
        << indent() << "}" << endl;

    if (!tfunction->is_oneway()) {
      out << endl << indent() << "::apache::thrift::TApplicationException x(e.what());" << endl
          << indent() << "oprot->writeMessageBegin(\"" << tfunction->get_name()
          << "\", ::apache::thrift::protocol::T_EXCEPTION, seqid);" << endl << indent()
          << "x.write(oprot);" << endl << indent() << "oprot->writeMessageEnd();" << endl
          << indent() << "oprot->getTransport()->writeEnd();" << endl << indent()
          << "oprot->getTransport()->flush();" << endl;
    }
    out << indent() << "return;" << endl;
    indent_down();
    out << indent() << "}" << endl << endl;

    if (tfunction->is_oneway()) {
      out << indent() << "if (this->eventHandler_.get() != NULL) {" << endl << indent()
          << "  this->eventHandler_->asyncComplete(ctx, " << service_func_name << ");" << endl
          << indent() << "}" << endl << endl << indent() << "return;" << endl;
      indent_down();
      out << "}" << endl << endl;
      return;
    }

    out << indent() << "if (this->eventHandler_.get() != NULL) {" << endl << indent()
        << "  this->eventHandler_->preWrite(ctx, " << service_func_name << ");" << endl << indent()
        << "}" << endl << endl << indent() << "oprot->writeMessageBegin(\"" << tfunction->get_name()
        << "\", ::apache::thrift::protocol::T_REPLY, seqid);" << endl << indent()
        << "result.write(oprot);" << endl << indent() << "oprot->writeMessageEnd();" << endl
        << indent() << "bytes = oprot->getTransport()->writeEnd();" << endl << indent()
        << "oprot->getTransport()->flush();" << endl << endl << indent()
        << "if (this->eventHandler_.get() != NULL) {" << endl << indent()
        << "  this->eventHandler_->postWrite(ctx, " << service_func_name << ", bytes);" << endl
        << indent() << "}" << endl;

    scope_down(out);
    out << endl;
  }

  else {

    if (gen_templates_) {
      out << indent() << "template <class Protocol_>" << endl;
    }
    out << "void " << tservice->get_name() << "AsyncProcessor" << class_suffix << "::process_"
        << tfunction->get_name() << "(tcxx::function<void(bool ok)> cob, int32_t seqid, "
        << prot_type << "* iprot, " << prot_type << "* oprot)" << endl;
    scope_up(out);

    if (gen_templates_ && !specialized) {

      out << indent() << "Protocol_* _iprot = dynamic_cast<Protocol_*>(iprot);" << endl << indent()
          << "Protocol_* _oprot = dynamic_cast<Protocol_*>(oprot);" << endl << indent()
          << "if (_iprot && _oprot) {" << endl << indent() << "  return process_"
          << tfunction->get_name() << "(cob, seqid, _iprot, _oprot);" << endl << indent() << "}"
          << endl << indent() << "T_GENERIC_PROTOCOL(this, iprot, _iprot);" << endl << indent()
          << "T_GENERIC_PROTOCOL(this, oprot, _oprot);" << endl << endl;
    }

    if (tfunction->is_oneway()) {
      out << indent() << "(void) seqid;" << endl << indent() << "(void) oprot;" << endl;
    }

    out << indent() << tservice->get_name() + "_" + tfunction->get_name() << "_args args;" << endl
        << indent() << "void* ctx = NULL;" << endl << indent()
        << "if (this->eventHandler_.get() != NULL) {" << endl << indent()
        << "  ctx = this->eventHandler_->getContext(" << service_func_name << ", NULL);" << endl
        << indent() << "}" << endl << indent() << "::apache::thrift::TProcessorContextFreer freer("
        << "this->eventHandler_.get(), ctx, " << service_func_name << ");" << endl << endl
        << indent() << "try {" << endl;
    indent_up();
    out << indent() << "if (this->eventHandler_.get() != NULL) {" << endl << indent()
        << "  this->eventHandler_->preRead(ctx, " << service_func_name << ");" << endl << indent()
        << "}" << endl << indent() << "args.read(iprot);" << endl << indent()
        << "iprot->readMessageEnd();" << endl << indent()
        << "uint32_t bytes = iprot->getTransport()->readEnd();" << endl << indent()
        << "if (this->eventHandler_.get() != NULL) {" << endl << indent()
        << "  this->eventHandler_->postRead(ctx, " << service_func_name << ", bytes);" << endl
        << indent() << "}" << endl;
    scope_down(out);

    out << indent() << "catch (const std::exception&) {" << endl << indent()
        << "  if (this->eventHandler_.get() != NULL) {" << endl << indent()
        << "    this->eventHandler_->handlerError(ctx, " << service_func_name << ");" << endl
        << indent() << "  }" << endl << indent() << "  return cob(false);" << endl << indent()
        << "}" << endl;

    if (tfunction->is_oneway()) {
      out << indent() << "if (this->eventHandler_.get() != NULL) {" << endl << indent()
          << "  this->eventHandler_->asyncComplete(ctx, " << service_func_name << ");" << endl
          << indent() << "}" << endl;
    }

    out << indent() << "freer.unregister();" << endl;
    if (tfunction->is_oneway()) {

      out << indent() << "iface_->" << tfunction->get_name() << "("
          << "tcxx::bind(cob, true)" << endl;
      indent_up();
      indent_up();
    } else {
      string ret_arg, ret_placeholder;
      if (!tfunction->get_returntype()->is_void()) {
        ret_arg = ", const " + type_name(tfunction->get_returntype()) + "& _return";
        ret_placeholder = ", tcxx::placeholders::_1";
      }

      out << indent() << "void (" << tservice->get_name() << "AsyncProcessor" << class_suffix
          << "::*return_fn)(tcxx::function<void(bool ok)> "
          << "cob, int32_t seqid, " << prot_type << "* oprot, void* ctx" << ret_arg
          << ") =" << endl;
      out << indent() << "  &" << tservice->get_name() << "AsyncProcessor" << class_suffix
          << "::return_" << tfunction->get_name() << ";" << endl;
      if (!xceptions.empty()) {
        out << indent() << "void (" << tservice->get_name() << "AsyncProcessor" << class_suffix
            << "::*throw_fn)(tcxx::function<void(bool ok)> "
            << "cob, int32_t seqid, " << prot_type << "* oprot, void* ctx, "
            << "::apache::thrift::TDelayedException* _throw) =" << endl;
        out << indent() << "  &" << tservice->get_name() << "AsyncProcessor" << class_suffix
            << "::throw_" << tfunction->get_name() << ";" << endl;
      }

      out << indent() << "iface_->" << tfunction->get_name() << "(" << endl;
      indent_up();
      indent_up();
      out << indent() << "tcxx::bind(return_fn, this, cob, seqid, oprot, ctx" << ret_placeholder
          << ")";
      if (!xceptions.empty()) {
        out << ',' << endl << indent() << "tcxx::bind(throw_fn, this, cob, seqid, oprot, "
            << "ctx, tcxx::placeholders::_1)";
      }
    }

    for (f_iter = fields.begin(); f_iter != fields.end(); ++f_iter) {
      out << ',' << endl << indent() << "args." << (*f_iter)->get_name();
    }
    out << ");" << endl;
    indent_down();
    indent_down();
    scope_down(out);
    out << endl;

    if (!tfunction->is_oneway()) {
      string ret_arg_decl, ret_arg_name;
      if (!tfunction->get_returntype()->is_void()) {
        ret_arg_decl = ", const " + type_name(tfunction->get_returntype()) + "& _return";
        ret_arg_name = ", _return";
      }
      if (gen_templates_) {
        out << indent() << "template <class Protocol_>" << endl;
      }
      out << "void " << tservice->get_name() << "AsyncProcessor" << class_suffix << "::return_"
          << tfunction->get_name() << "(tcxx::function<void(bool ok)> cob, int32_t seqid, "
          << prot_type << "* oprot, void* ctx" << ret_arg_decl << ')' << endl;
      scope_up(out);

      if (gen_templates_ && !specialized) {

        out << indent() << "Protocol_* _oprot = dynamic_cast<Protocol_*>(oprot);" << endl
            << indent() << "if (_oprot) {" << endl << indent() << "  return return_"
            << tfunction->get_name() << "(cob, seqid, _oprot, ctx" << ret_arg_name << ");" << endl
            << indent() << "}" << endl << indent() << "T_GENERIC_PROTOCOL(this, oprot, _oprot);"
            << endl << endl;
      }

      out << indent() << tservice->get_name() << "_" << tfunction->get_name() << "_presult result;"
          << endl;
      if (!tfunction->get_returntype()->is_void()) {

        out << indent() << "result.success = const_cast<" << type_name(tfunction->get_returntype())
            << "*>(&_return);" << endl << indent() << "result.__isset.success = true;" << endl;
      }

      out << endl << indent() << "if (this->eventHandler_.get() != NULL) {" << endl << indent()
          << "  ctx = this->eventHandler_->getContext(" << service_func_name << ", NULL);" << endl
          << indent() << "}" << endl << indent()
          << "::apache::thrift::TProcessorContextFreer freer("
          << "this->eventHandler_.get(), ctx, " << service_func_name << ");" << endl << endl
          << indent() << "if (this->eventHandler_.get() != NULL) {" << endl << indent()
          << "  this->eventHandler_->preWrite(ctx, " << service_func_name << ");" << endl
          << indent() << "}" << endl << endl << indent() << "oprot->writeMessageBegin(\""
          << tfunction->get_name() << "\", ::apache::thrift::protocol::T_REPLY, seqid);" << endl
          << indent() << "result.write(oprot);" << endl << indent() << "oprot->writeMessageEnd();"
          << endl << indent() << "uint32_t bytes = oprot->getTransport()->writeEnd();" << endl
          << indent() << "oprot->getTransport()->flush();" << endl << indent()
          << "if (this->eventHandler_.get() != NULL) {" << endl << indent()
          << "  this->eventHandler_->postWrite(ctx, " << service_func_name << ", bytes);" << endl
          << indent() << "}" << endl << indent() << "return cob(true);" << endl;
      scope_down(out);
      out << endl;
    }

    if (!tfunction->is_oneway() && !xceptions.empty()) {
      if (gen_templates_) {
        out << indent() << "template <class Protocol_>" << endl;
      }
      out << "void " << tservice->get_name() << "AsyncProcessor" << class_suffix << "::throw_"
          << tfunction->get_name() << "(tcxx::function<void(bool ok)> cob, int32_t seqid, "
          << prot_type << "* oprot, void* ctx, "
          << "::apache::thrift::TDelayedException* _throw)" << endl;
      scope_up(out);

      if (gen_templates_ && !specialized) {

        out << indent() << "Protocol_* _oprot = dynamic_cast<Protocol_*>(oprot);" << endl
            << indent() << "if (_oprot) {" << endl << indent() << "  return throw_"
            << tfunction->get_name() << "(cob, seqid, _oprot, ctx, _throw);" << endl << indent()
            << "}" << endl << indent() << "T_GENERIC_PROTOCOL(this, oprot, _oprot);" << endl
            << endl;
      }

      out << endl << indent() << "if (this->eventHandler_.get() != NULL) {" << endl << indent()
          << "  ctx = this->eventHandler_->getContext(" << service_func_name << ", NULL);" << endl
          << indent() << "}" << endl << indent()
          << "::apache::thrift::TProcessorContextFreer freer("
          << "this->eventHandler_.get(), ctx, " << service_func_name << ");" << endl << endl;

      out << indent() << tservice->get_name() << "_" << tfunction->get_name() << "_result result;"
          << endl << endl << indent() << "try {" << endl;
      indent_up();
      out << indent() << "_throw->throw_it();" << endl << indent() << "return cob(false);"
          << endl;
      indent_down();
      out << indent() << '}';
      for (x_iter = xceptions.begin(); x_iter != xceptions.end(); ++x_iter) {
        out << "  catch (" << type_name((*x_iter)->get_type()) << " &" << (*x_iter)->get_name()
            << ") {" << endl;
        indent_up();
        out << indent() << "result." << (*x_iter)->get_name() << " = " << (*x_iter)->get_name()
            << ";" << endl << indent() << "result.__isset." << (*x_iter)->get_name() << " = true;"
            << endl;
        scope_down(out);
      }

      out << " catch (std::exception& e) {" << endl;
      indent_up();
      out << indent() << "if (this->eventHandler_.get() != NULL) {" << endl << indent()
          << "  this->eventHandler_->handlerError(ctx, " << service_func_name << ");" << endl
          << indent() << "}" << endl << endl << indent()
          << "::apache::thrift::TApplicationException x(e.what());" << endl << indent()
          << "oprot->writeMessageBegin(\"" << tfunction->get_name()
          << "\", ::apache::thrift::protocol::T_EXCEPTION, seqid);" << endl << indent()
          << "x.write(oprot);" << endl << indent() << "oprot->writeMessageEnd();" << endl
          << indent() << "oprot->getTransport()->writeEnd();" << endl << indent()
          << "oprot->getTransport()->flush();" << endl <<

          indent() << "return cob(true);" << endl;
      scope_down(out);

      out << indent() << "if (this->eventHandler_.get() != NULL) {" << endl << indent()
          << "  this->eventHandler_->preWrite(ctx, " << service_func_name << ");" << endl
          << indent() << "}" << endl << endl << indent() << "oprot->writeMessageBegin(\""
          << tfunction->get_name() << "\", ::apache::thrift::protocol::T_REPLY, seqid);" << endl
          << indent() << "result.write(oprot);" << endl << indent() << "oprot->writeMessageEnd();"
          << endl << indent() << "uint32_t bytes = oprot->getTransport()->writeEnd();" << endl
          << indent() << "oprot->getTransport()->flush();" << endl << indent()
          << "if (this->eventHandler_.get() != NULL) {" << endl << indent()
          << "  this->eventHandler_->postWrite(ctx, " << service_func_name << ", bytes);" << endl
          << indent() << "}" << endl << indent() << "return cob(true);" << endl;
      scope_down(out);
      out << endl;
    }
  }
}
}
}

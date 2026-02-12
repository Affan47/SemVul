void t_cpp_generator::generate_service_interface_factory(t_service* tservice, string style) {
  string service_if_name = service_name_ + style + "If";


  t_service* base_service = tservice;
  while (base_service->get_extends() != NULL) {
    base_service = base_service->get_extends();
  }
  string base_if_name = type_name(base_service) + style + "If";


  string factory_name = service_if_name + "Factory";
  string extends;
  if (tservice->get_extends() != NULL) {
    extends = " : virtual public " + type_name(tservice->get_extends()) + style + "IfFactory";
  }

  f_header_ << "class " << factory_name << extends << " {" << endl << " public:" << endl;
  indent_up();
  f_header_ << indent() << "typedef " << service_if_name << " Handler;" << endl << endl << indent()
            << "virtual ~" << factory_name << "() {}" << endl << endl << indent() << "virtual "
            << service_if_name << "* getHandler("
            << "const ::apache::thrift::TConnectionInfo& connInfo) = 0;" << endl << indent()
            << "virtual void releaseHandler(" << base_if_name << "* /* handler */) = 0;" << endl;

  indent_down();
  f_header_ << "};" << endl << endl;


  string singleton_factory_name = service_if_name + "SingletonFactory";
  f_header_ << "class " << singleton_factory_name << " : virtual public " << factory_name << " {"
            << endl << " public:" << endl;
  indent_up();
  f_header_ << indent() << singleton_factory_name << "(const boost::shared_ptr<" << service_if_name
            << ">& iface) : iface_(iface) {}" << endl << indent() << "virtual ~"
            << singleton_factory_name << "() {}" << endl << endl << indent() << "virtual "
            << service_if_name << "* getHandler("
            << "const ::apache::thrift::TConnectionInfo&) {" << endl << indent()
            << "  return iface_.get();" << endl << indent() << "}" << endl << indent()
            << "virtual void releaseHandler(" << base_if_name << "* /* handler */) {}" << endl;

  f_header_ << endl << " protected:" << endl << indent() << "boost::shared_ptr<" << service_if_name
            << "> iface_;" << endl;

  indent_down();
  f_header_ << "};" << endl << endl;
}

void run() {
    generate_class_definition();


    generate_dispatch_call(false);
    if (generator_->gen_templates_) {
      generate_dispatch_call(true);
    }


    generate_process_functions();

    generate_factory();
  }

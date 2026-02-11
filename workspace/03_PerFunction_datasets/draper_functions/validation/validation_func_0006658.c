do_generate_master_states() {
    char temp[1024];

    Body.pushln("//----------------------------------------------------------");
    Body.pushln("// Master's State-machine ");
    Body.pushln("//----------------------------------------------------------");
    Body.pushln("private void _master_state_machine() {");
    Body.pushln("_master_should_start_workers = false;");
    Body.pushln("_master_should_finish = false;");
    Body.pushln("do {");
    Body.pushln("_master_state = _master_state_nxt ;");
    Body.pushln("switch(_master_state) {");
    gm_gps_beinfo * info = (gm_gps_beinfo *) FE.get_current_backend_info();

    std::list<gm_gps_basic_block*>& bb_blocks = info->get_basic_blocks();
    std::list<gm_gps_basic_block*>::iterator I;

    for (I = bb_blocks.begin(); I != bb_blocks.end(); I++) {
        gm_gps_basic_block* b = *I;
        int id = b->get_id();
        sprintf(temp, "case %d: _master_state_%d(); break;", id, id);
        Body.pushln(temp);
    }
    Body.pushln("}");
    Body.pushln("} while (!_master_should_start_workers && !_master_should_finish);");
    Body.pushln("}");
    Body.NL();

    Body.pushln("//@ Override");
    Body.pushln("public void compute() {");
    Body.pushln("// Graph size is not available in superstep 0");
    Body.pushln("if (getSuperstep() == 0) {");
    Body.pushln("return;");
    Body.pushln("}");
    Body.NL();

    Body.pushln("_master_state_machine();");
    Body.NL();

    Body.pushln("if (_master_should_finish) { ");
    Body.pushln("haltComputation();");
    Body.pushln("writeOutput();");
    Body.pushln("}");

    Body.pushln("}");
    Body.NL();

    gm_redirect_reproduce(f_body);
    gm_baseindent_reproduce(3);

    for (I = bb_blocks.begin(); I != bb_blocks.end(); I++) {
        gm_gps_basic_block* b = *I;
        do_generate_master_state_body(b);
    }
    gm_redirect_reproduce(stdout);
    gm_baseindent_reproduce(0);
}

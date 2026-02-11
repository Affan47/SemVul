generate_master_class_details(std::set<gm_symtab_entry*>& prop, gm_code_writer& Body) {
    std::set<gm_symtab_entry*>::iterator I;

    Body.pushln("@Override");
    Body.pushln("public void write(DataOutput out) throws IOException {");
    Body.pushln("out.writeInt(_master_state);");
    Body.pushln("out.writeInt(_master_state_nxt);");
    Body.pushln("out.writeBoolean(_master_should_start_workers);");
    Body.pushln("out.writeBoolean(_master_should_finish);");

    for (I = prop.begin(); I != prop.end(); I++) {
        gm_symtab_entry * sym = *I;
        gps_syminfo* syminfo = (gps_syminfo*) sym->find_info(GPS_TAG_BB_USAGE);
        if (!syminfo->is_used_in_master()) continue;

        if (sym->getType()->is_collection()) {
            genPutIOBCollection(sym->getId()->get_genname(), sym->getType(), Body, this);
        }
        else {
            genPutIOB(sym->getId()->get_genname(), sym->getType()->getTypeSummary(), Body, this);
        }
    }
    Body.pushln("}");

    Body.pushln("@Override");
    Body.pushln("public void readFields(DataInput in) throws IOException {");
    Body.pushln("_master_state = in.readInt();");
    Body.pushln("_master_state_nxt = in.readInt();");
    Body.pushln("_master_should_start_workers = in.readBoolean();");
    Body.pushln("_master_should_finish = in.readBoolean();");

    for (I = prop.begin(); I != prop.end(); I++) {
        gm_symtab_entry * sym = *I;
        gps_syminfo* syminfo = (gps_syminfo*) sym->find_info(GPS_TAG_BB_USAGE);
        if (!syminfo->is_used_in_master()) continue;

        if (sym->getType()->is_collection()) {
            genGetIOBCollection(sym->getId()->get_genname(), sym->getType(), Body, this);
        }
        else {
            genGetIOB(sym->getId()->get_genname(), sym->getType()->getTypeSummary(), Body, this);
        }
    }
    Body.pushln("}");
}

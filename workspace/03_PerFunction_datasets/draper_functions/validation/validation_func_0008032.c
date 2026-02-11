reset_angles() {
    for (SEC_strand_iterator strand(this); strand; ++strand) {
        if (strand->pointsToOutside()) {
            Angle abs(center, strand->get_fixpoint());
            strand->get_helix()->set_abs_angle(abs);
        }
    }
    set_rel_angle(0);
}

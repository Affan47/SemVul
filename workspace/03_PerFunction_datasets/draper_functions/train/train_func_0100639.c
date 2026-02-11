update_terminal_extension( void **, void **, ED4_base *this_object )
{
    if (this_object->is_terminal()){
        if (this_object->is_spacer_terminal()){
            if (this_object->parent->is_device_manager()) {
                ;

            }
        }
        else if (this_object->is_species_name_terminal()) {
            this_object->extension.size[WIDTH] = MAXSPECIESWIDTH - BRACKETWIDTH * this_object->calc_group_depth();
        }
        else if (this_object->is_sequence_info_terminal()) {
            this_object->extension.size[WIDTH] = MAXINFOWIDTH;
        }
        else if (this_object->is_line_terminal()) {
            this_object->extension.size[WIDTH] =
                TREETERMINALSIZE + MAXSPECIESWIDTH +
                ED4_ROOT->ref_terminals.get_ref_sequence_info()->extension.size[WIDTH] +
                ED4_ROOT->ref_terminals.get_ref_sequence()->extension.size[WIDTH];
        }
    }

    if (this_object->parent) {
        this_object->parent->resize_requested_by_child();
    }

    return ED4_R_OK;
}

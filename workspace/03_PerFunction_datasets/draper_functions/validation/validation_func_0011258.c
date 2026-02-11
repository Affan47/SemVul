print_one_row(ostream &out, int row, string space,
                        bool print_row_num)
{
    if (print_row_num)
	out << "\n" << space << row << ": " ;

    out << "{ " ;

    int elements = element_count();
    int j = 0;
    BaseType *bt_ptr = 0;


    while (j < elements && !bt_ptr) {
        bt_ptr = var_value(row, j++);
        if (bt_ptr) {
            if (bt_ptr->type() == dods_sequence_c)
            	static_cast<Sequence*>(bt_ptr)->print_val_by_rows
                     (out, space + "    ", false, print_row_num);
            else
                bt_ptr->print_val(out, space, false);
        }
    }


    while (j < elements) {
        bt_ptr = var_value(row, j++);
        if (bt_ptr) {
            out << ", ";
            if (bt_ptr->type() == dods_sequence_c)
            	static_cast<Sequence*>(bt_ptr)->print_val_by_rows
                        (out, space + "    ", false, print_row_num);
            else
                bt_ptr->print_val(out, space, false);
        }
    }

    out << " }" ;
}

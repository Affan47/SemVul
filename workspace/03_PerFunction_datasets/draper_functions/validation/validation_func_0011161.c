value_from_output_section(const Expression_eval_info* eei,
			    Output_section* os)
  {
    if (eei->result_section_pointer != NULL)
      *eei->result_section_pointer = os;
    return os->address();
  }

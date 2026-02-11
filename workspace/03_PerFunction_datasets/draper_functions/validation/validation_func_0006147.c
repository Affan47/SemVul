gsb_data_report_text_comparison_dup ( gint last_text_comparison_number )
{
    struct_text_comparison *text_comparison;
    struct_text_comparison *last_text_comparison;
    gint text_comparison_number;

    last_text_comparison = gsb_data_report_text_comparison_get_struct_by_no (last_text_comparison_number);

    if ( !last_text_comparison )
	return 0;

    text_comparison_number = gsb_data_report_text_comparison_new (0);
    text_comparison = gsb_data_report_text_comparison_get_struct_by_no (text_comparison_number);

    text_comparison -> report_number = last_text_comparison -> report_number;
    text_comparison -> link_to_last_text_comparison = last_text_comparison -> link_to_last_text_comparison;
    text_comparison -> field = last_text_comparison -> field;
    text_comparison -> operator = last_text_comparison -> operator;
    if (last_text_comparison -> text)
	text_comparison -> text = my_strdup (last_text_comparison -> text);
    text_comparison -> use_text = last_text_comparison -> use_text;
    text_comparison -> first_comparison = last_text_comparison -> first_comparison;
    text_comparison -> first_amount = last_text_comparison -> first_amount;
    text_comparison -> link_first_to_second_part = last_text_comparison -> link_first_to_second_part;
    text_comparison -> second_comparison = last_text_comparison -> second_comparison;
    text_comparison -> second_amount = last_text_comparison -> second_amount;

    return text_comparison_number;
}

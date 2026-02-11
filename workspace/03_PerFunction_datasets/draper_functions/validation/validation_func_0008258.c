icalvalue_set_geo(icalvalue* value, struct icalgeotype v) {
    struct icalvalue_impl* impl;
    icalerror_check_arg_rv( (value!=0),"value");

    icalerror_check_value_type(value, ICAL_GEO_VALUE);
    impl = (struct icalvalue_impl*)value;


    impl->data.v_geo = v;

    icalvalue_reset_kind(impl);
}

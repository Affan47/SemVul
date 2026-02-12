uip_nd6_init()
{
#if UIP_ND6_SEND_NA

  uip_icmp6_register_input_handler(&ns_input_handler);
#endif

#if UIP_ND6_SEND_NS


  uip_icmp6_register_input_handler(&na_input_handler);
#endif

#if UIP_CONF_ROUTER && UIP_ND6_SEND_RA

  uip_icmp6_register_input_handler(&rs_input_handler);
#endif

#if !UIP_CONF_ROUTER

  uip_icmp6_register_input_handler(&ra_input_handler);
#endif
}

dhcpc_request(struct uip_stack *ustack)
{
	struct dhcpc_state *s = ustack->dhcpc;

	if (s != NULL && s->state == STATE_INITIAL)
		handle_dhcp(ustack);
}

stop_adverts(void)
{
	struct Interface *iface;


	for (iface=IfaceList; iface; iface=iface->next) {
		if( ! iface->UnicastOnly ) {
			if (iface->AdvSendAdvert) {

				iface->cease_adv = 1;
				send_ra_forall(iface, NULL);
			}
		}
	}
}

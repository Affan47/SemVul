ap1394_hdr_print(register const u_char *bp, u_int length)
{
	register const struct firewire_header *fp;
	u_int16_t firewire_type;

	fp = (const struct firewire_header *)bp;

	(void)printf("%s > %s",
		     linkaddr_string(fp->firewire_dhost, LINKADDR_IEEE1394, FIREWIRE_EUI64_LEN),
		     linkaddr_string(fp->firewire_shost, LINKADDR_IEEE1394, FIREWIRE_EUI64_LEN));

	firewire_type = EXTRACT_16BITS(&fp->firewire_type);
	if (!qflag) {
		(void)printf(", ethertype %s (0x%04x)",
			       tok2str(ethertype_values,"Unknown", firewire_type),
                               firewire_type);
        } else {
                (void)printf(", %s", tok2str(ethertype_values,"Unknown Ethertype (0x%04x)", firewire_type));
        }

	(void)printf(", length %u: ", length);
}

commAvailable(commRcvrStruct_t *r) {
	uint8_t port = r->port;

	switch (commData.portTypes[port]) {
		case COMM_PORT_TYPE_SERIAL:
			if (commData.portHandles[port]) {
				return serialAvailable(commData.portHandles[port]);
			}
			break;

#ifdef CANx
		case COMM_PORT_TYPE_CAN:
			if (commData.portHandles[port]) {
				return canUartAvailable(commData.portHandles[port]);
			}
			break;
#endif

#ifdef HAS_USB
		case COMM_PORT_TYPE_USB:
			return usbAvailable();
			break;
#endif
	}

	return 0;
}

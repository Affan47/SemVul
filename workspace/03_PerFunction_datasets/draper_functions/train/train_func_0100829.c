getGpsLeverArm(CmtVector& arm, const CmtDeviceId deviceId)
{
	CMT3LOG("L3: getGpsLeverArm %08x\n",deviceId);
	CMT3EXITLOG;

	DO_DATA_REQUEST(CMT_MID_REQGPSLEVERARM);
	arm.m_data[0] = rcv.getDataFloat(0);
	arm.m_data[1] = rcv.getDataFloat(4);
	arm.m_data[2] = rcv.getDataFloat(8);
	return m_lastResult = XRV_OK;
}

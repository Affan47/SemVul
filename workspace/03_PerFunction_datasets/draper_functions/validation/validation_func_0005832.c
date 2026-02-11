sendPPM(u_int ppm, HDLCFrame& mcf, Status& eresult)
{
    for (int t = 0; t < 3; t++) {
	traceFCF("SEND send", ppm);

	if (transmitFrame(ppm|FCF_SNDR) && recvFrame(mcf, FCF_SNDR, conf.t4Timer, false, false))
	    return (true);
	if (abortRequested())
	    return (false);
	switchingPause(eresult);
    }
    switch (ppm) {
	case FCF_MPS:
	    eresult = Status(150, "No response to MPS repeated 3 tries");
	    break;
	case FCF_EOP:
	    eresult = Status(151, "No response to EOP repeated 3 tries");
	    break;
	case FCF_EOM:
	    eresult = Status(152, "No response to EOM repeated 3 tries");
	    break;
	default:
	    eresult = Status(153, "No response to PPM repeated 3 tries");
	    break;
    }
    protoTrace(eresult.string());
    return (false);
}

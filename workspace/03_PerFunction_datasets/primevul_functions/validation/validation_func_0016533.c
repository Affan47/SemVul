HRESULT Http::HrGetDepth(ULONG *ulDepth)
{
	std::string strDepth;


	auto hr = HrGetHeaderValue("Depth", &strDepth);
	if (hr != hrSuccess)
		*ulDepth = 0;
	else if (strDepth == "infinity")
		*ulDepth = 2;
	else {
		*ulDepth = atoi(strDepth.c_str());
		if (*ulDepth > 1)
			*ulDepth = 1;
	}
	return hr;
}

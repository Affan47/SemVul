Do(const Spectrum&
			inSpec,Spectrum& outSpec)
{

	if (!mConfig.GetPreserveOuts())
	{
		outSpec = inSpec;
	}

	int spectrumSize = inSpec.GetSize();
	TData spectralResolution = spectrumSize/inSpec.GetSpectralRange();

	int centerPoint = Round (mCenterFreqCtl.GetLastValue()*spectralResolution);
	int amount= Round(mAmount.GetLastValue()*spectralResolution);

	mBPFSpectrum.SetSize(spectrumSize);


	Array<Point>& magBPF=mBPFSpectrum.GetMagBPF().GetPointArray();

	Array<Point>& phaseBPF=mBPFSpectrum.GetPhaseBPF().GetPointArray();


	magBPF.SetSize(0);
	phaseBPF.SetSize(0);

	DataArray& inMag = inSpec.GetMagBuffer();
	DataArray& inPhase = inSpec.GetPhaseBuffer();

	TData binWidth = 1./spectralResolution;
	int i;
	TData freq = 0;
	TData mag;
	TData phase;
	int nPoints = 0;
	for (i=0; i<centerPoint-amount; i++)
	{
		mag = inMag[i+amount];
		phase = inPhase[i+amount];
		magBPF.AddElem(Point(freq,mag));
		phaseBPF.AddElem(Point(freq, phase));
		freq += binWidth;
		nPoints++;
	}

	freq = centerPoint * binWidth;
	magBPF.AddElem(Point(freq, inMag[centerPoint]));
	phaseBPF.AddElem(Point(freq, inPhase[centerPoint]));
	nPoints++;

	freq = (centerPoint+amount)*binWidth;

	for (i=centerPoint+amount ; i<spectrumSize; i++)
	{
		mag = inMag[i-amount];
		phase = inPhase[i-amount];
		magBPF.AddElem(Point(freq,mag));
		phaseBPF.AddElem(Point(freq, phase));
		freq += binWidth;
		nPoints++;
	}

	mBPFSpectrum.SetBPFSize(nPoints);
	mBPFSpectrum.SynchronizeTo(mFlag);
	outSpec.SetMagBuffer(mBPFSpectrum.GetMagBuffer());
	outSpec.SetPhaseBuffer(mBPFSpectrum.GetPhaseBuffer());

	return true;
}

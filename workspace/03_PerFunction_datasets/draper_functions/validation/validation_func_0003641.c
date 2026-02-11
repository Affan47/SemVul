Do(const Spectrum& in, Spectrum& out)
{

	SendFloatToInControl(mDeesser,"Amount",mAmount.GetLastValue());
	SendFloatToInControl(mDeesser,"LowCutoff",mLowCutoffFreqCtl.GetLastValue());
	SendFloatToInControl(mDeesser,"HighCutoff",mHighCutoffFreqCtl.GetLastValue());
	SendFloatToInControl(mDeesser,"Threshold",mThresholdCtl.GetLastValue());

	mDeesser.Do(in, out);
	return true;
}

CreateAnimated(size_t index)
{
	float* _values[1] = { &values[index] };
	return new FCDAnimated((FCDObject*) GetParent(), 1, FCDAnimatedStandardQualifiers::EMPTY, _values);
}

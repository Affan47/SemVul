getPickPath() const


{
    const SoDragger *subDragger = getActiveChildDragger();
    if (subDragger != NULL)
	return subDragger->getPickPath();
    else
	return pickPath;
}

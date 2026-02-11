protect() const
{
	return
			key_->name == "overbrace" ||
			key_->name == "underbrace" ||
			key_->name == "overleftarrow" ||
			key_->name == "overrightarrow" ||
			key_->name == "overleftrightarrow" ||
			key_->name == "underleftarrow" ||
			key_->name == "underrightarrow" ||
			key_->name == "underleftrightarrow";
}

isAccentDefined(tex_accent accent, KmodInfo & i) const
{
	map<tex_accent, KmodInfo>::const_iterator cit = kmod_list_.find(accent);
	if (cit == kmod_list_.end())
		return false;
	i = cit->second;
	return true;
}

static std::string ToModeLetters(const Modes::ChangeList& changelist)
	{

		Modes::ChangeList::List::const_iterator dummy;
		return ToModeLetters(changelist.getlist(), UINT_MAX, changelist.getlist().begin(), dummy);
	}

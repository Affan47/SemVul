CmdResult HandleLocal(LocalUser* user, const Params& parameters) CXX11_OVERRIDE
	{
		if (parameters.empty())
			return ShowSilenceList(user);


		bool is_remove = parameters[0][0] == '-';


		std::string mask = parameters[0];
		if (mask[0] == '-' || mask[0] == '+')
		{
			mask.erase(0);
			if (mask.empty())
				mask.assign("*");
			ModeParser::CleanMask(mask);
		}


		uint32_t flags = SilenceEntry::SF_DEFAULT;
		if (parameters.size() > 1)
		{
			if (!SilenceEntry::FlagsToBits(parameters[1], flags))
			{
				user->WriteNumeric(ERR_SILENCE, mask, parameters[1], "You specified one or more invalid SILENCE flags");
				return CMD_FAILURE;
			}
			else if (flags == SilenceEntry::SF_EXEMPT)
			{

				flags |= SilenceEntry::SF_DEFAULT;
			}
		}

		return is_remove ? RemoveSilence(user, mask, flags) : AddSilence(user, mask, flags);
	}

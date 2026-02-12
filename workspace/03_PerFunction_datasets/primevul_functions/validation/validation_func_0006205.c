CmdResult HandleLocal(LocalUser* user, const Params& parameters) CXX11_OVERRIDE
	{

		if (user->registered == REG_ALL)
		{
			user->CommandFloodPenalty += 1000;
			user->WriteNumeric(ERR_ALREADYREGISTERED, "You may not reregister");
			return CMD_FAILURE;
		}
		user->password = parameters[0];

		return CMD_SUCCESS;
	}

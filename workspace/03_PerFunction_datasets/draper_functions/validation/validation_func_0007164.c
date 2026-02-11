make_act(GpgOp::Type _op)
	{
		reset(ResetSessionAndData);

		op = _op;

		act = new GpgAction(this);

		connect(act, SIGNAL(readyRead()), SLOT(act_readyRead()));
		connect(act, SIGNAL(bytesWritten(int)), SLOT(act_bytesWritten(int)));
		connect(act, SIGNAL(needPassphrase(const QString &)), SLOT(act_needPassphrase(const QString &)));
		connect(act, SIGNAL(needCard()), SLOT(act_needCard()));
		connect(act, SIGNAL(finished()), SLOT(act_finished()));
		connect(act, SIGNAL(readyReadDiagnosticText()), SLOT(act_readyReadDiagnosticText()));

		act->input.bin = bin;
		act->input.op = op;
		act->input.opt_ascii = opt_ascii;
		act->input.opt_noagent = opt_noagent;
		act->input.opt_alwaystrust = opt_alwaystrust;
		act->input.opt_pubfile = opt_pubfile;
		act->input.opt_secfile = opt_secfile;
	}

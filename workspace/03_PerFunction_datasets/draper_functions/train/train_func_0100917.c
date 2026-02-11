handleExit(int code)
{

	if ( code>=0 )
		return true;
	else if ( code <= -100 )
	{
		switch (code)
		{
			case e_Fatal:
				m_error.setError(e_Fatal, "fatal internal error");
				return false;
			case e_ExecStackUnderflow:
				m_error.setError(e_ExecStackUnderflow, "stack overflow");
				return false;

			case e_Quit:
			case e_Info:
			case e_InterpreterExit:
			case e_RemapColor:
			case e_NeedInput:
			case e_NeedStdin:
			case e_NeedStdout:
			case e_NeedStderr:
			case e_VMreclaim:
			default:
				return true;
		}
	}
	else
	{
		const char* errors[]= { "", ERROR_NAMES };
		m_error.setError(code, errors[-code]);
		return false;
	}
}

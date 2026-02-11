assign (Option* node_, const char* op_)
{
    trace_with_mask ("CmdLineOpts::assign", CMDLINEOPTS);

    long l;
    double d;

	if (node_ && op_) {
		DL ((CMDLINEOPTS, "Assign '%s' to {-%c, --%s, t=%s}\n",
			 op_, node_->m_short_name, node_->m_long_name.c_str (),
			 node_->type_c_str ()));
	}


    switch (node_->m_type) {
    case Option::string_t:
		*(string*) node_->m_val = op_;
		break;

    case Option::int_t:
    case Option::long_t:
		errno = 0;
		l = strtol (op_, NULL, 0);

		if (errno != 0) {
			m_error = "Error: '" + string (strerror (errno)) + "',";
			m_error += " in converting to integer from '";
			m_error += string (op_) + "'.";
			return (false);
		}

		if (node_->m_type == Option::int_t) {
			*(int*) node_->m_val = int (l);
		}
		else {
			*(long*) node_->m_val = l;
		}
		break;

    case Option::uint_t:
    case Option::ulong_t:
		errno = 0;
		l = strtol (op_, NULL, 0);

		if (errno != 0) {
			m_error = "Error: '" + string (strerror (errno)) + "',";
			m_error += " in converting to unsinged integer from '";
			m_error += string (op_) + "'.";
			return (false);
		}

		if (node_->m_type == Option::uint_t) {
			*(unsigned int*) node_->m_val = int (l);
		}
		else {
			*(unsigned long*) node_->m_val = l;
		}
		break;

    case Option::double_t:
    case Option::float_t:
		errno = 0;
		d = strtod (op_, NULL);

		if (errno != 0) {
			m_error = "Error: '" + string (strerror (errno)) + "',";
			m_error += " in converting to double/float from '";
			m_error += string (op_) + "'.";
			return (false);
		}

		if (node_->m_type == Option::double_t) {
			*(double*) node_->m_val = d;
		}
		else {
			*(float*) node_->m_val = float (d);
		}
		break;

    case Option::flag_t:
		*(bool*) node_->m_val = true;
		break;

    case Option::func_t:
		(*(OPTS_FUNC)(node_->m_val)) ();
		break;

    case Option::func_one_t:
		(*(OPTS_FUNC_ONE)(node_->m_val)) (op_);
		break;

    case Option::none_t:
    default:
		m_error = "Undefined type for option '"+string (op_)+"'.";
		return (false);
    }

    return (true);
}

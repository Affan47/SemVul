print_fill(const std::list<edge2d>& edges,
			       const pair& offset,
			       const Color& fc,
			       const pen_data& line,
			       const std::string& len) const
  {
    std::stringstream obuf;
    obuf << set_fill_state(fc) << set_pen_state(line);


    std::stringstream attribs;

    if ( !(fc.is_unset()) )
      {
	attribs << "[fill";

	if (fc.alpha() < 1)
	  attribs << ",opacity=" << fc.alpha();

	attribs << "]";
      }

    obuf << print_paths(edges, offset, attribs.str(), len);

    return obuf.str();
  }

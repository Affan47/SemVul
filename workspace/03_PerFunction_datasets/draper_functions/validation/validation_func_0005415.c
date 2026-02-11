pic_header(const pair& sizes,
				 const pair& offsets,
				 const std::set<Color>& palette,
				 const std::string& len) const
  {
    std::stringstream obuf;
    obuf << print_palette(palette)
	 << set_unitlength(len)
	 << start_picture(sizes, offsets);

    return obuf.str();
  }

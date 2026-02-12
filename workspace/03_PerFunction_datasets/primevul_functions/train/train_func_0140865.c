static_runner() {

			std::locale utf8_loc = boost::locale::generator().generate("");

			utf8_loc = std::locale(utf8_loc, new customcodecvt());
			boost::filesystem::path::imbue(utf8_loc);
		}

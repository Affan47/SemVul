cmd_variant()
{
	CMD_REQUIRE_ARGS(1);

	const std::string& v = cmd_args[1];

#if defined(HOICHESS)
	if (0) {

#elif defined(HOIXIANGQI)
	if (v == "xiangqi") {

#else
# error "neither HOICHESS nor HOIXIANGQI defined"
#endif
	} else {
		printf("Error (variant not supported): %s\n", v.c_str());
	}
}

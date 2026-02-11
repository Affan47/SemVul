each_str255_benchmark_test() {
    int		cnt = 1000;
    char	js[] = "\"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\"";
    char	*json = (char*)malloc(sizeof(js) * cnt + 1);
    char	*s = json;

    for (; 0 < cnt; cnt--) {
	memcpy(s, js, sizeof(js));
	s += sizeof(js) - 1;
	*s++ = '\n';
    }
    *s = '\0';
    ut_benchmark("each str255 callback", 100000LL, each_bench, json);
}

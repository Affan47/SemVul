drv_Noritake_init(const char *section, const int quiet)
{
    WIDGET_CLASS wc;
    int ret;

    info("%s: %s", Name, "$Rev: 771 $");


    if ((ret = drv_Noritake_start(section)) != 0)
	return ret;


    if ((ret = drv_generic_text_init(section, Name)) != 0)
	return ret;


    wc = Widget_Text;
    wc.draw = drv_generic_text_draw;
    widget_register(&wc);


    if (!quiet) {
	char buffer[40];
	qprintf(buffer, sizeof(buffer), "%s %dx%d", Name, DCOLS, DROWS);
	if (drv_generic_text_greet(buffer, NULL)) {
	    sleep(3);
	    drv_Noritake_clear();
	}
    }

    return 0;
}

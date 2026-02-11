time_write_xml(output::pointer fp, const char *name, time_t this_thing,
    int show)
{
    if (this_thing == TIME_NOT_SET && !show)
	return;
    if (!name)
	name = "time";
    fp->fprintf
    (
	"<%s>%ld</%s> <!-- %.24s -->\n",
	name,
	(long)this_thing,
	name,
	ctime(&this_thing)
    );
}

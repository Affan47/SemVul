gvusershape_file_release(usershape_t *us)
{
    if (us->nocache) {
	if (us->f) {
	    fclose(us->f);
	    us->f = NULL;
	}
    }
}

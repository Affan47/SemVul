JAXopenrootwin(Jax *jax)
{
	if(!jax)
		return(0);
	jax->w=DefaultRootWindow(jax->d);
	JAXgetxwa(jax);
	jax->cmap=DefaultColormap(jax->d, DefaultScreen(jax->d));
	return(1);
}

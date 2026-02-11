createRenderTargetTexture(const core::dimension2d<u32>& size,
		const c8* name)
{
	os::Printer::log("createRenderTargetTexture is deprecated, use addRenderTargetTexture instead");
	ITexture* tex = addRenderTargetTexture(size, name);
	tex->grab();
	return tex;
}

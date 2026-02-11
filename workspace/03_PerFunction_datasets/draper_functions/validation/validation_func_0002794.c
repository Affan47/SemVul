g84_fifo_chan_engine_ctor(struct nvkm_fifo_chan *base,
			  struct nvkm_engine *engine,
			  struct nvkm_object *object)
{
	struct nv50_fifo_chan *chan = nv50_fifo_chan(base);
	int engn = engine->subdev.index;

	if (g84_fifo_chan_engine_addr(engine) < 0)
		return 0;

	return nvkm_object_bind(object, NULL, 0, &chan->engn[engn]);
}

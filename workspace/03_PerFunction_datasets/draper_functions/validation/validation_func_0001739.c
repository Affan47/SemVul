snd_p16v_pcm_pointer_capture(struct snd_pcm_substream *substream)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_emu10k1_pcm *epcm = runtime->private_data;
	snd_pcm_uframes_t ptr, ptr1, ptr2 = 0;
	int channel = 0;

	if (!epcm->running)
		return 0;

	ptr1 = snd_emu10k1_ptr20_read(emu, CAPTURE_POINTER, channel);
	ptr2 = bytes_to_frames(runtime, ptr1);
	ptr=ptr2;
	if (ptr >= runtime->buffer_size) {
		ptr -= runtime->buffer_size;
		dev_warn(emu->card->dev, "buffer capture limited!\n");
	}


	return ptr;
}

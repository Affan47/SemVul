accept_file(void *data, int result)
{
	progress_callback_data *pcd = data;
	if (result) {
		char val[10] = "ACCEPT";
		printf("write: %ld\n", write(fd, val, 10));
#ifndef __MINGW32__
		fsync(fd);
#endif
		pcd->input = eb_input_add(fd, EB_INPUT_READ, get_file2, pcd);
	} else {
		char val[10] = "DENY";
		write(fd, val, 10);
		close(fd);
		fclose(fp);
		xfer_in_progress = 0;
		ay_activity_bar_remove(pcd->tag);
		free(pcd);
	}
}

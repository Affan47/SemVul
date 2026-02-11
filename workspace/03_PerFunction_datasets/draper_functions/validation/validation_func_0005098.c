xfs_inode_item_format_convert(
	xfs_log_iovec_t		*buf,
	xfs_inode_log_format_t	*in_f)
{
	if (buf->i_len == sizeof(xfs_inode_log_format_32_t)) {
		xfs_inode_log_format_32_t *in_f32 = buf->i_addr;

		in_f->ilf_type = in_f32->ilf_type;
		in_f->ilf_size = in_f32->ilf_size;
		in_f->ilf_fields = in_f32->ilf_fields;
		in_f->ilf_asize = in_f32->ilf_asize;
		in_f->ilf_dsize = in_f32->ilf_dsize;
		in_f->ilf_ino = in_f32->ilf_ino;

		memcpy(in_f->ilf_u.ilfu_uuid.__u_bits,
		       in_f32->ilf_u.ilfu_uuid.__u_bits,
		       sizeof(uuid_t));
		in_f->ilf_blkno = in_f32->ilf_blkno;
		in_f->ilf_len = in_f32->ilf_len;
		in_f->ilf_boffset = in_f32->ilf_boffset;
		return 0;
	} else if (buf->i_len == sizeof(xfs_inode_log_format_64_t)){
		xfs_inode_log_format_64_t *in_f64 = buf->i_addr;

		in_f->ilf_type = in_f64->ilf_type;
		in_f->ilf_size = in_f64->ilf_size;
		in_f->ilf_fields = in_f64->ilf_fields;
		in_f->ilf_asize = in_f64->ilf_asize;
		in_f->ilf_dsize = in_f64->ilf_dsize;
		in_f->ilf_ino = in_f64->ilf_ino;

		memcpy(in_f->ilf_u.ilfu_uuid.__u_bits,
		       in_f64->ilf_u.ilfu_uuid.__u_bits,
		       sizeof(uuid_t));
		in_f->ilf_blkno = in_f64->ilf_blkno;
		in_f->ilf_len = in_f64->ilf_len;
		in_f->ilf_boffset = in_f64->ilf_boffset;
		return 0;
	}
	return -EFSCORRUPTED;
}

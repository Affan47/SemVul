static inline uint32_t count_rice_bits_in_partition_(
	const uint32_t rice_parameter,
	const uint32_t partition_samples,
	const FLAC__uint64 abs_residual_partition_sum
)
{
	return (uint32_t)(flac_min(
		FLAC__ENTROPY_CODING_METHOD_PARTITIONED_RICE_PARAMETER_LEN +
		(1+rice_parameter) * partition_samples +
		(
			rice_parameter?
				(abs_residual_partition_sum >> (rice_parameter-1))
				: (abs_residual_partition_sum << 1)
		)
		- (partition_samples >> 1),(uint32_t)(-1)));


	;
}

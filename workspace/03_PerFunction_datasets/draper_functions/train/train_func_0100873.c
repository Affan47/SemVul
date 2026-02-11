ipmi_print_sol_info(struct ipmi_intf * intf, uint8_t channel)
{
	struct sol_config_parameters params = {0};
	if (ipmi_get_sol_info(intf, channel, &params))
		return -1;

	if (csv_output)
	{
		printf("%s,",
			   val2str(params.set_in_progress & 0x03,
					   ipmi_set_in_progress_vals));
		printf("%s,", params.enabled?"true": "false");
		printf("%s,", params.force_encryption?"true":"false");
		printf("%s,", params.force_encryption?"true":"false");
		printf("%s,",
			   val2str(params.privilege_level, ipmi_privlvl_vals));
		printf("%d,", params.character_accumulate_level * 5);
		printf("%d,", params.character_send_threshold);
		printf("%d,", params.retry_count);
		printf("%d,", params.retry_interval * 10);

		printf("%s,",
			   val2str(params.volatile_bit_rate, ipmi_bit_rate_vals));

		printf("%s,",
			   val2str(params.non_volatile_bit_rate, ipmi_bit_rate_vals));

		printf("%d,", params.payload_channel);
		printf("%d\n", params.payload_port);
	}
	else
	{
		printf("Set in progress                 : %s\n",
			   val2str(params.set_in_progress & 0x03,
					   ipmi_set_in_progress_vals));
		printf("Enabled                         : %s\n",
			   params.enabled?"true": "false");
		printf("Force Encryption                : %s\n",
			   params.force_encryption?"true":"false");
		printf("Force Authentication            : %s\n",
			   params.force_authentication?"true":"false");
		printf("Privilege Level                 : %s\n",
			   val2str(params.privilege_level, ipmi_privlvl_vals));
		printf("Character Accumulate Level (ms) : %d\n",
			   params.character_accumulate_level * 5);
		printf("Character Send Threshold        : %d\n",
			   params.character_send_threshold);
		printf("Retry Count                     : %d\n",
			   params.retry_count);
		printf("Retry Interval (ms)             : %d\n",
			   params.retry_interval * 10);

		printf("Volatile Bit Rate (kbps)        : %s\n",
			   val2str(params.volatile_bit_rate, ipmi_bit_rate_vals));

		printf("Non-Volatile Bit Rate (kbps)    : %s\n",
			   val2str(params.non_volatile_bit_rate, ipmi_bit_rate_vals));

		printf("Payload Channel                 : %d (0x%02x)\n",
			   params.payload_channel, params.payload_channel);
		printf("Payload Port                    : %d\n",
			   params.payload_port);
	}

	return 0;
}

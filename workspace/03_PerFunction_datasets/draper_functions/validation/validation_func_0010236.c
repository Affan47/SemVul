e1000_phy_init_script(struct e1000_hw *hw)
{
	u32 ret_val;
	u16 phy_saved_data;

	if (hw->phy_init_script) {
		msleep(20);


		ret_val = e1000_read_phy_reg(hw, 0x2F5B, &phy_saved_data);


		e1000_write_phy_reg(hw, 0x2F5B, 0x0003);
		msleep(20);

		e1000_write_phy_reg(hw, 0x0000, 0x0140);
		msleep(5);

		switch (hw->mac_type) {
		case e1000_82541:
		case e1000_82547:
			e1000_write_phy_reg(hw, 0x1F95, 0x0001);
			e1000_write_phy_reg(hw, 0x1F71, 0xBD21);
			e1000_write_phy_reg(hw, 0x1F79, 0x0018);
			e1000_write_phy_reg(hw, 0x1F30, 0x1600);
			e1000_write_phy_reg(hw, 0x1F31, 0x0014);
			e1000_write_phy_reg(hw, 0x1F32, 0x161C);
			e1000_write_phy_reg(hw, 0x1F94, 0x0003);
			e1000_write_phy_reg(hw, 0x1F96, 0x003F);
			e1000_write_phy_reg(hw, 0x2010, 0x0008);
			break;

		case e1000_82541_rev_2:
		case e1000_82547_rev_2:
			e1000_write_phy_reg(hw, 0x1F73, 0x0099);
			break;
		default:
			break;
		}

		e1000_write_phy_reg(hw, 0x0000, 0x3300);
		msleep(20);


		e1000_write_phy_reg(hw, 0x2F5B, phy_saved_data);

		if (hw->mac_type == e1000_82547) {
			u16 fused, fine, coarse;


			e1000_read_phy_reg(hw,
					   IGP01E1000_ANALOG_SPARE_FUSE_STATUS,
					   &fused);

			if (!(fused & IGP01E1000_ANALOG_SPARE_FUSE_ENABLED)) {
				e1000_read_phy_reg(hw,
						   IGP01E1000_ANALOG_FUSE_STATUS,
						   &fused);

				fine = fused & IGP01E1000_ANALOG_FUSE_FINE_MASK;
				coarse =
				    fused & IGP01E1000_ANALOG_FUSE_COARSE_MASK;

				if (coarse >
				    IGP01E1000_ANALOG_FUSE_COARSE_THRESH) {
					coarse -=
					    IGP01E1000_ANALOG_FUSE_COARSE_10;
					fine -= IGP01E1000_ANALOG_FUSE_FINE_1;
				} else if (coarse ==
					   IGP01E1000_ANALOG_FUSE_COARSE_THRESH)
					fine -= IGP01E1000_ANALOG_FUSE_FINE_10;

				fused =
				    (fused & IGP01E1000_ANALOG_FUSE_POLY_MASK) |
				    (fine & IGP01E1000_ANALOG_FUSE_FINE_MASK) |
				    (coarse &
				     IGP01E1000_ANALOG_FUSE_COARSE_MASK);

				e1000_write_phy_reg(hw,
						    IGP01E1000_ANALOG_FUSE_CONTROL,
						    fused);
				e1000_write_phy_reg(hw,
						    IGP01E1000_ANALOG_FUSE_BYPASS,
						    IGP01E1000_ANALOG_FUSE_ENABLE_SW_CONTROL);
			}
		}
	}
}

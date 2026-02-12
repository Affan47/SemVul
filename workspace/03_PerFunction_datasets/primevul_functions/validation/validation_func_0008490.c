static void ov518_mode_init_regs(struct sd *sd)
{
	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;
	int hsegs, vsegs, packet_size;
	struct usb_host_interface *alt;
	struct usb_interface *intf;

	intf = usb_ifnum_to_if(sd->gspca_dev.dev, sd->gspca_dev.iface);
	alt = usb_altnum_to_altsetting(intf, sd->gspca_dev.alt);
	if (!alt) {
		gspca_err(gspca_dev, "Couldn't get altsetting\n");
		sd->gspca_dev.usb_err = -EIO;
		return;
	}

	if (alt->desc.bNumEndpoints < 1) {
		sd->gspca_dev.usb_err = -ENODEV;
		return;
	}

	packet_size = le16_to_cpu(alt->endpoint[0].desc.wMaxPacketSize);
	ov518_reg_w32(sd, R51x_FIFO_PSIZE, packet_size & ~7, 2);


	reg_w(sd, 0x2b, 0);
	reg_w(sd, 0x2c, 0);
	reg_w(sd, 0x2d, 0);
	reg_w(sd, 0x2e, 0);
	reg_w(sd, 0x3b, 0);
	reg_w(sd, 0x3c, 0);
	reg_w(sd, 0x3d, 0);
	reg_w(sd, 0x3e, 0);

	if (sd->bridge == BRIDGE_OV518) {

		reg_w_mask(sd, 0x20, 0x08, 0x08);


		reg_w_mask(sd, 0x28, 0x80, 0xf0);
		reg_w_mask(sd, 0x38, 0x80, 0xf0);
	} else {
		reg_w(sd, 0x28, 0x80);
		reg_w(sd, 0x38, 0x80);
	}

	hsegs = sd->gspca_dev.pixfmt.width / 16;
	vsegs = sd->gspca_dev.pixfmt.height / 4;

	reg_w(sd, 0x29, hsegs);
	reg_w(sd, 0x2a, vsegs);

	reg_w(sd, 0x39, hsegs);
	reg_w(sd, 0x3a, vsegs);


	reg_w(sd, 0x2f, 0x80);


	if (sd->bridge == BRIDGE_OV518PLUS && sd->revision == 0 &&
					      sd->sensor == SEN_OV7620AE)
		sd->clockdiv = 0;
	else
		sd->clockdiv = 1;


	reg_w(sd, 0x51, 0x04);
	reg_w(sd, 0x22, 0x18);
	reg_w(sd, 0x23, 0xff);

	if (sd->bridge == BRIDGE_OV518PLUS) {
		switch (sd->sensor) {
		case SEN_OV7620AE:


			if (sd->revision > 0 &&
					sd->gspca_dev.pixfmt.width == 640) {
				reg_w(sd, 0x20, 0x60);
				reg_w(sd, 0x21, 0x1f);
			} else {
				reg_w(sd, 0x20, 0x00);
				reg_w(sd, 0x21, 0x19);
			}
			break;
		case SEN_OV7620:
			reg_w(sd, 0x20, 0x00);
			reg_w(sd, 0x21, 0x19);
			break;
		default:
			reg_w(sd, 0x21, 0x19);
		}
	} else
		reg_w(sd, 0x71, 0x17);


	i2c_w(sd, 0x54, 0x23);

	reg_w(sd, 0x2f, 0x80);

	if (sd->bridge == BRIDGE_OV518PLUS) {
		reg_w(sd, 0x24, 0x94);
		reg_w(sd, 0x25, 0x90);
		ov518_reg_w32(sd, 0xc4,    400, 2);
		ov518_reg_w32(sd, 0xc6,    540, 2);
		ov518_reg_w32(sd, 0xc7,    540, 2);
		ov518_reg_w32(sd, 0xc8,    108, 2);
		ov518_reg_w32(sd, 0xca, 131098, 3);
		ov518_reg_w32(sd, 0xcb,    532, 2);
		ov518_reg_w32(sd, 0xcc,   2400, 2);
		ov518_reg_w32(sd, 0xcd,     32, 2);
		ov518_reg_w32(sd, 0xce,    608, 2);
	} else {
		reg_w(sd, 0x24, 0x9f);
		reg_w(sd, 0x25, 0x90);
		ov518_reg_w32(sd, 0xc4,    400, 2);
		ov518_reg_w32(sd, 0xc6,    381, 2);
		ov518_reg_w32(sd, 0xc7,    381, 2);
		ov518_reg_w32(sd, 0xc8,    128, 2);
		ov518_reg_w32(sd, 0xca, 183331, 3);
		ov518_reg_w32(sd, 0xcb,    746, 2);
		ov518_reg_w32(sd, 0xcc,   1750, 2);
		ov518_reg_w32(sd, 0xcd,     45, 2);
		ov518_reg_w32(sd, 0xce,    851, 2);
	}

	reg_w(sd, 0x2f, 0x80);
}

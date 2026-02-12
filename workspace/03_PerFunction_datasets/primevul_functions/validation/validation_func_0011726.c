void scale_rect(double factor_x, double factor_y, int blend, int interpolate, int Bpp,
    char *src_fb, int src_bytes_per_line, char *dst_fb, int dst_bytes_per_line,
    int Nx, int Ny, int nx, int ny, int X1, int Y1, int X2, int Y2, int mark) {


	int i, j, i1, i2, j1, j2;
	int I, J, I1, I2, J1, J2;

	double w, wx, wy, wtot;

	double x1, y1, x2, y2;
	double dx, dy;
	double ddx=0, ddy=0;

	char *src, *dest;


	unsigned short us = 0;
	unsigned char  uc = 0;
	unsigned int   ui = 0;

	int use_noblend_shortcut = 1;
	int shrink;
	static int constant_weights = -1, mag_int = -1;
	static int last_Nx = -1, last_Ny = -1, cnt = 0;
	static double last_factor = -1.0;
	int b, k;
	double pixave[4];

	if (factor_x <= 1.0 && factor_y <= 1.0) {
		shrink = 1;
	} else {
		shrink = 0;
	}


	dx = 1.0/factor_x;
	dy = 1.0/factor_y;


	if (factor_x != last_factor || Nx != last_Nx || Ny != last_Ny) {
		constant_weights = -1;
		mag_int = -1;
		last_Nx = Nx;
		last_Ny = Ny;
		last_factor = factor_x;
	}
	if (constant_weights < 0 && factor_x != factor_y) {
		constant_weights = 0;
		mag_int = 0;

	} else if (constant_weights < 0) {
		int n = 0;

		constant_weights = 0;
		mag_int = 0;

		for (i = 2; i<=128; i++) {
			double test = ((double) 1)/ i;
			double diff, eps = 1.0e-7;
			diff = factor_x - test;
			if (-eps < diff && diff < eps) {
				n = i;
				break;
			}
		}
		if (! blend || ! shrink || interpolate) {
			;
		} else if (n != 0) {
			if (Nx % n == 0 && Ny % n == 0) {
				static int didmsg = 0;
				if (mark && ! didmsg) {
					didmsg = 1;
					rfbLog("scale_and_mark_rect: using "
					    "constant pixel weight speedup "
					    "for 1/%d\n", n);
				}
				constant_weights = 1;
			}
		}

		n = 0;
		for (i = 2; i<=32; i++) {
			double test = (double) i;
			double diff, eps = 1.0e-7;
			diff = factor_x - test;
			if (-eps < diff && diff < eps) {
				n = i;
				break;
			}
		}
		if (! blend && factor_x > 1.0 && n) {
			mag_int = n;
		}
	}

	if (mark && factor_x > 1.0 && blend) {


		if (X1 > 0) X1--;
		if (Y1 > 0) Y1--;
	}


	i1 = FLOOR(X1/dx);


	i2 = CEIL( (X2+1)/dx ) - 1;


	i1 = nfix(i1, nx);
	i2 = nfix(i2, nx) + 1;


	j1 = FLOOR(Y1/dy);
	j2 = CEIL( (Y2+1)/dy ) - 1;

	j1 = nfix(j1, ny);
	j2 = nfix(j2, ny) + 1;


	if (mark && ! blend && mag_int && Bpp != 3) {
		int jmin, jmax, imin, imax;


		for (J=Y1; J < Y2; J++) {
		    jmin = J * mag_int;
		    jmax = jmin + mag_int;
		    for (I=X1; I < X2; I++) {

			src = src_fb + J*src_bytes_per_line + I*Bpp;
			if (Bpp == 4) {
				ui = *((unsigned int *)src);
			} else if (Bpp == 2) {
				us = *((unsigned short *)src);
			} else if (Bpp == 1) {
				uc = *((unsigned char *)src);
			}
			imin = I * mag_int;
			imax = imin + mag_int;

			for (j=jmin; j<jmax; j++) {
			    dest = dst_fb + j*dst_bytes_per_line + imin*Bpp;
			    for (i=imin; i<imax; i++) {
				if (Bpp == 4) {
					*((unsigned int *)dest) = ui;
				} else if (Bpp == 2) {
					*((unsigned short *)dest) = us;
				} else if (Bpp == 1) {
					*((unsigned char *)dest) = uc;
				}
				dest += Bpp;
			    }
			}
		    }
		}
		goto markit;
	}


	wx = 1.0;
	wy = 1.0;
	w  = 1.0;


	for (j=j1; j<j2; j++) {
		y1 =  j * dy;
		if (y1 > Ny - 1) {

			y1 = Ny - 1;
		}
		y2 = y1 + dy;


		J1 = (int) FLOOR(y1);
		J1 = nfix(J1, Ny);

		if (shrink && ! interpolate) {
			J2 = (int) CEIL(y2) - 1;
			J2 = nfix(J2, Ny);
		} else {
			J2 = J1 + 1;
			ddy = y1 - J1;
		}


		dest = dst_fb + j*dst_bytes_per_line + i1*Bpp;

		for (i=i1; i<i2; i++) {

			x1 =  i * dx;
			if (x1 > Nx - 1) {

				x1 = Nx - 1;
			}
			x2 = x1 + dx;

			cnt++;


			I1 = (int) FLOOR(x1);
			if (I1 >= Nx) I1 = Nx - 1;

			if (! blend && use_noblend_shortcut) {


				src = src_fb + J1*src_bytes_per_line + I1*Bpp;
				if (Bpp == 4) {
					*((unsigned int *)dest)
					    = *((unsigned int *)src);
				} else if (Bpp == 2) {
					*((unsigned short *)dest)
					    = *((unsigned short *)src);
				} else if (Bpp == 1) {
					*(dest) = *(src);
				} else if (Bpp == 3) {

					for (k=0; k<=2; k++) {
						*(dest+k) = *(src+k);
					}
				}
				dest += Bpp;
				continue;
			}

			if (shrink && ! interpolate) {
				I2 = (int) CEIL(x2) - 1;
				if (I2 >= Nx) I2 = Nx - 1;
			} else {
				I2 = I1 + 1;
				ddx = x1 - I1;
			}


			for (b=0; b<4; b++) {
				pixave[b] = 0.0;
			}


			wtot = 0.0;


			for (J=J1; J<=J2; J++) {

			    if (constant_weights) {
				;
			    } else if (! blend) {
				if (J != J1) {
					continue;
				}
				wy = 1.0;


			    } else if (! shrink || interpolate) {
				if (J >= Ny) {
					continue;
				} else if (J == J1) {
					wy = 1.0 - ddy;
				} else if (J != J1) {
					wy = ddy;
				}


			    } else if (J < y1) {
				wy = J+1 - y1;
			    } else if (J+1 > y2) {
				wy = y2 - J;
			    } else {
				wy = 1.0;
			    }

			    src = src_fb + J*src_bytes_per_line + I1*Bpp;

			    for (I=I1; I<=I2; I++) {


				if (constant_weights) {
					;
				} else if (! blend) {


					if (I != I1) {
						continue;
					}
					wx = 1.0;


				} else if (! shrink || interpolate) {
					if (I >= Nx) {
						continue;
					} else if (I == I1) {
						wx = 1.0 - ddx;
					} else if (I != I1) {
						wx = ddx;
					}


				} else if (I < x1) {


					wx = I+1 - x1;
				} else if (I+1 > x2) {


					wx = x2 - I;
				} else {


					wx = 1.0;
				}

				w = wx * wy;
				wtot += w;


				if (Bpp == 4) {

					pixave[0] += w * ((unsigned char) *(src  ));
					pixave[1] += w * ((unsigned char) *(src+1));
					pixave[2] += w * ((unsigned char) *(src+2));
					pixave[3] += w * ((unsigned char) *(src+3));
				} else if (Bpp == 2) {


					us = *((unsigned short *) src);
					pixave[0] += w*(us & main_red_mask);
					pixave[1] += w*(us & main_green_mask);
					pixave[2] += w*(us & main_blue_mask);
				} else if (Bpp == 1) {
					pixave[0] += w *
					    ((unsigned char) *(src));
				} else {
					for (b=0; b<Bpp; b++) {
						pixave[b] += w *
						    ((unsigned char) *(src+b));
					}
				}
				src += Bpp;
			    }
			}

			if (wtot <= 0.0) {
				wtot = 1.0;
			}
			wtot = 1.0/wtot;


			if (Bpp == 4) {
				*(dest  ) = (char) (wtot * pixave[0]);
				*(dest+1) = (char) (wtot * pixave[1]);
				*(dest+2) = (char) (wtot * pixave[2]);
				*(dest+3) = (char) (wtot * pixave[3]);
			} else if (Bpp == 2) {

				pixave[0] *= wtot;
				pixave[1] *= wtot;
				pixave[2] *= wtot;
				us =  (main_red_mask   & (int) pixave[0])
				    | (main_green_mask & (int) pixave[1])
				    | (main_blue_mask  & (int) pixave[2]);
				*( (unsigned short *) dest ) = us;
			} else if (Bpp == 1) {
				*(dest) = (char) (wtot * pixave[0]);
			} else {
				for (b=0; b<Bpp; b++) {
					*(dest+b) = (char) (wtot * pixave[b]);
				}
			}
			dest += Bpp;
		}
	}
	markit:
	if (mark) {
		mark_rect_as_modified(i1, j1, i2, j2, 1);
	}
}

/* sane - Scanner Access Now Easy.

   Copyright (C) 2007-2012 stef.dev@free.fr

   This file is part of the SANE package.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.

   As a special exception, the authors of SANE give permission for
   additional uses of the libraries contained in this release of SANE.

   The exception is that, if you link a SANE library with other files
   to produce an executable, this does not by itself cause the
   resulting executable to be covered by the GNU General Public
   License.  Your use of that executable is in no way restricted on
   account of linking the SANE library code into it.

   This exception does not, however, invalidate any other reasons why
   the executable file might be covered by the GNU General Public
   License.

   If you submit changes to SANE to the maintainers to be included in
   a subsequent release, you agree by submitting the changes that
   those changes may be distributed with this exception intact.

   If you write modifications of your own for SANE, it is your choice
   whether to permit this exception to apply to your modifications.
   If you do not wish that, delete this exception notice.
*/


/* here we have the various device settings...
 */
static Rts8891_Model hp4400c_model = {
  "HP4400c",			/* Name */
  "Hewlett-Packard",		/* Device vendor string */
  "4400c",			/* Device model name */
  "flatbed scanner",		/* Device  type */
  {1200, 600, 300, 150, 75, 0},	/* possible x-resolutions */
  {600, 300, 150, 0},		/* possible y-resolutions */
  1200,				/* max physical x dpi */
  600,				/* max physical y dpi */
  150,				/* min physical y dpi */

  SANE_FIX (8.3),		/* Start of scan area in mm  (x) */
  SANE_FIX (3.0),		/* Start of scan area in mm (y) */
  SANE_FIX (215.9),		/* Size of scan area in mm (x) */
  SANE_FIX (298.1),		/* Size of scan area in mm (y) */

  SANE_FIX (0.0),		/* Start of scan area in TA mode in mm (x) */
  SANE_FIX (0.0),		/* Start of scan area in TA mode in mm (y) */
  SANE_FIX (100.0),		/* Size of scan area in TA mode in mm (x) */
  SANE_FIX (100.0),		/* Size of scan area in TA mode in mm (y) */

  24, 12, 0,			/* R, G, and B CCD Line-distance correction in lines at
				   max motor resolution */
  /* default sensor */
  SENSOR_TYPE_4400,

  /* default gamma table */
  {0x00, 0x04, 0x08, 0x0c, 0x10, 0x14, 0x18, 0x1c, 0x20, 0x24, 0x28, 0x2c,
   0x30, 0x34, 0x38, 0x3c, 0x40, 0x44, 0x48, 0x4c, 0x50, 0x52, 0x53, 0x55,
   0x57, 0x58, 0x5a, 0x5c, 0x5d, 0x5f, 0x60, 0x62, 0x63, 0x64, 0x66, 0x67,
   0x68, 0x6a, 0x6b, 0x6c, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x74, 0x75, 0x76,
   0x77, 0x78, 0x79, 0x7a, 0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x82, 0x83,
   0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8d, 0x8e,
   0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x96, 0x97, 0x98, 0x99,
   0x9a, 0x9b, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3,
   0xa3, 0xa4, 0xa5, 0xa6, 0xa6, 0xa7, 0xa8, 0xa9, 0xa9, 0xaa, 0xab, 0xac,
   0xac, 0xad, 0xae, 0xaf, 0xaf, 0xb0, 0xb1, 0xb1, 0xb2, 0xb3, 0xb4, 0xb4,
   0xb5, 0xb6, 0xb6, 0xb7, 0xb8, 0xb8, 0xb9, 0xba, 0xba, 0xbb, 0xbc, 0xbc,
   0xbd, 0xbe, 0xbe, 0xbf, 0xc0, 0xc0, 0xc1, 0xc1, 0xc2, 0xc3, 0xc3, 0xc4,
   0xc5, 0xc5, 0xc6, 0xc6, 0xc7, 0xc8, 0xc8, 0xc9, 0xc9, 0xca, 0xcb, 0xcb,
   0xcc, 0xcc, 0xcd, 0xce, 0xce, 0xcf, 0xcf, 0xd0, 0xd1, 0xd1, 0xd2, 0xd2,
   0xd3, 0xd3, 0xd4, 0xd5, 0xd5, 0xd6, 0xd6, 0xd7, 0xd7, 0xd8, 0xd9, 0xd9,
   0xda, 0xda, 0xdb, 0xdb, 0xdc, 0xdc, 0xdd, 0xdd, 0xde, 0xdf, 0xdf, 0xe0,
   0xe0, 0xe1, 0xe1, 0xe2, 0xe2, 0xe3, 0xe3, 0xe4, 0xe4, 0xe5, 0xe5, 0xe6,
   0xe6, 0xe7, 0xe7, 0xe8, 0xe8, 0xe9, 0xe9, 0xea, 0xea, 0xeb, 0xeb, 0xec,
   0xec, 0xed, 0xed, 0xee, 0xee, 0xef, 0xef, 0xf0, 0xf0, 0xf1, 0xf1, 0xf2,
   0xf2, 0xf3, 0xf3, 0xf4, 0xf4, 0xf5, 0xf5, 0xf6, 0xf6, 0xf7, 0xf7, 0xf8,
   0xf8, 0xf9, 0xf9, 0xfa, 0xfa, 0xfa, 0xfb, 0xfb, 0xfc, 0xfc, 0xfd, 0xfd,
   0xfe, 0xfe, 0xff, 0xff},

  /* number of buttons */
  5,

  /* button names */
  { "copy", "mail", "image-copy", "scan", "power"},

  /* button titles */
  { "copy", "mail", "image copy", "scan", "power"},

  /* flags */
  RTS8891_FLAG_EMULATED_GRAY_MODE
};


static Rts8891_Model hp4470c_model = {
  "HP4470c",			/* Name */
  "Hewlett-Packard",		/* Device vendor string */
  "4470c",			/* Device model name */
  "flatbed scanner",		/* Device  type */
  {1200, 600, 300, 150, 75, 0},	/* possible x-resolutions */
  {600, 300, 150, 0},		/* possible y-resolutions */
  1200,				/* max physical x dpi */
  600,				/* max physical y dpi */
  150,				/* min physical y dpi */

  SANE_FIX (8.3),		/* Start of scan area in mm  (x) */
  SANE_FIX (3.0),		/* Start of scan area in mm (y) */
  SANE_FIX (215.9),		/* Size of scan area in mm (x) */
  SANE_FIX (298.1),		/* Size of scan area in mm (y) */

  SANE_FIX (0.0),		/* Start of scan area in TA mode in mm (x) */
  SANE_FIX (0.0),		/* Start of scan area in TA mode in mm (y) */
  SANE_FIX (100.0),		/* Size of scan area in TA mode in mm (x) */
  SANE_FIX (100.0),		/* Size of scan area in TA mode in mm (y) */

  24, 12, 0,			/* R, G, and B CCD Line-distance correction in lines at
				   max motor resolution */
  /* default sensor */
  SENSOR_TYPE_XPA,

  /* default gamma table */
  {0x00, 0x04, 0x08, 0x0c, 0x10, 0x14, 0x18, 0x1c, 0x20, 0x24, 0x28, 0x2c,
   0x30, 0x34, 0x38, 0x3c, 0x40, 0x44, 0x48, 0x4c, 0x50, 0x52, 0x53, 0x55,
   0x57, 0x58, 0x5a, 0x5c, 0x5d, 0x5f, 0x60, 0x62, 0x63, 0x64, 0x66, 0x67,
   0x68, 0x6a, 0x6b, 0x6c, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x74, 0x75, 0x76,
   0x77, 0x78, 0x79, 0x7a, 0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x82, 0x83,
   0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8d, 0x8e,
   0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x96, 0x97, 0x98, 0x99,
   0x9a, 0x9b, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3,
   0xa3, 0xa4, 0xa5, 0xa6, 0xa6, 0xa7, 0xa8, 0xa9, 0xa9, 0xaa, 0xab, 0xac,
   0xac, 0xad, 0xae, 0xaf, 0xaf, 0xb0, 0xb1, 0xb1, 0xb2, 0xb3, 0xb4, 0xb4,
   0xb5, 0xb6, 0xb6, 0xb7, 0xb8, 0xb8, 0xb9, 0xba, 0xba, 0xbb, 0xbc, 0xbc,
   0xbd, 0xbe, 0xbe, 0xbf, 0xc0, 0xc0, 0xc1, 0xc1, 0xc2, 0xc3, 0xc3, 0xc4,
   0xc5, 0xc5, 0xc6, 0xc6, 0xc7, 0xc8, 0xc8, 0xc9, 0xc9, 0xca, 0xcb, 0xcb,
   0xcc, 0xcc, 0xcd, 0xce, 0xce, 0xcf, 0xcf, 0xd0, 0xd1, 0xd1, 0xd2, 0xd2,
   0xd3, 0xd3, 0xd4, 0xd5, 0xd5, 0xd6, 0xd6, 0xd7, 0xd7, 0xd8, 0xd9, 0xd9,
   0xda, 0xda, 0xdb, 0xdb, 0xdc, 0xdc, 0xdd, 0xdd, 0xde, 0xdf, 0xdf, 0xe0,
   0xe0, 0xe1, 0xe1, 0xe2, 0xe2, 0xe3, 0xe3, 0xe4, 0xe4, 0xe5, 0xe5, 0xe6,
   0xe6, 0xe7, 0xe7, 0xe8, 0xe8, 0xe9, 0xe9, 0xea, 0xea, 0xeb, 0xeb, 0xec,
   0xec, 0xed, 0xed, 0xee, 0xee, 0xef, 0xef, 0xf0, 0xf0, 0xf1, 0xf1, 0xf2,
   0xf2, 0xf3, 0xf3, 0xf4, 0xf4, 0xf5, 0xf5, 0xf6, 0xf6, 0xf7, 0xf7, 0xf8,
   0xf8, 0xf9, 0xf9, 0xfa, 0xfa, 0xfa, 0xfb, 0xfb, 0xfc, 0xfc, 0xfd, 0xfd,
   0xfe, 0xfe, 0xff, 0xff},

  /* number of buttons */
  11,

  /* button names */
  {"plus", "minus", "copy", "mail", "image-copy", "www", "scan", "power",
   "cancel", "options", "toggle-mode"},

  /* button titles */
  {"plus", "minus", "copy", "mail", "image copy", "www", "scan", "power",
   "cancel", "options", "toggle color/gray mode"},

  /* flags */
  RTS8891_FLAG_EMULATED_GRAY_MODE
};

static Rts8891_Model astra4400_model = {
  "Astra 4400",			/* Name */
  "UMAX",			/* Device vendor string */
  "Astra 4400",			/* Device model name */
  "flatbed scanner",		/* Device  type */

  {1200, 600, 300, 150, 75, 0},	/* possible x-resolutions */
  {600, 300, 150, 0},		/* possible y-resolutions */
  1200,				/* max physical x dpi */
  600,				/* max physical y dpi */
  150,				/* min physical y dpi */

  SANE_FIX (8.3),		/* Start of scan area in mm  (x) */
  SANE_FIX (3.0),		/* Start of scan area in mm (y) */
  SANE_FIX (215.9),		/* Size of scan area in mm (x) */
  SANE_FIX (298.1),		/* Size of scan area in mm (y) */

  SANE_FIX (0.0),		/* Start of scan area in TA mode in mm (x) */
  SANE_FIX (0.0),		/* Start of scan area in TA mode in mm (y) */
  SANE_FIX (100.0),		/* Size of scan area in TA mode in mm (x) */
  SANE_FIX (100.0),		/* Size of scan area in TA mode in mm (y) */

  24, 12, 0,			/* R, G, and B CCD Line-distance correction in lines at
				   max motor resolution */
  /* default sensor */
  SENSOR_TYPE_XPA,

  /* default gamma table */
  {0x00, 0x04, 0x08, 0x0c, 0x10, 0x14, 0x18, 0x1c, 0x20, 0x24, 0x28, 0x2c,
   0x30, 0x34, 0x38, 0x3c, 0x40, 0x44, 0x48, 0x4c, 0x50, 0x52, 0x53, 0x55,
   0x57, 0x58, 0x5a, 0x5c, 0x5d, 0x5f, 0x60, 0x62, 0x63, 0x64, 0x66, 0x67,
   0x68, 0x6a, 0x6b, 0x6c, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x74, 0x75, 0x76,
   0x77, 0x78, 0x79, 0x7a, 0x7c, 0x7d, 0x7e, 0x7f, 0x80, 0x81, 0x82, 0x83,
   0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8d, 0x8e,
   0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x96, 0x97, 0x98, 0x99,
   0x9a, 0x9b, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0x9f, 0xa0, 0xa1, 0xa2, 0xa3,
   0xa3, 0xa4, 0xa5, 0xa6, 0xa6, 0xa7, 0xa8, 0xa9, 0xa9, 0xaa, 0xab, 0xac,
   0xac, 0xad, 0xae, 0xaf, 0xaf, 0xb0, 0xb1, 0xb1, 0xb2, 0xb3, 0xb4, 0xb4,
   0xb5, 0xb6, 0xb6, 0xb7, 0xb8, 0xb8, 0xb9, 0xba, 0xba, 0xbb, 0xbc, 0xbc,
   0xbd, 0xbe, 0xbe, 0xbf, 0xc0, 0xc0, 0xc1, 0xc1, 0xc2, 0xc3, 0xc3, 0xc4,
   0xc5, 0xc5, 0xc6, 0xc6, 0xc7, 0xc8, 0xc8, 0xc9, 0xc9, 0xca, 0xcb, 0xcb,
   0xcc, 0xcc, 0xcd, 0xce, 0xce, 0xcf, 0xcf, 0xd0, 0xd1, 0xd1, 0xd2, 0xd2,
   0xd3, 0xd3, 0xd4, 0xd5, 0xd5, 0xd6, 0xd6, 0xd7, 0xd7, 0xd8, 0xd9, 0xd9,
   0xda, 0xda, 0xdb, 0xdb, 0xdc, 0xdc, 0xdd, 0xdd, 0xde, 0xdf, 0xdf, 0xe0,
   0xe0, 0xe1, 0xe1, 0xe2, 0xe2, 0xe3, 0xe3, 0xe4, 0xe4, 0xe5, 0xe5, 0xe6,
   0xe6, 0xe7, 0xe7, 0xe8, 0xe8, 0xe9, 0xe9, 0xea, 0xea, 0xeb, 0xeb, 0xec,
   0xec, 0xed, 0xed, 0xee, 0xee, 0xef, 0xef, 0xf0, 0xf0, 0xf1, 0xf1, 0xf2,
   0xf2, 0xf3, 0xf3, 0xf4, 0xf4, 0xf5, 0xf5, 0xf6, 0xf6, 0xf7, 0xf7, 0xf8,
   0xf8, 0xf9, 0xf9, 0xfa, 0xfa, 0xfa, 0xfb, 0xfb, 0xfc, 0xfc, 0xfd, 0xfd,
   0xfe, 0xfe, 0xff, 0xff},

  /* number of buttons */
  11,

  /* button names */
  {"plus", "minus", "copy", "mail", "image-copy", "www", "scan", "power",
   "cancel", "options", "toggle-mode"},

  /* button titles */
  {"plus", "minus", "copy", "mail", "image copy", "www", "scan", "power",
   "cancel", "options", "toggle color/gray mode"},

  /* flags */
  RTS8891_FLAG_EMULATED_GRAY_MODE
};

/* full list of supported devices: vendor, product, description structure */
static Rts8891_USB_Device_Entry rts8891_usb_device_list[] = {
  {0x03f0, 0x0705, &hp4400c_model},
  {0x03f0, 0x0805, &hp4470c_model},
  {0x1606, 0x0070, &astra4400_model},
  {0, 0, NULL}
};
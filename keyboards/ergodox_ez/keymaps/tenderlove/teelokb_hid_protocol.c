#include QMK_KEYBOARD_H
#include "raw_hid.h"

enum command_ids
{
    id_version = 0x01,
    id_rgblight_enable,
    id_rgblight_disable,
    id_rgblight_toggle,
    id_rgblight_mode,
    id_rgblight_sethsv,
    id_rgblight_get_mode,
    id_rgblight_get_hue,
    id_rgblight_get_sat,
    id_rgblight_get_val,
};

void raw_hid_receive( uint8_t *data, uint8_t length )
{
    switch (data[0])
    {
	/* Version of the TeeloKB protocol */
	case id_version:
	    data[0] = 0x0;
	    data[1] = 0x1;
	    break;
	case id_rgblight_enable:
	    rgblight_enable();
	    break;
	case id_rgblight_disable:
	    rgblight_disable();
	    break;
	case id_rgblight_toggle:
	    rgblight_toggle();
	    break;
	case id_rgblight_mode:
	    rgblight_mode(data[1]);
	    break;
	case id_rgblight_sethsv:
	    {
		uint16_t hue = (data[1] << 8) + data[2];
		rgblight_sethsv(hue, data[3], data[4]);
		break;
	    }
	case id_rgblight_get_mode:
	    data[1] = rgblight_get_mode();
	    break;
	case id_rgblight_get_hue:
	    {
		uint16_t hue = rgblight_get_hue();
		data[1] = (hue >> 8) & 0xFF;
		data[2] = hue & 0xFF;
		break;
	    }
	case id_rgblight_get_sat:
	    data[1] = rgblight_get_sat();
	    break;
	case id_rgblight_get_val:
	    data[1] = rgblight_get_val();
	    break;
	default:
	    data[0] = 0xFF;
	    break;
    }

    /* send the buffer back */
    raw_hid_send(data, length);

}


/*
Copyright 2018 Jack Humbert <jack.humb@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    BASE, // default layer
    SYMB, // symbols
    MDIA, // media keys
};

enum custom_keycodes {
  EPRM = ML_SAFE_RANGE,
  VRSN,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_moonlander(
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_LEFT,              KC_RGHT, LGUI(KC_LBRC),    LGUI(KC_RBRC),    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_D,    KC_F,    KC_K,         KC_EQL,               LSFT(KC_QUOT),    KC_J,    KC_U,    KC_R,    KC_L,    KC_SCLN,  KC_BSLS,
  CTL_T(KC_EQL), KC_A,    KC_S,    KC_E,    KC_T,    KC_G,         KC_MINS,              LSFT(KC_SCLN),    KC_Y,    KC_N,    KC_I,    KC_O,    KC_H,     KC_QUOT,
        KC_LSFT, LCTL_T(KC_Z),KC_X,KC_C,    KC_V,    LGUI_T(KC_B),                                         KC_P,    KC_M,    KC_COMM, KC_DOT,  LCTL_T(KC_SLSH), KC_RSFT,
LT(SYMB,KC_GRV), MO(MDIA),A(KC_LSFT),KC_LALT,LGUI_T(KC_ENT),      LALT_T(KC_APP), RCTL_T(KC_ESC),   LGUI_T(KC_BSPACE),   KC_RALT, KC_LBRC, KC_RBRC, LT(SYMB, KC_ESC),
                                               KC_SPC,  LT(MDIA,KC_ENT), KC_END,         KC_RALT, LT(MDIA,KC_DEL), CTL_T(KC_ESC)
    ),

    [SYMB] = LAYOUT_moonlander(
        EPRM,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,           KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_PGUP,           KC_TRNS, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
        KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,  KC_PGDN,           KC_TRNS, KC_DOWN, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_TRNS,
        KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                             KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, KC_TRNS,
        VRSN,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          RGB_VAI,           RGB_TOG,          KC_TRNS, KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
                                            RGB_HUD, RGB_VAD, RGB_HUI, TOGGLE_LAYER_COLOR,KC_TRNS, KC_TRNS
    ),

    [MDIA] = LAYOUT_moonlander(
        VRSN,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_MPLY, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,         KC_TRNS,            KC_TRNS,               KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case EPRM:
        eeconfig_init();
        return false;
      case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
      #ifdef RGBLIGHT_ENABLE
      case RGB_SLD:
        rgblight_mode(1);
        return false;
      #endif
    }
  }
  return true;
}

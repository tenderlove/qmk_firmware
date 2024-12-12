#include QMK_KEYBOARD_H

enum layers {
    BASE, // default layer
    SYMB, // symbols
    MDIA, // media keys
    FKEYS,// F keys
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
    KC_TAB,      KC_Q,           KC_W,           KC_D,           KC_F,           KC_K,                                           KC_J,             KC_U,             KC_R,            KC_L,             KC_SCLN,          KC_BSLS,
CTL_T(KC_EQL),   KC_A,           KC_S,           KC_E,           KC_T,           KC_G,                                           KC_Y,             KC_N,             KC_I,            KC_O,             KC_H,             KC_QUOT,
    KC_LSFT,     KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_P,             KC_M,             KC_COMM,         KC_DOT,           KC_SLSH,          KC_RSFT,
LT(SYMB,KC_GRV), MO(MDIA),       _______,        LALT_T(KC_LEFT),LGUI_T(KC_ENT), KC_MINS,                                          LSFT(KC_SCLN),    LGUI_T(KC_BSPC),  RALT_T(KC_RGHT), LGUI(KC_LBRC),    KC_RBRC,          LT(SYMB, KC_ESC),
                                                                 KC_SPC,         MO(FKEYS),                                        _______,          CTL_T(KC_ESC)
  ),
  [SYMB] = LAYOUT(
    KC_PGUP,     KC_EXLM,        KC_AT,          KC_LCBR,        KC_RCBR,        KC_PIPE,                                          KC_UP,            KC_7,           KC_8,           KC_9,          KC_ASTR,         _______,
    KC_PGDN,     KC_HASH,        KC_DLR,         KC_LPRN,        KC_RPRN,        KC_GRV,                                           KC_DOWN,          KC_4,           KC_5,           KC_6,          KC_PLUS,         _______,
    _______,     KC_PERC,        KC_CIRC,        KC_LBRC,        KC_RBRC,        KC_TILD,                                          KC_AMPR,          KC_1,           KC_2,           KC_3,          KC_SLSH,         _______,
    _______,     _______,        _______,        _______,        _______,        _______,                                          _______,          _______,        KC_DOT,         KC_0,          KC_EQL,          _______,
                                                                 _______,        _______,                                          _______,          RGB_TOG
  ),
  [MDIA] = LAYOUT(
    _______,     _______,        _______,        KC_MS_U,        _______,        _______,                                          _______,          _______,        _______,        _______,       _______,         _______,
    _______,     _______,        KC_MS_L,        KC_MS_D,        KC_MS_R,        _______,                                          _______,          KC_MPLY,        _______,        _______,       _______,         _______,
    _______,     _______,        _______,        KC_BTN1,        KC_BTN2,        _______,                                          _______,          KC_MPRV,        KC_MNXT,        _______,       _______,         _______,
    _______,     _______,        _______,        _______,        _______,        _______,                                          _______,          KC_VOLD,        KC_VOLU,        KC_MUTE,       _______,         _______,
                                                                 _______,        _______,                                          _______,          _______
  ),
  [FKEYS] = LAYOUT(
    _______,     _______,        _______,        _______,        _______,        _______,                                          _______,            KC_F7,          KC_F8,          KC_F9,        KC_F10,          KC_F11,
    _______,     _______,        _______,        _______,        _______,        _______,                                          _______,            KC_F4,          KC_F5,          KC_F6,       _______,          KC_F12,
    _______,     _______,        _______,        _______,        _______,        _______,                                          _______,            KC_F1,          KC_F2,          KC_F3,       _______,         _______,
    _______,     _______,        _______,        _______,        _______,        _______,                                          _______,          _______,        _______,        _______,       _______,         _______,
                                                                 _______,        _______,                                          _______,          _______
  ),
};

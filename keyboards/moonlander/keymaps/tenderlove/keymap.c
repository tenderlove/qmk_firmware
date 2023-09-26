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

enum td_keycodes {
    MDIA_RBRC
};

typedef enum {
  TAP_NONE,
  SINGLE_TAP,
  SINGLE_HOLD,
  TAP_UNKNOWN
} td_state_t;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_moonlander(
        _______,  _______, _______, _______,         _______,        _______, _______,              _______,        _______,  _______,           _______,         _______,       _______,       _______,
        KC_TAB,   KC_Q,    KC_W,    KC_D,            KC_F,           KC_K,    _______,              LSFT(KC_QUOT),  KC_J,     KC_U,              KC_R,            KC_L,          KC_SCLN,       KC_BSLS,
  CTL_T(KC_EQL),  KC_A,    KC_S,    KC_E,            KC_T,           KC_G,    KC_MINS,              LSFT(KC_SCLN),  KC_Y,     KC_N,              KC_I,            KC_O,          KC_H,          KC_QUOT,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,            KC_V,           KC_B,                                          KC_P,     KC_M,              KC_COMM,         KC_DOT,        KC_SLSH,       KC_RSFT,
LT(SYMB,KC_GRV),  MO(MDIA),_______, LALT_T(KC_LEFT), LGUI_T(KC_ENT), _______,                                       _______,  LGUI_T(KC_BSPACE), RALT_T(KC_RGHT), LGUI(KC_LBRC), TD(MDIA_RBRC), LT(SYMB, KC_ESC),
                                               KC_SPC,  _______, _______,         _______, _______, CTL_T(KC_ESC)
    ),

    [SYMB] = LAYOUT_moonlander(
        EPRM,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,           _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_PGUP, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_PGUP,           _______, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
        KC_PGDN, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,  KC_PGDN,           _______, KC_DOWN, KC_4,    KC_5,    KC_6,    KC_PLUS, _______,
        _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                             KC_AMPR, KC_1,    KC_2,    KC_3,    KC_SLSH, _______,
        KC_GRV,  _______, _______, _______, _______,          RGB_VAI,           RGB_TOG,          _______, KC_DOT,  KC_0,    KC_EQL,  _______,
                                            RGB_HUD, RGB_VAD, RGB_HUI, TOGGLE_LAYER_COLOR,_______, RGB_TOG
    ),

    [MDIA] = LAYOUT_moonlander(
        VRSN,    _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_MS_U, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,           _______, _______, KC_MPLY, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                             _______, KC_MPRV, KC_MNXT, _______, _______, _______,
        _______, _______, _______, KC_BTN1, KC_BTN2,          _______,           _______,          KC_VOLD, KC_VOLU, KC_MUTE, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),
};

typedef struct {
    bool is_press_action;
    td_state_t state;
} tap;

static tap tap_state = {
    .is_press_action = true,
    .state = 0
};

td_state_t
current_state(qk_tap_dance_state_t *state)
{
    if (state->count == 1) {
        if (!state->pressed) {
            return SINGLE_TAP;
        }
        else {
            return SINGLE_HOLD;
        }
    }
    else {
        return TAP_UNKNOWN;
    }
}

void
ql_finished(qk_tap_dance_state_t *state, void *user_data)
{
    tap_state.state = current_state(state);

    switch(tap_state.state) {
        case SINGLE_TAP:
            tap_code16(LGUI(KC_RBRC));
            break;
        case SINGLE_HOLD:
            layer_on(MDIA);
            break;
        default:
            break;
    }
}

void
ql_reset(qk_tap_dance_state_t *state, void *user_data)
{
    if (tap_state.state == SINGLE_HOLD) {
        layer_off(MDIA);
    }

    tap_state.state = TAP_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [MDIA_RBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)
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

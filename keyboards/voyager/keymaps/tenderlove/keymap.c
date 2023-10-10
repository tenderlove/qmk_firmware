#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"
#include "keymap_hungarian.h"
#include "keymap_swedish.h"
#include "keymap_br_abnt2.h"
#include "keymap_canadian_multilingual.h"
#include "keymap_german_ch.h"
#include "keymap_jp.h"
#include "keymap_korean.h"
#include "keymap_bepo.h"
#include "keymap_italian.h"
#include "keymap_slovenian.h"
#include "keymap_lithuanian_azerty.h"
#include "keymap_danish.h"
#include "keymap_norwegian.h"
#include "keymap_portuguese.h"
#include "keymap_contributions.h"
#include "keymap_czech.h"
#include "keymap_romanian.h"
#include "keymap_russian.h"
#include "keymap_uk.h"
#include "keymap_estonian.h"
#include "keymap_belgian.h"
#include "keymap_us_international.h"
#include "keymap_croatian.h"
#include "keymap_turkish_q.h"
#include "keymap_slovak.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)
#define SE_SECT_MAC ALGR(KC_6)
#define MOON_LED_LEVEL LED_LEVEL

enum layers {
    BASE, // default layer
    SYMB, // symbols
    MDIA, // media keys
};

enum td_keycodes {
    MDIA_RBRC,
    BACK_LBRC
};

typedef enum {
  TAP_NONE,
  SINGLE_TAP,
  DOUBLE_TAP,
  SINGLE_HOLD,
  DOUBLE_HOLD,
  TAP_UNKNOWN
} td_state_t;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_voyager(
    KC_TAB,      KC_Q,           KC_W,           KC_D,           KC_F,           KC_K,                                           KC_J,             KC_U,             KC_R,            KC_L,             KC_SCLN,          KC_BSLS,
CTL_T(KC_EQL),   KC_A,           KC_S,           KC_E,           KC_T,           KC_G,                                           KC_Y,             KC_N,             KC_I,            KC_O,             KC_H,             KC_QUOT,
    KC_LSFT,     KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_P,             KC_M,             KC_COMM,         KC_DOT,           KC_SLSH,          KC_RSFT,
LT(SYMB,KC_GRV), MO(MDIA),       _______,        LALT_T(KC_LEFT),LGUI_T(KC_ENT), KC_MINS,                                        LSFT(KC_SCLN),    LGUI_T(KC_BSPACE),RALT_T(KC_RGHT), TD(BACK_LBRC),    TD(MDIA_RBRC),    LT(SYMB, KC_ESC),
                                                                 KC_SPC,         _______,                                        _______,          CTL_T(KC_ESC)
  ),
  [SYMB] = LAYOUT_voyager(
    KC_PGUP,     KC_EXLM,        KC_AT,          KC_LCBR,        KC_RCBR,        KC_PIPE,                                          KC_UP,            KC_7,           KC_8,           KC_9,          KC_ASTR,         _______,
    KC_PGDN,     KC_HASH,        KC_DLR,         KC_LPRN,        KC_RPRN,        KC_GRV,                                           KC_DOWN,          KC_4,           KC_5,           KC_6,          KC_PLUS,         _______,
    _______,     KC_PERC,        KC_CIRC,        KC_LBRC,        KC_RBRC,        KC_TILD,                                          KC_AMPR,          KC_1,           KC_2,           KC_3,          KC_SLSH,         _______,
    _______,     _______,        _______,        _______,        _______,        _______,                                          _______,          _______,        KC_DOT,         KC_0,          KC_EQL,          _______,
                                                                 _______,        _______,                                          _______,          RGB_TOG
  ),
  [MDIA] = LAYOUT_voyager(
    _______,     _______,        _______,        KC_MS_U,        _______,        _______,                                          _______,          _______,        _______,        _______,       _______,         _______,
    _______,     _______,        KC_MS_L,        KC_MS_D,        KC_MS_R,        _______,                                          _______,          KC_MPLY,        _______,        _______,       _______,         _______,
    _______,     _______,        _______,        KC_BTN1,        KC_BTN2,        _______,                                          _______,          KC_MPRV,        KC_MNXT,        _______,       _______,         _______,
    _______,     _______,        _______,        _______,        _______,        _______,                                          _______,          KC_VOLD,        KC_VOLU,        KC_MUTE,       _______,         _______,
                                                                 _______,        _______,                                          _______,          _______
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
    else if (state->count == 2) {
        if (!state->pressed) {
            return DOUBLE_TAP;
        }
        else {
            return DOUBLE_HOLD;
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
            tap_code(KC_RBRC);
            break;
        case DOUBLE_TAP:
            tap_code16(LGUI(KC_RBRC));
            break;
        case SINGLE_HOLD:
        case DOUBLE_HOLD:
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

void
lbrc_finished(qk_tap_dance_state_t *state, void *user_data)
{
    tap_state.state = current_state(state);

    switch(tap_state.state) {
        case SINGLE_TAP:
            tap_code(KC_LBRC);
            break;
        case DOUBLE_TAP:
            tap_code16(LGUI(KC_LBRC));
            break;
        case SINGLE_HOLD:
        case DOUBLE_HOLD:
            layer_on(MDIA);
            break;
        default:
            break;
    }
}

void
lbrc_reset(qk_tap_dance_state_t *state, void *user_data)
{
    if (tap_state.state == SINGLE_HOLD) {
        layer_off(MDIA);
    }

    tap_state.state = TAP_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [MDIA_RBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset),
  [BACK_LBRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lbrc_finished, lbrc_reset)
};

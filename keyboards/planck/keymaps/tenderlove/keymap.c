// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum planck_layers {
  _NORMAN,
  _SYMB,
  _MOUSE,
  _ADJUST
};

enum planck_keycodes {
  NORMAN = SAFE_RANGE,
  SYMB,
  MOUSE,
  BACKLIT,
  BOOTLOADER
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_NORMAN] = {
  {LT(_MOUSE,KC_TAB),KC_Q,    KC_W,    KC_D,    KC_F,          KC_K,    KC_J,    KC_U,          KC_R,    KC_L,    KC_SCLN, LT(_ADJUST, KC_BSPC)},
  {CTL_T(KC_EQL),    KC_A,    KC_S,    KC_E,    KC_T,          KC_G,    KC_Y,    KC_N,          KC_I,    KC_O,    KC_H,    KC_QUOT},
  {KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,          KC_B,    KC_P,    KC_M,          KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT},
  {LT(_SYMB,KC_GRV), BACKLIT,  KC_TAB, KC_LALT, GUI_T(KC_ENT), KC_SPC,  CTL_T(KC_BSPC), KC_ESC, KC_RALT, KC_LBRC, KC_RBRC, LT(_SYMB,KC_MINS)}
},

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMB] = {
  {_______,        KC_EXLM,    KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_UP,   KC_7,    KC_8,   KC_9,  KC_ASTR, LGUI(KC_LBRC)},
  {LGUI(KC_LBRC),  KC_HASH,    KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,  KC_DOWN, KC_4,    KC_5,   KC_6,  KC_PLUS, LGUI(KC_RBRC)},
  {KC_LEFT,        KC_PERC,    KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_AMPR, KC_1,    KC_2,   KC_3,  KC_BSLS, KC_RIGHT },
  {KC_TRNS,        BOOTLOADER, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DOT, KC_0,  KC_UP,   KC_TRNS }
},

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = {
  {_______, KC_F12,  KC_DEL,  _______, _______, _______, _______, _______, KC_MS_U, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, KC_MS_L, _______, KC_MS_R, _______, KC_WH_U},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MS_D, _______, KC_MS_U, KC_WH_D},
  {_______, _______, _______, _______, _______, KC_BTN1, KC_BTN2, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R}
},

[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, _______,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______, _______,  _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)

};

#ifdef AUDIO_ENABLE

#define NORMAN_SOUND \
    E__NOTE(_GS6 ),  \
    E__NOTE(_A6  ),  \
    S__NOTE(_REST),  \
    Q__NOTE(_E7  ),

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_norman[][2]     = SONG(NORMAN_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif


void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case NORMAN:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_norman, false, 0);
        #endif
          if (record->event.pressed) {
              set_single_persistent_default_layer(_NORMAN);
          }
      }
      return false;
      break;
    case SYMB:
      return false;
      break;
    case MOUSE:
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
    case BOOTLOADER:
      shutdown_user();
      clear_keyboard();
      print("\n\nJump to bootloader... ");

      *(uint16_t *)0x0800 = 0x7777; // these two are a-star-specific

      bootloader_jump(); // should not return
      print("not supported.\n");
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_startup, false, 0);
}

void shutdown_user()
{
    PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_NOTE_ARRAY(music_scale, false, 0);
}

#endif

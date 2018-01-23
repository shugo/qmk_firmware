#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  TCODE_TOGGLE,
  DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

// Fillers to make layering more clear
#define KC_ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define KC_AJST ADJUST
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_TCTG TCODE_TOGGLE
#define KC_DRS1 DYN_REC_START1
#define KC_DRS2 DYN_REC_START2
#define KC_DMP1 DYN_MACRO_PLAY1
#define KC_DMP2 DYN_MACRO_PLAY2
#define KC_DRS  DYN_REC_STOP
#define KC_DBG  DEBUG

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |  Ins |   `  |   1  |   2  |   3  |   4  |   5  |      |   6  |   7  |   8  |   9  |   0  | Bksp | Del  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   -  | Tab  |   Q  |   W  |   E  |   R  |   T  |      |   Y  |   U  |   I  |   O  |   P  |   [  |   ]  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   =  | Esc  |   A  |   S  |   D  |   F  |   G  |      |   H  |   J  |   K  |   L  |   ;  |   "  |Enter |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Pg Up| Shift|   Z  |   X  |   C  |   V  |   B  |      |   N  |   M  |   ,  |   .  |   /  | Home | End  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Pg Dn|Adjust| Ctrl | Alt  | GUI  |Lower |Space |      |Space |Raise | Left | Down |  Up  | Right|   \  |
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_QWERTY] = KC_KEYMAP(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
     ESC ,GRV , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,MINS,EQL ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     HOME,TAB , Q  , W  , E  , R  , T  ,      Y  , U  , I  , O  , P  ,LBRC,RBRC,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     END ,LCTL, A  , S  , D  , F  , G  ,      H  , J  , K  , L  ,SCLN,QUOT,ENT ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     PGUP,LSFT, Z  , X  , C  , V  , B  ,      N  , M  ,COMM,DOT ,SLSH,BSLS,RSFT,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     PGDN,DEL ,INS ,LALT,LGUI,LOWR,SPC ,     BSPC,RASE,LEFT,DOWN, UP ,RGHT,RCTL
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

/* Lower
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |      |   ~  |  F1  |  F3  |  F3  |  F4  |  F5  |      |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   _  |      |   !  |   @  |   #  |   $  |   %  |      |   ^  |   &  |   *  |   (  |   )  |   {  |   }  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   +  |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |  F6  |   _  |   +  |   {  |   }  |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |  F7  |  F8  |  F9  |  F10 |  F11 |      |  F12 |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |      |
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_LOWER] = KC_KEYMAP(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         ,TILD, F1 , F2 , F3 , F4 , F5 ,      F6 , F7 , F8 , F9 ,F10 ,F11 ,F12 ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     UNDS,    ,EXLM, AT ,HASH,DLR ,PERC,     CIRC,AMPR,ASTR,LPRN,RPRN,LCBR,RCBR,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     PLUS,    , F1 , F2 , F3 , F4 , F5 ,      F6 ,MINS,PLUS,LCBR,RCBR,    ,BTN3,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    , F7 , F8 , F9 ,F10 ,F11 ,     F12 ,    ,    ,    ,    ,    ,BTN2,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,MS_L,MS_D,MS_U,MS_R,BTN1
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

/* Raise
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |      |   ~  |  F1  |  F3  |  F3  |  F4  |  F5  |      |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   _  |      |   1  |   2  |   3  |   4  |   5  |      |   6  |   7  |   8  |   9  |   0  |   {  |   }  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |   +  |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |  F6  |   -  |   =  |   [  |   ]  |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |  F7  |  F8  |  F9  |  F10 |  F11 |      |  F12 |ISO # |ISO / |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |      |
 * `------------------------------------------------'      `------------------------------------------------'
 */
  [_RAISE] = KC_KEYMAP(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
     DRS ,TILD, F1 , F2 , F3 , F4 , F5 ,      F6 , F7 , F8 , F9 ,F10 ,F11 ,F12 ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     DRS1,    , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,LCBR,RCBR,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     DMP1,    , F1 , F2 , F3 , F4 , F5 ,      F6 ,MINS,PLUS,LBRC,RBRC,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     DRS2,    , F7 , F8 , F9 ,F10 ,F11 ,     F12 ,NUHS,NUBS,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     DMP2,    ,    ,    ,    ,DBG ,TCTG,         ,    ,MNXT,VOLD,VOLU,MPLY,MUTE
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_ADJUST] = KEYMAP(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, \
    _______, _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, KC_DEL,  _______, \
    _______, _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

#include "tc_tbl.h"

static bool tcode_enabled;
static int tcode_prev_key_index;

/*
 * Viterbi Keyboard Matrix
 *
 * Left keyboard:
 * Cols: 0 1 2 3 4 5 6 (Left to Right)
 * Rows: 0 1 2 3 4 (Top to Bottom)
 *
 * Right keyboard:
 * Cols: 6 5 4 3 2 1 0 (Left to Right)
 * Rows: 5 6 7 8 9 (Top to Bottom)
 */

static inline bool is_tcode_key(keyrecord_t *record) {
  keypos_t kp = record->event.key;
  return (0 <= kp.row && kp.row <= 3 && 2 <= kp.col && kp.col <= 6) ||
	  (5 <= kp.row && kp.row <= 8 && 2 <= kp.col && kp.col <= 6);
}

static inline int tcode_key_index(keyrecord_t *record) {
  keypos_t kp = record->event.key;
  if (kp.row <= 3) {
    return kp.row * 10 + kp.col - 2;
  }
  else {
    return (kp.row - 5) * 10 + (6 - kp.col) + 5;
  }
}

static inline bool process_tcode(uint16_t keycode, keyrecord_t *record) {
  if (!tcode_enabled) {
    return true;
  }
  if (!is_tcode_key(record) || get_mods() != 0) {
    tcode_prev_key_index = -1;
    return true;
  }
  if (!record->event.pressed) {
    return false;
  }
  int i = tcode_key_index(record);
  dprintf("T-Code: row = %d, col = %d, i = %d\n",
	  record->event.key.row,
	  record->event.key.col,
	  i);
  if (tcode_prev_key_index == -1) {
    tcode_prev_key_index = i;
  }
  else {
    int j = tcode_prev_key_index + i * 40;
    dprintf("T-Code: tcode_prev_key_index = %d, i = %d, j = %d\n",
	    tcode_prev_key_index, i, j);
    if (0 <= j && j < 40 * 40) {
      uint16_t ch = pgm_read_word(tcode_table + j);
      process_unicode(ch | QK_UNICODE, record);
    }
    else {
      process_unicode(0x3013 | QK_UNICODE, record);
    }
    tcode_prev_key_index = -1;
  }
  return false;
}

void matrix_init_user(void) {
  tcode_enabled = false;
  tcode_prev_key_index = -1;
  debug_enable = true;
  set_unicode_input_mode(UC_LNX);
}

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_tcode(keycode, record)) {
    return false;
  }
  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }
  switch (keycode) {
    case TCODE_TOGGLE:
      if (record->event.pressed) {
        tcode_enabled = !tcode_enabled;
        if (tcode_enabled) {
	  tcode_prev_key_index = -1;
        }
      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}

/* Copyright 2019 Trevor
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

bool numlock_status = false;

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  KVM_1,
  KVM_2,
  KVM_3,
  KVM_4
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( /* Base */
    KC_GRV,  KC_1,    KC_2,    KC_3,        KC_4,       KC_5,                KC_MUTE,             KC_6,    KC_7,       KC_8,    KC_9,    KC_0,     KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,        KC_R,       KC_T,                KC_UP,               KC_Y,    KC_U,       KC_I,    KC_O,    KC_P,     KC_DEL,
    KC_ESC,  KC_A,    KC_S,    KC_D,        KC_F,       KC_G,    KC_LEFT,    KC_DOWN, KC_RGHT,    KC_H,    KC_J,       KC_K,    KC_L,    KC_SCLN,  KC_ENTER,
    KC_LSFT, KC_Z,    KC_X,    KC_C,        KC_V,       KC_B,    TG(_LOWER),          TG(_RAISE), KC_N,    KC_M,       KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
    KC_LCTL, KC_LALT, KC_PSCR, MO(_RAISE),  MO(_LOWER), KC_LGUI, KC_LCTL,             KC_RCTL,    KC_SPC,  KC_RCTL,    KC_HOME, KC_END,  KC_PGDN,  KC_PGUP
  ),

  [_LOWER] = LAYOUT( /* Lower */
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH,     KC_DLR,     KC_PERC,             KC_MPLY,             KC_CIRC, KC_AMPR,    KC_ASTR, KC_LPRN, KC_RPRN,  KC_DEL,
    _______, KC_LCBR, KC_RCBR, KC_LBRC,     KC_RBRC,    KC_PLUS,             KC_PGUP,             KC_BSLS, KC_LPRN,    KC_RPRN, KC_QUOT, KC_DQUO,  _______,
    _______, _______, _______, KC_MINS,     KC_UNDS,    KC_EQL,  KC_HOME,    KC_PGDN, KC_END,     KC_LEFT, KC_DOWN,    KC_UP,   KC_RGHT, KC_COLN,  _______,
    _______, _______, _______, _______,     _______,    KC_PIPE, _______,             _______,    KC_LCBR, KC_RCBR,    KC_LBRC, KC_RBRC, KC_QUES,  _______,
    _______, _______, _______, _______,     _______,    _______, _______,             _______,    _______, _______,    KC_END,  _______, _______,  KC_PGDN
  ),

  [_RAISE] = LAYOUT( /* Raise */
    _______, KVM_1,   KVM_2,   KVM_3,       KVM_4,      _______,             RGB_TOG,             _______, KC_CLR,     KC_PSLS, KC_PAST, KC_PMNS,  _______,
    _______, KC_F1,   KC_F2,   KC_F3,       KC_F4,      KC_F5,               RGB_HUI,             _______, KC_P7,      KC_P8,   KC_P9,   KC_PLUS,  _______,
    _______, KC_F6,   KC_F7,   KC_F8,       KC_F9,      KC_F10,  RGB_MOD,    RGB_HUD, RGB_RMOD,   _______, KC_P4,      KC_P5,   KC_P6,   KC_COLN,  _______,
    _______, KC_F11,  KC_F12,  TG(_ADJUST), _______,    KC_CAPS, _______,             _______,    _______, KC_P1,      KC_P2,   KC_P3,   KC_PENT,  _______,
    _______, _______, _______, _______,     _______,    _______, _______,             _______,    _______, KC_P0,      _______, KC_PDOT, RESET,    _______
  ),

  [_ADJUST] = LAYOUT( /* Adjust */
    _______, _______, _______, _______,     _______,    _______,             _______,             _______, _______,    _______, _______, _______,  _______,
    _______, _______, _______, _______,     _______,    _______,             _______,             _______, _______,    _______, _______, _______,  _______,
    _______, _______, _______, _______,     _______,    RGB_TOG, _______,    _______, _______,    RGB_MOD, _______,    _______, _______, _______,  _______,
    _______, _______, _______, _______,     RGB_M_T,    RGB_M_B, _______,             _______,    RGB_HUI, RGB_HUD,    RGB_SAI, RGB_SAD, RGB_VAI,  RGB_VAD,
    _______, _______, _______, _______,     _______,    _______, _______,             _______,    _______, _______,    _______, _______, _______,  _______
  )

};

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(B5);
  setPinOutput(B6);
  setPinOutput(B7);
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KVM_1: // Send code to KVM to switch to computer 1
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_SCROLLLOCK));
        SEND_STRING(SS_TAP(X_SCROLLLOCK));
        SEND_STRING("1");
      } else {
        // nothing goes here
      }
      break;
    case KVM_2: // Send code to KVM to switch to computer 2
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_SCROLLLOCK));
        SEND_STRING(SS_TAP(X_SCROLLLOCK));
        SEND_STRING("2");
      } else {
        // nothing goes here
      }
      break;
    case KVM_3: // Send code to KVM to switch to computer 3
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_SCROLLLOCK));
        SEND_STRING(SS_TAP(X_SCROLLLOCK));
        SEND_STRING("3");
      } else {
        // nothing goes here
      }
      break;
    case KVM_4: // Send code to KVM to switch to computer 4
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_SCROLLLOCK));
        SEND_STRING(SS_TAP(X_SCROLLLOCK));
        SEND_STRING("4");
      } else {
        // nothing goes here
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

uint32_t layer_state_set_user(uint32_t state) {

  switch (biton32(state)) {
    case _QWERTY:
      writePinLow(B6);
      writePinLow(B7);
      break;
    case _LOWER:
      writePinHigh(B6);
      writePinLow(B7);
      break;
    case _RAISE:
      writePinHigh(B7);
      writePinLow(B6);
      if(!numlock_status) {
        SEND_STRING(SS_TAP(X_NUMLOCK));
      }
      break;
    case _ADJUST:
      writePinHigh(B6);
      writePinHigh(B7);
      break;
  }
  return state;
}

void encoder_update_user(uint8_t index, bool clockwise) {
  switch(biton32(layer_state)) {
    case _LOWER:
      if (clockwise) {
        tap_code(KC_PGDN);
      } else {
        tap_code(KC_PGUP);
      }
      break;
    case _RAISE:
      if (clockwise) {
        tap_code(KC_PGDN);
      } else {
        tap_code(KC_PGUP);
      }
      break;
    case _ADJUST:
      if (clockwise) {
        tap_code(KC_PGDN);
      } else {
        tap_code(KC_PGDN);
      }
      break;
    default:
      if (clockwise) {
        tap_code(KC_VOLU);
      } else {
        tap_code(KC_VOLD);
      }
      break;
  }
}

void led_set_user(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinHigh(B5);
  } else {
    writePinLow(B5);
  }
  if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
    numlock_status = true;
  } else {
    numlock_status = false;
  }
}

#ifdef OLED_DRIVER_ENABLE
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

static const char PROGMEM numlock_on[] = {
  0x4E, 0x55, 0x4D, 0x20, 0x20, 0x99, 0x9A, 0x00
};

static const char PROGMEM numlock_off[] = {
  0x20, 0x20, 0x20, 0x20, 0x20, 0x99, 0x9A, 0x00
};

static const char PROGMEM capslock_on[] = {
  0x43, 0x41, 0x50, 0x20, 0x20, 0xB9, 0xBA, 0x00
};

static const char PROGMEM capslock_off[] = {
  0x20, 0x20, 0x20, 0x20, 0x20, 0xB9, 0xBA, 0x00
};

static void render_status(void) {
  // Name and version info
  /* oled_write_P(PSTR("Pariah v0.1\n\n"), false); */

  // Layer status
  oled_write_P(PSTR("LAYER: "), false);
  switch (get_highest_layer(layer_state)) {
    case _QWERTY:
      oled_write_P(PSTR("DEFAULT   v0.1\n"), false);
      break;
    case _LOWER:
      oled_write_P(PSTR("LOWER     v0.1\n"), false);
      break;
    case _RAISE:
      oled_write_P(PSTR("RAISE     v0.1\n"), false);
      break;
    case _ADJUST:
      oled_write_P(PSTR("ADJUST    v0.1\n"), false);
      break;
    default:
      oled_write_P(PSTR("Undefined v0.1\n"), false);
  }

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  if (led_state.num_lock) {
    oled_write_ln_P(numlock_on, false);
  } else {
    oled_write_ln_P(numlock_off, false);
  }
  if (led_state.caps_lock) {
    oled_write_ln_P(capslock_on, false);
  } else {
    oled_write_ln_P(capslock_off, false);
  }
  oled_write_ln_P(PSTR(""), false);

  // Logo
  render_logo();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_0;
}

void oled_task_user(void) {
  render_status();
}
#endif

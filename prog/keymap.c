/*
 * Copyright (C) 2022 Kawashima Teruaki
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include "kbdconfig.h"
#include "src/lib/mzkbd/keymap.h"
#include "src/lib/mzkbd/keycode.h"
#include "src/lib/mzkbd/mzkbd_keycode.h"
#include "src/lib/mzkbd/layer.h"
#include "src/lib/mzkbd/simcmd.h"

#define LAYOUT( \
    L11,  L12, L13, L14, L15, L17, L19, L28, L27, L26, L25, L24, L23,  L22,      \
    L32, L31, L33, L34, L36, L16, L18, L29, L48, L47, L46, L45, L44, L43,   L21, \
     L52,  L51, L53, L35, L37, L38, L39, L49, L68, L66, L65, L64, L63, L42, L41, \
      L72,  L71, L54, L55, L56, L57, L58, L69, L67, L87, L86, L84,  L62,    L61, \
      L92,    L73, L74, L75, L76, L77, L59, L89, L88, LA6, L85,  L83,  L82, L81, \
       L91,  L93, L94, L95,  L97,  L78,  L79, LA8, LA7, LA5, LA4, LA3, LA2, LA1, \
                        L96,   L98,     LA9,L99 \
) { \
    { L11, L12, L13, L14, L15, L16, L17, L18, L19 }, \
    { L21, L22, L23, L24, L25, L26, L27, L28, L29 }, \
    { L31, L32, L33, L34, L35, L36, L37, L38, L39 }, \
    { L41, L42, L43, L44, L45, L46, L47, L48, L49 }, \
    { L51, L52, L53, L54, L55, L56, L57, L58, L59 }, \
    { L61, L62, L63, L64, L65, L66, L67, L68, L69 }, \
    { L71, L72, L73, L74, L75, L76, L77, L78, L79 }, \
    { L81, L82, L83, L84, L85, L86, L87, L88, L89 }, \
    { L91, L92, L93, L94, L95, L96, L97, L98, L99 }, \
    { LA1, LA2, LA3, LA4, LA5, LA6, LA7, LA8, LA9 }, \
}

enum ly_name {
    LY_BASE,
    LY_FUNC,
    MUM_LY,
};

#define MO_FUNC  MO(LY_FUNC)

static const kbdkey_t s_key_matrix[MUM_LY][NUM_PINS][NUM_PINS-1] = {
    [LY_BASE] = LAYOUT(
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_HOME,
         KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
          KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,   KC_ENT,        KC_PGDN,
          KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,    KC_RSFT,    KC_UP,   KC_END,
           KC_LCTL,  MO_FUNC, KC_LGUI, KC_LALT,  KC_SPC,   KC_SPC,  KC_RALT, KC_RGUI, KC_APP,  MO_FUNC, KC_RCTL,      KC_LEFT, KC_DOWN, KC_RGHT,
                                              KC_BTN1,   KC_BTN2,     AG_MS_X,AG_MS_Y
    ),
    [LY_FUNC] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______,
         _______,  _______, _______, _______, CMD_BLR, _______, _______, _______, KC_INS,  _______, KC_PSCR, _______, _______, KC_INT3, KC_VOLU,
          _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BRID, KC_BRIU,   _______,       KC_VOLD,
          _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,    _______, KC_MUTE,
           _______,  XXXXXXX, _______, _______,  _______,  KC_BRK,  _______, _______, KC_CAPS, XXXXXXX, _______,      KC_MPRV, KC_MPLY, KC_MNXT,
                                              _______,   _______,     AG_MS_X,AG_MS_Y
    ),
};

kbdkey_t keymap_get_keycode(int column, int row)
{
#if USE_LAYER
    layer_t layer = MUM_LY;
    kbdkey_t key = KC_TRANSPARENT;
    do {
        layer--;
        if (layer_is_on(layer)) {
            key = s_key_matrix[layer][row][column];
        }
    } while (key == KC_TRANSPARENT && layer > 0);
    return key;
#else
    return s_key_matrix[row][column];
#endif
}

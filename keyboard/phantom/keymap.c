/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

/* 
 * Keymap for Phantom controller
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap.h"


// Convert physical keyboard layout to matrix array.
// This is a macro to define keymap easily in keyboard layout form.
#define KEYMAP( \
/*  esc  ?1   f1   f2   f3   f4   ?2   f5   f6   f7   f8   f9   f10  f11  f12 |PRSC SCRL PAUS */ \
    K5A, K0D, K5C, K5D, K5E, K5F, K0G, K5G, K5H, K5I, K5J, K5K, K5L, K5M, K5N, K5O, K5P, K5Q, \
/*  `    1    2    3    4    5    6    7    8    9    10   _    =    ?3   BKSP INS  HOME PGUP */ \
    K5B, K4A, K4B, K4C, K4D, K4E, K4F, K4G, K4H, K4I, K4J, K4K, K4L, K4M, K4N, K4O, K4P, K4Q, \
/*   tab   q    w    e    r    t    y    u    i    o    p    [    ]    \       DEL  END  PGDN */ \
     K3A,  K3B, K3C, K3D, K3E, K3F, K3G, K3H, K3I, K3J, K3K, K3L, K3M, K3N,    K3O, K3P, K3Q, \
/*   CAP     a    s    d    f    g    h    j    k    l    ;    '    ?4   ENTR  ?5   ?6   ?7   */ \
     K2A,    K2B, K2C, K2D, K2E, K2F, K2G, K2H, K2I, K2J, K2K, K2L, K2M, K2N,  K2O, K2P, K2Q, \
/*  SHFT   ?8   z    x    c    v    b    n    m    ,    .    /     ?9     SHFT ?10  UP   ?11  */ \
    K1A,   K1B, K1C, K1D, K1E, K1F, K1G, K1H, K1I, K1J, K1K, K1L,  K1M,   K1N, K1O, K1P, K1Q, \
/*   CTRL   SUPR  ALT     ?12    ?13    SPAC  ?14    ?15     ALT  SUPR  CTRL   LEFT DOWN RIGH */ \
     K0A,   K0B,  K0C,    K0E,   K0F,   K0H,  K0I,   K0K,    K0L, K0M,  K0N,   K0O, K0P, K0Q  \
) { \
/*             0         1         2         3         4         5         6         7         8         9        10        11         12       13         14        15        16    */ \
/*             A         B         C         D         E         F         G         H         I         J         K         L          M        N          O         P         Q    */ \
/* 0 */   { KC_##K0A, KC_##K0B, KC_##K0C, KC_##K0D, KC_##K0E, KC_##K0F, KC_##K0G, KC_##K0H, KC_##K0I, KC_NO   , KC_##K0K, KC_##K0L, KC_##K0M, KC_##K0N, KC_##K0O, KC_##K0P, KC_##K0Q}, \
/* 1 */   { KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_##K1F, KC_##K1G, KC_##K1H, KC_##K1I, KC_##K1J, KC_##K1K, KC_##K1L, KC_##K1M, KC_##K1N, KC_##K1O, KC_##K1P, KC_##K1Q}, \
/* 2 */   { KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F, KC_##K2G, KC_##K2H, KC_##K2I, KC_##K2J, KC_##K2K, KC_##K2L, KC_##K2M, KC_##K2N, KC_##K2O, KC_##K2P, KC_##K2Q}, \
/* 3 */   { KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F, KC_##K3G, KC_##K3H, KC_##K3I, KC_##K3J, KC_##K3K, KC_##K3L, KC_##K3M, KC_##K3N, KC_##K3O, KC_##K3P, KC_##K3Q}, \
/* 4 */   { KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D, KC_##K4E, KC_##K4F, KC_##K4G, KC_##K4H, KC_##K4I, KC_##K4J, KC_##K4K, KC_##K4L, KC_##K4M, KC_##K4N, KC_##K4O, KC_##K4P, KC_##K4Q}, \
/* 5 */   { KC_##K5A, KC_##K5B, KC_##K5C, KC_##K5D, KC_##K5E, KC_##K5F, KC_##K5G, KC_##K5H, KC_##K5I, KC_##K5J, KC_##K5K, KC_##K5L, KC_##K5M, KC_##K5N, KC_##K5O, KC_##K5P, KC_##K5Q}, \
}

#define KEYCODE(layer, row, col) (pgm_read_byte(&keymaps[(layer)][(row)][(col)]))


// Assign Fn key(0-7) to a layer to which switch with the Fn key pressed.
static const uint8_t PROGMEM fn_layer[] = {
    0,              // Fn0
    1,              // Fn1
    2,              // Fn2
    3,              // Fn3
    4,              // Fn4
    5,              // Fn5
    6,              // Fn6
    7               // Fn7
};

// Assign Fn key(0-7) to a keycode sent when release Fn key without use of the layer.
// See layer.c for details.
static const uint8_t PROGMEM fn_keycode[] = {
    KC_NO,          // Fn0
    KC_NO,          // Fn1
    KC_NO,          // Fn2
    KC_NO,          // Fn3
    KC_NO,          // Fn4
    KC_NO,          // Fn5
    KC_NO,          // Fn6
    KC_NO           // Fn7
};

/* 
 * Phantom keyboard layout 7bit style
 * 
 *  esc  ?1   f1   f2   f3   f4   ?2   f5   f6   f7   f8   f9   f10  f11  f12 |PRSC SCRL PAUS 
 *  `    1    2    3    4    5    6    7    8    9    10   _    =    ?3   BKSP INS  HOME PGUP
 *   tab   q    w    e    r    t    y    u    i    o    p    [    ]    \       DEL  END  PGDN
 *   CAP     a    s    d    f    g    h    j    k    l    ;    '    ?4   ENTR  ?5   ?6   ?7  
 *  SHFT   ?8   z    x    c    v    b    n    m    ,    .    /     ?9     SHFT ?10  UP   ?11 
 *   CTRL   SUPR  ALT     ?12    ?13    SPAC  ?14    ?15     ALT  SUPR  CTRL   LEFT DOWN RIGH
 */
 
static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Layer 0: Default Layer
 *
 * DVORAK:
 *
 *  CAPS f1   f2   f3   f4   f5   f6   f7   f8   f9   f10  f11  f12  PRSC PAUS Fn1  Fn2  Fn3
 *  `    1    2    3    4    5    6    7    8    9    0    [    ]    BKSP DEL  VOLU HOME PGUP
 *   TAB   '    ,    .    p    y    f    g    c    r    l    /    =    \       VOLD END  PGDN
 *   LCTL    a    o    e    u    i    d    h    t    n    s    -    ENT  F15   MPLY MUTE MSTP 
 *  ESC  LSFT   ;    q    j    k    x    b    m    w    v    z     RSFT  F16   MPRV UP   MNXT
 *   LCTL   LGUI  ALT     WH_U    WH_D    SPC   F13    F14    RALT  RGUI  RCTL LEFT DOWN RIGH
 
 */

  KEYMAP(\
    CAPS, F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,   F10, F11,  F12,  PSCR, BRK,   FN1,  FN2,  FN3, \
    GRV,  1,    2,    3,    4,    5,    6,    7,    8,    9,    0,   LBRC, RBRC, BSPC, DEL,   VOLU, HOME, PGUP, \
     TAB,   QUOT, COMM, DOT,  P,    Y,    F,    G,    C,    R,    L,    SLSH, EQL,  BSLS,     VOLD, END,  PGDN, \
      LCTL,    A,    O,    E,    U,    I,    D,    H,    T,    N,   S,    MINS, ENT,   F15,   MPLY, MUTE, MSTP, \
    ESC,  LSFT,   SCLN, Q,    J,    K,    X,    B,    M,    W,    V,   Z,     RSFT,    F16,   MPRV,   UP, MNXT, \
     LCTL,  LGUI,  LALT,       WH_U,   WH_D,   SPC,      F13,    F14,    RALT,  RGUI,  RCTL,  LEFT, DOWN, RGHT),


/*  
 *  DVORAK + mouse/numpad
 *
 *  CAPS f1   f2   f3   f4   f5   f6   f7   f8   f9   f10  f11  f12  PRSC PAUS Fn1  Fn2  Fn3
 *  `    BTN4 BTN3 BTN5 ACL0 5    6    7    8    9    0    [    ]    BKSP DEL  PPLS PMNS NLCK
 *   TAB   BTN1 MS_U BTN2 ACL1 y    f    g    c    r    l    /    =    \       P7   P8   P9
 *   LCTL    MS_L MS_D MS_R ACL2 i    d    h    t    n    s    -    ENT  F15   P4   P5   P6
 *  ESC  LSFT   ;    q    j    k    x    b    m    w    v    z     RSFT  F16   P1   P2   P3
 *   LCTL   LGUI  ALT     WH_U    WH_D    SPC   F13    F14    RALT  RGUI  RCTL P0   PDOT PENT
 

 */

  KEYMAP(\
    CAPS, F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,   F10, F11,  F12,  PSCR, BRK,   FN1,  FN2,  FN3, \
    GRV,  BTN4, BTN3, BTN5, 4,    5,    6,    7,    8,    9,    0,   LBRC, RBRC, BSPC, DEL,   PPLS, PMNS, NLCK, \
     TAB,   BTN1, MS_U, BTN2, P,    Y,    F,    G,    C,    R,    L,    SLSH, EQL,  BSLS,     P7,   P8,   P9, \
      LCTL,    MS_L, MS_D, MS_R, U,    I,    D,    H,    T,    N,   S,    MINS, ENT,   F15,   P4,   P5,   P6, \
    ESC,  LSFT,   SCLN, Q,    J,    K,    X,    B,    M,    W,    V,   Z,     RSFT,    F16,   P1,   P2,   P3, \
     LCTL,  LGUI,  LALT,       WH_U,   WH_D,   SPC,      F13,    F14,    RALT,  RGUI,  RCTL,  P0,   PDOT, PENT),


/* QWERTY */

  KEYMAP(\
    CAPS, F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,   F10, F11,  F12,  PSCR, BRK,   FN1,  FN2,  FN3, \
    GRV,  1,    2,    3,    4,    5,    6,    7,    8,    9,    0,   MINS, EQL, BSPC, DEL,    VOLU, HOME, PGUP, \
     TAB,   Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    LBRC, RBRC, BSLS,     VOLD, END,  PGDN, \
      LCTL,    A,    S,    D,    F,    G,    H,    J,    K,    L,   SCLN, QUOT, ENT,   F15,   MPLY, MUTE, MSTP, \
    ESC,  LSFT,   Z,    X,    C,    V,    B,    N,    M,    COMM, DOT, SLSH,  RSFT,    F16,   MPRV,   UP, MNXT, \
     LCTL,  LGUI,  LALT,       WH_U,   WH_D,   SPC,      F13,    F14,    RALT,  RGUI,  RCTL,  LEFT, DOWN, RGHT),

};


uint8_t keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t col)
{
    return KEYCODE(layer, row, col);
}

uint8_t keymap_fn_layer(uint8_t index)
{
    return pgm_read_byte(&fn_layer[index]);
}

uint8_t keymap_fn_keycode(uint8_t index)
{
    return pgm_read_byte(&fn_keycode[index]);
}

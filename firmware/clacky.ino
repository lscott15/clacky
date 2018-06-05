

#include <Code_Sc.h>
#include <LayerState.h>
#include <Code_LayerHold.h>
#include <Key_LayeredKeys.h>

#include <Row.h>
#include <Scanner_uC.h>
#include <ScanDelay.h>

#include <Code_LEDLock.h>
#include <LED_uC.h>

/* Speed Configuration 
 *  Here we set the delay to allow the switch to debounce so we don't send
 *  the same keypress multiple times
 */
 ScanDelay scanDelay(9000);

/* Read Pins
 *  Set up which pins will read which rows/columns
 */
 uint8_t readPins[] = {13, 14, 15, 16, 17, 18, 19, 20, 0, 1, 2, 3, 4, 5, 21};
 uint8_t readPinCount = sizeof(readPins)/sizeof(*readPins);

 Scanner_uC scanner(LOW, readPins, readPinCount);

// LEDS
LED_uC LED_capslock(26);


/* Codes
 *  Here we are mapping our key objects to the codes they should send when pressed
 */


// enumerate the two layers
enum layerIds { NORMAL, FN};

// keep track of the active layer
LayerState layerState;

// function
Code_LayerHold l_function(FN, layerState);
 
// alphas
Code_Sc s_q(KEY_Q);
Code_Sc s_w(KEY_W);
Code_Sc s_e(KEY_E);
Code_Sc s_r(KEY_R);
Code_Sc s_t(KEY_T);
Code_Sc s_y(KEY_Y);
Code_Sc s_u(KEY_U);
Code_Sc s_i(KEY_I);
Code_Sc s_o(KEY_O);
Code_Sc s_p(KEY_P);
Code_Sc s_a(KEY_A);
Code_Sc s_s(KEY_S);
Code_Sc s_d(KEY_D);
Code_Sc s_f(KEY_F);
Code_Sc s_g(KEY_G);
Code_Sc s_h(KEY_H);
Code_Sc s_j(KEY_J);
Code_Sc s_k(KEY_K);
Code_Sc s_l(KEY_L);
Code_Sc s_z(KEY_Z);
Code_Sc s_x(KEY_X);
Code_Sc s_c(KEY_C);
Code_Sc s_v(KEY_V);
Code_Sc s_b(KEY_B);
Code_Sc s_n(KEY_N);
Code_Sc s_m(KEY_M);

// symbols
Code_Sc s_backTick(KEY_TILDE);
Code_Sc s_minus(KEY_MINUS);
Code_Sc s_equal(KEY_EQUAL);
Code_Sc s_leftBracket(KEY_LEFT_BRACE);
Code_Sc s_rightBracket(KEY_RIGHT_BRACE);
Code_Sc s_backslash(KEY_BACKSLASH);
Code_Sc s_semicolon(KEY_SEMICOLON);
Code_Sc s_quote(KEY_QUOTE);
Code_Sc s_comma(KEY_COMMA);
Code_Sc s_period(KEY_PERIOD);
Code_Sc s_slash(KEY_SLASH);

// nums
Code_Sc s_1(KEY_1);
Code_Sc s_2(KEY_2);
Code_Sc s_3(KEY_3);
Code_Sc s_4(KEY_4);
Code_Sc s_5(KEY_5);
Code_Sc s_6(KEY_6);
Code_Sc s_7(KEY_7);
Code_Sc s_8(KEY_8);
Code_Sc s_9(KEY_9);
Code_Sc s_0(KEY_0);

// funs
Code_Sc s_f1(KEY_F1);
Code_Sc s_f2(KEY_F2);
Code_Sc s_f3(KEY_F3);
Code_Sc s_f4(KEY_F4);
Code_Sc s_f5(KEY_F5);
Code_Sc s_f6(KEY_F6);
Code_Sc s_f7(KEY_F7);
Code_Sc s_f8(KEY_F8);
Code_Sc s_f9(KEY_F9);
Code_Sc s_f10(KEY_F10);
Code_Sc s_f11(KEY_F11);
Code_Sc s_f12(KEY_F12);
Code_Sc s_f17(KEY_F17);

// mods
Code_Sc s_lShift(MODIFIERKEY_LEFT_SHIFT);
Code_Sc s_rShift(MODIFIERKEY_RIGHT_SHIFT);
Code_Sc s_lAlt(MODIFIERKEY_LEFT_ALT);
Code_Sc s_rAlt(MODIFIERKEY_RIGHT_ALT);
Code_Sc s_lCtrl(MODIFIERKEY_LEFT_CTRL);
Code_Sc s_rCtrl(MODIFIERKEY_RIGHT_CTRL);
Code_Sc s_lSuper(MODIFIERKEY_LEFT_GUI);
Code_Sc s_rSuper(MODIFIERKEY_RIGHT_GUI);

// specials
Code_Sc s_enter(KEY_ENTER);
Code_Sc s_esc(KEY_ESC);
Code_Sc s_backspace(KEY_BACKSPACE);
Code_Sc s_tab(KEY_TAB);
Code_Sc s_space(KEY_SPACE);

//Code_Sc s_caps(KEY_CAPS_LOCK);
Code_LEDLock s_caps(KEY_CAPS_LOCK, LED_capslock);

// arrows
Code_Sc s_up(KEY_UP);
Code_Sc s_left(KEY_LEFT);
Code_Sc s_down(KEY_DOWN);
Code_Sc s_right(KEY_RIGHT);

// nav cluster
Code_Sc s_insert(KEY_INSERT);
Code_Sc s_delete(KEY_DELETE);
Code_Sc s_home(KEY_HOME);
Code_Sc s_end(KEY_END);
Code_Sc s_pageUp(KEY_PAGE_UP);
Code_Sc s_pageDown(KEY_PAGE_DOWN);

Code_Sc s_print(KEY_PRINTSCREEN);
Code_Sc s_breezeFile(KEYPAD_8);
Code_Sc s_breezeCancel(KEYPAD_MINUS);
Code_Sc s_breezeDel(KEY_NUM_LOCK);
Code_Sc s_breezeIns(KEYPAD_0);

Code_Sc code_null(NULL); // This is used for "missing" columns under the spacebar

/* Keys
 *  Here we pack Codes into Keys
 */

// Layered keys here, they are used in the constructor for our actual row keys

Key* const ptrsKeys_insert[] = { &s_insert, &s_breezeIns };
Key_LayeredKeys k_insert(ptrsKeys_insert);

Key* const ptrsKeys_delete[] = { &s_delete, &s_breezeDel };
Key_LayeredKeys k_delete(ptrsKeys_delete);

Key* const ptrsKeys_home[] = { &s_home, &s_breezeFile };
Key_LayeredKeys k_home(ptrsKeys_home);

Key* const ptrsKeys_end[] = {&s_end, &s_breezeCancel };
Key_LayeredKeys k_end(ptrsKeys_end);

Key* const ptrsKeys_p[] = {&s_p, &s_print};
Key_LayeredKeys k_p(ptrsKeys_p);

// layer interface
LayerStateInterface& Key_LayeredKeys::refLayerState = layerState;

// normal keys, and rows
Key* const ptrsKeys_0[] = {&s_esc, &s_f1, &s_f2, &s_f3, &s_f4, &s_f5, &s_f6, &s_f7, &s_f8, &s_f9, &s_f10, &s_f11, &s_f12, &s_f17, &k_insert};
uint8_t keyCount_0 = sizeof(ptrsKeys_0)/sizeof(*ptrsKeys_0);

Key* const ptrsKeys_1[] = {&s_backTick, &s_1, &s_2, &s_3, &s_4, &s_5, &s_6, &s_7, &s_8, &s_9, &s_0, &s_minus, &s_equal, &s_backspace, &k_home};
uint8_t keyCount_1 = sizeof(ptrsKeys_1)/sizeof(*ptrsKeys_1);
 
Key* const ptrsKeys_2[] = {&s_tab, &s_q, &s_w, &s_e, &s_r, &s_t, &s_y, &s_u, &s_i, &s_o, &k_p, &s_leftBracket, &s_rightBracket, &s_backslash, &s_pageUp};
uint8_t keyCount_2 = sizeof(ptrsKeys_2)/sizeof(*ptrsKeys_2);

Key* ptrsKeys_3[] = {&s_caps, &s_a, &s_s, &s_d, &s_f, &s_g, &s_h, &s_j, &s_k, &s_l, &s_semicolon, &s_quote, &s_enter, &k_delete, &k_end};
uint8_t keyCount_3 = sizeof(ptrsKeys_3)/sizeof(*ptrsKeys_3);

Key* const ptrsKeys_4[] = {&s_lShift, &s_z, &s_x, &s_c, &s_v, &s_b, &s_n, &s_m, &s_comma, &s_period, &s_slash, &s_rShift, &s_up, &code_null, &s_pageDown};
uint8_t keyCount_4 = sizeof(ptrsKeys_4)/sizeof(*ptrsKeys_4);

Key* const ptrsKeys_5[] = {&s_lCtrl, &s_lSuper, &s_lAlt, &s_space, &code_null, &code_null, &code_null, &code_null, &s_rAlt, &s_rSuper, &l_function, &s_rCtrl, &s_left, &s_down, &s_right};
uint8_t keyCount_5 = sizeof(ptrsKeys_5)/sizeof(*ptrsKeys_5);


/* Rows
 *  Here we pack our key objects into Row objects
 */
Row row_0(scanner, 22, ptrsKeys_0, keyCount_0);
Row row_1(scanner, 23, ptrsKeys_1, keyCount_1);
Row row_2(scanner, 6, ptrsKeys_2, keyCount_2);
Row row_3(scanner, 7, ptrsKeys_3, keyCount_3);
Row row_4(scanner, 8, ptrsKeys_4, keyCount_4);
Row row_5(scanner, 9, ptrsKeys_5, keyCount_5);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  row_0.process();
  row_1.process();
  row_2.process();
  row_3.process();
  row_4.process();
  row_5.process();
  scanDelay.delay();
}

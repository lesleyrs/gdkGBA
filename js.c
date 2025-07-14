#ifdef __wasm
#include <stdlib.h>
#include <stddef.h>

#include <js/glue.h>
#include <js/dom_pk_codes.h>

#include "io.h"

void __unordtf2() {}

extern void* screen;

static bool onkeydown(void *user_data, int key, int code, int modifiers) {
    switch (code) {
        case DOM_PK_ARROW_UP:     key_input.w &= ~BTN_U;   break;
        case DOM_PK_ARROW_DOWN:   key_input.w &= ~BTN_D;   break;
        case DOM_PK_ARROW_LEFT:   key_input.w &= ~BTN_L;   break;
        case DOM_PK_ARROW_RIGHT:  key_input.w &= ~BTN_R;   break;
        case DOM_PK_A:      key_input.w &= ~BTN_A;   break;
        case DOM_PK_S:      key_input.w &= ~BTN_B;   break;
        case DOM_PK_Q:      key_input.w &= ~BTN_LT;  break;
        case DOM_PK_W:      key_input.w &= ~BTN_RT;  break;
        case DOM_PK_TAB:    key_input.w &= ~BTN_SEL; break;
        case DOM_PK_ENTER: key_input.w &= ~BTN_STA; break;
    default:                                   break;
    }

    if (code == DOM_PK_F5 || code == DOM_PK_F11 || code == DOM_PK_F12 || code == DOM_PK_0 || code == DOM_PK_MINUS || code == DOM_PK_EQUAL) {
        return 0;
    }
    return 1;
}


static bool onkeyup(void *user_data, int key, int code, int modifiers) {
    switch (code) {
        case DOM_PK_ARROW_UP:     key_input.w |= BTN_U;   break;
        case DOM_PK_ARROW_DOWN:   key_input.w |= BTN_D;   break;
        case DOM_PK_ARROW_LEFT:   key_input.w |= BTN_L;   break;
        case DOM_PK_ARROW_RIGHT:  key_input.w |= BTN_R;   break;
        case DOM_PK_A:      key_input.w |= BTN_A;   break;
        case DOM_PK_S:      key_input.w |= BTN_B;   break;
        case DOM_PK_Q:      key_input.w |= BTN_LT;  break;
        case DOM_PK_W:      key_input.w |= BTN_RT;  break;
        case DOM_PK_TAB:    key_input.w |= BTN_SEL; break;
        case DOM_PK_ENTER: key_input.w |= BTN_STA; break;
    default:                                  break;
    }

    if (code == DOM_PK_F5 || code == DOM_PK_F11 || code == DOM_PK_F12 || code == DOM_PK_0 || code == DOM_PK_MINUS || code == DOM_PK_EQUAL) {
        return 0;
    }
    return 1;
}

void platform_init() {
    JS_createCanvas(240, 160);
    JS_setTitle("gdkGBA");
    JS_addKeyDownEventListener(NULL, onkeydown);
    JS_addKeyUpEventListener(NULL, onkeyup);
    screen = malloc(240 * 160 * 4);
}
void platform_uninit() {
}
#endif

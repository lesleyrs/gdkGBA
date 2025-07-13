#ifdef __wasm
#include <stdlib.h>
#include <stddef.h>

#include <js/glue.h>
#include <js/key_codes.h>

#include "io.h"

void __unordtf2() {}

extern void* screen;

static bool onkeydown(void *user_data, int key_code, int modifiers) {
    switch (key_code) {
        case DOM_VK_UP:     key_input.w &= ~BTN_U;   break;
        case DOM_VK_DOWN:   key_input.w &= ~BTN_D;   break;
        case DOM_VK_LEFT:   key_input.w &= ~BTN_L;   break;
        case DOM_VK_RIGHT:  key_input.w &= ~BTN_R;   break;
        case DOM_VK_A:      key_input.w &= ~BTN_A;   break;
        case DOM_VK_S:      key_input.w &= ~BTN_B;   break;
        case DOM_VK_Q:      key_input.w &= ~BTN_LT;  break;
        case DOM_VK_W:      key_input.w &= ~BTN_RT;  break;
        case DOM_VK_TAB:    key_input.w &= ~BTN_SEL; break;
        case DOM_VK_RETURN: key_input.w &= ~BTN_STA; break;
    default:                                   break;
    }

    if (key_code == DOM_VK_F5 || key_code == DOM_VK_F11 || key_code == DOM_VK_F12) {
        return 0;
    }
    return 1;
}


static bool onkeyup(void *user_data, int key_code, int modifiers) {
    switch (key_code) {
        case DOM_VK_UP:     key_input.w |= BTN_U;   break;
        case DOM_VK_DOWN:   key_input.w |= BTN_D;   break;
        case DOM_VK_LEFT:   key_input.w |= BTN_L;   break;
        case DOM_VK_RIGHT:  key_input.w |= BTN_R;   break;
        case DOM_VK_A:      key_input.w |= BTN_A;   break;
        case DOM_VK_S:      key_input.w |= BTN_B;   break;
        case DOM_VK_Q:      key_input.w |= BTN_LT;  break;
        case DOM_VK_W:      key_input.w |= BTN_RT;  break;
        case DOM_VK_TAB:    key_input.w |= BTN_SEL; break;
        case DOM_VK_RETURN: key_input.w |= BTN_STA; break;
    default:                                  break;
    }

    if (key_code == DOM_VK_F5 || key_code == DOM_VK_F11 || key_code == DOM_VK_F12) {
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

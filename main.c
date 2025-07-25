#include <stdio.h>
#include <stdlib.h>

#include "arm.h"
#include "arm_mem.h"

#include "io.h"
#include "platform.h"
#include "video.h"

const int64_t max_rom_sz = 32 * 1024 * 1024;

static uint32_t to_pow2(uint32_t val) {
    val--;

    val |= (val >>  1);
    val |= (val >>  2);
    val |= (val >>  4);
    val |= (val >>  8);
    val |= (val >> 16);

    return val + 1;
}

int main(int argc, char* argv[]) {
    printf("gdkGBA - Gameboy Advance emulator made by gdkchan\n");
    printf("This is FREE software released into the PUBLIC DOMAIN\n\n");

    arm_init();

    if (argc < 2) {
        printf("Error: Invalid number of arguments!\n");
        printf("Please specify a ROM file.\n");

#ifndef __wasm
        return 0;
#endif
    }

    FILE *image;

    image = fopen("gba_bios.bin", "rb");

    if (image == NULL) {
        printf("Error: GBA BIOS not found!\n");
#ifdef __wasm
#include "gba_bios.h"
#include <string.h>
        memcpy(bios, gba_bios_bin, sizeof(gba_bios_bin));
        printf("Loading HLE BIOS replacement.\n");
#else
        printf("Place it on this directory with the name \"gba_bios.bin\".\n");

        return 0;
#endif
    }

    fread(bios, 16384, 1, image);

    fclose(image);

#ifdef __wasm
#include <js/glue.h>
    if (argc < 2) {
        platform_init();
        JS_setFont("bold 13px Roboto");
        JS_fillStyle("white");
        const char *text[] = {
            "Error: Invalid number of arguments!\n",
            "Please specify a ROM file.\n",
            "(.gba)",
            "Click to browse...",
        };

        int count = sizeof(text) / sizeof(text[0]);
        int y = 160 / count;
        int y_step = 64;

        for (int i = 0; i < count; i++) {
            JS_fillText(text[i], (240 - JS_measureTextWidth(text[i])) / 2, (y + i * y_step) / 2);
        }

        int len;
        uint8_t *file = JS_openFilePicker(&len, NULL);
        cart_rom_size = len;
        cart_rom_mask = to_pow2(cart_rom_size) - 1;
        if (cart_rom_size > max_rom_sz) cart_rom_size = max_rom_sz;
        memcpy(rom, file, cart_rom_size);
        free(file);
    } else {
#endif
    image = fopen(argv[1], "rb");

    if (image == NULL) {
        printf("Error: ROM file couldn't be opened.\n");
        printf("Make sure that the file exists and the name is correct.\n");

        return 0;
    }

    fseek(image, 0, SEEK_END);

    cart_rom_size = ftell(image);
    cart_rom_mask = to_pow2(cart_rom_size) - 1;

    if (cart_rom_size > max_rom_sz) cart_rom_size = max_rom_sz;

    fseek(image, 0, SEEK_SET);
    fread(rom, cart_rom_size, 1, image);

    fclose(image);

    platform_init();
#ifdef __wasm
    }
#endif
    arm_reset();

    bool run = true;

    while (run) {
        run_frame();
#ifndef __wasm
     SDL_Event event;

     while (SDL_PollEvent(&event)) {
         switch (event.type) {
             case SDL_KEYDOWN:
                 switch (event.key.keysym.sym) {
                     case SDLK_UP:     key_input.w &= ~BTN_U;   break;
                     case SDLK_DOWN:   key_input.w &= ~BTN_D;   break;
                     case SDLK_LEFT:   key_input.w &= ~BTN_L;   break;
                     case SDLK_RIGHT:  key_input.w &= ~BTN_R;   break;
                     case SDLK_a:      key_input.w &= ~BTN_A;   break;
                     case SDLK_s:      key_input.w &= ~BTN_B;   break;
                     case SDLK_q:      key_input.w &= ~BTN_LT;  break;
                     case SDLK_w:      key_input.w &= ~BTN_RT;  break;
                     case SDLK_TAB:    key_input.w &= ~BTN_SEL; break;
                     case SDLK_RETURN: key_input.w &= ~BTN_STA; break;
                     default:                                   break;
                 }
             break;

             case SDL_KEYUP:
                 switch (event.key.keysym.sym) {
                     case SDLK_UP:     key_input.w |= BTN_U;   break;
                     case SDLK_DOWN:   key_input.w |= BTN_D;   break;
                     case SDLK_LEFT:   key_input.w |= BTN_L;   break;
                     case SDLK_RIGHT:  key_input.w |= BTN_R;   break;
                     case SDLK_a:      key_input.w |= BTN_A;   break;
                     case SDLK_s:      key_input.w |= BTN_B;   break;
                     case SDLK_q:      key_input.w |= BTN_LT;  break;
                     case SDLK_w:      key_input.w |= BTN_RT;  break;
                     case SDLK_TAB:    key_input.w |= BTN_SEL; break;
                     case SDLK_RETURN: key_input.w |= BTN_STA; break;
                     default:                                  break;
                 }
             break;

             case SDL_QUIT: run = false; break;
         }
     }
#endif
    }

    platform_uninit();
    arm_uninit();

    return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <time.h>
#include "array.h"
#include "stack.h"
#include "queue.h"
#include "linked_list.h"
#include "../render/render_helpers.h"

int main() {

    t_visualizer DNSVisualizer = {
        .window = NULL,
        .renderer = NULL,
    };
    
    if (sdl_initialize(&DNSVisualizer)) {
        visualizer_cleanup(&DNSVisualizer, EXIT_FAILURE);
    }

    if(TTF_Init() == -1) {
        visualizer_cleanup(&DNSVisualizer, EXIT_FAILURE);
    }

    // TODO: add health checks
    VisualizerContext ctx = {
        .current_state = STATE_HOME,
        .arr = create_dns_array(10),
        .visualizer = DNSVisualizer,
    };
    
    // TODO: rm 
    TTF_Font *ourFont = TTF_OpenFont("./fonts/8bitOperatorPlus8-Regular.ttf", 12);

    if (ourFont == NULL) {
        printf("could not load font\n");
        visualizer_cleanup(&DNSVisualizer, EXIT_FAILURE);
    }

    while(true) {
    // 1. HANDLE EVENTS
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        handle_global_input(&ctx, &event);

        switch (ctx.current_state) {
            case STATE_HOME:
                handle_home_input(&ctx, &event);
                break;
            case STATE_ARRAY_VIEW:
                handle_array_input(&ctx, &event);
                break;
            default:
                break;
        }
    }

    // 2. RENDER CURRENT STATE
    switch (ctx.current_state) {
        case STATE_HOME:
            draw_homescreen(ctx);
            break;
        case STATE_ARRAY_VIEW:
            draw_array_screen(ctx);
            break;
        default:
            break;
    }
        SDL_Delay(16);
    }

    visualizer_cleanup(&DNSVisualizer, EXIT_SUCCESS);
    TTF_CloseFont(ourFont);
    printf("SDL2 Setup succeeded \n");
    return 0;
}
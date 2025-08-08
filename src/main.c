#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "array.h"
#include "stack.h"
#include "queue.h"
#include "linked_list.h"
#include "sorting_algorithms.h"
#include "../render/render_helpers.h"

int main() {
    dns_arr_t* sort = create_dns_array(0);
    for(int i = 0; i < 10; i++) {
        dns_arr_append(sort);
        SDL_Delay(1000);
    }

    for(int i = 0; i < sort->size; i++) {
        printf("value at index %d is: %d\n", i, sort->data[i]);
    }

    printf("bubble sort call\n");

    sort = bubble_sort(sort);

    for(int i = 0; i < sort->size; i++) {
        printf("Sorted value at index %d is: %d\n", i, sort->data[i]);
    }
    

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
        .stack = stack_create(5),
        .queue = queue_create(5),
        .ll = linked_list_create(),
        .visualizer = DNSVisualizer,
    };
    
    stack_push_multiple_types(ctx.stack);
    
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
            case STATE_STACK_VIEW:
                handle_stack_input(&ctx, &event);
                break;
            case STATE_QUEUE_VIEW:
                handle_queue_input(&ctx, &event);
                break;
            case STATE_LL_VIEW:
                handle_ll_input(&ctx, &event);
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
        case STATE_STACK_VIEW:
           draw_stack_screen(ctx);
           break;
        case STATE_QUEUE_VIEW:
            draw_queue_screen(ctx); 
            break;
        case STATE_LL_VIEW:
            draw_ll_screen(ctx);
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
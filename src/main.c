#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "array.h"

#define WINDOW_TITLE "01 Open Window"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef struct Visualizer {
    SDL_Window *window;
    SDL_Renderer *renderer;
} t_visualizer;

void visualizer_cleanup(t_visualizer * visualizer, int exit_status);
bool sdl_initialize(t_visualizer *visualzier);

int main() {
    srand(time(NULL));  

    dns_arr_t *arr = create_dns_array(10);

    printf("This is the new array with size: %d and index 2: %d\n", arr->size, arr->arr[2]);

    int set = dns_arr_set(arr, 5, 2);
    printf("Index 2 after new set: %d and in func %d\n", arr->arr[2], set);

    printf("Index 10 before del: %d and size %d\n", arr->arr[10], arr->size);
    int del = dns_arr_del_at_index(arr, 9);
    printf("Index 9 after del: %d and size %d\n", arr->arr[9], arr->size);

    int add = dns_arr_append(arr, 20);
    printf("Index 10 after appending 20: %d and size %d\n", arr->arr[10], arr->size);

    t_visualizer DNSVisualizer = {
        .window = NULL,
        .renderer = NULL,
    };

    if (sdl_initialize(&DNSVisualizer)) {
        visualizer_cleanup(&DNSVisualizer, EXIT_FAILURE);
    }

    SDL_Rect rectangle;
    rectangle.x = 200;
    rectangle.y = 200;
    rectangle.w = 200;
    rectangle.h = 200;

    while(true) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch (event.type)
            {
            case SDL_QUIT:
                visualizer_cleanup(&DNSVisualizer, EXIT_SUCCESS);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_ESCAPE:
                    visualizer_cleanup(&DNSVisualizer, EXIT_SUCCESS);
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(DNSVisualizer.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(DNSVisualizer.renderer);

        
        SDL_SetRenderDrawColor(DNSVisualizer.renderer, 160, 32, 240, SDL_ALPHA_OPAQUE);

        SDL_RenderDrawRect(DNSVisualizer.renderer, &rectangle);
        
        SDL_RenderPresent(DNSVisualizer.renderer);
        
        SDL_Delay(16);

    }

    visualizer_cleanup(&DNSVisualizer, EXIT_SUCCESS);

    printf("SDL2 Setup succeeded \n");
    return 0;
}

void visualizer_cleanup(t_visualizer *visualizer, int exit_status) {
    SDL_DestroyRenderer(visualizer->renderer);
    SDL_DestroyWindow(visualizer->window);
    SDL_Quit();
    exit(exit_status);
}

bool sdl_initialize(t_visualizer *visualzier) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        fprintf(stderr, "Error initialiazing SDL: %s\n", SDL_GetError());
        return true;
    }
    

    visualzier->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    if (!visualzier->window) {
        fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        return true;
    }

    visualzier->renderer = SDL_CreateRenderer(visualzier->window, -1, 0);
    
    if (!visualzier->renderer) {
        fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
        return true;
    }

    return false;
}




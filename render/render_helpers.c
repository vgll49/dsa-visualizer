#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "render_helpers.h"


#define WINDOW_TITLE "01 Open Window"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720



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

SDL_Rect draw_text(t_visualizer visualizer, int x, int y, TTF_Font* font, char* text, SDL_Color color) {
    SDL_Surface* surface_text = TTF_RenderText_Solid(font, text, color);

    int text_height;
    int text_width;
    TTF_SizeUTF8(font, text, &text_width, &text_height);
    SDL_Rect text_rect;
    text_rect.w = text_width;
    text_rect.x = x;
    text_rect.y = y;
    text_rect.h = text_height;

    SDL_Texture* texture_text = SDL_CreateTextureFromSurface(visualizer.renderer, surface_text);
    SDL_SetRenderDrawColor(visualizer.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(visualizer.renderer, &text_rect);
    SDL_RenderCopy(visualizer.renderer, texture_text, NULL, &text_rect);
    SDL_DestroyTexture(texture_text);

    return text_rect;
}

void draw_homescreen(VisualizerContext ctx) {
    SDL_SetRenderDrawColor(ctx.visualizer.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(ctx.visualizer.renderer);


    TTF_Font *head_font = TTF_OpenFont("./fonts/8bitOperatorPlus8-Regular.ttf", 64);
    TTF_Font *body_font = TTF_OpenFont("./fonts/8bitOperatorPlus8-Regular.ttf", 24);

    SDL_Color color_head = {255, 255, 255};
    SDL_Color color_body = {160, 32, 240};

    char* header_text = "Welcome to my DSA Visualizer";
    int header_text_height;
    int header_text_width;
    TTF_SizeUTF8(head_font, header_text, &header_text_width, &header_text_height);

    int header_pos_x = SCREEN_WIDTH/2 - header_text_width/2;
    
    SDL_Rect header_pos = draw_text(ctx.visualizer, header_pos_x, 100, head_font, header_text, color_head);


    // TODO: Add loop through arr of strings, add them with spcaing of y * 2
    SDL_Rect body_pos = draw_text(ctx.visualizer, header_pos.x, header_pos.y * 2, body_font, "> press 1 for Array Operations", color_body);
    draw_text(ctx.visualizer, header_pos.x, header_pos.y + 150, body_font, "> press 2 for Stack Operations", color_body);
    draw_text(ctx.visualizer, header_pos.x, header_pos.y + 200, body_font, "> press 3 for Queue Operations", color_body);

    SDL_RenderPresent(ctx.visualizer.renderer);
}
 


void draw_array_screen(VisualizerContext ctx) {
    SDL_SetRenderDrawColor(ctx.visualizer.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(ctx.visualizer.renderer);

    for (int i = 0; i < ctx.arr->size; i++) {
        int height = 50 + (ctx.arr->data[i]*5);

        SDL_Rect rect;
        rect.x = (i+1) * 75;
        rect.y = SCREEN_HEIGHT - height;
        rect.h = height;
        rect.w = 50;

        draw_value_rectangle(ctx.visualizer, rect, ctx.arr->data[i]);
    }
    
    SDL_RenderPresent(ctx.visualizer.renderer);
}

void draw_value_rectangle(t_visualizer visualizer, SDL_Rect rect, int number) {
        TTF_Font *value_font = TTF_OpenFont("./fonts/8bitOperatorPlus8-Regular.ttf", 12);

        char *num_text = malloc(12);
        int text_height;
        int text_widht;
        
        sprintf(num_text, "%d", number);

        TTF_SizeUTF8(value_font, num_text, &text_widht, &text_height);
        SDL_Color color = {255, 255, 255};
        SDL_Surface* surface_text = TTF_RenderText_Solid(value_font, num_text, color);
        free(num_text);


        SDL_Rect text_rect;
        text_rect.x = rect.x + rect.w/2 - text_widht/2;
        text_rect.y = 680;
        text_rect.h = text_height;
        text_rect.w = text_widht;


        SDL_Texture* texture_text = SDL_CreateTextureFromSurface(visualizer.renderer, surface_text);
        SDL_FreeSurface(surface_text);

        SDL_SetRenderDrawColor(visualizer.renderer, 160, 32, 240, SDL_ALPHA_OPAQUE);
        
        SDL_RenderFillRect(visualizer.renderer, &rect);
        SDL_RenderFillRect(visualizer.renderer, &text_rect);
        SDL_RenderCopy(visualizer.renderer, texture_text, NULL, &text_rect);
        SDL_DestroyTexture(texture_text);
}

void handle_array_input(VisualizerContext *ctx, SDL_Event *event) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.scancode)
        {
        case SDL_SCANCODE_A:
            dns_arr_append(ctx->arr);
            break;
        case SDL_SCANCODE_D: 
            dns_arr_del_at_index(ctx->arr, 0);
            break;
        default:
            break;
        }
    }
}

void handle_stack_input(VisualizerContext *ctx, SDL_Event *event) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.scancode)
        {
        case SDL_SCANCODE_A:
            dns_arr_append(ctx->arr);
            break;
        case SDL_SCANCODE_D: 
            dns_arr_del_at_index(ctx->arr, 0);
            break;
        default:
            break;
        }
    }
}

void handle_queue_input(VisualizerContext *ctx, SDL_Event *event) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.scancode)
        {
        case SDL_SCANCODE_A:
            dns_arr_append(ctx->arr);
            break;
        case SDL_SCANCODE_D: 
            dns_arr_del_at_index(ctx->arr, 0);
            break;
        default:
            break;
        }
    }
}


void handle_global_input(VisualizerContext *ctx, SDL_Event *event) {
            switch (event->type)
            {
            case SDL_QUIT:
                visualizer_cleanup(&ctx->visualizer, EXIT_SUCCESS);
                break;
            case SDL_KEYDOWN:
                switch (event->key.keysym.scancode)
                {
                case SDL_SCANCODE_ESCAPE:
                    visualizer_cleanup(&ctx->visualizer, EXIT_SUCCESS);
                    break;
                case SDL_SCANCODE_H:
                    ctx->current_state = STATE_HOME;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
}

void handle_home_input(VisualizerContext *ctx, SDL_Event *event) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.scancode)
        {
        case SDL_SCANCODE_1:
            ctx->current_state = STATE_ARRAY_VIEW;
            break;
        default:
            break;
        }
    }
}
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "render_helpers.h"

#define WINDOW_TITLE "01 Open Window"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

char* concat(const char *s1, const char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1); 
    strcpy(result, s1);
    strcat(result, s2);

    if (!result) {
    fprintf(stderr, "Failed to allocate memory for concatenated string\n");
    return NULL;
    }

    return result;
}

void draw_arrow (t_visualizer visualizer, int x1, int y1, int x2, int y2) {
    // line till next element
    SDL_RenderDrawLine(visualizer.renderer, x1, y1, x2, y2);

    // arrow head
    SDL_RenderDrawLine(visualizer.renderer, x2, y2 , x2 - 10, y2 - 10);
    SDL_RenderDrawLine(visualizer.renderer, x2, y2 , x2 - 10, y2 + 10);
}

SDL_Texture* render_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, SDL_Rect* rect_out) {
    int w, h;
    if (TTF_SizeUTF8(font, text, &w, &h) != 0) return NULL;   

    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) return NULL;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) return NULL;

    rect_out->w = w;
    rect_out->h = h;

    return texture;
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

SDL_Rect render_text_line(t_visualizer visualizer, int x, int y, TTF_Font* font, char* text, SDL_Color color) {
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
    
    SDL_Rect header_pos = render_text_line(ctx.visualizer, header_pos_x, 100, head_font, header_text, color_head);


    // TODO: Add loop through arr of strings, add them with spcaing of y * 2
    SDL_Rect body_pos = render_text_line(ctx.visualizer, header_pos.x, header_pos.y * 2, body_font, "> press 1 for Array Operations", color_body);
    render_text_line(ctx.visualizer, header_pos.x, header_pos.y + 150, body_font, "> press 2 for Stack Operations", color_body);
    render_text_line(ctx.visualizer, header_pos.x, header_pos.y + 200, body_font, "> press 3 for Queue Operations", color_body);
    render_text_line(ctx.visualizer, header_pos.x, header_pos.y + 250, body_font, "> press 4 for LinkedList Operations", color_body);
    SDL_RenderPresent(ctx.visualizer.renderer);
}
 
void draw_stack_screen(VisualizerContext ctx) {
    SDL_SetRenderDrawColor(ctx.visualizer.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(ctx.visualizer.renderer);

    for (int i = 0; i < ctx.stack->count; i++) {
        int height = 50;

        SDL_Rect rect;
        rect.x = SCREEN_WIDTH/2 - 100;
        rect.y = SCREEN_HEIGHT - ((i+1) * 75);
        rect.h = height;
        rect.w = 200;

        char *num_text = malloc(100);

        switch (ctx.stack->stack_elements[i].data_type) {
            case TYPE_INT:
                sprintf(num_text, "%d", *(int*)ctx.stack->stack_elements[i].data);
            break;
            case TYPE_FLOAT:
                sprintf(num_text, "%.2f", *(float*)ctx.stack->stack_elements[i].data);
            break;
            case TYPE_CHAR:
                sprintf(num_text, "%c", *(char*)ctx.stack->stack_elements[i].data);
            break;
            case TYPE_STRING:
                sprintf(num_text, "%s", (char *)ctx.stack->stack_elements[i].data);            
                break;
            default:
            break;
        }

        draw_value_rectangle(ctx.visualizer, rect, num_text);
        free(num_text);
    }

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

        char *num_text = malloc(12);
        sprintf(num_text, "%d", ctx.arr->data[i]);
        draw_value_rectangle(ctx.visualizer, rect, num_text);
        free(num_text);
    }
    
    SDL_RenderPresent(ctx.visualizer.renderer);
}

void draw_queue_screen(VisualizerContext ctx) { 
    SDL_SetRenderDrawColor(ctx.visualizer.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(ctx.visualizer.renderer);

    for (int i = 0; i < ctx.queue->count; i++) {
    
        SDL_Rect rect;
        rect.x = SCREEN_WIDTH - ((i+1) * 75);
        rect.y = SCREEN_HEIGHT/2 - 100;
        rect.h = 200;
        rect.w = 50;

        char *num_text = malloc(12);
        sprintf(num_text, "%d", ctx.queue->data[i]);
        draw_value_rectangle(ctx.visualizer, rect, num_text);
        free(num_text);
    }
    
    SDL_RenderPresent(ctx.visualizer.renderer);
}

void draw_ll_screen(VisualizerContext ctx) { 
    SDL_SetRenderDrawColor(ctx.visualizer.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(ctx.visualizer.renderer);

    t_node *current = malloc(sizeof(t_node));
    current = ctx.ll->head;
    int i = 0;
        while(current != NULL) {
            SDL_Rect rect;
            rect.x = (50) + i * 300;
            rect.y = SCREEN_HEIGHT/2 - 100;
            rect.h = 100;
            rect.w = 200;
            if(current->next != NULL) {
                draw_ll_element(ctx.visualizer, rect, current, false);
            } else {
                draw_ll_element(ctx.visualizer, rect, current, true);
            }
            i++;
            current = current->next;
        }
    SDL_RenderPresent(ctx.visualizer.renderer);

}

void draw_value_rectangle(t_visualizer visualizer, SDL_Rect rect, char* val) {
    TTF_Font *font = TTF_OpenFont("./fonts/8bitOperatorPlus8-Regular.ttf", 12);

    SDL_Color color = {255, 255, 255};

    SDL_Rect text_rect;
    SDL_Texture* val_texture = render_text(visualizer.renderer, font, val, color, &text_rect);
    if (!val_texture) {
        TTF_CloseFont(font);
        return;
    }  

    text_rect.x = rect.x + rect.w/2 - text_rect.w/2;
    text_rect.y = rect.y;

    SDL_SetRenderDrawColor(visualizer.renderer, 160, 32, 240, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(visualizer.renderer, &rect);
    SDL_RenderFillRect(visualizer.renderer, &text_rect);
    SDL_RenderCopy(visualizer.renderer, val_texture, NULL, &text_rect);
    SDL_DestroyTexture(val_texture);

    TTF_CloseFont(font);

}

void draw_ll_element(t_visualizer visualizer, SDL_Rect rect, t_node* val_node, bool isTail) {
    TTF_Font *font = TTF_OpenFont("./fonts/8bitOperatorPlus8-Regular.ttf", 12);
    if (!font) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        return;
    }   

    SDL_Color color = {255, 255, 255};

    char val_text[32];
    sprintf(val_text, "val: %d", val_node->val);

    SDL_Rect text_rect;
    SDL_Texture* val_texture = render_text(visualizer.renderer, font, val_text, color, &text_rect);
    if (!val_texture) {
        TTF_CloseFont(font);
        return;
    }  

    text_rect.x = rect.x + rect.w/2 - text_rect.w /2;
    text_rect.y = rect.y;

    SDL_SetRenderDrawColor(visualizer.renderer, 160, 32, 240, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(visualizer.renderer, &rect);
    SDL_RenderFillRect(visualizer.renderer, &text_rect);
    SDL_RenderCopy(visualizer.renderer, val_texture, NULL, &text_rect);
    SDL_DestroyTexture(val_texture);

    if (!isTail) {
        SDL_Rect next_rect;
        SDL_Texture* next_texture = render_text(visualizer.renderer, font, "next node:", color, &next_rect);
        if (next_texture) {
            next_rect.x = rect.x + rect.w / 2 - next_rect.w / 2;
            next_rect.y = text_rect.y + 70;
            SDL_RenderFillRect(visualizer.renderer, &next_rect);
            SDL_RenderCopy(visualizer.renderer, next_texture, NULL, &next_rect);
            SDL_DestroyTexture(next_texture);

            draw_arrow(visualizer,
                rect.x + rect.w, next_rect.y + next_rect.h / 2,
                rect.x + rect.w + 100, next_rect.y + next_rect.h / 2);
        }
    }

    TTF_CloseFont(font);
}


// MARK: REFACTOR THIS TO SINGLE FUNC
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
            stack_push_multiple_types(ctx->stack);
            break;
        case SDL_SCANCODE_D: 
            stack_pop(ctx->stack);
            break;
        default:
            break;
        }
    }
}

void handle_ll_input(VisualizerContext *ctx, SDL_Event *event) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.scancode)
        {
        case SDL_SCANCODE_A:
            linked_list_add_to_tail(ctx->ll);
            break;
        case SDL_SCANCODE_D: 
            linked_list_pop(ctx->ll);
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
            queue_push(ctx->queue);
            break;
        case SDL_SCANCODE_D: 
            queue_pop(ctx->queue);
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
        case SDL_SCANCODE_2:
            ctx->current_state = STATE_STACK_VIEW;
            break;
        case SDL_SCANCODE_3:
            ctx->current_state = STATE_QUEUE_VIEW;
            break;
        case SDL_SCANCODE_4:
            ctx->current_state = STATE_LL_VIEW;
            break;
        default:
            break;
        }
    }
}


#ifndef RENDER_HELPERS_H
#define RENDER_HELPERS_H
#include "../src/array.h"


typedef struct Visualizer {
    SDL_Window *window;
    SDL_Renderer *renderer;
} t_visualizer;


typedef enum {
    STATE_HOME,
    STATE_ARRAY_VIEW,
} VisualizerState;

typedef struct {
    VisualizerState current_state;
    dns_arr_t *arr;
    t_visualizer visualizer;
} VisualizerContext;

void visualizer_cleanup(t_visualizer * visualizer, int exit_status);
bool sdl_initialize(t_visualizer *visualzier);
void draw_array_screen(VisualizerContext ctx) ;
void draw_value_rectangle(t_visualizer Visualizer, SDL_Rect rect, int number);
void draw_homescreen(VisualizerContext ctx);
void handle_array_input(VisualizerContext *ctx, SDL_Event *event);
void handle_global_input(VisualizerContext *ctx, SDL_Event *event);
void handle_home_input(VisualizerContext *ctx, SDL_Event *event);
#endif
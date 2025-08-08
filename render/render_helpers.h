#ifndef RENDER_HELPERS_H
#define RENDER_HELPERS_H
#include "../src/array.h"
#include "../src/queue.h"
#include "../src/stack.h"
#include "../src/linked_list.h"
#include "../src/sorting_algorithms.h"


typedef struct Visualizer {
    SDL_Window *window;
    SDL_Renderer *renderer;
} t_visualizer;


typedef enum {
    STATE_HOME,
    STATE_ARRAY_VIEW,
    STATE_STACK_VIEW,
    STATE_QUEUE_VIEW,
    STATE_LL_VIEW,
} VisualizerState;

typedef struct {
    VisualizerState current_state;
    dns_arr_t *arr;
    dns_stack_t *stack;
    dns_int_queue_t *queue;
    t_linked_list *ll;
    t_visualizer visualizer;
} VisualizerContext;

void visualizer_cleanup(t_visualizer * visualizer, int exit_status);
bool sdl_initialize(t_visualizer *visualzier);
void draw_array_screen(VisualizerContext ctx);
void draw_stack_screen(VisualizerContext ctx);
void draw_queue_screen(VisualizerContext ctx);
void draw_ll_screen(VisualizerContext ctx);
void draw_ll_element(t_visualizer visualizer, SDL_Rect rect, t_node* val_node, bool isTail);
void draw_value_rectangle(t_visualizer visualizer, SDL_Rect rect, char* val);
void draw_homescreen(VisualizerContext ctx);
void handle_array_input(VisualizerContext *ctx, SDL_Event *event);
void handle_ll_input(VisualizerContext *ctx, SDL_Event *event);
void handle_global_input(VisualizerContext *ctx, SDL_Event *event);
void handle_home_input(VisualizerContext *ctx, SDL_Event *event);
void handle_stack_input(VisualizerContext *ctx, SDL_Event *event);
void handle_queue_input(VisualizerContext *ctx, SDL_Event *event);

#endif
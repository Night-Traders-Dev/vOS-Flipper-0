#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <furi.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <gui/modules/submenu.h>
#include <gui/modules/widget.h>
#include <gui/modules/text_input.h>

// Enums for scenes
typedef enum {
    BasicScenesMainMenuScene,
    BasicScenesGreetingScene,
    BasicScenesNewInputScene,
    BasicScenesNewMessageScene,
    BasicScenesSceneCount,
} BasicScenesScene;

// Enums for views
typedef enum {
    BasicScenesSubmenuView,
    BasicScenesWidgetView,
    BasicScenesTextInputView,
} BasicScenesView;

// Enums for menu items
typedef enum {
    BasicScenesMainMenuSceneGreeting,
    BasicScenesMainMenuSceneNew,
    BasicScenesMainMenuSceneNotif, // Added this
} BasicScenesMainMenuSceneIndex;

// Enums for events
typedef enum {
    BasicScenesMainMenuSceneGreetingEvent,
    BasicScenesMainMenuSceneNewEvent,
} BasicScenesMainMenuEvent;

// Struct for the app
typedef struct App {
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;
    Submenu* submenu;
    Widget* widget;
    TextInput* text_input;
    char* user_name;
    uint8_t user_name_size;
} App;

// Function prototypes
void basic_scenes_menu_callback(void* context, uint32_t index);
void basic_scenes_main_menu_scene_on_enter(void* context);
bool basic_scenes_main_menu_scene_on_event(void* context, SceneManagerEvent event);
void basic_scenes_main_menu_scene_on_exit(void* context);

void basic_scenes_greeting_scene_on_enter(void* context);
bool basic_scenes_greeting_scene_on_event(void* context, SceneManagerEvent event);
void basic_scenes_greeting_scene_on_exit(void* context);

void basic_scenes_new_input_scene_on_enter(void* context);
bool basic_scenes_new_input_scene_on_event(void* context, SceneManagerEvent event);
void basic_scenes_new_input_scene_on_exit(void* context);

void basic_scenes_new_message_scene_on_enter(void* context);
bool basic_scenes_new_message_scene_on_event(void* context, SceneManagerEvent event);
void basic_scenes_new_message_scene_on_exit(void* context);

void basic_scenes_text_input_callback(void* context); // Added this

bool basic_scene_custom_callback(void* context, uint32_t custom_event);
bool basic_scene_back_event_callback(void* context);

App* app_alloc();
void app_free(App* app);

#endif // SCENE_MANAGER_H

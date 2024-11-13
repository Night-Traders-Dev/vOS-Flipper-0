#include "scene_man.h"
#include "../notif_man/notif_man.h" // Include the header for notif_man

bool basic_scene_custom_callback(void* context, uint32_t custom_event) {
    furi_assert(context);
    App* app = context;
    return scene_manager_handle_custom_event(app->scene_manager, custom_event);
}

bool basic_scene_back_event_callback(void* context) {
    furi_assert(context);
    App* app = context;
    return scene_manager_handle_back_event(app->scene_manager);
}

// Menu callback for handling submenu selections
void basic_scenes_menu_callback(void* context, uint32_t index) {
    App* app = context;
    switch(index) {
        case BasicScenesMainMenuSceneGreeting:
            scene_manager_handle_custom_event(app->scene_manager, BasicScenesMainMenuSceneGreetingEvent);
            break;
        case BasicScenesMainMenuSceneNew:
            scene_manager_handle_custom_event(app->scene_manager, BasicScenesMainMenuSceneNewEvent);
            break;
        case BasicScenesMainMenuSceneNotif: // New case for NotifMan
            main_fap(NULL); // Call the notif_man functionality
            break;
    }
}

// Main menu scene handlers
void basic_scenes_main_menu_scene_on_enter(void* context) {
    App* app = context;
    submenu_reset(app->submenu);
    submenu_set_header(app->submenu, "vOS on Flipper Zero");
    submenu_add_item(app->submenu, "Greeting", BasicScenesMainMenuSceneGreeting, basic_scenes_menu_callback, app);
    submenu_add_item(app->submenu, "New", BasicScenesMainMenuSceneNew, basic_scenes_menu_callback, app);
    submenu_add_item(app->submenu, "NotifMan", BasicScenesMainMenuSceneNotif, basic_scenes_menu_callback, app); // New item
    view_dispatcher_switch_to_view(app->view_dispatcher, BasicScenesSubmenuView);
}

bool basic_scenes_main_menu_scene_on_event(void* context, SceneManagerEvent event) {
    App* app = context;
    bool consumed = false;
    switch(event.type) {
        case SceneManagerEventTypeCustom:
            switch(event.event) {
                case BasicScenesMainMenuSceneGreetingEvent:
                    scene_manager_next_scene(app->scene_manager, BasicScenesGreetingScene);
                    consumed = true;
                    break;
                case BasicScenesMainMenuSceneNewEvent:
                    scene_manager_next_scene(app->scene_manager, BasicScenesNewInputScene);
                    consumed = true;
                    break;
            }
            break;
        default:
            break;
    }
    return consumed;
}

void basic_scenes_main_menu_scene_on_exit(void* context) {
    App* app = context;
    submenu_reset(app->submenu);
}

// Greeting scene handlers
void basic_scenes_greeting_scene_on_enter(void* context) {
    App* app = context;
    widget_reset(app->widget);
    widget_add_string_element(app->widget, 0, 15, AlignLeft, AlignCenter, FontPrimary, "Welcome to vOS for Flipper Zero:");
    widget_add_string_element(app->widget, 0, 30, AlignLeft, AlignCenter, FontBigNumbers, "Test Version");
    view_dispatcher_switch_to_view(app->view_dispatcher, BasicScenesWidgetView);
}

bool basic_scenes_greeting_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false; // Event not handled
}

void basic_scenes_greeting_scene_on_exit(void* context) {
    UNUSED(context);
}

// New input scene handlers
void basic_scenes_new_input_scene_on_enter(void* context) {
    App* app = context;
    text_input_reset(app->text_input);
    text_input_set_header_text(app->text_input, "Enter your name:");
    text_input_set_result_callback(app->text_input, basic_scenes_text_input_callback, app, app->user_name, app->user_name_size, true);
    view_dispatcher_switch_to_view(app->view_dispatcher, BasicScenesTextInputView);
}

void basic_scenes_text_input_callback(void* context) {
    App* app = context;
    // Transition to the new message scene
    scene_manager_next_scene(app->scene_manager, BasicScenesNewMessageScene);
}

bool basic_scenes_new_input_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false; // Event not handled
}

void basic_scenes_new_input_scene_on_exit(void* context) {
    UNUSED(context);
}

// New message scene handlers
void basic_scenes_new_message_scene_on_enter(void* context) {
    App* app = context;
    widget_reset(app->widget);
    FuriString* message = furi_string_alloc();
    furi_string_printf(message, "Hello, %s!", app->user_name);
    widget_add_string_element(app->widget, 0, 0, AlignLeft, AlignCenter, FontPrimary, furi_string_get_cstr(message));
    furi_string_free(message);
    view_dispatcher_switch_to_view(app->view_dispatcher, BasicScenesWidgetView);
}

bool basic_scenes_new_message_scene_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false; // Event not handled
}

void basic_scenes_new_message_scene_on_exit(void* context) {
    UNUSED(context);
}

// Scene manager handlers
void (*const basic_scenes_scene_on_enter_handlers[])(void*) = {
    basic_scenes_main_menu_scene_on_enter,
    basic_scenes_greeting_scene_on_enter,
    basic_scenes_new_input_scene_on_enter,
    basic_scenes_new_message_scene_on_enter,
};

bool (*const basic_scenes_scene_on_event_handlers[])(void*, SceneManagerEvent) = {
    basic_scenes_main_menu_scene_on_event,
    basic_scenes_greeting_scene_on_event,
    basic_scenes_new_input_scene_on_event,
    basic_scenes_new_message_scene_on_event,
};

void (*const basic_scenes_scene_on_exit_handlers[])(void*) = {
    basic_scenes_main_menu_scene_on_exit,
    basic_scenes_greeting_scene_on_exit,
    basic_scenes_new_input_scene_on_exit,
    basic_scenes_new_message_scene_on_exit,
};

static const SceneManagerHandlers basic_scenes_scene_manager_handlers = {
    .on_enter_handlers = basic_scenes_scene_on_enter_handlers,
    .on_event_handlers = basic_scenes_scene_on_event_handlers,
    .on_exit_handlers = basic_scenes_scene_on_exit_handlers,
    .scene_num = BasicScenesSceneCount,
};

// App allocation and freeing functions
App* app_alloc() {
    App* app = malloc(sizeof(App));
    app->user_name_size = 16;
    app->user_name = malloc(app->user_name_size);
    app->scene_manager = scene_manager_alloc(&basic_scenes_scene_manager_handlers, app);
    app->view_dispatcher = view_dispatcher_alloc();
    view_dispatcher_set_event_callback_context(app->view_dispatcher, app);
    view_dispatcher_set_custom_event_callback(app->view_dispatcher, basic_scene_custom_callback);
    view_dispatcher_set_navigation_event_callback(app->view_dispatcher, basic_scene_back_event_callback);

    app->submenu = submenu_alloc();
    view_dispatcher_add_view(app->view_dispatcher, BasicScenesSubmenuView, submenu_get_view(app->submenu));

    app->widget = widget_alloc();
    view_dispatcher_add_view(app->view_dispatcher, BasicScenesWidgetView, widget_get_view(app->widget));

    app->text_input = text_input_alloc();
    view_dispatcher_add_view(app->view_dispatcher, BasicScenesTextInputView, text_input_get_view(app->text_input));

    return app;
}

void app_free(App* app) {
    furi_assert(app);

    view_dispatcher_remove_view(app->view_dispatcher, BasicScenesSubmenuView);
    view_dispatcher_remove_view(app->view_dispatcher, BasicScenesWidgetView);
    view_dispatcher_remove_view(app->view_dispatcher, BasicScenesTextInputView);

    scene_manager_free(app->scene_manager);
    view_dispatcher_free(app->view_dispatcher);
    submenu_free(app->submenu);
    widget_free(app->widget);
    text_input_free(app->text_input);
    
    free(app->user_name);
    free(app);
}

#include <furi.h>
#include <gui/gui.h>
#include "scene_man/scene_man.h"

int32_t main_entry(void* p) {
    UNUSED(p);
    App* app = app_alloc();
    Gui* gui = furi_record_open(RECORD_GUI);
    view_dispatcher_attach_to_gui(app->view_dispatcher, gui, ViewDispatcherTypeFullscreen);
    scene_manager_next_scene(app->scene_manager, BasicScenesMainMenuScene);
    view_dispatcher_run(app->view_dispatcher);
    app_free(app);
    return 0;
}

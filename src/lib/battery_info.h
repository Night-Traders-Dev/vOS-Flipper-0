#pragma once

#include <furi.h>
#include <power/power_service/power.h>
#include <gui/gui.h>
#include <gui/view.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <gui/modules/submenu.h>
#include <gui/modules/dialog_ex.h>

#include "../assets/assets_icons.h"


typedef struct BatteryInfo BatteryInfo;

typedef struct {
    float vbus_voltage;
    float gauge_voltage;
    float gauge_current;
    float gauge_temperature;
    float charging_voltage;
    uint8_t charge;
    uint8_t health;
} BatteryInfoModel;

BatteryInfo* battery_info_alloc(void);

void battery_info_free(BatteryInfo* battery_info);

View* battery_info_get_view(BatteryInfo* battery_info);

void battery_info_set_data(BatteryInfo* battery_info, BatteryInfoModel* data);

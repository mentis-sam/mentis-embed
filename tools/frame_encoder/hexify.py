import binascii

from dataclasses import dataclass

def convert_file(filename):
    with open(filename, 'rb') as f:
        content = f.read()

    data = binascii.hexlify(content, ",", 1).decode("utf-8")

    data = data.replace(",", ", 0x")
    data = "0x" + data

    return data, data.count(",")+1


def create_header(name, filenames):

    data = []
    data_l = []

    for filename in filenames:
        temp_data, temp_data_l = convert_file(filename)

        data.append(temp_data)
        data_l.append(temp_data_l)

    sdata = ','.join(map(str, data)) 
    sdata_l = ','.join(map(str, data_l)) 

    header_template = \
"""#ifndef %NAME_C%_H
#define %NAME_C%_H

#include <pgmspace.h>
#include <stdint.h>

const uint8_t %NAME%[] PROGMEM = 
{%DATA%}; 
    
const uint32_t %NAME%l[%RAMES%] PROGMEM = {%DATA_L%}; 

#endif
"""
    header_template = header_template.replace("%NAME_C%", name.upper())
    header_template = header_template.replace("%NAME%", name)
    header_template = header_template.replace("%RAMES%", str(len(filenames)))
    header_template = header_template.replace("%DATA_L%", sdata_l)
    header_template = header_template.replace("%DATA%", sdata)

    with open(f"tools/frame_encoder/output/{name[:-2]}.h", "w") as text_file:
        text_file.write(header_template)
    
# This is fucking terrible
def complete_folder(name, folder, sub_folders, sub_file_num):
    for index, sub_fo in enumerate(sub_folders):
            filenames = [f'img/{folder}/{sub_fo}/{sub_fo} {n}.png' for n in range(1,sub_file_num[index]+1)]
            create_header(f"{name.lower()}_{sub_fo.lower()}_i", filenames)

def complete_simple_folder(name, folder, filename, sub_file_num):
    filenames = [f'img/{folder}/{filename} {n}.png' for n in range(1,sub_file_num+1)]
    create_header(f"{name}_i", filenames)

def complete_single(name, folder, filename):
    filenames = [f'img/{folder}/{filename}.png']
    create_header(f"{name}_i", filenames)

#complete_folder("colonise", "From scratch", ["Close", "Colonising", "Inject", "Insert", "Wipe"], [12] * 5)

#complete_simple_folder("fruiting", "Fruiting", "Fruiting", 5)

#complete_simple_folder("grow_ready", "Grow/Ready", "Ready", 12)

#complete_single("help_lid", "Help", "Close lid")
#complete_single("help_inject", "Help", "Inject spores")
#complete_single("help_insert", "Help", "Insert bag into device")
#complete_single("help_wipe", "Help", "Wipe injection port")

#complete_folder("menu", "Menu", ["Dehydrate", "From Scratch", "Mycelium", "Settings"], [12] * 4)

#complete_folder("mycelium", "Mycelium", ["Close", "Fruiting", "Insert"], [12] * 3)

#complete_folder("settings", "Settings", ["Airflow", "Temperature", "Time Period", "Light"], [10, 11, 49, 10])

#This is marginally better to read
f = []
f.extend([f'img/Settings/Menu/Settings {n}.png' for n in range(1,7)])
f.extend([f'img/Settings/Menu/Colonisation {n}.png' for n in range(1,5)])
f.extend([f'img/Settings/Menu/Fruiting {n}.png' for n in range(1,6)])
f.extend([f'img/Settings/Menu/Dehydration {n}.png' for n in range(1,4)])
f.extend([f'img/Settings/Menu/Beep {n}.png' for n in range(1,6)])
f.extend([f'img/Settings/Menu/Reset {n}.png' for n in range(1,3)])

create_header("settings_menu_i", f)

#f = []
#f.extend([f'img/Settings/Temperature/Temperature {n}.png' for n in range(1,12)])

#create_header("settings_temperature_i", f)



f = []
f.extend([f'img/Dehydration/Cancel/Dehydrating cancel {n}.png' for n in range(1,3)])

create_header("dehydrate_cancel_i", f)

f = []
f.extend([f'img/Dehydration/Dehydrating/Dehydrating {n}.png' for n in range(1,13)])

create_header("dehydrate_dehydrating_i", f)

f = []
f.extend([f'img/Dehydration/Complete/Dehydration complete {n}.png' for n in range(1,13)])

create_header("dehydrate_complete_i", f)

f = []
f.extend([f'img/From scratch/Cancel/Colonising cancel {n}.png' for n in range(1,3)])

create_header("colonise_cancel_i", f)

f = []
f.extend([f'img/From scratch/Close/Close {n}.png' for n in range(1,13)])

create_header("colonise_close_i", f)

f = []
f.extend([f'img/From scratch/Colonising/Colonising {n}.png' for n in range(1,13)])

create_header("colonise_colonising_i", f)

f = []
f.extend([f'img/From scratch/Inject/Inject {n}.png' for n in range(1,13)])

create_header("colonise_inject_i", f)

f = []
f.extend([f'img/From scratch/Insert/Insert {n}.png' for n in range(1,13)])

create_header("colonise_insert_i", f)

f = []
f.extend([f'img/From scratch/Wipe/Wipe {n}.png' for n in range(1,13)])

create_header("colonise_wipe_i", f)

f = []
f.extend([f'img/Grow/Ready/Ready {n}.png' for n in range(1,13)])

create_header("ready_i", f)

complete_single("help_lid", "Help", "Close lid")
complete_single("help_inject", "Help", "Inject spores")
complete_single("help_insert", "Help", "Insert bag into device")
complete_single("help_wipe", "Help", "Wipe injection port")

f = []
f.extend([f'img/Menu/Dehydrate/Dehydrate {n}.png' for n in range(1,13)])

create_header("menu_dehydrate_i", f)

f = []
f.extend([f'img/Menu/From scratch/From scratch {n}.png' for n in range(1,13)])

create_header("menu_colonise_i", f)

f = []
f.extend([f'img/Menu/Mycelium/Mycelium {n}.png' for n in range(1,13)])

create_header("menu_mycelium_i", f)

f = []
f.extend([f'img/Menu/Settings/Settings {n}.png' for n in range(1,13)])

create_header("menu_settings_i", f)

f = []
f.extend([f'img/Mycelium/Cancel/Fruiting cancel {n}.png' for n in range(1,3)])

create_header("mycelium_cancel_i", f)

f = []
f.extend([f'img/Mycelium/Close/Close {n}.png' for n in range(1,13)])

create_header("mycelium_close_i", f)

f = []
f.extend([f'img/Mycelium/Fruiting/Fruiting {n}.png' for n in range(1,13)])

create_header("mycelium_fruiting_i", f)

f = []
f.extend([f'img/Mycelium/Harvest/Harvest {n}.png' for n in range(1,13)])

create_header("mycelium_harvest_i", f)

f = []
f.extend([f'img/Mycelium/Insert/Insert {n}.png' for n in range(1,13)])

create_header("mycelium_insert_i", f)

f = []
f.extend([f'img/Settings/Temperature/CF/Temperature {n}.png' for n in range(1,12)])

create_header("settings_temperature_cf_i", f)

f = []
f.extend([f'img/Settings/Temperature/Dehydration/Temperature {n}.png' for n in range(1,12)])

create_header("settings_temperature_d_i", f)

f = []
f.extend([f'img/Settings/Airflow/Airflow {n}.png' for n in range(1,11)])

create_header("settings_airflow_i", f)

f = []
f.extend([f'img/Settings/Light/Light {n}.png' for n in range(1,11)])

create_header("settings_light_i", f)

f = []
f.extend([f'img/Settings/Time Period/Dehydration/Time Period {n}.png' for n in range(1,6)])

create_header("settings_timeperiod_d_i", f)

f = []
f.extend([f'img/Settings/Time Period/Colonisation/Time Period {n}.png' for n in range(1,9)])

create_header("settings_timeperiod_c_i", f)

f = []
f.extend([f'img/Settings/Time Period/Fruiting/Time Period {n}.png' for n in range(1,15)])

create_header("settings_timeperiod_f_i", f)

f = []
f.extend([f'img/Settings/Factory Reset/Factory Reset {n}.png' for n in range(1,3)])

create_header("settings_factory_rs_i", f)
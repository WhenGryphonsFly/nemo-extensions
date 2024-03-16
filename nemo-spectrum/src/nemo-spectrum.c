/*
 *  Nemo Spectrum
 *
 *  Copyright (C) 2024 WhenGryphonsFly
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  Author: WhenGryphonsFly <84215159+WhenGryphonsFly@users.noreply.github.com>
 *
 */

//====================================================================================================================//
// Preprocessor directives //=========================================================================================//
//====================================================================================================================//
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "nemo-spectrum.h"
#include <gtk/gtk.h>
#include <libnemo-extension/nemo-file-info.h>

//====================================================================================================================//
// Global and static variables //=====================================================================================//
//====================================================================================================================//

typedef struct {
    GtkBuilder *xml;
    GtkWidget *root;

    GtkWidget *entry_sort_order;
    GtkWidget *button_cancel;
    GtkWidget *button_apply;
    GtkWidget *button_information;
} SpectrumWindow;

//====================================================================================================================//
// Static functions //================================================================================================//
//====================================================================================================================//

#define NEMO_METADATA_NEMO_SORT_ORDER "nemo-sort-order"

static SpectrumWindow *
create_window (NemoFileInfo *info)
{
    SpectrumWindow *window;
    char *sort_order_string;
    GError *error;

    window = g_new0 (SpectrumWindow, 1);
    window->xml = gtk_builder_new ();
    gtk_builder_set_translation_domain (window->xml, "nemo-extensions");

    error = NULL;
    gtk_builder_add_from_file (window->xml, INTERFACES_DIR"/spectrum.glade", &error)
    if (error != NULL)
    {
    	fprintf (stderr, "Error: %s", error->message);
    	g_assert (false);
    }
    window->root = GTK_WIDGET (gtk_builder_get_object (window->xml, "root"));

    sort_order_string = nemo_file_info_get_string_attribute (info, NEMO_METADATA_NEMO_SORT_ORDER);
    window->entry_sort_order = GTK_WIDGET (gtk_builder_get_object (window->xml, "entry_sort_order"));
    gtk_entry_set_text (GTK_ENTRY (window->entry_sort_order), sort_order_string);

    window->button_cancel = GTK_WIDGET (gtk_builder_get_object (window->xml, "button_cancel"));
    window->button_apply = GTK_WIDGET (gtk_builder_get_object (window->xml, "button_apply"));
    window->button_information = GTK_WIDGET (gtk_builder_get_object (window->xml, "button_information"));

    return window;
}

//====================================================================================================================//
// nemo-info-provider.h //============================================================================================//
//====================================================================================================================//
#include <libnemo-extension/nemo-info-provider.h>

static NemoOperationResult
nemo_spectrum_info_update_file_info(NemoInfoProvider     *provider, 
                                    NemoFileInfo         *file,
                                    GClosure             *update_complete,
                                    NemoOperationHandle **handle)
{
    // TODO
    return NEMO_OPERATION_COMPLETE;
}

static void
nemo_spectrum_info_cancel_update(NemoInfoProvider    *provider,
                                 NemoOperationHandle *handle)
{
    // TODO
    //handle->cancelled = TRUE;
}

static void nemo_spectrum_info_provider_iface_init(NemoInfoProviderIface *iface) {
    iface->update_file_info = nemo_spectrum_info_update_file_info;
    iface->cancel_update = nemo_spectrum_info_cancel_update;
}

static void nemo_spectrum_info_init_hook(GTypeModule* module, GType spectrum_type) {
    static const GInterfaceInfo info_provider_iface_info = {
        (GInterfaceInitFunc) nemo_spectrum_info_provider_iface_init,
        NULL,
        NULL
    };
    g_type_module_add_interface(
        module,
        spectrum_type,
        NEMO_TYPE_INFO_PROVIDER,
        &info_provider_iface_info
    );
}

//====================================================================================================================//
// nemo-property-page-provider.h //===================================================================================//
//====================================================================================================================//
#include <libnemo-extension/nemo-property-page-provider.h>

static GList* nemo_spectrum_property_page_get_pages(NemoPropertyPageProvider* provider, GList* files) {
    NemoFileInfo *fileinfo;
    SpectrumWindow *window;
    GList *pages;
    NemoPropertyPage *page;

    // Only show the page if 1 file is selected
    if (!files || files->next != NULL) {
        return NULL;
    }

    fileinfo = NEMO_FILE_INFO (files->data);
    window = create_window (fileinfo);
    gtk_widget_hide (window->button_cancel);

    pages = NULL;
    page = nemo_property_page_new(
        "NemoSpectrum::property_page",
        gtk_label_new("Sort Order"), // TODO _()
        window->root
    );
    pages = g_list_append(pages, page);

    return pages;
}

static void nemo_spectrum_property_page_provider_iface_init(NemoPropertyPageProviderIface *iface) {
    iface->get_pages = nemo_spectrum_property_page_get_pages;
}

static void nemo_spectrum_property_page_init_hook(GTypeModule* module, GType spectrum_type) {
    static const GInterfaceInfo property_page_provider_iface_info = {
        (GInterfaceInitFunc) nemo_spectrum_property_page_provider_iface_init,
        NULL,
        NULL
    };
    g_type_module_add_interface(
        module,
        spectrum_type,
        NEMO_TYPE_PROPERTY_PAGE_PROVIDER,
        &property_page_provider_iface_info
    );
}

//====================================================================================================================//
// nemo-name-and-desc-provider.h //===================================================================================//
//====================================================================================================================//
#include <libnemo-extension/nemo-name-and-desc-provider.h>

static GList* nemo_spectrum_name_and_desc_get_name_and_desc(NemoNameAndDescProvider* provider) {
    GList* ret = NULL;
    gchar* string = g_strdup_printf (
        "nemo-spectrum:::%s",
        "TODO_DESCRIPTION"); // TODO _()

    ret = g_list_append(ret, string);
    return ret;
}

static void nemo_spectrum_name_and_desc_provider_iface_init(NemoNameAndDescProviderIface *iface) {
    iface->get_name_and_desc = nemo_spectrum_name_and_desc_get_name_and_desc;
}

static void nemo_spectrum_name_and_desc_init_hook(GTypeModule* module, GType spectrum_type) {
    static const GInterfaceInfo name_and_desc_provider_iface_info = {
        (GInterfaceInitFunc) nemo_spectrum_name_and_desc_provider_iface_init,
        NULL,
        NULL
    };
    g_type_module_add_interface(
        module,
        spectrum_type,
        NEMO_TYPE_NAME_AND_DESC_PROVIDER,
        &name_and_desc_provider_iface_info
    );
}

//====================================================================================================================//
// nemo-extension-types.h //==========================================================================================//
//====================================================================================================================//
#include <libnemo-extension/nemo-extension-types.h>

static GType spectrum_type = 0;
static GType nemo_spectrum_get_type(void) {
    return spectrum_type;
}

static void nemo_spectrum_class_init(NemoSpectrumClass* class) {
    //parent_class = g_type_class_peek_parent(class);
}

static void nemo_spectrum_instance_init(NemoSpectrum* instance) {
}

static void nemo_spectrum_register_type(GTypeModule* module) {
    static const GTypeInfo info = {
        sizeof(NemoSpectrumClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) nemo_spectrum_class_init, // TODO
        (GClassFinalizeFunc) NULL,
        NULL,
        sizeof(NemoSpectrum),
        0,
        (GInstanceInitFunc) nemo_spectrum_instance_init, // TODO
        // Empty valueTable
    };
    spectrum_type = g_type_module_register_type(
        module,
        G_TYPE_OBJECT,
        "NemoSpectrum",
        &info,
        0
    );

    // Add init hooks here

    nemo_spectrum_info_init_hook(module, spectrum_type);
    nemo_spectrum_property_page_init_hook(module, spectrum_type);
    nemo_spectrum_name_and_desc_init_hook(module, spectrum_type);
}

void nemo_module_initialize(GTypeModule* module) {
    // TODO

    nemo_spectrum_register_type(module);
}

void nemo_module_shutdown(void) {
    // TODO
}

void nemo_module_list_types(const GType** types, int* num_types) {
    static GType type_list[1];
    type_list[0] = NEMO_TYPE_SPECTRUM;
    *types = type_list;
    *num_types = 1;
}

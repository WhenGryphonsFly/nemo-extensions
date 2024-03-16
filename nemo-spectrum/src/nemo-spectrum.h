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

#ifndef NEMO_SPECTRUM_H
#define NEMO_SPECTRUM_H
#include <glib-object.h>
G_BEGIN_DECLS



#define NEMO_TYPE_SPECTRUM (nemo_spectrum_get_type())

typedef struct _NemoSpectrum      NemoSpectrum;
typedef struct _NemoSpectrumClass NemoSpectrumClass;

struct _NemoSpectrum {
    GObject parent;
};

struct _NemoSpectrumClass {
	GObjectClass parent;
};



G_END_DECLS
#endif//NEMO_SPECTRUM_H

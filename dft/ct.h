/*
 * Copyright (c) 2003 Matteo Frigo
 * Copyright (c) 2003 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "dft.h"

typedef void (*dftwapply) (const plan *ego, R *rio, R *iio);
typedef struct ct_solver_s ct_solver;
typedef plan *(*mkinferior)(const ct_solver *ego,
			    int dec, int r, int m, int s, int vl, int vs, 
			    R *rio, R *iio,
			    planner *plnr);

typedef struct {
     plan super;
     dftwapply apply;
} plan_dftw;

extern plan *X(mkplan_dftw)(size_t size, const plan_adt *adt, dftwapply apply);

#define MKPLAN_DFTW(type, adt, apply) \
  (type *)X(mkplan_dftw)(sizeof(type), adt, apply)

struct ct_solver_s {
     solver super;
     int r;
     int dec;
#    define DECDIF 0
#    define DECDIT 1

     mkinferior mkcldw;
};

ct_solver *X(mksolver_dft_ct)(size_t size, int r, int dec, mkinferior mkdlcw);

solver *X(mksolver_dft_ct_directw)(kdftw codelet, const ct_desc *desc, 
				   int dec);
solver *X(mksolver_dft_ct_directwbuf)(kdftw codelet, 
				      const ct_desc *desc, int dec);
solver *X(mksolver_dft_ctsq)(kdftwsq codelet, const ct_desc *desc, int dec);

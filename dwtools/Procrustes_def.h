/* Procrustes_def.h
 *
 * Copyright (C) 1993-2005 David Weenink
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#define ooSTRUCT Procrustes
oo_DEFINE_CLASS (Procrustes, AffineTransform)

	oo_DOUBLE (s)

	#if oo_DECLARING
		void v_transform (double **in, long nrows, double **out)
			override;
		autoAffineTransform v_invert ()
			override;
	#endif
			
oo_END_CLASS (Procrustes)	
#undef ooSTRUCT


/* End of file Procrustes_def.h */	

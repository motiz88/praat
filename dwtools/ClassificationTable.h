#ifndef _ClassificationTable_h_
#define _ClassificationTable_h_
/* ClassificationTable.h
 *
 * Copyright (C) 1993-2012, 2015 David Weenink
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

#include "TableOfReal.h"
#include "SSCP.h"
#include "Confusion.h"

#include "Strings_.h"


Thing_define (ClassificationTable, TableOfReal) {
};

autoClassificationTable ClassificationTable_create (long numberOfRows, long numberOfColumns);

autoCategories ClassificationTable_to_Categories_maximumProbability (ClassificationTable me);

autoStrings ClassificationTable_to_Strings_maximumProbability (ClassificationTable me);

autoConfusion ClassificationTable_to_Confusion (ClassificationTable me, bool onlyClassLabels);

/* Correlations between the classes (columns) */
autoCorrelation ClassificationTable_to_Correlation_columns (ClassificationTable me);

void Confusion_and_ClassificationTable_increase (Confusion me, ClassificationTable thee);

#endif /* _ClassificationTable_h_ */


#ifndef COS_GEN_ALGORITHM_H
#define COS_GEN_ALGORITHM_H

/*
 o---------------------------------------------------------------------o
 |
 | COS generics for algorithms
 |
 o---------------------------------------------------------------------o
 |
 | C Object System
 |
 | Copyright (c) 2006+ Laurent Deniau, laurent.deniau@cern.ch
 |
 | For more information, see:
 | http://cern.ch/laurent.deniau/cos.html
 |
 o---------------------------------------------------------------------o
 |
 | This file is part of the C Object System framework.
 |
 | The C Object System is free software; you can redistribute it and/or
 | modify it under the terms of the GNU Lesser General Public License
 | as published by the Free Software Foundation; either version 3 of
 | the License, or (at your option) any later version.
 |
 | The C Object System is distributed in the hope that it will be
 | useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: algorithm.h,v 1.1 2008/10/24 16:11:00 ldeniau Exp $
 |
*/

#ifndef COS_OBJECT_H
#error "COS: missing #include <cos/Object.h>"
#endif 

// in place (value returned is discarded)
defgeneric(void, gapply, fun, _1);

// map-reduce discarding Nil result
defgeneric(OBJ, gmap   , fun, _1);
defgeneric(OBJ, gmap2  , fun, _1, _2);
defgeneric(OBJ, gmap3  , fun, _1, _2, _3);
defgeneric(OBJ, gmap4  , fun, _1, _2, _3, _4);
defgeneric(OBJ, gscan  , fun, acc, _1);

// map-reduce stopping on Nil result
defgeneric(OBJ, gfilter, fun, _1);
defgeneric(OBJ, gfold  , fun, acc, _1);

// generator stopping on Nil result
defgeneric(OBJ, gunfold, fun, seed);

// sorting (fun must return Ordered)
defgeneric(OBJ, gsort  , fun, _1);

// linear      find if fun returns TrueFalse
// logarithmic find if fun returns Ordered
defgeneric(OBJ, gfind  , fun, obj, _1);

// seq-like algorithms
defgeneric(OBJ, greverse, _1);

// bag-like algorithms
defgeneric(OBJ, gunique, _1);
defgeneric(OBJ, group  , _1);
defgeneric(OBJ, gsplit , _1);

// set-like algorithms
defgeneric(OBJ, gdiff     , _1, _2);
defgeneric(OBJ, gunion    , _1, _2);
defgeneric(OBJ, gintersect, _1, _2);

#endif // COS_GEN_ALGORITHM_H


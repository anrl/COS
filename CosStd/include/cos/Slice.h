#ifndef COS_SLICE_H
#define COS_SLICE_H

/*
 o---------------------------------------------------------------------o
 |
 | COS Slice
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
 | $Id: Slice.h,v 1.1 2008/09/28 19:56:26 ldeniau Exp $
 |
*/

#include <cos/Index.h>
#include <cos/Range.h>

// ----- definitions

defclass(Slice, Value)
endclass

defclass(Slice1, Slice)
  U32 start;
  U32 size;
  I32 stride;
endclass

defclass(Slice2, Slice)
  U32 start;
  U32 size  [2];
  I32 stride[2];
endclass

defclass(Slice3, Slice)
  U32 start;
  U32 size  [3];
  I32 stride[3];
endclass

defclass(Slice4, Slice)
  U32 start;
  U32 size  [4];
  I32 stride[4];
endclass

defclass(Slice5, Slice)
  U32 start;
  U32 size  [5];
  I32 stride[5];
endclass

// ----- evaluation

static inline U32
Slice1_eval(struct Slice1 *s, U32 i0) {
  return s->start + i0 * s->stride;
}

static inline U32
Slice2_eval(struct Slice2 *s, U32 i0, U32 i1) {
  return s->start + i0 * s->stride[0] + i1 * s->stride[1];
}

static inline U32
Slice3_eval(struct Slice3 *s, U32 i0, U32 i1, U32 i2) {
  return s->start + i0 * s->stride[0] + i1 * s->stride[1] + i2 * s->stride[2];
}

static inline U32
Slice4_eval(struct Slice4 *s, U32 i0, U32 i1, U32 i2, U32 i3) {
  return s->start + i0 * s->stride[0] + i1 * s->stride[1] + i2 * s->stride[2]
                  + i3 * s->stride[3];
}

static inline U32
Slice5_eval(struct Slice5 *s, U32 i0, U32 i1, U32 i2, U32 i3, U32 i4) {
  return s->start + i0 * s->stride[0] + i1 * s->stride[1] + i2 * s->stride[2]
                  + i3 * s->stride[3] + i4 * s->stride[4];
}

// ----- size

static inline U32
Slice1_size(struct Slice1 *s) {
  return s->size;
}

static inline U32
Slice2_size(struct Slice2 *s) {
  return s->size[0] * s->size[1];
}

static inline U32
Slice3_size(struct Slice3 *s) {
  return s->size[0] * s->size[1] * s->size[2];
}

static inline U32
Slice4_size(struct Slice4 *s) {
  return s->size[0] * s->size[1] * s->size[2] * s->size[3];
}

static inline U32
Slice5_size(struct Slice5 *s) {
  return s->size[0] * s->size[1] * s->size[2] * s->size[3] * s->size[4];
}

// ----- last

static inline U32
Slice1_last(struct Slice1 *s) {
  return Slice1_eval(s, s->size-1);
}

static inline U32
Slice2_last(struct Slice2 *s) {
  return Slice2_eval(s, s->size[0]-1, s->size[1]-1);
}

static inline U32
Slice3_last(struct Slice3 *s) {
  return Slice3_eval(s, s->size[0]-1, s->size[1]-1, s->size[2]-1);
}

static inline U32
Slice4_last(struct Slice4 *s) {
  return Slice4_eval(s, s->size[0]-1, s->size[1]-1, s->size[2]-1, s->size[3]-1);
}

static inline U32
Slice5_last(struct Slice5 *s) {
  return Slice5_eval(s, s->size[0]-1, s->size[1]-1, s->size[2]-1, s->size[3]-1, s->size[4]-1);
}

// ----- continuity

static inline BOOL
Slice1_iscontiguous(struct Slice1 *s) {
  return s->stride == 1;
}

static inline BOOL
Slice2_iscontiguous(struct Slice2 *s) {
  return s->stride[1] == 1
      && s->stride[0] == (I32)s->size[1];
}

static inline BOOL
Slice3_iscontiguous(struct Slice3 *s) {
  U32 size;

  return s->stride[2] == 1
      && s->stride[1] == (I32)(size  = s->size[2])
      && s->stride[0] == (I32)(size *= s->size[1]);
}

static inline BOOL
Slice4_iscontiguous(struct Slice4 *s) {
  U32 size;

  return s->stride[3] == 1
      && s->stride[2] == (I32)(size  = s->size[3])
      && s->stride[1] == (I32)(size *= s->size[2])
      && s->stride[0] == (I32)(size *= s->size[1]);
}

static inline BOOL
Slice5_iscontiguous(struct Slice5 *s) {
  U32 size;

  return s->stride[4] == 1
      && s->stride[3] == (I32)(size  = s->size[4])
      && s->stride[2] == (I32)(size *= s->size[3])
      && s->stride[1] == (I32)(size *= s->size[2])
      && s->stride[0] == (I32)(size *= s->size[1]);
}

// ----- conversion

static inline void
Slice1_range(struct Slice1 *s, struct Range1 *r, U32 size) {
  U32 start = Index_normalize(r->start, size);
  U32 end   = Index_normalize(r->end  , size);
  s->size   = (end - start + r->stride) / r->stride;
  s->stride = r->stride;
  s->start  = start;  
}

static inline void
Slice2_range(struct Slice2 *s, struct Range2 *r, U32 size[2]) {
  U32 i = 2, s0 = 0, ss = 1;

  while (i--) {
    U32 start = Index_normalize(r->start[i], size[i]);
    U32 end   = Index_normalize(r->end  [i], size[i]);
    s->size  [i] = (end - start + r->stride[i]) / r->stride[i];
    s->stride[i] = r->stride[i] * ss;
    s0 += s->stride[i] * start;
    ss *= size[i];
  }
  s->start = s0;
}

static inline void
Slice3_range(struct Slice3 *s, struct Range3 *r, U32 size[3]) {
  U32 i = 3, s0 = 0, ss = 1;

  while (i--) {
    U32 start = Index_normalize(r->start[i], size[i]);
    U32 end   = Index_normalize(r->end  [i], size[i]);
    s->size  [i] = (end - start + r->stride[i]) / r->stride[i];
    s->stride[i] = r->stride[i] * ss;
    s0 += s->stride[i] * start;
    ss *= size[i];
  }
  s->start = s0;
}

static inline void
Slice4_range(struct Slice4 *s, struct Range4 *r, U32 size[4]) {
  U32 i = 4, s0 = 0, ss = 1;

  while (i--) {
    U32 start = Index_normalize(r->start[i], size[i]);
    U32 end   = Index_normalize(r->end  [i], size[i]);
    s->size  [i] = (end - start + r->stride[i]) / r->stride[i];
    s->stride[i] = r->stride[i] * ss;
    s0 += s->stride[i] * start;
    ss *= size[i];
  }
  s->start = s0;
}

static inline void
Slice5_range(struct Slice5 *s, struct Range5 *r, U32 size[5]) {
  U32 i = 5, s0 = 0, ss = 1;

  while (i--) {
    U32 start = Index_normalize(r->start[i], size[i]);
    U32 end   = Index_normalize(r->end  [i], size[i]);
    s->size  [i] = (end - start + r->stride[i]) / r->stride[i];
    s->stride[i] = r->stride[i] * ss;
    s0 += s->stride[i] * start;
    ss *= size[i];
  }
  s->start = s0;
}

// ----- merging

static inline void
Slice1_srange(struct Slice1 *sr, struct Range1 *r, struct Slice1 *s) {
  COS_UNUSED(sr, r, s);
}

static inline void
Slice2_srange(struct Slice2 *sr, struct Range2 *r, struct Slice2 *s) {
  COS_UNUSED(sr, r, s);
}

static inline void
Slice3_srange(struct Slice3 *sr, struct Range3 *r, struct Slice3 *s) {
  COS_UNUSED(sr, r, s);
}

static inline void
Slice4_srange(struct Slice4 *sr, struct Range4 *r, struct Slice4 *s) {
  COS_UNUSED(sr, r, s);
}

static inline void
Slice5_srange(struct Slice5 *sr, struct Range5 *r, struct Slice5 *s) {
  COS_UNUSED(sr, r, s);
}

// ----- automatic constructors

#define aSlice(...)  ( (OBJ)atSlice(__VA_ARGS__) )
#define atSlice(...) COS_PP_CAT_NARG(aSlice_, __VA_ARGS__)(__VA_ARGS__)

#define atSlice_2(start,sizes) \
        atSlice_3(start,sizes, \
                  COS_PP_IF(COS_PP_ISTUPLE(sizes))( \
                   (COS_PP_DUPSEQ(COS_PP_LEN(sizes),1)),1))

#define atSlice_3(start,sizes,strides) \
        atSliceN(COS_PP_IF(COS_PP_ISTUPLE(sizes))(COS_PP_LEN(sizes),1), \
                 start,sizes,strides)

#define atSliceN(N,start,sizes,strides) \
        ( &(struct COS_PP_CAT(Slice,N)) { \
          {{{{ COS_CLS_NAME(COS_PP_CAT(Slice,N)).Behavior.id, COS_RC_AUTO }}}}, \
           start, \
           COS_PP_IF(COS_PP_ISONE(N))(sizes  , { COS_PP_SEQ(sizes  ) }), \
           COS_PP_IF(COS_PP_ISONE(N))(strides, { COS_PP_SEQ(strides) }) } )

#endif // COS_SLICE_H
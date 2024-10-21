/*
 *  Copyright 2011-16 ARM Limited and Contributors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of ARM Limited nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY ARM LIMITED AND CONTRIBUTORS "AS IS" AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL ARM LIMITED AND CONTRIBUTORS BE LIABLE FOR ANY
 *  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * NE10 Library : math/NE10_subc.neon.c
 */

#include "NE10_types.h"
#include "macros.h"


#include <arm_neon.h>


ne10_result_t ne10_subc_float_neon (ne10_float32_t * dst, ne10_float32_t * src, const ne10_float32_t cst, ne10_uint32_t count)
{
    NE10_DstSrcCst_DO_COUNT_TIMES_FLOAT_NEON
    (
        n_dst = vsubq_f32 (n_src , n_cst);
        ,
        n_rest = vsub_f32 (n_rest, n_rest_cst);
    );
}

ne10_result_t ne10_subc_vec2f_neon (ne10_vec2f_t * dst, ne10_vec2f_t * src, const ne10_vec2f_t * cst, ne10_uint32_t count)
{
    NE10_DstSrcCst_DO_COUNT_TIMES_VEC2F_NEON
    (
        n_dst = vsubq_f32 (n_src , n_cst);
        ,
        n_rest = vsub_f32 (n_rest, n_rest_cst);
    );
}

ne10_result_t ne10_subc_vec3f_neon (ne10_vec3f_t * dst, ne10_vec3f_t * src, const ne10_vec3f_t * cst, ne10_uint32_t count)
{
    NE10_DstSrcCst_DO_COUNT_TIMES_VEC3F_NEON
    (
        n_dst1 = vsubq_f32 (n_src1 , n_cst1);
        n_dst2 = vsubq_f32 (n_src2 , n_cst2);
        n_dst3 = vsubq_f32 (n_src3 , n_cst3);
        ,
        n_rest.val[0] = vsub_f32 (n_rest.val[0], n_rest_cst.val[0]);
        n_rest.val[1] = vsub_f32 (n_rest.val[1], n_rest_cst.val[1]);
        n_rest.val[2] = vsub_f32 (n_rest.val[2], n_rest_cst.val[2]);
    );
}

ne10_result_t ne10_subc_vec4f_neon (ne10_vec4f_t * dst, ne10_vec4f_t * src, const ne10_vec4f_t * cst, ne10_uint32_t count)
{
    NE10_DstSrcCst_DO_COUNT_TIMES_VEC4F_NEON
    (
        n_dst = vsubq_f32 (n_src , n_cst);
    );
}

/* Copyright (C) 2010-2015 (see AUTHORS file for a list of contributors)
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 */

#include <volk_gnsssdr/volk_gnsssdr.h>
#include <qa_16s_quad_max_star_aligned16.h>
#include <volk_gnsssdr/volk_gnsssdr_16s_quad_max_star_aligned16.h>
#include <cstdlib>
#include <ctime>

//test for sse2

#ifndef LV_HAVE_SSE2

void qa_16s_quad_max_star_aligned16::t1()
{
    printf("sse2 not available... no test performed\n");
}

#else

void qa_16s_quad_max_star_aligned16::t1()
{
    const int vlen = 34;

    __VOLK_ATTR_ALIGNED(16) short input0[vlen];
    __VOLK_ATTR_ALIGNED(16) short input1[vlen];
    __VOLK_ATTR_ALIGNED(16) short input2[vlen];
    __VOLK_ATTR_ALIGNED(16) short input3[vlen];

    __VOLK_ATTR_ALIGNED(16) short output0[vlen];
    __VOLK_ATTR_ALIGNED(16) short output1[vlen];

    for(int i = 0; i < vlen; ++i)
        {
            short plus0 = (short) (rand() - (RAND_MAX/2));
            short plus1 = (short) (rand() - (RAND_MAX/2));
            short plus2 = (short) (rand() - (RAND_MAX/2));
            short plus3 = (short) (rand() - (RAND_MAX/2));

            short minus0 = (short) (rand() - (RAND_MAX/2));
            short minus1 = (short) (rand() - (RAND_MAX/2));
            short minus2 = (short) (rand() - (RAND_MAX/2));
            short minus3 = (short) (rand() - (RAND_MAX/2));

            input0[i] = plus0 - minus0;
            input1[i] = plus1 - minus1;
            input2[i] = plus2 - minus2;
            input3[i] = plus3 - minus3;
        }

    volk_gnsssdr_16s_quad_max_star_aligned16_manual(output0, input0, input1, input2, input3, 2*vlen, "generic");

    volk_gnsssdr_16s_quad_max_star_aligned16_manual(output1, input0, input1, input2, input3, 2*vlen, "sse2");

    printf("16s_quad_max_star_aligned\n");
    for(int i = 0; i < vlen; ++i)
        {
            printf("generic... %d, sse2... %d, inputs: %d, %d, %d, %d\n", output0[i], output1[i], input0[i], input1[i], input2[i], input3[i]);
        }

    for(int i = 0; i < vlen; ++i)
        {
            CPPUNIT_ASSERT_EQUAL(output0[i], output1[i]);
        }
}

#endif

/*
 * Copyright (C) 2018 Sean Anderson
 *
 * This file is part of appdir.
 *
 * appdir is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * appdir is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with appdir. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TEST_H
#define TEST_H

#include <string.h>

/* Stolen from <http://www.jera.com/techinfo/jtns/jtn002.html> */
#define stringify2(x) #x
#define stringify(x) stringify2(x)
#define __LINE_STR__ stringify(__LINE__)
#define assert(message, test) do { if (!(test)) \
	return (__FILE__ ":" __LINE_STR__ ": " message); } while (0)
#define assert_nonnull(var) assert(#var " is NULL", (var))
#define assert_eq(x, y) assert(#x " does not equal " #y, (x) == (y))
#define assert_streq(x, y) assert(#x " does not equal " #y, !strcmp((x), (y)))
#define assert_strlisteq(l1, l2) do { \
	size_t i; \
	assert_nonnull(l1); \
	assert_nonnull(l2); \
	for (i = 0; l1[i] && l2[i]; i++) { \
		assert_nonnull(l1[i]); \
		assert_nonnull(l2[i]); \
		assert_streq(l1[i], l2[i]); \
	} \
	assert_eq(l1[i], l2[i]); \
	assert("One of " #l1 " or " #l2 " is empty", i > 0); \
} while (0)

#endif /* TEST_H */

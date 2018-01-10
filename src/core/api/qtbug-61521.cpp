/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <stdlib.h>
#include <unistd.h>

#define SHIM_ALIAS_SYMBOL(fn) __attribute__((weak, alias(#fn)))
#define SHIM_SYMBOL_VERSION(fn) __asm__(".symver __" #fn "," #fn "@Qt_5")
#define SHIM_HIDDEN __attribute__ ((visibility ("hidden")))

extern "C" {

SHIM_SYMBOL_VERSION(malloc);
void* __malloc(size_t size)
    SHIM_ALIAS_SYMBOL(ShimMalloc);

SHIM_SYMBOL_VERSION(free);
void __free(void* ptr)
    SHIM_ALIAS_SYMBOL(ShimFree);

SHIM_SYMBOL_VERSION(realloc);
void* __realloc(void* ptr, size_t size)
    SHIM_ALIAS_SYMBOL(ShimRealloc);

SHIM_SYMBOL_VERSION(calloc);
void* __calloc(size_t n, size_t size)
    SHIM_ALIAS_SYMBOL(ShimCalloc);

SHIM_SYMBOL_VERSION(cfree);
void __cfree(void* ptr)
    SHIM_ALIAS_SYMBOL(ShimCFree);

SHIM_SYMBOL_VERSION(valloc);
void* __valloc(size_t size)
    SHIM_ALIAS_SYMBOL(ShimValloc);

SHIM_SYMBOL_VERSION(posix_memalign);
int __posix_memalign(void** r, size_t a, size_t s)
    SHIM_ALIAS_SYMBOL(ShimPosixMemalign);

SHIM_HIDDEN void* ShimMalloc(size_t size) {
    return malloc(size);
}

SHIM_HIDDEN void ShimFree(void* ptr) {
    free(ptr);
}

SHIM_HIDDEN void* ShimRealloc(void* ptr, size_t size) {
    return realloc(ptr,size);
}

SHIM_HIDDEN void* ShimCalloc(size_t n, size_t size) {
    return calloc(n,size);
}

SHIM_HIDDEN void ShimCFree(void* ptr) {
    free(ptr);
}

SHIM_HIDDEN void* ShimValloc(size_t size) {
    return  valloc(size);
}

SHIM_HIDDEN int ShimPosixMemalign(void** r, size_t a, size_t s) {
    return posix_memalign(r,a,s);
}
}  // extern "C"

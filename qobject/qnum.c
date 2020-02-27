/*
 * QNum Module
 *
 * Copyright (C) 2009 Red Hat Inc.
 *
 * Authors:
 *  Luiz Capitulino <lcapitulino@redhat.com>
 *  Anthony Liguori <aliguori@us.ibm.com>
 *  Marc-André Lureau <marcandre.lureau@redhat.com>
 *
 * This work is licensed under the terms of the GNU LGPL, version 2.1 or later.
 * See the COPYING.LIB file in the top-level directory.
 */

#include "qemu/osdep.h"
#include "qapi/qmp/qnum.h"

/**
 * qobject_to_qint(): Convert a QObject into a QInt
 */
QNum *qobject_to_qnum(const QObject *obj)
{
    if (qobject_type(obj) != QTYPE_QNUM)
        return NULL;

    return container_of(obj, QNum, base);
}

/**
 * qint_destroy_obj(): Free all memory allocated by a
 * QInt object
 */
void qnum_destroy_obj(QObject *obj)
{
    assert(obj != NULL);
    g_free(qobject_to_qnum(obj));
}

static const QType qnum_type = {
    .code = QTYPE_QNUM,
    .destroy = qnum_destroy_obj,
};

/**
 * qnum_from_uint(): Create a new QNum from an uint64_t
 *
 * Return strong reference.
 */
QNum *qnum_from_uint(uint64_t value)
{
    QNum *qn = g_malloc( sizeof(QNum));
    QOBJECT_INIT(qn,&qnum_type);
    qn->kind = QNUM_U64;
    qn->u.u64 = value;

    return qn;
}


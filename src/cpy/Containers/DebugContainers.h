//
// Created by Paul Ross on 15/12/2024.
//

#ifndef PYTHONEXTENSIONPATTERNS_DEBUGCONTAINERS_H
#define PYTHONEXTENSIONPATTERNS_DEBUGCONTAINERS_H

#include "pyextpatt_util.h"

#define ACCEPT_SIGSEGV 0

#pragma mark - Tuples
void dbg_PyTuple_SetItem_steals(void);
void dbg_PyTuple_SET_ITEM_steals(void);
void dbg_PyTuple_SetItem_steals_replace(void);
void dbg_PyTuple_SET_ITEM_steals_replace(void);
void dbg_PyTuple_SetItem_replace_with_same(void);
void dbg_PyTuple_SET_ITEM_replace_with_same(void);
void dbg_PyTuple_SetIem_NULL(void);
void dbg_PyTuple_SET_ITEM_NULL(void);
void dbg_PyTuple_SetIem_NULL_SetItem(void);
void dbg_PyTuple_SET_ITEM_NULL_SET_ITEM(void);
void dbg_PyTuple_SetItem_fails_not_a_tuple(void);
void dbg_PyTuple_SetItem_fails_out_of_range(void);
void dbg_PyTuple_PyTuple_Pack(void);
void dbg_PyTuple_Py_BuildValue(void);
#pragma mark - Lists
void dbg_PyList_SetItem_steals(void);
void dbg_PyList_SET_ITEM_steals(void);
void dbg_PyList_SetItem_steals_replace(void);
void dbg_PyList_SET_ITEM_steals_replace(void);
void dbg_PyList_SetItem_replace_with_same(void);
void dbg_PyList_SET_ITEM_replace_with_same(void);
void dbg_PyList_SetIem_NULL(void);
void dbg_PyList_SET_ITEM_NULL(void);
void dbg_PyList_SetIem_NULL_SetItem(void);
void dbg_PyList_SET_ITEM_NULL_SET_ITEM(void);
void dbg_PyList_SetItem_fails_not_a_tuple(void);
void dbg_PyList_SetItem_fails_out_of_range(void);
void dbg_PyList_Append(void);
void dbg_PyList_Append_fails_not_a_list(void);
void dbg_PyList_Append_fails_NULL(void);
void dbg_PyList_Insert(void);
void dbg_PyList_Insert_Is_Truncated(void);
void dbg_PyList_Insert_Negative_Index(void);
void dbg_PyList_Insert_fails_not_a_list(void);
void dbg_PyList_Insert_fails_NULL(void);
void dbg_PyList_Py_BuildValue(void);

#pragma mark - Dictionaries - setters
void dbg_PyDict_SetItem_increments(void);

#if ACCEPT_SIGSEGV
void dbg_PyDict_SetItem_NULL_key(void);
void dbg_PyDict_SetItem_NULL_value(void);
#endif // ACCEPT_SIGSEGV

void dbg_PyDict_SetItem_fails_not_a_dict(void);
void dbg_PyDict_SetItem_fails_not_hashable(void);
void dbg_PyDict_SetDefault_default_unused(void);
void dbg_PyDict_SetDefault_default_used(void);
void dbg_PyDict_SetDefaultRef_default_unused(void);
#if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 13
void dbg_PyDict_SetDefaultRef_default_used(void);
void dbg_PyDict_SetDefaultRef_default_unused_result_non_null(void);
#endif // #if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 13

#pragma mark - Dictionaries - getters
void dbg_PyDict_GetItem(void);
#if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 13
void dbg_PyDict_GetItemRef(void);
#endif // #if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 13
void dbg_PyDict_GetItemWithError_fails(void);

#pragma mark - Dictionaries - deleters

#if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 13
void dbg_PyDict_Pop_key_present(void);
void dbg_PyDict_Pop_key_absent(void);
#endif // #if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 13

#pragma mark - Sets

void dbg_PySet_Add(void);
void dbg_PySet_Discard(void);
void dbg_PySet_Pop(void);

#pragma mark - Struct Sequence

void dbg_PyStructSequence_simple_ctor(void);
void dbg_PyStructSequence_setitem_abandons(void);
void dbg_PyStructSequence_n_in_sequence_too_large(void);
void dbg_PyStructSequence_with_unnamed_field(void);

#if ACCEPT_SIGSEGV
void dbg_PyTuple_SetItem_SIGSEGV_on_same_value(void);
void dbg_PyList_SetItem_SIGSEGV_on_same_value(void);
void dbg_PyDict_SetItem_SIGSEGV_on_key_NULL(void);
void dbg_PyDict_SetItem_SIGSEGV_on_value_NULL(void);
void dbg_PyDict_GetItem_key_NULL(void);
#endif

#endif //PYTHONEXTENSIONPATTERNS_DEBUGCONTAINERS_H

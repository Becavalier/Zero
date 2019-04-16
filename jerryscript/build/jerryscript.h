/* Copyright JS Foundation and other contributors, http://js.foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "jerryscript-config.h"
#line 1 "/Users/jason/Desktop/Repo/zero-main/jerryscript/jerry-core/include/jerryscript.h"

#ifndef JERRYSCRIPT_H
#define JERRYSCRIPT_H

#line 1 "/Users/jason/Desktop/Repo/zero-main/jerryscript/jerry-core/include/jerryscript-core.h"

#ifndef JERRYSCRIPT_CORE_H
#define JERRYSCRIPT_CORE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#line 1 "/Users/jason/Desktop/Repo/zero-main/jerryscript/jerry-core/include/jerryscript-compiler.h"

#ifndef JERRYSCRIPT_COMPILER_H
#define JERRYSCRIPT_COMPILER_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/** \addtogroup jerry-compiler Jerry compiler compatibility components
 * @{
 */

#ifdef __GNUC__

/*
 * Compiler-specific macros relevant for GCC.
 */
#define JERRY_ATTR_ALIGNED(ALIGNMENT) __attribute__((aligned(ALIGNMENT)))
#define JERRY_ATTR_ALWAYS_INLINE __attribute__((always_inline))
#define JERRY_ATTR_CONST __attribute__((const))
#define JERRY_ATTR_DEPRECATED __attribute__((deprecated))
#define JERRY_ATTR_FORMAT(...) __attribute__((format(__VA_ARGS__)))
#define JERRY_ATTR_HOT __attribute__((hot))
#define JERRY_ATTR_NOINLINE __attribute__((noinline))
#define JERRY_ATTR_NORETURN __attribute__((noreturn))
#define JERRY_ATTR_PURE __attribute__((pure))
#define JERRY_ATTR_SECTION(SECTION) __attribute__((section(SECTION)))
#define JERRY_ATTR_WARN_UNUSED_RESULT __attribute__((warn_unused_result))

#define JERRY_LIKELY(x) __builtin_expect(!!(x), 1)
#define JERRY_UNLIKELY(x) __builtin_expect(!!(x), 0)

#endif /* __GNUC__ */

#ifdef _MSC_VER

/*
 * Compiler-specific macros relevant for Microsoft Visual C/C++ Compiler.
 */
#define JERRY_ATTR_DEPRECATED __declspec(deprecated)
#define JERRY_ATTR_NOINLINE __declspec(noinline)
#define JERRY_ATTR_NORETURN __declspec(noreturn)

/*
 * Microsoft Visual C/C++ Compiler doesn't support for VLA, using _alloca
 * instead.
 */
void * __cdecl _alloca (size_t _Size);
#define JERRY_VLA(type, name, size) type *name = (type *) (_alloca (sizeof (type) * size))

#endif /* _MSC_VER */

/*
 * Default empty definitions for all compiler-specific macros. Define any of
 * these in a guarded block above (e.g., as for GCC) to fine tune compilation
 * for your own compiler. */

/**
 * Function attribute to align function to given number of bytes.
 */
#ifndef JERRY_ATTR_ALIGNED
#define JERRY_ATTR_ALIGNED(ALIGNMENT)
#endif /* !JERRY_ATTR_ALIGNED */

/**
 * Function attribute to inline function to all call sites.
 */
#ifndef JERRY_ATTR_ALWAYS_INLINE
#define JERRY_ATTR_ALWAYS_INLINE
#endif /* !JERRY_ATTR_ALWAYS_INLINE */

/**
 * Function attribute to declare that function has no effect except the return
 * value and it only depends on parameters.
 */
#ifndef JERRY_ATTR_CONST
#define JERRY_ATTR_CONST
#endif /* !JERRY_ATTR_CONST */

/**
 * Function attribute to trigger warning if deprecated function is called.
 */
#ifndef JERRY_ATTR_DEPRECATED
#define JERRY_ATTR_DEPRECATED
#endif /* !JERRY_ATTR_DEPRECATED */

/**
 * Function attribute to declare that function is variadic and takes a format
 * string and some arguments as parameters.
 */
#ifndef JERRY_ATTR_FORMAT
#define JERRY_ATTR_FORMAT(...)
#endif /* !JERRY_ATTR_FORMAT */

/**
 * Function attribute to predict that function is a hot spot, and therefore
 * should be optimized aggressively.
 */
#ifndef JERRY_ATTR_HOT
#define JERRY_ATTR_HOT
#endif /* !JERRY_ATTR_HOT */

/**
 * Function attribute not to inline function ever.
 */
#ifndef JERRY_ATTR_NOINLINE
#define JERRY_ATTR_NOINLINE
#endif /* !JERRY_ATTR_NOINLINE */

/**
 * Function attribute to declare that function never returns.
 */
#ifndef JERRY_ATTR_NORETURN
#define JERRY_ATTR_NORETURN
#endif /* !JERRY_ATTR_NORETURN */

/**
 * Function attribute to declare that function has no effect except the return
 * value and it only depends on parameters and global variables.
 */
#ifndef JERRY_ATTR_PURE
#define JERRY_ATTR_PURE
#endif /* !JERRY_ATTR_PURE */

/**
 * Function attribute to place function in given section.
 */
#ifndef JERRY_ATTR_SECTION
#define JERRY_ATTR_SECTION(SECTION)
#endif /* !JERRY_ATTR_SECTION */

/**
 * Function attribute to trigger warning if function's caller doesn't use (e.g.,
 * check) the return value.
 */
#ifndef JERRY_ATTR_WARN_UNUSED_RESULT
#define JERRY_ATTR_WARN_UNUSED_RESULT
#endif /* !JERRY_ATTR_WARN_UNUSED_RESULT */

/**
 * Helper to predict that a condition is likely.
 */
#ifndef JERRY_LIKELY
#define JERRY_LIKELY(x) (x)
#endif /* !JERRY_LIKELY */

/**
 * Helper to predict that a condition is unlikely.
 */
#ifndef JERRY_UNLIKELY
#define JERRY_UNLIKELY(x) (x)
#endif /* !JERRY_UNLIKELY */

/**
 * Helper to declare (or mimic) a C99 variable-length array.
 */
#ifndef JERRY_VLA
#define JERRY_VLA(type, name, size) type name[size]
#endif /* !JERRY_VLA */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* !JERRYSCRIPT_COMPILER_H */
#line 24 "/Users/jason/Desktop/Repo/zero-main/jerryscript/jerry-core/include/jerryscript-core.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/** \addtogroup jerry Jerry engine interface
 * @{
 */

/**
 * Major version of JerryScript API.
 */
#define JERRY_API_MAJOR_VERSION 1

/**
 * Minor version of JerryScript API.
 */
#define JERRY_API_MINOR_VERSION 0

/**
 * JerryScript init flags.
 */
typedef enum
{
  JERRY_INIT_EMPTY               = (0u),      /**< empty flag set */
  JERRY_INIT_SHOW_OPCODES        = (1u << 0), /**< dump byte-code to log after parse */
  JERRY_INIT_SHOW_REGEXP_OPCODES = (1u << 1), /**< dump regexp byte-code to log after compilation */
  JERRY_INIT_MEM_STATS           = (1u << 2), /**< dump memory statistics */
  JERRY_INIT_MEM_STATS_SEPARATE  = (1u << 3), /**< deprecated, an unused placeholder now */
  JERRY_INIT_DEBUGGER            = (1u << 4), /**< deprecated, an unused placeholder now */
} jerry_init_flag_t;

/**
 * JerryScript API Error object types.
 */
typedef enum
{
  JERRY_ERROR_NONE = 0,  /**< No Error */

  JERRY_ERROR_COMMON,    /**< Error */
  JERRY_ERROR_EVAL,      /**< EvalError */
  JERRY_ERROR_RANGE,     /**< RangeError */
  JERRY_ERROR_REFERENCE, /**< ReferenceError */
  JERRY_ERROR_SYNTAX,    /**< SyntaxError */
  JERRY_ERROR_TYPE,      /**< TypeError */
  JERRY_ERROR_URI        /**< URIError */
} jerry_error_t;

/**
 * JerryScript feature types.
 */
typedef enum
{
  JERRY_FEATURE_CPOINTER_32_BIT, /**< 32 bit compressed pointers */
  JERRY_FEATURE_ERROR_MESSAGES, /**< error messages */
  JERRY_FEATURE_JS_PARSER, /**< js-parser */
  JERRY_FEATURE_MEM_STATS, /**< memory statistics */
  JERRY_FEATURE_PARSER_DUMP, /**< parser byte-code dumps */
  JERRY_FEATURE_REGEXP_DUMP, /**< regexp byte-code dumps */
  JERRY_FEATURE_SNAPSHOT_SAVE, /**< saving snapshot files */
  JERRY_FEATURE_SNAPSHOT_EXEC, /**< executing snapshot files */
  JERRY_FEATURE_DEBUGGER, /**< debugging */
  JERRY_FEATURE_VM_EXEC_STOP, /**< stopping ECMAScript execution */
  JERRY_FEATURE_JSON, /**< JSON support */
  JERRY_FEATURE_PROMISE, /**< promise support */
  JERRY_FEATURE_TYPEDARRAY, /**< Typedarray support */
  JERRY_FEATURE_DATE, /**< Date support */
  JERRY_FEATURE_REGEXP, /**< Regexp support */
  JERRY_FEATURE_LINE_INFO, /**< line info available */
  JERRY_FEATURE_LOGGING, /**< logging */
  JERRY_FEATURE_SYMBOL, /**< symbol support */
  JERRY_FEATURE__COUNT /**< number of features. NOTE: must be at the end of the list */
} jerry_feature_t;

/**
 * Option flags for jerry_parse and jerry_parse_function functions.
 */
typedef enum
{
  JERRY_PARSE_NO_OPTS = 0, /**< no options passed */
  JERRY_PARSE_STRICT_MODE = (1 << 0) /**< enable strict mode */
} jerry_parse_opts_t;

/**
 * GC operational modes.
 */
typedef enum
{
  JERRY_GC_SEVERITY_LOW, /**< free unused objects, but keep memory
                          *   allocated for performance improvements
                          *   such as property hash tables for large objects */
  JERRY_GC_SEVERITY_HIGH /**< free as much memory as possible */
} jerry_gc_mode_t;

/**
 * Jerry regexp flags.
 */
typedef enum
{
  JERRY_REGEXP_FLAG_GLOBAL = (1u << 1),      /**< Globally scan string */
  JERRY_REGEXP_FLAG_IGNORE_CASE = (1u << 2), /**< Ignore case */
  JERRY_REGEXP_FLAG_MULTILINE = (1u << 3)    /**< Multiline string scan */
} jerry_regexp_flags_t;

/**
 * Character type of JerryScript.
 */
typedef uint8_t jerry_char_t;

/**
 * Size type of JerryScript.
 */
typedef uint32_t jerry_size_t;

/**
 * Length type of JerryScript.
 */
typedef uint32_t jerry_length_t;

/**
 * Description of a JerryScript value.
 */
typedef uint32_t jerry_value_t;

/**
 * Description of ECMA property descriptor.
 */
typedef struct
{
  /** Is [[Value]] defined? */
  bool is_value_defined;

  /** Is [[Get]] defined? */
  bool is_get_defined;

  /** Is [[Set]] defined? */
  bool is_set_defined;

  /** Is [[Writable]] defined? */
  bool is_writable_defined;

  /** [[Writable]] */
  bool is_writable;

  /** Is [[Enumerable]] defined? */
  bool is_enumerable_defined;

  /** [[Enumerable]] */
  bool is_enumerable;

  /** Is [[Configurable]] defined? */
  bool is_configurable_defined;

  /** [[Configurable]] */
  bool is_configurable;

  /** [[Value]] */
  jerry_value_t value;

  /** [[Get]] */
  jerry_value_t getter;

  /** [[Set]] */
  jerry_value_t setter;
} jerry_property_descriptor_t;

/**
 * Description of JerryScript heap memory stats.
 * It is for memory profiling.
 */
typedef struct
{
  size_t version; /**< the version of the stats struct */
  size_t size; /**< heap total size */
  size_t allocated_bytes; /**< currently allocated bytes */
  size_t peak_allocated_bytes; /**< peak allocated bytes */
  size_t reserved[4]; /**< padding for future extensions */
} jerry_heap_stats_t;

/**
 * Type of an external function handler.
 */
typedef jerry_value_t (*jerry_external_handler_t) (const jerry_value_t function_obj,
                                                   const jerry_value_t this_val,
                                                   const jerry_value_t args_p[],
                                                   const jerry_length_t args_count);

/**
 * Native free callback of an object.
 */
typedef void (*jerry_object_native_free_callback_t) (void *native_p);

/**
 * Callback which tells whether the ECMAScript execution should be stopped.
 *
 * As long as the function returns with undefined the execution continues.
 * When a non-undefined value is returned the execution stops and the value
 * is thrown by the engine (if the error flag is not set for the returned
 * value the engine automatically sets it).
 *
 * Note: if the function returns with a non-undefined value it
 *       must return with the same value for future calls.
 */
typedef jerry_value_t (*jerry_vm_exec_stop_callback_t) (void *user_p);

/**
 * Function type applied for each data property of an object.
 */
typedef bool (*jerry_object_property_foreach_t) (const jerry_value_t property_name,
                                                 const jerry_value_t property_value,
                                                 void *user_data_p);
/**
 * Function type applied for each object in the engine.
 */
typedef bool (*jerry_objects_foreach_t) (const jerry_value_t object,
                                         void *user_data_p);

/**
 * Function type applied for each matching object in the engine.
 */
typedef bool (*jerry_objects_foreach_by_native_info_t) (const jerry_value_t object,
                                                        void *object_data_p,
                                                        void *user_data_p);

/**
 * User context item manager
 */
typedef struct
{
  /**
   * Callback responsible for initializing a context item, or NULL to zero out the memory. This is called lazily, the
   * first time jerry_get_context_data () is called with this manager.
   *
   * @param [in] data The buffer that JerryScript allocated for the manager. The buffer is zeroed out. The size is
   * determined by the bytes_needed field. The buffer is kept alive until jerry_cleanup () is called.
   */
  void (*init_cb) (void *data);

  /**
   * Callback responsible for deinitializing a context item, or NULL. This is called as part of jerry_cleanup (),
   * right *before* the VM has been cleaned up. This is a good place to release strong references to jerry_value_t's
   * that the manager may be holding.
   * Note: because the VM has not been fully cleaned up yet, jerry_object_native_info_t free_cb's can still get called
   * *after* all deinit_cb's have been run. See finalize_cb for a callback that is guaranteed to run *after* all
   * free_cb's have been run.
   *
   * @param [in] data The buffer that JerryScript allocated for the manager.
   */
  void (*deinit_cb) (void *data);

  /**
   * Callback responsible for finalizing a context item, or NULL. This is called as part of jerry_cleanup (),
   * right *after* the VM has been cleaned up and destroyed and jerry_... APIs cannot be called any more. At this point,
   * all values in the VM have been cleaned up. This is a good place to clean up native state that can only be cleaned
   * up at the very end when there are no more VM values around that may need to access that state.
   *
   * @param [in] data The buffer that JerryScript allocated for the manager. After returning from this callback,
   * the data pointer may no longer be used.
   */
  void (*finalize_cb) (void *data);

  /**
   * Number of bytes to allocate for this manager. This is the size of the buffer that JerryScript will allocate on
   * behalf of the manager. The pointer to this buffer is passed into init_cb, deinit_cb and finalize_cb. It is also
   * returned from the jerry_get_context_data () API.
   */
  size_t bytes_needed;
} jerry_context_data_manager_t;

/**
 * Function type for allocating buffer for JerryScript context.
 */
typedef void *(*jerry_context_alloc_t) (size_t size, void *cb_data_p);

/**
 * Type information of a native pointer.
 */
typedef struct
{
  jerry_object_native_free_callback_t free_cb; /**< the free callback of the native pointer */
} jerry_object_native_info_t;

/**
 * An opaque declaration of the JerryScript context structure.
 */
typedef struct jerry_context_t jerry_context_t;

/**
 * Enum that contains the supported binary operation types
 */
typedef enum
{
  JERRY_BIN_OP_EQUAL = 0u,    /**< equal comparison (==) */
  JERRY_BIN_OP_STRICT_EQUAL,  /**< strict equal comparison (===) */
  JERRY_BIN_OP_LESS,          /**< less relation (<) */
  JERRY_BIN_OP_LESS_EQUAL,    /**< less or equal relation (<=) */
  JERRY_BIN_OP_GREATER,       /**< greater relation (>) */
  JERRY_BIN_OP_GREATER_EQUAL, /**< greater or equal relation (>=)*/
  JERRY_BIN_OP_INSTANCEOF,    /**< instanceof operation */
} jerry_binary_operation_t;

/**
 * General engine functions.
 */
void jerry_init (jerry_init_flag_t flags);
void jerry_cleanup (void);
void jerry_register_magic_strings (const jerry_char_t * const *ex_str_items_p,
                                   uint32_t count,
                                   const jerry_length_t *str_lengths_p);
void jerry_gc (jerry_gc_mode_t mode);
void *jerry_get_context_data (const jerry_context_data_manager_t *manager_p);

bool jerry_get_memory_stats (jerry_heap_stats_t *out_stats_p);

/**
 * Parser and executor functions.
 */
bool jerry_run_simple (const jerry_char_t *script_source_p, size_t script_source_size, jerry_init_flag_t flags);
jerry_value_t jerry_parse (const jerry_char_t *resource_name_p, size_t resource_name_length,
                           const jerry_char_t *source_p, size_t source_size, uint32_t parse_opts);
jerry_value_t jerry_parse_function (const jerry_char_t *resource_name_p, size_t resource_name_length,
                                    const jerry_char_t *arg_list_p, size_t arg_list_size,
                                    const jerry_char_t *source_p, size_t source_size, uint32_t parse_opts);
jerry_value_t jerry_run (const jerry_value_t func_val);
jerry_value_t jerry_eval (const jerry_char_t *source_p, size_t source_size, uint32_t parse_opts);

jerry_value_t jerry_run_all_enqueued_jobs (void);

/**
 * Get the global context.
 */
jerry_value_t jerry_get_global_object (void);

/**
 * Checker functions of 'jerry_value_t'.
 */
bool jerry_value_is_abort (const jerry_value_t value);
bool jerry_value_is_array (const jerry_value_t value);
bool jerry_value_is_boolean (const jerry_value_t value);
bool jerry_value_is_constructor (const jerry_value_t value);
bool jerry_value_is_error (const jerry_value_t value);
bool jerry_value_is_function (const jerry_value_t value);
bool jerry_value_is_number (const jerry_value_t value);
bool jerry_value_is_null (const jerry_value_t value);
bool jerry_value_is_object (const jerry_value_t value);
bool jerry_value_is_promise (const jerry_value_t value);
bool jerry_value_is_string (const jerry_value_t value);
bool jerry_value_is_symbol (const jerry_value_t value);
bool jerry_value_is_undefined (const jerry_value_t value);

/**
 * JerryScript API value type information.
 */
typedef enum
{
  JERRY_TYPE_NONE = 0u, /**< no type information */
  JERRY_TYPE_UNDEFINED, /**< undefined type */
  JERRY_TYPE_NULL,      /**< null type */
  JERRY_TYPE_BOOLEAN,   /**< boolean type */
  JERRY_TYPE_NUMBER,    /**< number type */
  JERRY_TYPE_STRING,    /**< string type */
  JERRY_TYPE_OBJECT,    /**< object type */
  JERRY_TYPE_FUNCTION,  /**< function type */
  JERRY_TYPE_ERROR,     /**< error/abort type */
  JERRY_TYPE_SYMBOL,    /**< symbol type */
} jerry_type_t;

jerry_type_t jerry_value_get_type (const jerry_value_t value);

/**
 * Checker function of whether the specified compile feature is enabled.
 */
bool jerry_is_feature_enabled (const jerry_feature_t feature);

/**
 * Binary operations
 */
jerry_value_t jerry_binary_operation (jerry_binary_operation_t op,
                                      const jerry_value_t lhs,
                                      const jerry_value_t rhs);

/**
 * Error manipulation functions.
 */
jerry_value_t jerry_create_abort_from_value (jerry_value_t value, bool release);
jerry_value_t jerry_create_error_from_value (jerry_value_t value, bool release);
jerry_value_t jerry_get_value_from_error (jerry_value_t value, bool release);

/**
 * Error object function(s).
 */
jerry_error_t jerry_get_error_type (jerry_value_t value);

/**
 * Getter functions of 'jerry_value_t'.
 */
bool jerry_get_boolean_value (const jerry_value_t value);
double jerry_get_number_value (const jerry_value_t value);

/**
 * Functions for string values.
 */
jerry_size_t jerry_get_string_size (const jerry_value_t value);
jerry_size_t jerry_get_utf8_string_size (const jerry_value_t value);
jerry_length_t jerry_get_string_length (const jerry_value_t value);
jerry_length_t jerry_get_utf8_string_length (const jerry_value_t value);
jerry_size_t jerry_string_to_char_buffer (const jerry_value_t value, jerry_char_t *buffer_p, jerry_size_t buffer_size);
jerry_size_t jerry_string_to_utf8_char_buffer (const jerry_value_t value,
                                               jerry_char_t *buffer_p,
                                               jerry_size_t buffer_size);
jerry_size_t jerry_substring_to_char_buffer (const jerry_value_t value,
                                             jerry_length_t start_pos,
                                             jerry_length_t end_pos,
                                             jerry_char_t *buffer_p,
                                             jerry_size_t buffer_size);
jerry_size_t jerry_substring_to_utf8_char_buffer (const jerry_value_t value,
                                                  jerry_length_t start_pos,
                                                  jerry_length_t end_pos,
                                                  jerry_char_t *buffer_p,
                                                  jerry_size_t buffer_size);

/**
 * Functions for array object values.
 */
uint32_t jerry_get_array_length (const jerry_value_t value);

/**
 * Converters of 'jerry_value_t'.
 */
bool jerry_value_to_boolean (const jerry_value_t value);
jerry_value_t jerry_value_to_number (const jerry_value_t value);
jerry_value_t jerry_value_to_object (const jerry_value_t value);
jerry_value_t jerry_value_to_primitive (const jerry_value_t value);
jerry_value_t jerry_value_to_string (const jerry_value_t value);

/**
 * Acquire types with reference counter (increase the references).
 */
jerry_value_t jerry_acquire_value (jerry_value_t value);

/**
 * Release the referenced values.
 */
void jerry_release_value (jerry_value_t value);

/**
 * Create functions of API values.
 */
jerry_value_t jerry_create_array (uint32_t size);
jerry_value_t jerry_create_boolean (bool value);
jerry_value_t jerry_create_error (jerry_error_t error_type, const jerry_char_t *message_p);
jerry_value_t jerry_create_error_sz (jerry_error_t error_type, const jerry_char_t *message_p,
                                     jerry_size_t message_size);
jerry_value_t jerry_create_external_function (jerry_external_handler_t handler_p);
jerry_value_t jerry_create_number (double value);
jerry_value_t jerry_create_number_infinity (bool sign);
jerry_value_t jerry_create_number_nan (void);
jerry_value_t jerry_create_null (void);
jerry_value_t jerry_create_object (void);
jerry_value_t jerry_create_promise (void);
jerry_value_t jerry_create_regexp (const jerry_char_t *pattern, uint16_t flags);
jerry_value_t jerry_create_regexp_sz (const jerry_char_t *pattern, jerry_size_t pattern_size, uint16_t flags);
jerry_value_t jerry_create_string_from_utf8 (const jerry_char_t *str_p);
jerry_value_t jerry_create_string_sz_from_utf8 (const jerry_char_t *str_p, jerry_size_t str_size);
jerry_value_t jerry_create_string (const jerry_char_t *str_p);
jerry_value_t jerry_create_string_sz (const jerry_char_t *str_p, jerry_size_t str_size);
jerry_value_t jerry_create_symbol (const jerry_value_t value);
jerry_value_t jerry_create_undefined (void);

/**
 * General API functions of JS objects.
 */
jerry_value_t jerry_has_property (const jerry_value_t obj_val, const jerry_value_t prop_name_val);
jerry_value_t jerry_has_own_property (const jerry_value_t obj_val, const jerry_value_t prop_name_val);
bool jerry_delete_property (const jerry_value_t obj_val, const jerry_value_t prop_name_val);
bool jerry_delete_property_by_index (const jerry_value_t obj_val, uint32_t index);

jerry_value_t jerry_get_property (const jerry_value_t obj_val, const jerry_value_t prop_name_val);
jerry_value_t jerry_get_property_by_index (const jerry_value_t obj_val, uint32_t index);
jerry_value_t jerry_set_property (const jerry_value_t obj_val, const jerry_value_t prop_name_val,
                                  const jerry_value_t value_to_set);
jerry_value_t jerry_set_property_by_index (const jerry_value_t obj_val, uint32_t index,
                                           const jerry_value_t value_to_set);

void jerry_init_property_descriptor_fields (jerry_property_descriptor_t *prop_desc_p);
jerry_value_t jerry_define_own_property (const jerry_value_t obj_val,
                                         const jerry_value_t prop_name_val,
                                         const jerry_property_descriptor_t *prop_desc_p);

bool jerry_get_own_property_descriptor (const jerry_value_t obj_val,
                                        const jerry_value_t prop_name_val,
                                        jerry_property_descriptor_t *prop_desc_p);
void jerry_free_property_descriptor_fields (const jerry_property_descriptor_t *prop_desc_p);

jerry_value_t jerry_call_function (const jerry_value_t func_obj_val, const jerry_value_t this_val,
                                   const jerry_value_t args_p[], jerry_size_t args_count);
jerry_value_t jerry_construct_object (const jerry_value_t func_obj_val, const jerry_value_t args_p[],
                                      jerry_size_t args_count);

jerry_value_t jerry_get_object_keys (const jerry_value_t obj_val);
jerry_value_t jerry_get_prototype (const jerry_value_t obj_val);
jerry_value_t jerry_set_prototype (const jerry_value_t obj_val, const jerry_value_t proto_obj_val);

bool jerry_get_object_native_pointer (const jerry_value_t obj_val,
                                      void **out_native_pointer_p,
                                      const jerry_object_native_info_t **out_pointer_info_p);
void jerry_set_object_native_pointer (const jerry_value_t obj_val,
                                      void *native_pointer_p,
                                      const jerry_object_native_info_t *native_info_p);

bool jerry_objects_foreach (jerry_objects_foreach_t foreach_p,
                            void *user_data);
bool jerry_objects_foreach_by_native_info (const jerry_object_native_info_t *native_info_p,
                                           jerry_objects_foreach_by_native_info_t foreach_p,
                                           void *user_data_p);

bool jerry_foreach_object_property (const jerry_value_t obj_val, jerry_object_property_foreach_t foreach_p,
                                    void *user_data_p);

/**
 * Promise resolve/reject functions.
 */
jerry_value_t jerry_resolve_or_reject_promise (jerry_value_t promise, jerry_value_t argument, bool is_resolve);

/**
 * Symbol functions.
 */
jerry_value_t jerry_get_symbol_descriptive_string (const jerry_value_t symbol);

/**
 * Input validator functions.
 */
bool jerry_is_valid_utf8_string (const jerry_char_t *utf8_buf_p, jerry_size_t buf_size);
bool jerry_is_valid_cesu8_string (const jerry_char_t *cesu8_buf_p, jerry_size_t buf_size);

/*
 * Dynamic memory management functions.
 */
void *jerry_heap_alloc (size_t size);
void jerry_heap_free (void *mem_p, size_t size);

/*
 * External context functions.
 */
jerry_context_t *jerry_create_context (uint32_t heap_size, jerry_context_alloc_t alloc, void *cb_data_p);

/**
 * Miscellaneous functions.
 */
void jerry_set_vm_exec_stop_callback (jerry_vm_exec_stop_callback_t stop_cb, void *user_p, uint32_t frequency);
jerry_value_t jerry_get_backtrace (uint32_t max_depth);

/**
 * Array buffer components.
 */
bool jerry_value_is_arraybuffer (const jerry_value_t value);
jerry_value_t jerry_create_arraybuffer (const jerry_length_t size);
jerry_value_t jerry_create_arraybuffer_external (const jerry_length_t size,
                                                 uint8_t *buffer_p,
                                                 jerry_object_native_free_callback_t free_cb);
jerry_length_t jerry_arraybuffer_write (const jerry_value_t value,
                                        jerry_length_t offset,
                                        const uint8_t *buf_p,
                                        jerry_length_t buf_size);
jerry_length_t jerry_arraybuffer_read (const jerry_value_t value,
                                       jerry_length_t offset,
                                       uint8_t *buf_p,
                                       jerry_length_t buf_size);
jerry_length_t jerry_get_arraybuffer_byte_length (const jerry_value_t value);
uint8_t *jerry_get_arraybuffer_pointer (const jerry_value_t value);


/**
 * TypedArray functions.
 */

/**
 * TypedArray types.
 */
typedef enum
{
  JERRY_TYPEDARRAY_INVALID = 0,
  JERRY_TYPEDARRAY_UINT8,
  JERRY_TYPEDARRAY_UINT8CLAMPED,
  JERRY_TYPEDARRAY_INT8,
  JERRY_TYPEDARRAY_UINT16,
  JERRY_TYPEDARRAY_INT16,
  JERRY_TYPEDARRAY_UINT32,
  JERRY_TYPEDARRAY_INT32,
  JERRY_TYPEDARRAY_FLOAT32,
  JERRY_TYPEDARRAY_FLOAT64,
} jerry_typedarray_type_t;


bool jerry_value_is_typedarray (jerry_value_t value);
jerry_value_t jerry_create_typedarray (jerry_typedarray_type_t type_name, jerry_length_t length);
jerry_value_t jerry_create_typedarray_for_arraybuffer_sz (jerry_typedarray_type_t type_name,
                                                          const jerry_value_t arraybuffer,
                                                          jerry_length_t byte_offset,
                                                          jerry_length_t length);
jerry_value_t jerry_create_typedarray_for_arraybuffer (jerry_typedarray_type_t type_name,
                                                       const jerry_value_t arraybuffer);
jerry_typedarray_type_t jerry_get_typedarray_type (jerry_value_t value);
jerry_length_t jerry_get_typedarray_length (jerry_value_t value);
jerry_value_t jerry_get_typedarray_buffer (jerry_value_t value,
                                           jerry_length_t *byte_offset,
                                           jerry_length_t *byte_length);
jerry_value_t jerry_json_parse (const jerry_char_t *string_p, jerry_size_t string_size);
jerry_value_t jerry_json_stringify (const jerry_value_t object_to_stringify);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* !JERRYSCRIPT_CORE_H */
#line 20 "/Users/jason/Desktop/Repo/zero-main/jerryscript/jerry-core/include/jerryscript.h"
#line 1 "/Users/jason/Desktop/Repo/zero-main/jerryscript/jerry-core/include/jerryscript-debugger.h"

#ifndef JERRYSCRIPT_DEBUGGER_H
#define JERRYSCRIPT_DEBUGGER_H

#line 1 "/Users/jason/Desktop/Repo/zero-main/jerryscript/jerry-core/include/jerryscript-port.h"

#ifndef JERRYSCRIPT_PORT_H
#define JERRYSCRIPT_PORT_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/** \addtogroup jerry_port Jerry engine port
 * @{
 */

/*
 * Termination Port API
 *
 * Note:
 *      It is questionable whether a library should be able to terminate an
 *      application. However, as of now, we only have the concept of completion
 *      code around jerry_parse and jerry_run. Most of the other API functions
 *      have no way of signaling an error. So, we keep the termination approach
 *      with this port function.
 */

/**
 * Error codes
 */
typedef enum
{
  ERR_OUT_OF_MEMORY = 10,
  ERR_REF_COUNT_LIMIT = 12,
  ERR_DISABLED_BYTE_CODE = 13,
  ERR_FAILED_INTERNAL_ASSERTION = 120
} jerry_fatal_code_t;

/**
 * Signal the port that jerry experienced a fatal failure from which it cannot
 * recover.
 *
 * @param code gives the cause of the error.
 *
 * Note:
 *      Jerry expects the function not to return.
 *
 * Example: a libc-based port may implement this with exit() or abort(), or both.
 */
void JERRY_ATTR_NORETURN jerry_port_fatal (jerry_fatal_code_t code);

/*
 *  I/O Port API
 */

/**
 * Jerry log levels. The levels are in severity order
 * where the most serious levels come first.
 */
typedef enum
{
  JERRY_LOG_LEVEL_ERROR,    /**< the engine will terminate after the message is printed */
  JERRY_LOG_LEVEL_WARNING,  /**< a request is aborted, but the engine continues its operation */
  JERRY_LOG_LEVEL_DEBUG,    /**< debug messages from the engine, low volume */
  JERRY_LOG_LEVEL_TRACE     /**< detailed info about engine internals, potentially high volume */
} jerry_log_level_t;

/**
 * Display or log a debug/error message. The function should implement a printf-like
 * interface, where the first argument specifies the log level
 * and the second argument specifies a format string on how to stringify the rest
 * of the parameter list.
 *
 * This function is only called with messages coming from the jerry engine as
 * the result of some abnormal operation or describing its internal operations
 * (e.g., data structure dumps or tracing info).
 *
 * It should be the port that decides whether error and debug messages are logged to
 * the console, or saved to a database or to a file.
 *
 * Example: a libc-based port may implement this with vfprintf(stderr) or
 * vfprintf(logfile), or both, depending on log level.
 *
 * Note:
 *      This port function is called by jerry-core when JERRY_ENABLE_LOGGING is
 *      defined. It is also common practice though to use this function in
 *      application code.
 */
void JERRY_ATTR_FORMAT (printf, 2, 3) jerry_port_log (jerry_log_level_t level, const char *format, ...);

/*
 * Date Port API
 */

/**
 * Get local time zone adjustment, in milliseconds, for the given timestamp.
 * The timestamp can be specified in either UTC or local time, depending on
 * the value of is_utc. Adding the value returned from this function to
 * a timestamp in UTC time should result in local time for the current time
 * zone, and subtracting it from a timestamp in local time should result in
 * UTC time.
 *
 * Ideally, this function should satisfy the stipulations applied to LocalTZA
 * in section 20.3.1.7 of the ECMAScript version 9.0 spec.
 *
 * See Also:
 *          ECMA-262 v9, 20.3.1.7
 *
 * Note:
 *      This port function is called by jerry-core when
 *      JERRY_BUILTIN_DATE is defined to 1. Otherwise this function is
 *      not used.
 *
 * @param unix_ms The unix timestamp we want an offset for, given in
 *                millisecond precision (could be now, in the future,
 *                or in the past). As with all unix timestamps, 0 refers to
 *                1970-01-01, a day is exactly 86 400 000 milliseconds, and
 *                leap seconds cause the same second to occur twice.
 * @param is_utc Is the given timestamp in UTC time? If false, it is in local
 *               time.
 *
 * @return milliseconds between local time and UTC for the given timestamp,
 *         if available
 *.        0 if not available / we are in UTC.
 */
double jerry_port_get_local_time_zone_adjustment (double unix_ms, bool is_utc);

/**
 * Get system time
 *
 * Note:
 *      This port function is called by jerry-core when
 *      JERRY_BUILTIN_DATE is defined to 1. It is also common practice
 *      in application code to use this function for the initialization of the
 *      random number generator.
 *
 * @return milliseconds since Unix epoch
 */
double jerry_port_get_current_time (void);

/**
 * Get the current context of the engine. Each port should provide its own
 * implementation of this interface.
 *
 * Note:
 *      This port function is called by jerry-core when
 *      JERRY_ENABLE_EXTERNAL_CONTEXT is defined. Otherwise this function is not
 *      used.
 *
 * @return the pointer to the engine context.
 */
struct jerry_context_t *jerry_port_get_current_context (void);

/**
 * Makes the process sleep for a given time.
 *
 * Note:
 *      This port function is called by jerry-core when JERRY_DEBUGGER is
 *      defined. Otherwise this function is not used.
 *
 * @param sleep_time milliseconds to sleep.
 */
void jerry_port_sleep (uint32_t sleep_time);

/**
 * Print a single character.
 *
 * Note:
 *      This port function is here so the jerry-ext components would have
 *      a common way to print out information.
 *      If possible do not use from the jerry-core.
 *
 * @param c the character to print.
 */
void jerry_port_print_char (char c);

/**
 * Open a source file and read its contents into a buffer.
 *
 * Note:
 *      This port function is called by jerry-core when JERRY_ES2015_MODULE_SYSTEM
 *      is enabled. The path is specified in the import statement's 'from "..."'
 *      section.
 *
 *  @param file_name_p Path that points to the EcmaScript file in the
 *                     filesystem.
 *  @param out_size_p The opened file's size in bytes.
 *
 *  @return the pointer to the buffer which contains the content of the file.
 */
uint8_t *jerry_port_read_source (const char *file_name_p, size_t *out_size_p);

/**
 * Frees the allocated buffer after the contents of the file are not needed
 * anymore.
 *
 * @param buffer_p The pointer the allocated buffer.
 */
void jerry_port_release_source (uint8_t *buffer_p);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* !JERRYSCRIPT_PORT_H */
#line 21 "/Users/jason/Desktop/Repo/zero-main/jerryscript/jerry-core/include/jerryscript-debugger.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/** \addtogroup jerry-debugger Jerry engine interface - Debugger feature
 * @{
 */

/**
 * JerryScript debugger protocol version.
 */
#define JERRY_DEBUGGER_VERSION (9)

/**
 * Types for the client source wait and run method.
 */
typedef enum
{
  JERRY_DEBUGGER_SOURCE_RECEIVE_FAILED = 0, /**< source is not received */
  JERRY_DEBUGGER_SOURCE_RECEIVED = 1, /**< a source has been received */
  JERRY_DEBUGGER_SOURCE_END = 2, /**< the end of the sources signal received */
  JERRY_DEBUGGER_CONTEXT_RESET_RECEIVED, /**< the context reset request has been received */
} jerry_debugger_wait_for_source_status_t;

/**
 * Callback for jerry_debugger_wait_and_run_client_source
 *
 * The callback receives the resource name, source code and a user pointer.
 *
 * @return this value is passed back by jerry_debugger_wait_and_run_client_source
 */
typedef jerry_value_t (*jerry_debugger_wait_for_source_callback_t) (const jerry_char_t *resource_name_p,
                                                                    size_t resource_name_size,
                                                                    const jerry_char_t *source_p,
                                                                    size_t source_size, void *user_p);

/**
 * Engine debugger functions.
 */
bool jerry_debugger_is_connected (void);
void jerry_debugger_stop (void);
void jerry_debugger_continue (void);
void jerry_debugger_stop_at_breakpoint (bool enable_stop_at_breakpoint);
jerry_debugger_wait_for_source_status_t
jerry_debugger_wait_for_client_source (jerry_debugger_wait_for_source_callback_t callback_p,
                                       void *user_p, jerry_value_t *return_value);
void jerry_debugger_send_output (const jerry_char_t *buffer, jerry_size_t str_size);
void jerry_debugger_send_log (jerry_log_level_t level, const jerry_char_t *buffer, jerry_size_t str_size);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* !JERRYSCRIPT_DEBUGGER_H */
#line 21 "/Users/jason/Desktop/Repo/zero-main/jerryscript/jerry-core/include/jerryscript.h"
#line 1 "/Users/jason/Desktop/Repo/zero-main/jerryscript/jerry-core/include/jerryscript-snapshot.h"

#ifndef JERRYSCRIPT_SNAPSHOT_H
#define JERRYSCRIPT_SNAPSHOT_H


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/** \addtogroup jerry-snapshot Jerry engine interface - Snapshot feature
 * @{
 */

/**
 * Jerry snapshot format version.
 */
#define JERRY_SNAPSHOT_VERSION (22u)

/**
 * Flags for jerry_generate_snapshot and jerry_generate_function_snapshot.
 */
typedef enum
{
  JERRY_SNAPSHOT_SAVE_STATIC = (1u << 0), /**< static snapshot */
  JERRY_SNAPSHOT_SAVE_STRICT = (1u << 1), /**< strict mode code */
} jerry_generate_snapshot_opts_t;

/**
 * Flags for jerry_exec_snapshot_at and jerry_load_function_snapshot_at.
 */
typedef enum
{
  JERRY_SNAPSHOT_EXEC_COPY_DATA = (1u << 0), /**< copy snashot data */
  JERRY_SNAPSHOT_EXEC_ALLOW_STATIC = (1u << 1), /**< static snapshots allowed */
} jerry_exec_snapshot_opts_t;

/**
 * Snapshot functions.
 */
jerry_value_t jerry_generate_snapshot (const jerry_char_t *resource_name_p, size_t resource_name_length,
                                       const jerry_char_t *source_p, size_t source_size,
                                       uint32_t generate_snapshot_opts, uint32_t *buffer_p, size_t buffer_size);
jerry_value_t jerry_generate_function_snapshot (const jerry_char_t *resource_name_p, size_t resource_name_length,
                                                const jerry_char_t *source_p, size_t source_size,
                                                const jerry_char_t *args_p, size_t args_size,
                                                uint32_t generate_snapshot_opts, uint32_t *buffer_p,
                                                size_t buffer_size);

jerry_value_t jerry_exec_snapshot (const uint32_t *snapshot_p, size_t snapshot_size,
                                   size_t func_index, uint32_t exec_snapshot_opts);
jerry_value_t jerry_load_function_snapshot (const uint32_t *function_snapshot_p,
                                            const size_t function_snapshot_size,
                                            size_t func_index, uint32_t exec_snapshot_opts);

size_t jerry_merge_snapshots (const uint32_t **inp_buffers_p, size_t *inp_buffer_sizes_p, size_t number_of_snapshots,
                              uint32_t *out_buffer_p, size_t out_buffer_size, const char **error_p);
size_t jerry_get_literals_from_snapshot (const uint32_t *snapshot_p, size_t snapshot_size,
                                         jerry_char_t *lit_buf_p, size_t lit_buf_size, bool is_c_format);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* !JERRYSCRIPT_SNAPSHOT_H */
#line 22 "/Users/jason/Desktop/Repo/zero-main/jerryscript/jerry-core/include/jerryscript.h"

#endif /* !JERRYSCRIPT_H */

#ifndef PMPI_INCLUDED
#define PMPI_INCLUDED

/* A  type that allows us to have sentinel type values that are still
   valid */
#define ompi_fortran_bogus_type_t int

/* C type corresponding to FORTRAN INTEGER */
#define ompi_fortran_integer_t int

#define OMPI_DECLSPEC

#define PMPI_Fint ompi_fortran_integer_t
#define OMPI_MPI_AINT_TYPE ptrdiff_t
#define OMPI_MPI_OFFSET_TYPE long long
#define OMPI_MPI_COUNT_TYPE long long

#include <stddef.h>

#define OMPI_PREDEFINED_GLOBAL(type, global) ((type) ((void *) &(global)))

#if defined(c_plusplus) || defined(__cplusplus)
extern "C" {
#endif

/*
 * Typedefs
 */

typedef OMPI_MPI_AINT_TYPE PMPI_Aint;
typedef OMPI_MPI_OFFSET_TYPE PMPI_Offset;
typedef OMPI_MPI_COUNT_TYPE PMPI_Count;
typedef struct ompi_communicator_t *PMPI_Comm;
typedef struct ompi_datatype_t *PMPI_Datatype;
typedef struct ompi_errhandler_t *PMPI_Errhandler;
typedef struct ompi_file_t *PMPI_File;
typedef struct ompi_group_t *PMPI_Group;
typedef struct ompi_info_t *PMPI_Info;
typedef struct ompi_op_t *PMPI_Op;
typedef struct ompi_request_t *PMPI_Request;
typedef struct ompi_message_t *PMPI_Message;
typedef struct ompi_status_public_t PMPI_Status;
typedef struct ompi_win_t *PMPI_Win;
typedef struct mca_base_var_enum_t *PMPI_T_enum;
typedef struct ompi_mpit_cvar_handle_t *PMPI_T_cvar_handle;
typedef struct mca_base_pvar_handle_t *PMPI_T_pvar_handle;
typedef struct mca_base_pvar_session_t *PMPI_T_pvar_session;

/*
 * PMPI_Status
 */
struct ompi_status_public_t {
    /* These fields are publicly defined in the MPI specification.
       User applications may freely read from these fields. */
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
    /* The following two fields are internal to the Open MPI
       implementation and should not be accessed by MPI applications.
       They are subject to change at any time.  These are not the
       droids you're looking for. */
    int _cancelled;
    size_t _ucount;
};
typedef struct ompi_status_public_t ompi_status_public_t;

/*
 * User typedefs
 */
typedef int (PMPI_Datarep_extent_function)(PMPI_Datatype, PMPI_Aint *, void *);
typedef int (PMPI_Datarep_conversion_function)(void *, PMPI_Datatype,
                                              int, void *, PMPI_Offset, void *);
typedef void (PMPI_Comm_errhandler_function)(PMPI_Comm *, int *, ...);

    /* This is a little hackish, but errhandler.h needs space for a
       PMPI_File_errhandler_fn.  While it could just be removed, this
       allows us to maintain a stable ABI within OMPI, at least for
       apps that don't use MPI I/O. */
typedef void (ompi_file_errhandler_fn)(PMPI_File *, int *, ...);
typedef void (PMPI_Win_errhandler_function)(PMPI_Win *, int *, ...);
typedef void (PMPI_User_function)(void *, void *, int *, PMPI_Datatype *);
typedef int (PMPI_Comm_copy_attr_function)(PMPI_Comm, int, void *,
                                            void *, void *, int *);
typedef int (PMPI_Comm_delete_attr_function)(PMPI_Comm, int, void *, void *);
typedef int (PMPI_Type_copy_attr_function)(PMPI_Datatype, int, void *,
                                            void *, void *, int *);
typedef int (PMPI_Type_delete_attr_function)(PMPI_Datatype, int,
                                              void *, void *);
typedef int (PMPI_Win_copy_attr_function)(PMPI_Win, int, void *,
                                           void *, void *, int *);
typedef int (PMPI_Win_delete_attr_function)(PMPI_Win, int, void *, void *);
typedef int (PMPI_Grequest_query_function)(void *, PMPI_Status *);
typedef int (PMPI_Grequest_free_function)(void *);
typedef int (PMPI_Grequest_cancel_function)(void *, int);

/*
 * Miscellaneous constants
 */
#define PMPI_ANY_SOURCE         -1                      /* match any source rank */
#define PMPI_PROC_NULL          -2                      /* rank of null process */
#define PMPI_ROOT               -4                      /* special value for intercomms */
#define PMPI_ANY_TAG            -1                      /* match any message tag */
#define PMPI_MAX_PROCESSOR_NAME OPAL_MAX_PROCESSOR_NAME /* max proc. name length */
#define PMPI_MAX_ERROR_STRING   OPAL_MAX_ERROR_STRING   /* max error message length */
#define PMPI_MAX_OBJECT_NAME    OPAL_MAX_OBJECT_NAME    /* max object name length */
#define PMPI_MAX_LIBRARY_VERSION_STRING 256             /* max length of library version string */
#define PMPI_UNDEFINED          -32766                  /* undefined stuff */
#define PMPI_DIST_GRAPH         3                       /* dist graph topology */
#define PMPI_CART               1                       /* cartesian topology */
#define PMPI_GRAPH              2                       /* graph topology */
#define PMPI_KEYVAL_INVALID     -1                      /* invalid key value */

/*
 * More constants
 */
#define PMPI_UNWEIGHTED           ((int *) 2)           /* unweighted graph */
#define PMPI_WEIGHTS_EMPTY        ((int *) 3)           /* empty weights */
#define PMPI_BOTTOM               ((void *) 0)          /* base reference address */
#define PMPI_IN_PLACE             ((void *) 1)          /* in place buffer */
#define PMPI_BSEND_OVERHEAD       128                   /* size of bsend header + ptr */
#define PMPI_MAX_INFO_KEY         OPAL_MAX_INFO_KEY     /* max info key length */
#define PMPI_MAX_INFO_VAL         OPAL_MAX_INFO_VAL     /* max info value length */
#define PMPI_ARGV_NULL            ((char **) 0)         /* NULL argument vector */
#define PMPI_ARGVS_NULL           ((char ***) 0)        /* NULL argument vectors */
#define PMPI_ERRCODES_IGNORE      ((int *) 0)           /* don't return error codes */
#define PMPI_MAX_PORT_NAME        OPAL_MAX_PORT_NAME    /* max port name length */
#define PMPI_ORDER_C              0                     /* C row major order */
#define PMPI_ORDER_FORTRAN        1                     /* Fortran column major order */
#define PMPI_DISTRIBUTE_BLOCK     0                     /* block distribution */
#define PMPI_DISTRIBUTE_CYCLIC    1                     /* cyclic distribution */
#define PMPI_DISTRIBUTE_NONE      2                     /* not distributed */
#define PMPI_DISTRIBUTE_DFLT_DARG (-1)                  /* default distribution arg */

/*
 * Since these values are arbitrary to Open MPI, we might as well make
 * them the same as ROMIO for ease of mapping.  These values taken
 * from ROMIO's mpio.h file.
 */
#define PMPI_MODE_CREATE              1  /* ADIO_CREATE */
#define PMPI_MODE_RDONLY              2  /* ADIO_RDONLY */
#define PMPI_MODE_WRONLY              4  /* ADIO_WRONLY  */
#define PMPI_MODE_RDWR                8  /* ADIO_RDWR  */
#define PMPI_MODE_DELETE_ON_CLOSE    16  /* ADIO_DELETE_ON_CLOSE */
#define PMPI_MODE_UNIQUE_OPEN        32  /* ADIO_UNIQUE_OPEN */
#define PMPI_MODE_EXCL               64  /* ADIO_EXCL */
#define PMPI_MODE_APPEND            128  /* ADIO_APPEND */
#define PMPI_MODE_SEQUENTIAL        256  /* ADIO_SEQUENTIAL */

#define PMPI_DISPLACEMENT_CURRENT   -54278278

#define PMPI_SEEK_SET               600
#define PMPI_SEEK_CUR               602
#define PMPI_SEEK_END               604

/* Max data representation length */
#define PMPI_MAX_DATAREP_STRING OPAL_MAX_DATAREP_STRING

/*
 * MPI-2 One-Sided Communications asserts
 */
#define PMPI_MODE_NOCHECK             1
#define PMPI_MODE_NOPRECEDE           2
#define PMPI_MODE_NOPUT               4
#define PMPI_MODE_NOSTORE             8
#define PMPI_MODE_NOSUCCEED          16

#define PMPI_LOCK_EXCLUSIVE           1
#define PMPI_LOCK_SHARED              2

#define PMPI_WIN_FLAVOR_CREATE        1
#define PMPI_WIN_FLAVOR_ALLOCATE      2
#define PMPI_WIN_FLAVOR_DYNAMIC       3
#define PMPI_WIN_FLAVOR_SHARED        4

#define PMPI_WIN_UNIFIED              0
#define PMPI_WIN_SEPARATE             1

/*
 * Predefined attribute keyvals
 *
 * DO NOT CHANGE THE ORDER WITHOUT ALSO CHANGING THE ORDER IN
 * src/attribute/attribute_predefined.c and mpif.h.in.
 */
enum {
    /* MPI-1 */
    PMPI_TAG_UB,
    PMPI_HOST,
    PMPI_IO,
    PMPI_WTIME_IS_GLOBAL,

    /* MPI-2 */
    PMPI_APPNUM,
    PMPI_LASTUSEDCODE,
    PMPI_UNIVERSE_SIZE,
    PMPI_WIN_BASE,
    PMPI_WIN_SIZE,
    PMPI_WIN_DISP_UNIT,
    PMPI_WIN_CREATE_FLAVOR,
    PMPI_WIN_MODEL,

    /* Even though these four are IMPI attributes, they need to be there
       for all MPI jobs */
    IMPI_CLIENT_SIZE,
    IMPI_CLIENT_COLOR,
    IMPI_HOST_SIZE,
    IMPI_HOST_COLOR
};

/*
 * Error classes and codes
 * Do not change the values of these without also modifying mpif.h.in.
 */
#define PMPI_SUCCESS                   0
#define PMPI_ERR_BUFFER                1
#define PMPI_ERR_COUNT                 2
#define PMPI_ERR_TYPE                  3
#define PMPI_ERR_TAG                   4
#define PMPI_ERR_COMM                  5
#define PMPI_ERR_RANK                  6
#define PMPI_ERR_REQUEST               7
#define PMPI_ERR_ROOT                  8
#define PMPI_ERR_GROUP                 9
#define PMPI_ERR_OP                    10
#define PMPI_ERR_TOPOLOGY              11
#define PMPI_ERR_DIMS                  12
#define PMPI_ERR_ARG                   13
#define PMPI_ERR_UNKNOWN               14
#define PMPI_ERR_TRUNCATE              15
#define PMPI_ERR_OTHER                 16
#define PMPI_ERR_INTERN                17
#define PMPI_ERR_IN_STATUS             18
#define PMPI_ERR_PENDING               19
#define PMPI_ERR_ACCESS                20
#define PMPI_ERR_AMODE                 21
#define PMPI_ERR_ASSERT                22
#define PMPI_ERR_BAD_FILE              23
#define PMPI_ERR_BASE                  24
#define PMPI_ERR_CONVERSION            25
#define PMPI_ERR_DISP                  26
#define PMPI_ERR_DUP_DATAREP           27
#define PMPI_ERR_FILE_EXISTS           28
#define PMPI_ERR_FILE_IN_USE           29
#define PMPI_ERR_FILE                  30
#define PMPI_ERR_INFO_KEY              31
#define PMPI_ERR_INFO_NOKEY            32
#define PMPI_ERR_INFO_VALUE            33
#define PMPI_ERR_INFO                  34
#define PMPI_ERR_IO                    35
#define PMPI_ERR_KEYVAL                36
#define PMPI_ERR_LOCKTYPE              37
#define PMPI_ERR_NAME                  38
#define PMPI_ERR_NO_MEM                39
#define PMPI_ERR_NOT_SAME              40
#define PMPI_ERR_NO_SPACE              41
#define PMPI_ERR_NO_SUCH_FILE          42
#define PMPI_ERR_PORT                  43
#define PMPI_ERR_QUOTA                 44
#define PMPI_ERR_READ_ONLY             45
#define PMPI_ERR_RMA_CONFLICT          46
#define PMPI_ERR_RMA_SYNC              47
#define PMPI_ERR_SERVICE               48
#define PMPI_ERR_SIZE                  49
#define PMPI_ERR_SPAWN                 50
#define PMPI_ERR_UNSUPPORTED_DATAREP   51
#define PMPI_ERR_UNSUPPORTED_OPERATION 52
#define PMPI_ERR_WIN                   53
#define PMPI_T_ERR_MEMORY              54
#define PMPI_T_ERR_NOT_INITIALIZED     55
#define PMPI_T_ERR_CANNOT_INIT         56
#define PMPI_T_ERR_INVALID_INDEX       57
#define PMPI_T_ERR_INVALID_ITEM        58
#define PMPI_T_ERR_INVALID_HANDLE      59
#define PMPI_T_ERR_OUT_OF_HANDLES      60
#define PMPI_T_ERR_OUT_OF_SESSIONS     61
#define PMPI_T_ERR_INVALID_SESSION     62
#define PMPI_T_ERR_CVAR_SET_NOT_NOW    63
#define PMPI_T_ERR_CVAR_SET_NEVER      64
#define PMPI_T_ERR_PVAR_NO_STARTSTOP   65
#define PMPI_T_ERR_PVAR_NO_WRITE       66
#define PMPI_T_ERR_PVAR_NO_ATOMIC      67
#define PMPI_ERR_RMA_RANGE             68
#define PMPI_ERR_RMA_ATTACH            69
#define PMPI_ERR_RMA_FLAVOR            70
#define PMPI_ERR_RMA_SHARED            71
#define PMPI_T_ERR_INVALID             72
#define PMPI_T_ERR_INVALID_NAME        73

/* Per MPI-3 p349 47, PMPI_ERR_LASTCODE must be >= the last predefined
   PMPI_ERR_<foo> code. Set the last code to allow some room for adding
   error codes without breaking ABI. */
#define PMPI_ERR_LASTCODE              92

/*
 * Comparison results.  Don't change the order of these, the group
 * comparison functions rely on it.
 * Do not change the order of these without also modifying mpif.h.in.
 */
enum {
  PMPI_IDENT,
  PMPI_CONGRUENT,
  PMPI_SIMILAR,
  PMPI_UNEQUAL
};

/*
 * PMPI_Init_thread constants
 * Do not change the order of these without also modifying mpif.h.in.
 */
enum {
  PMPI_THREAD_SINGLE,
  PMPI_THREAD_FUNNELED,
  PMPI_THREAD_SERIALIZED,
  PMPI_THREAD_MULTIPLE
};

/*
 * Datatype combiners.
 * Do not change the order of these without also modifying mpif.h.in.
 * (see also mpif-common.h.fin).
 */
enum {
  PMPI_COMBINER_NAMED,
  PMPI_COMBINER_DUP,
  PMPI_COMBINER_CONTIGUOUS,
  PMPI_COMBINER_VECTOR,
  PMPI_COMBINER_HVECTOR_INTEGER,
  PMPI_COMBINER_HVECTOR,
  PMPI_COMBINER_INDEXED,
  PMPI_COMBINER_HINDEXED_INTEGER,
  PMPI_COMBINER_HINDEXED,
  PMPI_COMBINER_INDEXED_BLOCK,
  PMPI_COMBINER_STRUCT_INTEGER,
  PMPI_COMBINER_STRUCT,
  PMPI_COMBINER_SUBARRAY,
  PMPI_COMBINER_DARRAY,
  PMPI_COMBINER_F90_REAL,
  PMPI_COMBINER_F90_COMPLEX,
  PMPI_COMBINER_F90_INTEGER,
  PMPI_COMBINER_RESIZED,
  PMPI_COMBINER_HINDEXED_BLOCK
};

/*
 * Communicator split type constants.
 * Do not change the order of these without also modifying mpif.h.in
 * (see also mpif-common.h.fin).
 */
enum {
  PMPI_COMM_TYPE_SHARED,
  OMPI_COMM_TYPE_HWTHREAD,
  OMPI_COMM_TYPE_CORE,
  OMPI_COMM_TYPE_L1CACHE,
  OMPI_COMM_TYPE_L2CACHE,
  OMPI_COMM_TYPE_L3CACHE,
  OMPI_COMM_TYPE_SOCKET,
  OMPI_COMM_TYPE_NUMA,
  OMPI_COMM_TYPE_BOARD,
  OMPI_COMM_TYPE_HOST,
  OMPI_COMM_TYPE_CU,
  OMPI_COMM_TYPE_CLUSTER
};
#define OMPI_COMM_TYPE_NODE PMPI_COMM_TYPE_SHARED

/*
 * MPIT Verbosity Levels
 */
enum {
  PMPI_T_VERBOSITY_USER_BASIC,
  PMPI_T_VERBOSITY_USER_DETAIL,
  PMPI_T_VERBOSITY_USER_ALL,
  PMPI_T_VERBOSITY_TUNER_BASIC,
  PMPI_T_VERBOSITY_TUNER_DETAIL,
  PMPI_T_VERBOSITY_TUNER_ALL,
  PMPI_T_VERBOSITY_MPIDEV_BASIC,
  PMPI_T_VERBOSITY_MPIDEV_DETAIL,
  PMPI_T_VERBOSITY_MPIDEV_ALL
};

/*
 * MPIT Scopes
 */
enum {
  PMPI_T_SCOPE_CONSTANT,
  PMPI_T_SCOPE_READONLY,
  PMPI_T_SCOPE_LOCAL,
  PMPI_T_SCOPE_GROUP,
  PMPI_T_SCOPE_GROUP_EQ,
  PMPI_T_SCOPE_ALL,
  PMPI_T_SCOPE_ALL_EQ
};

/*
 * MPIT Object Binding
 */
enum {
  PMPI_T_BIND_NO_OBJECT,
  PMPI_T_BIND_MPI_COMM,
  PMPI_T_BIND_MPI_DATATYPE,
  PMPI_T_BIND_MPI_ERRHANDLER,
  PMPI_T_BIND_MPI_FILE,
  PMPI_T_BIND_MPI_GROUP,
  PMPI_T_BIND_MPI_OP,
  PMPI_T_BIND_MPI_REQUEST,
  PMPI_T_BIND_MPI_WIN,
  PMPI_T_BIND_MPI_MESSAGE,
  PMPI_T_BIND_MPI_INFO
};

/*
 * MPIT pvar classes
 */
enum {
  PMPI_T_PVAR_CLASS_STATE,
  PMPI_T_PVAR_CLASS_LEVEL,
  PMPI_T_PVAR_CLASS_SIZE,
  PMPI_T_PVAR_CLASS_PERCENTAGE,
  PMPI_T_PVAR_CLASS_HIGHWATERMARK,
  PMPI_T_PVAR_CLASS_LOWWATERMARK,
  PMPI_T_PVAR_CLASS_COUNTER,
  PMPI_T_PVAR_CLASS_AGGREGATE,
  PMPI_T_PVAR_CLASS_TIMER,
  PMPI_T_PVAR_CLASS_GENERIC
};

/*
 * NULL handles
 */
#define PMPI_GROUP_NULL OMPI_PREDEFINED_GLOBAL(PMPI_Group, ompi_mpi_group_null)
#define PMPI_COMM_NULL OMPI_PREDEFINED_GLOBAL(PMPI_Comm, ompi_mpi_comm_null)
#define PMPI_REQUEST_NULL OMPI_PREDEFINED_GLOBAL(PMPI_Request, ompi_request_null)
#define PMPI_MESSAGE_NULL OMPI_PREDEFINED_GLOBAL(PMPI_Message, ompi_message_null)
#define PMPI_OP_NULL OMPI_PREDEFINED_GLOBAL(PMPI_Op, ompi_mpi_op_null)
#define PMPI_ERRHANDLER_NULL OMPI_PREDEFINED_GLOBAL(PMPI_Errhandler, ompi_mpi_errhandler_null)
#define PMPI_INFO_NULL OMPI_PREDEFINED_GLOBAL(PMPI_Info, ompi_mpi_info_null)
#define PMPI_WIN_NULL OMPI_PREDEFINED_GLOBAL(PMPI_Win, ompi_mpi_win_null)
#define PMPI_FILE_NULL OMPI_PREDEFINED_GLOBAL(PMPI_File, ompi_mpi_file_null)
#define PMPI_T_ENUM_NULL ((PMPI_T_enum) NULL)

/*
 * PMPI_INFO_ENV handle
 */
#define PMPI_INFO_ENV OMPI_PREDEFINED_GLOBAL(PMPI_Info, ompi_mpi_info_env)

#define PMPI_STATUS_IGNORE ((PMPI_Status *) 0)
#define PMPI_STATUSES_IGNORE ((PMPI_Status *) 0)

/*
 * Special PMPI_T handles
 */
#define PMPI_T_PVAR_ALL_HANDLES ((PMPI_T_pvar_handle) -1)
#define PMPI_T_PVAR_HANDLE_NULL ((PMPI_T_pvar_handle) 0)
#define PMPI_T_PVAR_SESSION_NULL ((PMPI_T_pvar_session) 0)
#define PMPI_T_CVAR_HANDLE_NULL ((PMPI_T_cvar_handle) 0)

/* MPI-2 specifies that the name "PMPI_TYPE_NULL_DELETE_FN" (and all
   related friends) must be accessible in C, C++, and Fortran. This is
   unworkable if the back-end Fortran compiler uses all caps for its
   linker symbol convention -- it results in two functions with
   different signatures that have the same name (i.e., both C and
   Fortran use the symbol PMPI_TYPE_NULL_DELETE_FN).  So we have to
   #define the C names to be something else, so that they names are
   *accessed* through PMPI_TYPE_NULL_DELETE_FN, but their actual symbol
   name is different.

   However, this file is included when the fortran wrapper functions
   are compiled in Open MPI, so we do *not* want these #defines in
   this case (i.e., we need the Fortran wrapper function to be
   compiled as PMPI_TYPE_NULL_DELETE_FN).  So add some #if kinds of
   protection for this case. */

#if !defined(OMPI_COMPILING_FORTRAN_WRAPPERS)

#define PMPI_TYPE_NULL_DELETE_FN OMPI_C_MPI_TYPE_NULL_DELETE_FN
#define PMPI_TYPE_NULL_COPY_FN OMPI_C_MPI_TYPE_NULL_COPY_FN
#define PMPI_TYPE_DUP_FN OMPI_C_MPI_TYPE_DUP_FN

#define PMPI_COMM_NULL_DELETE_FN OMPI_C_MPI_COMM_NULL_DELETE_FN
#define PMPI_COMM_NULL_COPY_FN OMPI_C_MPI_COMM_NULL_COPY_FN
#define PMPI_COMM_DUP_FN OMPI_C_MPI_COMM_DUP_FN

#define PMPI_WIN_NULL_DELETE_FN OMPI_C_MPI_WIN_NULL_DELETE_FN
#define PMPI_WIN_NULL_COPY_FN OMPI_C_MPI_WIN_NULL_COPY_FN
#define PMPI_WIN_DUP_FN OMPI_C_MPI_WIN_DUP_FN

/* PMPI_CONVERSION_FN_NULL is a sentinel value, but it has to be large
   enough to be the same size as a valid function pointer.  It
   therefore shares many characteristics between Fortran constants and
   Fortran sentinel functions.  For example, it shares the problem of
   having Fortran compilers have all-caps versions of the symbols that
   must be able to be present, and therefore has to be in this
   conditional block in mpi.h. */
#define PMPI_CONVERSION_FN_NULL ((PMPI_Datarep_conversion_function*) 0)
#endif

OMPI_DECLSPEC int OMPI_C_MPI_TYPE_NULL_DELETE_FN( PMPI_Datatype datatype,
                                                  int type_keyval,
                                                  void* attribute_val_out,
                                                  void* extra_state );
OMPI_DECLSPEC int OMPI_C_MPI_TYPE_NULL_COPY_FN( PMPI_Datatype datatype,
                                                int type_keyval,
                                                void* extra_state,
                                                void* attribute_val_in,
                                                void* attribute_val_out,
                                                int* flag );
OMPI_DECLSPEC int OMPI_C_MPI_TYPE_DUP_FN( PMPI_Datatype datatype,
                                          int type_keyval,
                                          void* extra_state,
                                          void* attribute_val_in,
                                          void* attribute_val_out,
                                          int* flag );
OMPI_DECLSPEC int OMPI_C_MPI_COMM_NULL_DELETE_FN( PMPI_Comm comm,
                                                  int comm_keyval,
                                                  void* attribute_val_out,
                                                  void* extra_state );
OMPI_DECLSPEC int OMPI_C_MPI_COMM_NULL_COPY_FN( PMPI_Comm comm,
                                                int comm_keyval,
                                                void* extra_state,
                                                void* attribute_val_in,
                                                void* attribute_val_out,
                                                int* flag );
OMPI_DECLSPEC int OMPI_C_MPI_COMM_DUP_FN( PMPI_Comm comm, int comm_keyval,
                                          void* extra_state,
                                          void* attribute_val_in,
                                          void* attribute_val_out,
                                          int* flag );
OMPI_DECLSPEC int OMPI_C_MPI_WIN_NULL_DELETE_FN( PMPI_Win window,
                                                 int win_keyval,
                                                 void* attribute_val_out,
                                                 void* extra_state );
OMPI_DECLSPEC int OMPI_C_MPI_WIN_NULL_COPY_FN( PMPI_Win window, int win_keyval,
                                               void* extra_state,
                                               void* attribute_val_in,
                                               void* attribute_val_out,
                                               int* flag );
OMPI_DECLSPEC int OMPI_C_MPI_WIN_DUP_FN( PMPI_Win window, int win_keyval,
                                         void* extra_state,
                                         void* attribute_val_in,
                                         void* attribute_val_out,
                                         int* flag );

/*
 * External variables
 *
 * The below externs use the ompi_predefined_xxx_t structures to maintain
 * back compatibility between MPI library versions.
 * See ompi/communicator/communicator.h comments with struct ompi_communicator_t
 * for full explanation why we chose to use the ompi_predefined_xxx_t structure.
 */
OMPI_DECLSPEC extern struct ompi_predefined_communicator_t ompi_mpi_comm_world;
OMPI_DECLSPEC extern struct ompi_predefined_communicator_t ompi_mpi_comm_self;
OMPI_DECLSPEC extern struct ompi_predefined_communicator_t ompi_mpi_comm_null;

OMPI_DECLSPEC extern struct ompi_predefined_group_t ompi_mpi_group_empty;
OMPI_DECLSPEC extern struct ompi_predefined_group_t ompi_mpi_group_null;

OMPI_DECLSPEC extern struct ompi_predefined_request_t ompi_request_null;

OMPI_DECLSPEC extern struct ompi_predefined_message_t ompi_message_null;
OMPI_DECLSPEC extern struct ompi_predefined_message_t ompi_message_no_proc;

OMPI_DECLSPEC extern struct ompi_predefined_op_t ompi_mpi_op_null;
OMPI_DECLSPEC extern struct ompi_predefined_op_t ompi_mpi_op_min;
OMPI_DECLSPEC extern struct ompi_predefined_op_t ompi_mpi_op_max;
OMPI_DECLSPEC extern struct ompi_predefined_op_t ompi_mpi_op_sum;
OMPI_DECLSPEC extern struct ompi_predefined_op_t ompi_mpi_op_prod;
OMPI_DECLSPEC extern struct ompi_predefined_op_t ompi_mpi_op_land;
OMPI_DECLSPEC extern struct ompi_predefined_op_t ompi_mpi_op_band;
OMPI_DECLSPEC extern struct ompi_predefined_op_t ompi_mpi_op_lor;
OMPI_DECLSPEC extern struct ompi_predefined_op_t ompi_mpi_op_bor;
OMPI_DECLSPEC extern struct ompi_predefined_op_t ompi_mpi_op_lxor;
OMPI_DECLSPEC extern struct ompi_predefined_op_t ompi_mpi_op_bxor;
OMPI_DECLSPEC extern struct ompi_predefined_op_t ompi_mpi_op_maxloc;
OMPI_DECLSPEC extern struct ompi_predefined_op_t ompi_mpi_op_minloc;
OMPI_DECLSPEC extern struct ompi_predefined_op_t ompi_mpi_op_replace;
OMPI_DECLSPEC extern struct ompi_predefined_op_t ompi_mpi_op_no_op;


OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_datatype_null;

OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_char;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_signed_char;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_unsigned_char;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_byte;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_short;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_unsigned_short;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_int;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_unsigned;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_long;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_unsigned_long;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_long_long_int;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_unsigned_long_long;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_float;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_double;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_long_double;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_wchar;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_packed;

/*
 * Following are the C++/C99 datatypes
 */
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_cxx_bool;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_cxx_cplex;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_cxx_dblcplex;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_cxx_ldblcplex;

/*
 * Following are the Fortran datatypes
 */
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_logical;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_character;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_integer;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_real;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_dblprec;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_cplex;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_dblcplex;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_ldblcplex;

/* Aggregate struct datatypes are not const */
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_2int;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_2integer;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_2real;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_2dblprec;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_2cplex;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_2dblcplex;

OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_float_int;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_double_int;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_longdbl_int;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_short_int;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_long_int;

/* Optional MPI2 datatypes, always declared and defined, but not "exported" as PMPI_LOGICAL1 */
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_logical1;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_logical2;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_logical4;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_logical8;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_integer1;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_integer2;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_integer4;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_integer8;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_integer16;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_real2;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_real4;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_real8;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_real16;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_complex8;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_complex16;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_complex32;

/* New datatypes from the MPI 2.2 standard */
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_int8_t;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_uint8_t;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_int16_t;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_uint16_t;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_int32_t;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_uint32_t;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_int64_t;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_uint64_t;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_aint;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_offset;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_count;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_c_bool;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_c_float_complex;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_c_double_complex;
OMPI_DECLSPEC extern struct ompi_predefined_datatype_t ompi_mpi_c_long_double_complex;

OMPI_DECLSPEC extern struct ompi_predefined_errhandler_t ompi_mpi_errhandler_null;
OMPI_DECLSPEC extern struct ompi_predefined_errhandler_t ompi_mpi_errors_are_fatal;
OMPI_DECLSPEC extern struct ompi_predefined_errhandler_t ompi_mpi_errors_return;

OMPI_DECLSPEC extern struct ompi_predefined_win_t ompi_mpi_win_null;
OMPI_DECLSPEC extern struct ompi_predefined_file_t ompi_mpi_file_null;

OMPI_DECLSPEC extern struct ompi_predefined_info_t ompi_mpi_info_null;
OMPI_DECLSPEC extern struct ompi_predefined_info_t ompi_mpi_info_env;

OMPI_DECLSPEC extern PMPI_Fint *PMPI_F_STATUS_IGNORE;
OMPI_DECLSPEC extern PMPI_Fint *PMPI_F_STATUSES_IGNORE;

#if !OMPI_OMIT_MPI1_COMPAT_DECLS
/*
 * Removed datatypes.  These datatypes are only available if Open MPI
 * was configured with --enable-mpi1-compatibility.
 *
 * These datatypes were formally removed from the MPI specification
 * and should no longer be used in MPI applications.
 */
#define PMPI_UB OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_ub)
#define PMPI_LB OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_lb)

#endif /* !OMPI_OMIT_MPI1_COMPAT_DECLS */

/*
 * MPI predefined handles
 */
#define PMPI_COMM_WORLD OMPI_PREDEFINED_GLOBAL( PMPI_Comm, ompi_mpi_comm_world)
#define PMPI_COMM_SELF OMPI_PREDEFINED_GLOBAL(PMPI_Comm, ompi_mpi_comm_self)

#define PMPI_GROUP_EMPTY OMPI_PREDEFINED_GLOBAL(PMPI_Group, ompi_mpi_group_empty)

#define PMPI_MESSAGE_NO_PROC OMPI_PREDEFINED_GLOBAL(PMPI_Message, ompi_message_no_proc)

#define PMPI_MAX OMPI_PREDEFINED_GLOBAL(PMPI_Op, ompi_mpi_op_max)
#define PMPI_MIN OMPI_PREDEFINED_GLOBAL(PMPI_Op, ompi_mpi_op_min)
#define PMPI_SUM OMPI_PREDEFINED_GLOBAL(PMPI_Op, ompi_mpi_op_sum)
#define PMPI_PROD OMPI_PREDEFINED_GLOBAL(PMPI_Op, ompi_mpi_op_prod)
#define PMPI_LAND OMPI_PREDEFINED_GLOBAL(PMPI_Op, ompi_mpi_op_land)
#define PMPI_BAND OMPI_PREDEFINED_GLOBAL(PMPI_Op, ompi_mpi_op_band)
#define PMPI_LOR OMPI_PREDEFINED_GLOBAL(PMPI_Op, ompi_mpi_op_lor)
#define PMPI_BOR OMPI_PREDEFINED_GLOBAL(PMPI_Op, ompi_mpi_op_bor)
#define PMPI_LXOR OMPI_PREDEFINED_GLOBAL(PMPI_Op, ompi_mpi_op_lxor)
#define PMPI_BXOR OMPI_PREDEFINED_GLOBAL(PMPI_Op, ompi_mpi_op_bxor)
#define PMPI_MAXLOC OMPI_PREDEFINED_GLOBAL(PMPI_Op, ompi_mpi_op_maxloc)
#define PMPI_MINLOC OMPI_PREDEFINED_GLOBAL(PMPI_Op, ompi_mpi_op_minloc)
#define PMPI_REPLACE OMPI_PREDEFINED_GLOBAL(PMPI_Op, ompi_mpi_op_replace)
#define PMPI_NO_OP OMPI_PREDEFINED_GLOBAL(PMPI_Op, ompi_mpi_op_no_op)

/* C datatypes */
#define PMPI_DATATYPE_NULL OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_datatype_null)
#define PMPI_BYTE OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_byte)
#define PMPI_PACKED OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_packed)
#define PMPI_CHAR OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_char)
#define PMPI_SHORT OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_short)
#define PMPI_INT OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_int)
#define PMPI_LONG OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_long)
#define PMPI_FLOAT OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_float)
#define PMPI_DOUBLE OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_double)
#define PMPI_LONG_DOUBLE OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_long_double)
#define PMPI_UNSIGNED_CHAR OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_unsigned_char)
#define PMPI_SIGNED_CHAR OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_signed_char)
#define PMPI_UNSIGNED_SHORT OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_unsigned_short)
#define PMPI_UNSIGNED_LONG OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_unsigned_long)
#define PMPI_UNSIGNED OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_unsigned)
#define PMPI_FLOAT_INT OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_float_int)
#define PMPI_DOUBLE_INT OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_double_int)
#define PMPI_LONG_DOUBLE_INT OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_longdbl_int)
#define PMPI_LONG_INT OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_long_int)
#define PMPI_SHORT_INT OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_short_int)
#define PMPI_2INT OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_2int)

#define PMPI_WCHAR OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_wchar)
#if OPAL_HAVE_LONG_LONG
#define PMPI_LONG_LONG_INT OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_long_long_int)
#define PMPI_LONG_LONG OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_long_long_int)
#define PMPI_UNSIGNED_LONG_LONG OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_unsigned_long_long)
#endif  /* OPAL_HAVE_LONG_LONG */
#define PMPI_2COMPLEX OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_2cplex)
#define PMPI_2DOUBLE_COMPLEX OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_2dblcplex)

/* Fortran datatype bindings */
#define PMPI_CHARACTER OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_character)
#define PMPI_LOGICAL OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_logical)
#if OMPI_HAVE_FORTRAN_LOGICAL1
#define PMPI_LOGICAL1 OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_logical1)
#endif
#if OMPI_HAVE_FORTRAN_LOGICAL2
#define PMPI_LOGICAL2 OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_logical2)
#endif
#if OMPI_HAVE_FORTRAN_LOGICAL4
#define PMPI_LOGICAL4 OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_logical4)
#endif
#if OMPI_HAVE_FORTRAN_LOGICAL8
#define PMPI_LOGICAL8 OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_logical8)
#endif
#define PMPI_INTEGER OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_integer)
#if OMPI_HAVE_FORTRAN_INTEGER1
#define PMPI_INTEGER1 OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_integer1)
#endif
#if OMPI_HAVE_FORTRAN_INTEGER2
#define PMPI_INTEGER2 OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_integer2)
#endif
#if OMPI_HAVE_FORTRAN_INTEGER4
#define PMPI_INTEGER4 OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_integer4)
#endif
#if OMPI_HAVE_FORTRAN_INTEGER8
#define PMPI_INTEGER8 OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_integer8)
#endif
#if OMPI_HAVE_FORTRAN_INTEGER16
#define PMPI_INTEGER16 OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_integer16)
#endif
#define PMPI_REAL OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_real)
#if OMPI_HAVE_FORTRAN_REAL4
#define PMPI_REAL4 OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_real4)
#endif
#if OMPI_HAVE_FORTRAN_REAL8
#define PMPI_REAL8 OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_real8)
#endif
#if OMPI_HAVE_FORTRAN_REAL16
#define PMPI_REAL16 OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_real16)
#endif
#define PMPI_DOUBLE_PRECISION OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_dblprec)
#define PMPI_COMPLEX OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_cplex)
#if OMPI_HAVE_FORTRAN_REAL4
#define PMPI_COMPLEX8 OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_complex8)
#endif
#if OMPI_HAVE_FORTRAN_REAL8
#define PMPI_COMPLEX16 OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_complex16)
#endif
#if OMPI_HAVE_FORTRAN_REAL16
#define PMPI_COMPLEX32 OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_complex32)
#endif
#define PMPI_DOUBLE_COMPLEX OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_dblcplex)
#define PMPI_2REAL OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_2real)
#define PMPI_2DOUBLE_PRECISION OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_2dblprec)
#define PMPI_2INTEGER OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_2integer)

/* New datatypes from the MPI 2.2 standard */
#define PMPI_INT8_T                OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_int8_t)
#define PMPI_UINT8_T               OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_uint8_t)
#define PMPI_INT16_T               OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_int16_t)
#define PMPI_UINT16_T              OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_uint16_t)
#define PMPI_INT32_T               OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_int32_t)
#define PMPI_UINT32_T              OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_uint32_t)
#define PMPI_INT64_T               OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_int64_t)
#define PMPI_UINT64_T              OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_uint64_t)
#define PMPI_AINT                  OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_aint)
#define PMPI_OFFSET                OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_offset)
#define PMPI_C_BOOL                OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_c_bool)
#if HAVE_FLOAT__COMPLEX
#define PMPI_C_COMPLEX             OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_c_float_complex)
#define PMPI_C_FLOAT_COMPLEX       OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_c_float_complex)
#endif
#if HAVE_DOUBLE__COMPLEX
#define PMPI_C_DOUBLE_COMPLEX      OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_c_double_complex)
#endif
#if HAVE_LONG_DOUBLE__COMPLEX
#define PMPI_C_LONG_DOUBLE_COMPLEX OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_c_long_double_complex)
#endif
#define PMPI_CXX_BOOL              OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_cxx_bool)
#define PMPI_CXX_COMPLEX           OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_cxx_cplex)
#define PMPI_CXX_FLOAT_COMPLEX     OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_cxx_cplex)
#define PMPI_CXX_DOUBLE_COMPLEX    OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_cxx_dblcplex)
#define PMPI_CXX_LONG_DOUBLE_COMPLEX OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_cxx_ldblcplex)

/* New datatypes from the 3.0 standard */
#define PMPI_COUNT                 OMPI_PREDEFINED_GLOBAL(PMPI_Datatype, ompi_mpi_count)

#define PMPI_ERRORS_ARE_FATAL OMPI_PREDEFINED_GLOBAL(PMPI_Errhandler, ompi_mpi_errors_are_fatal)
#define PMPI_ERRORS_RETURN OMPI_PREDEFINED_GLOBAL(PMPI_Errhandler, ompi_mpi_errors_return)

/* Typeclass definition for PMPI_Type_match_size */
#define PMPI_TYPECLASS_INTEGER    1
#define PMPI_TYPECLASS_REAL       2
#define PMPI_TYPECLASS_COMPLEX    3

/* Aint helper macros (MPI-3.1) */
#define PMPI_Aint_add(base, disp) ((PMPI_Aint) ((char *) (base) + (disp)))
#define PMPI_Aint_diff(addr1, addr2) ((PMPI_Aint) ((char *) (addr1) - (char *) (addr2)))

#include "pmpi_proto.h"

#if defined(c_plusplus) || defined(__cplusplus)
}
#endif

#endif /* PMPI_INCLUDED */

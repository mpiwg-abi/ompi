.. _mpi_keyval_free:


MPI_Keyval_free
===============

.. include_body

:ref:`MPI_Keyval_free` - Frees attribute key for communicator cache
attribute -- use of this routine is deprecated.


SYNTAX
------


C Syntax
^^^^^^^^

.. code-block:: c

   #include <mpi.h>

   int MPI_Keyval_free(int *keyval)


Fortran Syntax
^^^^^^^^^^^^^^

.. code-block:: fortran

   INCLUDE 'mpif.h'
   MPI_KEYVAL_FREE(KEYVAL, IERROR)
   	INTEGER	KEYVAL, IERROR


INPUT PARAMETER
---------------
* ``keyval``: Frees the integer key value (integer).

OUTPUT PARAMETER
----------------
* ``IERROR``: Fortran only: Error status (integer).

DESCRIPTION
-----------

Note that use of this routine is *deprecated* as of MPI-2. Please use
:ref:`MPI_Comm_free_keyval` instead.

Frees an extant attribute key. This function sets the value of keyval to
MPI_KEYVAL_INVALID. Note that it is not erroneous to free an attribute
key that is in use, because the actual free does not transpire until
after all references (in other communicators on the process) to the key
have been freed. These references need to be explicitly freed by the
program, either via calls to :ref:`MPI_Attr_delete` that free one attribute
instance, or by calls to :ref:`MPI_Comm_free` that free all attribute instances
associated with the freed communicator.


NOTE
----

Key values are global (they can be used with any and all communicators).


ERRORS
------

.. include:: ./ERRORS.rst

.. seealso::
   :ref:`MPI_Keyval_create` :ref:`MPI_Comm_free_keyval`

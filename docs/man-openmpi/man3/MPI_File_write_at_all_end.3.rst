.. _mpi_file_write_at_all_end:


MPI_File_write_at_all_end
=========================

.. include_body

:ref:`MPI_File_write_at_all_end` - Writes a file at explicitly specified
offsets; ending part of a split collective routine (blocking).


SYNTAX
------



C Syntax
^^^^^^^^

.. code-block:: c

   #include <mpi.h>

   int MPI_File_write_at_all_end(MPI_File fh, const void *buf,
   	MPI_Status *status)


Fortran Syntax
^^^^^^^^^^^^^^

.. code-block:: fortran

   USE MPI
   ! or the older form: INCLUDE 'mpif.h'
   MPI_FILE_WRITE_AT_ALL_END(FH, BUF, STATUS, IERROR)
   	<type>	BUF(*)
   	INTEGER	FH, STATUS(MPI_STATUS_SIZE), IERROR


Fortran 2008 Syntax
^^^^^^^^^^^^^^^^^^^

.. code-block:: fortran

   USE mpi_f08
   MPI_File_write_at_all_end(fh, buf, status, ierror)
   	TYPE(MPI_File), INTENT(IN) :: fh
   	TYPE(*), DIMENSION(..), INTENT(IN), ASYNCHRONOUS :: buf
   	TYPE(MPI_Status) :: status
   	INTEGER, OPTIONAL, INTENT(OUT) :: ierror


INPUT/OUTPUT PARAMETER
----------------------
* ``fh``: File handle (handle).

INPUT PARAMETER
---------------
* ``buf``: Initial address of buffer (choice).

OUTPUT PARAMETERS
-----------------
* ``status``: Status object (status).
* ``IERROR``: Fortran only: Error status (integer).

DESCRIPTION
-----------

:ref:`MPI_File_write_at_all_end` is the ending part of a split collective
routine that stores the number of elements actually written into the
file associated with *fh* in *status.* The data is written into those
parts of the file specified by the current view. All other fields of
*status* are undefined.


NOTES
-----

All the nonblocking collective routines for data access are "split" into
two routines, each with \_begin or \_end as a suffix. These split
collective routines are subject to the semantic rules described in
Section 9.4.5 of the MPI-2 standard.


ERRORS
------

.. include:: ./ERRORS.rst

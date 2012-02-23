Klatch - a DICT client for KDE
==============================

Introduction
------------

Dependencies
------------

Building
--------

To compile and install Klatch, run these commands in its source tree::

  mkdir build
  cd build
  cmake ..
  make
  sudo make install

If this fails because of missing C++11 support, you need to use a newer
compiler. For example, on Debian g++ from the gcc-snapshot package can
be used by adding the following option to the CMake invocation::

  -DCMAKE_CXX_COMPILER=/usr/lib/gcc-snapshot/bin/g++

Download
--------

You can download Klatch in either `tar.gz`_ or `zip`_ formats.

.. _tar.gz: http://github.com/fthomas/klatch/tarball/master
.. _zip:    http://github.com/fthomas/klatch/zipball/master

The version control system used for development of Klatch is Git. The
`Git repository`_ can be inspected and browsed online at `GitHub`_ and
it can be cloned by running::

  git clone git://github.com/fthomas/klatch.git

.. _Git repository: http://github.com/fthomas/klatch
.. _GitHub: http://github.com/

Issues and feedback
-------------------

For bug reports, feature requests, or general feedback either use the
`issue tracker`_ or `write me an email`_.

.. _issue tracker: http://github.com/fthomas/klatch/issues
.. _write me an email: frank@timepit.eu

License
-------

Klatch is `free software`_ and licensed under the `GPLv3`_ or any later
version. The full text of the license can be found in the file
``COPYING`` in Klatch's source tree.

.. _free software: http://www.gnu.org/philosophy/free-sw.html
.. _GPLv3: http://www.gnu.org/licenses/gpl-3.0.html

Author
------

Klatch was written by Frank S. Thomas <frank@timepit.eu>

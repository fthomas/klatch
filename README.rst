Klatch - a DICT client for KDE
==============================

Introduction
------------

Klatch is a KDE client for the Dictionary Server Protocol (`DICT`_).
It can query multiple DICT servers simultaneously and has a simple user
interface for querying words and displaying their definitions. It also
features a scripting interface for processing definitions via
`QtScript`_ which is based on the ECMAScript standard. This allows, for
example, to append selected definitions to an external vocabulary
collections, like `kvtml`_ files.

.. _DICT: https://en.wikipedia.org/wiki/DICT
.. _QtScript: https://en.wikipedia.org/wiki/QtScript
.. _kvtml: http://edu.kde.org/contrib/kvtml.php

Packages
--------

Source and (amd64) binary packages for Debian are available in my
`personal package archive`_. Packages for other distributions are not
available yet.

.. _personal package archive: http://timepit.eu/~frank/wiki/debian/#ppa

Download
--------

The latest Klatch source code can be downloaded as `tar.gz`_ or `zip`_
archives.

.. _tar.gz: http://github.com/fthomas/klatch/tarball/master
.. _zip:    http://github.com/fthomas/klatch/zipball/master

The version control system used for development of Klatch is Git. The
`Git repository`_ can be inspected and browsed online at `GitHub`_ and
it can be cloned by running::

  git clone git://github.com/fthomas/klatch.git

.. _Git repository: http://github.com/fthomas/klatch
.. _GitHub: http://github.com/

Dependencies
------------

Klatch is a KDE program written in C++. To build it, a C++ compiler
with `C++11`_ support, the `KDE`_ and `Qt`_ libraries, and `CMake`_ are
required.

.. _C++11: https://en.wikipedia.org/wiki/C++11
.. _KDE: http://kde.org/
.. _Qt: http://qt-project.org/
.. _CMake: http://www.cmake.org/

Building
--------

To compile and install Klatch, run these commands in its source tree::

  mkdir build
  cd build
  cmake ..
  make
  sudo make install

If this fails because of missing C++11 support, you need to use a newer
compiler. For example, on Debian ``g++`` from the gcc-snapshot package
can be used by adding the following option to the CMake invocation::

  -DCMAKE_CXX_COMPILER=/usr/lib/gcc-snapshot/bin/g++

Issues and feedback
-------------------

For bug reports, feature requests, or general feedback either use the
`issue tracker`_ or `write me an email`_.

.. _issue tracker: http://github.com/fthomas/klatch/issues
.. _write me an email: frank@timepit.eu

Localizing
----------

If you would like to help translating Klatch, you can use `Transifex`_
to create or update translations of the `klatch.pot`_ file into your
language.

.. _Transifex: https://www.transifex.net/projects/p/klatch/
.. _klatch.pot: https://www.transifex.net/projects/p/klatch/resource/pot/

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

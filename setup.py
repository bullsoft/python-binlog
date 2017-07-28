#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vi:ts=4:et

""""""

PACKAGE = "binlog"
VERSION = "0.6.4"

import os, sys, re, glob
import distutils
from distutils.core import setup
from distutils.extension import Extension

py3 = sys.version_info[0] == 3

try:
    # python 2
    exception_base = StandardError
except NameError:
    # python 3
    exception_base = Exception

class ConfigurationError(exception_base):
    pass

def fail(msg):
    sys.stderr.write(msg + "\n")
    exit(10)

def get_data_files():
    # a list of tuples with (path to install to, a list of local files)
    data_files = []
    if sys.platform == "win32":
        datadir = os.path.join("doc", PACKAGE)
    else:
        datadir = os.path.join("share", "doc", PACKAGE)
    #
    files = ["AUTHORS", "ChangeLog", "LICENSE"]
    if files:
        data_files.append((os.path.join(datadir), files))
    files = glob.glob(os.path.join("examples", "*.py"))
    if files:
        data_files.append((os.path.join(datadir, "examples"), files))
    #
    assert data_files
    for install_dir, files in data_files:
        assert files
        for f in files:
            assert os.path.isfile(f), (f, install_dir)
    return data_files

def scan_argv(argv, s, default=None):
    p = default
    i = 1
    while i < len(argv):
        arg = argv[i]
        if str.find(arg, s) == 0:
            if s.endswith('='):
                # --option=value
                p = arg[len(s):]
            else:
                # --option
                # set value to True
                p = True
            del argv[i]
        else:
            i = i + 1
    # print(argv)
    return p


class ExtensionConfiguration(object):
    def __init__(self, argv=[]):
        self.argv = argv
        self.original_argv = argv[:]

def get_extension(argv):
    sources = [
        os.path.join("src", "pybinlog.cpp"),
        os.path.join("src", "docstring.cpp"),
        os.path.join("src", "binlog.cpp"),
    ]
    depends = [
        os.path.join("src", "pybinlog.h"),
        os.path.join("src", "docstring.h"),
    ]
    ext_config = ExtensionConfiguration(argv)
    ext = Extension(
        name=PACKAGE,
        sources=sources,
        depends=depends,
    )
    # print(ext.__dict__); sys.exit(1)
    return ext

setup_args = dict(
    name=PACKAGE,
    version=VERSION,
    description='binlog -- A Python Interface To Mysql binlog',
    long_description='''\
binlog -- A Python Interface To Mysql binlog
============================================

Requirements
------------

- Python 2.6, 2.7 or 3.1 through 3.6.
- mysql-binlog-events 1.0.2 or higher

''',
    author="ideal",
    author_email="idealities@gmail.com",
    maintainer="Yuanchun Shang",
    maintainer_email="idealities@gmail.com",
    url="https://github.com/bullsoft/python-binlog",
    license="GPLv3",
    keywords=['mysql', 'binlog'],
    classifiers=[
        'Development Status :: 5 - Production/Stable',
        'Environment :: Web Environment',
        'Intended Audience :: Developers',
        'Operating System :: POSIX',
        'Programming Language :: Python :: 2',
        'Programming Language :: Python :: 2.6',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.2',
        'Programming Language :: Python :: 3.3',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
    ],
)

if __name__ == "__main__":
    setup_args['data_files'] = get_data_files()
    ext = get_extension(sys.argv)
    setup_args['ext_modules'] = [ext]

    for o in ext.extra_objects:
        assert os.path.isfile(o), o
    setup(**setup_args)

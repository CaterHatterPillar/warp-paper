#!/bin/python

import os
import sys
import shutil
import subprocess

subprocess.call(["gnuplot", "msswarp.gnuplot"])

os.chdir('tex/')

subprocess.call("pdflatex -shell-escape GAME_HARD_01.tex", shell=True)

subprocess.call(["bibtex", "web.aux"])
subprocess.call(["bibtex", "GAME_HARD_01.aux"])

subprocess.call("pdflatex -shell-escape GAME_HARD_01.tex", shell=True)
subprocess.call("pdflatex -shell-escape GAME_HARD_01.tex", shell=True)

shutil.copyfile("GAME_HARD_01.pdf", "../GAME_HARD_01.pdf")
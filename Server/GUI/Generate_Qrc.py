# to generate bg_rc.py from bg.qrc
import os

os.system('pyrcc5 bg.qrc -o bg_rc.py')
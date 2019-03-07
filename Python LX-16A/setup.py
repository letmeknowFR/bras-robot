from setuptools import setup

setup(
    name='lewansoul_lx16a',
    version='0.1',
    description='Driver pour controler LewanSoul LX-16A servos',
    author='Khelaf HAMICI',
    author_email='khelaf.hamici@letmeknow.fr',
    url='https://github.com/letmeknowFR/',
    py_modules=['lewansoul_lx16a'],
    license='MIT',
    install_requires=['pyserial'],
)

#!usr/bin/python

from optparse import OptionParser





if __name__ == "__main__":
	usage='usage: deuterium options* command parameter*'
	version='Deuterium Version '

	optionparser = OptionParser(usage=usage, version=version)
	optionparser.add_option('-p', '--processor', dest='processor')
	optionparser.add_option('-s', '--selection', dest='selection')
	optionparser.add_option('', '--test', dest='istest', action='store_true', default=False)
	optionparser.add_option('', '--force', dest='isforced', action='store_true', default=False)



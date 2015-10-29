import sys
import windrosebin
for x in sys.argv:
    print x
print type(sys.argv)
windrosebin.allocate()
windrosebin.check(sys.argv[1],sys.argv[2],len(sys.argv))
windrosebin.calc(sys.argv[1],sys.argv[3],len(sys.argv))
windrosebin.printLines()
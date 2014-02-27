import subprocess
args = [str(i) for i in xrange(1,10000)]
command = ['./ex10'] + args
subprocess.call(command)

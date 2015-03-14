import numpy as np
import sys
import getopt
import math
def main():
  try:
    opts, args = getopt.getopt(sys.argv[1:],"m:v:o:",["--mean=","--var=","--output"])
  except:
    sys.exit(2)
  for opt, arg in opts:
    if(opt in ("-m","--mean")):
      m=float(arg)
    elif(opt in ("-v","--var")):
      v=float(arg)
    elif(opt in ("-o","--output")):
      of=arg

  print m,v
  low=int(m-math.sqrt(v))
  high=int(m+math.sqrt(v))
  print "mean: ", (high-low)/2
  print "var: ", (high-low)*(high-low)/12

  with open(of,"w") as f:
    for i in xrange(0,10000):
      f.write("{} {}\n".format(np.random.randint(low,high),np.random.randint(low,high)))

      
if __name__=="__main__":
  main()

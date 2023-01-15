import os, signal, shlex, subprocess, time, json

class TextColors:
    """
    Colors for use in print.
    """
    GREEN = "\033[0;32m"
    RED = "\033[0;31m"
    END = "\033[0m"


prog_arglist = ["thread3"]
total_score = 0
points = {}
expected = {}
thread_count = {}
prog_result = {}
clone_good = {}
result_good = {}

expected["thread3"] = "999000"
thread_count["thread3"] = 4



if not os.path.exists("output"):
  os.makedirs("output")
## check the fork programs
for prog in prog_arglist:
  output = "Testing {}...".format(prog)
  out = "./output/" + prog +".stdout"
  outfd = open(out,'w+')
  outerr = "./output/" + prog +".stderr"
  errfd = open(outerr,'w+')
  cmd = "timeout 20s ./" + prog
  args = shlex.split(cmd)
  proc = subprocess.Popen(args, stdout=outfd, stderr=errfd, shell=False) 
  proc.wait()
  outfd.seek(0)
  out_content = outfd.read().splitlines()
  result = []
  thread_pids = []
  done_pids = []
  results = []
  tcount = 0
  dcount = 0
  for line in out_content:
    if line.find("tid") != -1:
      pid = line.split(" ")[-1]
      thread_pids.append(pid)
      tcount = tcount + 1
    elif line.find("done") != -1:
      done_pid = line.split(" ")[0]
      done_pids.append(pid)
      dcount = dcount + 1
    elif line.find("result") != -1:
        results.append(line.split(" ")[-1])

  if ((thread_pids.sort() == done_pids.sort()) and (dcount == tcount) and (dcount == int(thread_count[prog]))):
    clone_good[prog] = True
  else:
    clone_good[prog] = False
  
  exp_result = [expected[prog]]

  if (exp_result == results):
    result_good[prog] = True
  else:
    result_good[prog] = False
  
  if clone_good[prog] and result_good[prog]:
    result = TextColors.GREEN + "Pass"+ TextColors.END
    points[prog] = 100
  else:
    result = TextColors.RED + "Fail" + TextColors.END
    points[prog] = 0

 
  total_score += points[prog]
  print("%-20s %45s (%d/%d)\n" %( output, result, points[prog], 100))

  outfd.close()
  errfd.close()

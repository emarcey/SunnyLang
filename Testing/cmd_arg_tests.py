import os

exe_path = r'C:\Users\evan.marcey\eclipse-workspace\Sunny'

os.chdir(exe_path)

def execute_test(test):
    cmd = 'Debug\Sunny.exe {a}'.format(a=' '.join(test['args']))
    res = os.system(cmd)
    return res==test['result']

tests = [
    {'args':[''],'result':1},
    {'args':['test.st','test.st'],'result':1},
    {'args':['cmds.csv'],'result':1},
    {'args':['test.st'],'result':0},
    {'args':['test1.st'],'result':1}
    ]

ct = 0

for test in tests:
    ct+=1
    print("Test {x}:\t{r}".format(x=ct,r=execute_test(test)))

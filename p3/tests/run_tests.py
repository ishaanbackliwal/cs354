import os
from datetime import datetime

def out_msg():
    curr = datetime.now()
    msg = "             ---> Test PASSED | {}".format(curr)
    return msg


print("Running test_align1 ...")
if os.system("./test_align1") == 0:
    print(out_msg())

print("Running test_align2 ...")
if os.system("./test_align2") == 0:
    print(out_msg())

print("Running test_align3 ...")
if os.system("./test_align3") == 0:
    print(out_msg())

print("Running test_alloc1 ...")
if os.system("./test_alloc1") == 0:
    print(out_msg())

print("Running test_alloc2 ...")
if os.system("./test_alloc2") == 0:
    print(out_msg())

print("Running test_alloc3 ...")
if os.system("./test_alloc3") == 0:
    print(out_msg())

print("Running test_alloc1_nospace ...")
if os.system("./test_alloc1_nospace") == 0:
    print(out_msg())

print("Running test_alloc2_nospace ...")
if os.system("./test_alloc2_nospace") == 0:
    print(out_msg())

print("Running test_coalesce1 ...")
if os.system("./test_coalesce1") == 0:
    print(out_msg())

print("Running test_coalesce2 ...")
if os.system("./test_coalesce2") == 0:
    print(out_msg())

print("Running test_coalesce3 ...")
if os.system("./test_coalesce3") == 0:
    print(out_msg())

print("Running test_coalesce4 ...")
if os.system("./test_coalesce4") == 0:
    print(out_msg())

print("Running test_coalesce5 ...")
if os.system("./test_coalesce5") == 0:
    print(out_msg())

print("Running test_coalesce6 ...")
if os.system("./test_coalesce6") == 0:
    print(out_msg())

print("Running test_free1 ...")
if os.system("./test_free1") == 0:
    print(out_msg())

print("Running test_free2 ...")
if os.system("./test_free2") == 0:
    print(out_msg())
    
print("Running test_writeable ...")
if os.system("./test_writeable") == 0:
    print(out_msg())
